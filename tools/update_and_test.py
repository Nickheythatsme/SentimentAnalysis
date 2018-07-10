# Script to pull from github, and rebuild the project.
# The script then posts test results to the commit page on github
import subprocess
import os
import sys
import logging
import requests
import json
import time

# Set up logging
logger = logging.getLogger('update_and_test')

# Get git_authentication for commenting
git_auth = ''

# Build/clean/test commands (defaults)
build_type = "make"

def run_git():
    """ Try to run "git pull." 
    RETURNS TRUE if we've updated, FALSE if nothing has been updated
    RAISIES SubprocessError if there is a problem with git
    """
    command = ["git","pull","origin","master"]
    logger.info('Running "{}"'.format(command))
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    message = result.stdout.decode("utf-8")
    logger.info("git pull returned: " + message)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error('git error: ' + err)
        raise Exception("git error: " + err)
    if "Already up-to-date.\n" == message or "Already up to date.\n" == message:
        logger.info('git repro is already up to date')
        return False
    logger.info('git repro has been updated')
    return True


def build():
    """ Run make clean and then make all to rebuild the repro """
    # Run '{build_type} clean'
    clean_cmd = [build_type,"clean"]
    logger.info('Running "{}"'.format(clean_cmd))
    result = subprocess.run(clean_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error('make clean error: Makefile probably doesn\'t exist. ' + err)
        raise Exception("make error: no makefile found")

    # Run '{build_type} all'
    build_cmd = [build_type,"all"]
    logger.info('Running "{}"'.format(build_cmd))
    result = subprocess.run(build_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error("compilation error: " + err)
        return err # Return make error
    logger.info('project compiled')
    return True


def run_tests():
    test_cmd = [build_type,"test"]
    logger.info('Running "{}"'.format(test_cmd))
    result = subprocess.run(test_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error("Error running tests: " + err)
    message = result.stdout.decode("utf-8")
    logger.info('tests completed:\n' + message)
    return message


def comment_results(test_results):
    command = ["git","log","-n 1"]
    logger.info('Running "{}"'.format(command))
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error('git error: ' + err)
        raise Exception("git error: " + err)

    # Get the most recent sha code
    message = result.stdout.decode("utf-8")
    recent_sha = message.split('\n')[0].split(' ')[1]

    logger.info("Making POST request...")
    # Make the POST request with the test results
    rdata = {"body":test_results}
    r = requests.post('https://api.github.com/repos/nickheythatsme/sentimentanalysis/commits/'+recent_sha+'/comments', \
            auth=(git_auth), data=json.dumps(rdata))
    logger.info("POST request returned status code: " + str(r.status_code))
    return r.status_code

def run_update_test():
    build_results = build()
    if build_results != True:
        comment_results(build_results)
    else: 
        test_results = run_tests()
        comment_results(test_results)


def cycle():
    try:
        if run_git():
            run_update_test()
    except Exception as e:
        logging.error("Exception occurred during cycle: " + str(e))


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: update_and_test [github-username:github-password] [make/ninja]")
        sys.exit(1)
    git_auth = (sys.argv[1].split(':')[0], sys.argv[1].split(':')[1])
    build_type = sys.argv[2]
    logging.basicConfig(level=logging.DEBUG)
    logger.setLevel(logging.INFO)

    # Start loop
    run_git()
    run_update_test()
    while(1):
        cycle()
        time.sleep(30)
