import json
import argparse
import subprocess

def run_command(command):
    try:
        # Run the command and capture its output
        output = subprocess.check_output(
            command, shell=True, stderr=subprocess.STDOUT, universal_newlines=True)
        return output
    except subprocess.CalledProcessError as e:
        print(e)


def open_repos():

    # Open the "repos.json" file for reading
    with open("repos.json", "r") as file:
        # Read the JSON data from the file
        json_data = file.read()

    # Deserialize the JSON data
    data = json.loads(json_data)

    return data


def command_repos(repos, sub_command):
    try:
        # Print the deserialized data
        for key, value in repos.items():
            print("Repo: ", key)
            command = None
            if (value["dir"] != ""):
                command = "cd " + value["dir"] + " && " + sub_command
            else:
                command = sub_command
            output = run_command(command)
            print(output)

    except Exception as e:
        print("Invalid repos.json parameters")
        print(e)

def checkout_repos(repos, branch):
    try:
        # Print the deserialized data
        for key, value in repos.items():
            print("Repo: ", key)
            command = None

            if(branch == None):
                branch = value["branch"]
            if (value["dir"] != ""):
                command = "cd " + value["dir"] + " && " + \
                    "git checkout " + branch
            else:
                command = "git checkout " + branch
            output = run_command(command)
            print(output)

    except Exception as e:
        print("Invalid repos.json parameters")
        print(e)

def push_repos(repos):
    try:
        # Print the deserialized data
        for key, value in repos.items():
            print("Repo: ", key)
            command = None
            if (value["dir"] != ""):
                command = "cd " + value["dir"] + " && " + \
                    "git push origin " + value["branch"]
            else:
                command = "git push origin " + value["branch"]
            output = run_command(command)
            print(output)

    except Exception as e:
        print("Invalid repos.json parameters")
        print(e)


def parse_args():
    parser = argparse.ArgumentParser(description="Pull or clear JSON data")
    parser.add_argument("action", choices=[
                        "pull", "clear", "add", "commit", "push", "status", "pull", "checkout"], help="Action to perform (pull or clear)")
    parser.add_argument('-m', '--message', type=str,
                        required=False, help='Commit message')
    
    parser.add_argument('-b', '--branch', type=str,
                        required=False, help='Targeted branch')
    # Parse the command-line arguments
    args = parser.parse_args()

    return args


def main():
    args = parse_args()
    repos = open_repos()

    action = args.action
    message = args.message
    branch = args.branch
    if (action == "pull"):
        command_repos(repos, "git pull")
    elif (action == "clear"):
        command_repos(repos, "git checkout .")
    elif (action == "add"):
        command_repos(repos, "git add .")
    elif (action == "commit"):
        command_repos(repos, "git commit -m \"" + message + "\"")
    elif (action == "push"):
        push_repos(repos)
    elif (action == "status"):
        command_repos(repos, "git status")
    elif(action == "checkout"):
        checkout_repos(repos, branch)
    else:
        print("invalid input")


main()
