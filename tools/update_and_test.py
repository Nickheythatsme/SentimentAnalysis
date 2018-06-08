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

def run_git():
    """ Try to run "git pull." 
    RETURNS TRUE if we've updated, FALSE if nothing has been updated
    RAISIES SubprocessError if there is a problem with git
    """
    command = ["git","pull","origin","master"]
    logger.info('Running "{}"'.format(command))
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    logger.info("git pull returned: " + str(result.returncode))
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error('git error: ' + err)
        raise Exception("git error: " + err)
    if "Already up-to-date" or "Already up to date" in result.stdout.decode("utf-8") :
        logger.info('git repro is already up to date')
        return False
    logger.info('git repro has been updated')
    return True


def run_make():
    """ Run make clean and then make all to rebuild the repro """
    # Run 'make clean'
    make_clean = ["make","clean"]
    logger.info('Running "{}"'.format(make_clean))
    result = subprocess.run(make_clean, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error('make clean error: Makefile probably doesn\'t exist. ' + err)
        raise Exception("make error: no makefile found")

    # Run 'make all'
    make_all = ["make","all"]
    logger.info('Running "{}"'.format(make_all))
    result = subprocess.run(make_all, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error("compilation error: " + err)
        raise Exception("compilation error: " + err)
    logger.info('project compiled')
    return True

def run_tests():
    make_test = ["make","test"]
    logger.info('Running "{}"'.format(make_test))
    result = subprocess.run(make_test, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error("Error running tests: " + err)
    message = result.stdout.decode("utf-8")
    logger.info('tests completed:\n' + message)
    return message

def comment_results(test_results):
    command = ["git","show-ref"]
    logger.info('Running "{}"'.format(command))
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error('git error: ' + err)
        raise Exception("git error: " + err)
    # Get the most recent sha code
    message = result.stdout.decode("utf-8")
    recent_sha = message.split('\n')[0].split(' ')[0]

    # Make the POST request with the test results
    rdata = {"body":test_results}
    r = requests.post('https://api.github.com/repos/nickheythatsme/sentimentanalysis/commits/'+recent_sha+'/comments', auth=git_auth, data=json.dumps(rdata))
    print(r.status_code)
    return r.status_code


def cycle():
    try:
        if run_git():
            run_make()
            test_results = run_tests()
            comment_results(test_results)
    except Exception as e:
        logging.error("Exception occurred during cycle: " + e)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: update_and_test [github username:githubpassword]")
        sys.exit(1)
    logging.basicConfig(level=logging.DEBUG)
    logger.setLevel(logging.INFO)
    git_auth = sys.argv[1]
    while(1):
        cycle()
        time.sleep(10)

