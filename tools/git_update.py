import subprocess
import os
import sys
import logging

logger = logging.getLogger('update_and_test')
logger.setLevel(logging.DEBUG)

def run_git():
    """ Try to run "git pull." 
    RETURNS TRUE if we've updated, FALSE if nothing has been updated
    RAISIES SubprocessError if there is a problem with git
    """
    command = ["git","pull","origin","master"]
    logger.info('Running "{}"'.format(command))
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error('git error: ' + err)
        raise Exception("git error: " + err)
    if result.stdout.decode("utf-8") == "Already up to date.\n":
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
    print(result)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        logger.error("Error running tests: " + err)
        raise Exception("testing error: " + err)
    message = result.stdout.decode("utf-8")
    logger.info('tests completed:\n',message)
    return message


def main():
    try:
        if run_git():
            run_make()
            run_tests()
    except Exception as e:
        logging.error("Exception occurred during cycle: " + e)


if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    logger.setLevel(logging.INFO)
    logger.info('test')
    main()

