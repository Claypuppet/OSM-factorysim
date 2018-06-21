import os
import json
import yaml

logs_directory = './logs'
log_file_name = 'statistics.json'
config_file_name = 'used_config.yaml'
result_file_name = 'quality_check.txt'
filename = 'overzicht.txt'

def get_config_file(file_name):
    with open(file_name, 'r') as stream:
        return yaml.load(stream)

def get_log_file(file_name):
    with open(file_name) as content:
        return json.load(content)

def get_total_brokes(log_file, machines):
    return sum([machine['totalTimesBroken'] for machine in machines])

def get_lost_time(log_file, machines):
    return sum([sum([sum([product['avgIdleTime']]) for product in machine['products']]) for machine in machines])

def get_total_lost(log_file, machines):
    return sum([sum([product['totalLost'] for product in machine['products']]) for machine in machines])

def get_total_reconfigures(log_file, machines):
    return log_file['machineFinalStatistics']['timesReconfigured']


log = 'naam, normale_kantoortafels, luxe_kantoortafels, total_lost_products, total_broken_machines, total_time_not_producing, total_reconfigures\n'
# string = '{naam}, {normale_kantoortafels}, {luxe_kantoortafels}, {total_lost_products}, {total_broken_machines}, {total_time_not_producing}, {total_reconfigures}\n'


for file_or_foldername in os.listdir(logs_directory):
    file_or_folderpath = os.path.join(logs_directory, file_or_foldername)
    if os.path.isdir(file_or_folderpath):
        log_file = get_log_file(os.path.join(file_or_folderpath, log_file_name))
        config_file = get_config_file(os.path.join(file_or_folderpath, config_file_name))

        machines = log_file['machineFinalStatistics']['machines']

        normale_kantoortafels = log_file['machineFinalStatistics']['totalEndProducts']['1']
        luxe_kantoortafels = log_file['machineFinalStatistics']['totalEndProducts']['2']
        total_time_not_producing = get_lost_time(log_file, machines)
        total_broken_machines = get_total_brokes(log_file, machines)
        total_lost_products = get_total_lost(log_file, machines)
        total_reconfigures = get_total_reconfigures(log_file, machines)

        log += config_file['name'] + ', ' + str(normale_kantoortafels) + ', ' + str(luxe_kantoortafels) + ', ' + str(total_lost_products) + ', ' + str(total_broken_machines) + ', ' + str(total_time_not_producing) + ', ' + str(total_reconfigures) + '\n'

filepath = os.path.join(logs_directory, filename)
with open(filepath, "w") as text_file:
    text_file.write(log)