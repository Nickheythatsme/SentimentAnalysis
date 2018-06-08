import os
import requests
import sys
import tarfile

data_package_url = "http://ai.stanford.edu/~amaas/data/sentiment/aclImdb_v1.tar.gz"
file_name = "aclImdb_v1.tar.gz"

#Check to see if we already have the data
def check_data(path):
    if not os.path.exists(path):
        return False
    return True


#Get the package for the data (Given in a tar.gz)
def get_data_package(url):
    try:
        r = requests.get(url)
    except requests.ConnectionError:
        print("Error: Connection Error")
        return False
    except TimeoutError:
        print("Error: Timeout")
        return False
    except Exception as err:
        print("Error: Uknown error")
        print( str(err) )
        return False
    return r


#Write the tar.gz file to the data folder
def write_package(file_out, package):
    try:
        fout = open(file_out,'wb')
    except FileNotFoundError:
        print("Error: Directory not found")
        return False
    except Exception as err:
        print("Error: Unknown error")
        print( str(err) )
        return False
    fout.write(package)
    fout.close()
    return True


#Unzip the tarball into our data directory
def unzip_tar(file_location, extract_location):
    try:
        tarball = tarfile.open(file_location, 'r:*')
    except FileNotFoundError:
        print("Error: File not found")
        return False
    except tarfile.ReadError:
        print("Error: Error reading tarball")
        return False
    except Exception as err:
        print("Error: Uknown error")
        print( str(err) )
        return False
    result = True
    try:
        tarball.extractall(extract_location)
    except KeyboardInterrupt:
        print("Keyboard interrupt. Stopping extraction")
        result = False
    except Exception as e:
        print("Uknown error" + str(e))
        return False
    tarball.close()
    return result


def main():
    if len(sys.argv) < 2:
        data_dir = "./data/"
    else:
        data_dir = sys.argv[1]

    tar_file_location = data_dir + file_name
    if os.path.exists(data_dir + 'aclImdb'):
        print("Data already exists.")
        sys.exit(0)

    os.makedirs(data_dir, exist_ok="True")
    print("Data does not exist. Downloading and unzipping data")

    #Download the tar.gz file
    print("Downloading data from {}".format(data_package_url))
    package = get_data_package(data_package_url)
    if not package:
        print("Error getting package")
        sys.exit(1)

    #Write the tar.gz file
    print("Writing package to {}".format(tar_file_location))
    if not write_package(tar_file_location, package.content):
        print("Error writing package")
        sys.exit(1)

    #Unzip the file into our directory
    print("Unzipping data to {}".format(data_dir))
    if not unzip_tar(tar_file_location, data_dir):
        print("Error unzipping package")
        sys.exit(1)

    print("Removing old tar.gz file")
    os.remove(tar_file_location)
    return

main()
