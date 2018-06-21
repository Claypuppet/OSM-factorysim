import os
import json
import yaml

import SpendedTime


logs_directory = './'
log_file_name = 'statistics.json'
config_file_name = 'used_config.yaml'

def get_config_file(file_name):
    with open(file_name, 'r') as stream:
        return yaml.load(stream)

def get_log_file(file_name):
    with open(file_name) as content:
        return json.load(content)

def is_result_directory(path):
    return (os.path.isdir(path) and log_file_name in os.listdir(path) and config_file_name in os.listdir(path))

def main():
    for file_or_foldername in os.listdir(logs_directory):
        file_or_folderpath = os.path.join(logs_directory, file_or_foldername)
        if is_result_directory(file_or_folderpath):
            log_file = get_log_file(os.path.join(file_or_folderpath, log_file_name))
            config_file = get_config_file(os.path.join(file_or_folderpath, config_file_name))

            for product_id in [i['id'] for i in config_file['productionLine']['products']]:
                SpendedTime.generate_chart(file_or_folderpath, config_file, log_file, product_id)

if __name__ == '__main__':
    main()