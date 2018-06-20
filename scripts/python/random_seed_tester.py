#!/usr/bin/python3
import subprocess
import argparse

parser = argparse.ArgumentParser(description='Test the reliability of a program')
parser.add_argument('program', type=str, help='The program to be tested')
parser.add_argument('program_args', type=str, help='The arguments of the program (in quotes if multiple)')
parser.add_argument('count', type=int, help='How many times should the program execute')

if __name__ == "__main__":
    args = parser.parse_args()
    execute_arguments = (args.program  +  " " + args.program_args).split()
    first_result = None

    # Execute given times
    for x in range(args.count):
        print("executing", x + 1, "/", args.count)
        # Execute program with arguments
        result = subprocess.run(execute_arguments, stdout=subprocess.PIPE)
        if not first_result:
            first_result = result.stdout
            # print(cmpResult)
        elif result.stdout != first_result:
            # Output was different from first
            raise Exception("This program is not reliable.")

    # All executions were same as first
    print("This program is reliable")
