import sys
from sys import argv
from itertools import permutations
import crypt


def main():
    # Check in one argument submitted in CLI
    if len(argv) != 2:
        print("usage: python crack.py hashed_password")
        sys.exit(1)

    # Getting the salt from the hashed password
    hashed_password = argv[1]
    salt = hashed_password[:2]

    # Trying every guess possible from 1 letter to 5 letters
    letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for i in range(5):
        for guess in permutations(letters, i):
            tentative_password = "".join(guess)
            if crypt.crypt(tentative_password, salt) == hashed_password:
                print(tentative_password)
                sys.exit(0)
    print("password not found")


if __name__ == "__main__":
    main()
