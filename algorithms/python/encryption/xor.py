#!/usr/bin/env python

"""An implementation of XOR encryption for shifting the binary digits of text.
"""

import re
import sys
from argparse import ArgumentParser

# Type Constants
FLOAT = "\d*\.\d+"
INTEGER = "\d+"

IS_TTY = sys.stdin.isatty()


def get_key(source: str) -> int:
    """Converts a string key representing integers or floats to a key in
    Binary.

    :param source: the string representation
    :type source: str
    :return: the key in Binary
    :rtype: int
    """

    if re.match(FLOAT, xor_args.key):
        return int(float(xor_args.key) // 1)
    elif re.match(INTEGER, xor_args.key):
        return int(xor_args.key)
    else:
        return None


def encrypt(data: str, key: int) -> str:
    """A generator that encrypts data using the key provided.

    :param data: the data to encrypt
    :type data: str
    :param key: the key to encrypt the data using
    :type key: int
    """

    for char in data:
        # Preserve new-lines in text.
        if char == "\n":
            yield "\n"
        else:
            yield f"{chr(ord(char) ^ key)}"


def decrypt(data: str, key: int) -> str:
    """A generator that decrypts data using the key provided.

    :param data: the data to decrypt
    :type data: str
    :param key: the key to decrypt the data using
    :type key: int
    """

    for char in data:
        if char == "\n":
            yield "\n"
        else:
            yield f"{chr(ord(char) ^ key)}"


if __name__ == "__main__":
    xor_parser = ArgumentParser(description="""An encryption algorithm that uses
                                XOR (a bitwise operator) to encrypt or decrypt
                                text.""")
    xor_parser.add_argument("action", help="the action to take")
    xor_parser.add_argument("key", help="the key to decrpyt and encrypt with")
    xor_args = xor_parser.parse_args()

    if re.match(FLOAT, xor_args.key):
        print("Warning: Leading decimal places of key are trimmed.")

    key = get_key(xor_args.key)

    if key is None:
        print("Key must be an integer.")
        sys.exit(1)

    data = sys.stdin.read()

    if xor_args.action.lower() == "encrypt":
        print("".join(encrypt(data, key)), end="")
    elif xor_args.action.lower() == "decrypt":
        print("".join(decrypt(data, key)), end="")
    else:
        print(f"{xor_args.action} is not an action.")
