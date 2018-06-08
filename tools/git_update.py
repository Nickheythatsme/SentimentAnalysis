import subprocess
import os
import sys

def run_git(path):
    """ Try to run "git pull." 
    RETURNS TRUE if we've updated, FALSE if nothing has been updated
    RAISIES SubprocessError if there is a problem with git
    """
    result = subprocess.run(["git","pull"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        err = result.stderr.decode("utf-8")
        print("Error: ", err, end='')
        raise Exception("git error: " + err)
    if result.stdout.decode("utf-8") == "Already up to date.\n":
        return False
    return True

def main():
    print(run_git('.'))

main()

