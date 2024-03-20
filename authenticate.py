# User Authentication script

#need to use fernet
#need to recieve data from main.cpp, validate input data against known userbase, then send back either true or false (maybe 1 or 0)
#need to get fernet stuff from my desktop onto the cloud first

#imports
import sys
from cryptography.fernet import Fernet

def create_key():
    key = Fernet.generate_key()
    with open("key.key","wb") as f:
        f.write(key)

def load_key():
    with open("key.key", "rb") as f:
        return f.read()

def main():
    pass





if __name__ == "__main__":
    main()
