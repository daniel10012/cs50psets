from sys import argv
import cs50
import sys


# Main function
def main():
    # Make sure one argument is entered
    k = argv[1]
    if len(argv) != 2:
        print("Usage: python vigenere.py k")
        sys.exit(1)
    # Make sure the argument is a positive integer
    if not k.isalpha():
        print("please enter a text key")
        sys.exit(1)
    # Get the text input from the user
    key = [ord(letter.lower()) - ord('a') for letter in k]
    plaintext = input("plaintext: ")
    ciphertext = ""
    n = 0
    for letter in plaintext:

        index = key[n % len(key)]
        if ord(letter) >= 97 and ord(letter) <= 122:
            ref = 'a'
        elif ord(letter) >= 65 and ord(letter) <= 90:
            ref = 'A'
        if (ord(letter) >= 65 and ord(letter) <= 90) or (ord(letter) >= 97 and ord(letter) <= 122):
            ciphertext += chr(((ord(letter) - ord(ref) + index) % 26) + ord(ref))
        else:
            ciphertext += letter
        if letter.isalpha():
            print(letter)
            n += 1
    print(f"ciphertext: {ciphertext}")
    sys.exit(0)

# Run the main function
if __name__ == "__main__":
    main()
