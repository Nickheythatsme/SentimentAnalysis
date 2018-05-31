import os
import sys
import time
import subprocess
import logging

logger = logging.getLogger('update/tester')

def run_update(path):
    proc = subprocess.run(['git','pull'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if proc.returncode is not 0:
        proc_output = proc.stderr.decode("utf-8")
        logger.error("Error updating git: " + proc_output)
        return -1;
    proc_output = proc.stdout.decode("utf-8")
    logger.info("updated project")

def main():
    run_update('.')
    
main()
