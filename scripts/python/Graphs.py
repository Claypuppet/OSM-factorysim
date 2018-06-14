import sys
import json
import yaml

import SpendedTime

def get_config_file(file_name):
    with open(file_name, 'r') as stream:
        return yaml.load(stream)

def get_log_file(file_name):
    with open(file_name) as content:
        return json.load(content)

def main():
    log_file_name = 'log.json'
    log_file = get_log_file(log_file_name)

    config_file_name = 'config.yaml'
    config_file = get_config_file(config_file_name)

    SpendedTime.generate_chart(config_file, log_file)

if __name__ == '__main__':
    main()