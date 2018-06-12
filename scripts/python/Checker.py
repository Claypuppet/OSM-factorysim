# string = "{name}, {configurated_value}, {simulated_value}"
#     config_machines = config_file['productionLine']['machines']
#     log_machines = log_file['finalStatistics']['machines']
#
#     print 'Mean time between failure checks:'
#     for config_machine in config_machines:
#         for simulated_machine in log_machines:
#             if config_machine['id'] == simulated_machine['id']:
#                 data = {'name':config_machine['name'],
#                         'configurated_value':config_machine['meanTimeBetweenFailureInHours'],
#                         'simulated_value':simulated_machine['MTBFinHours']}
#
#         print string.format(**data)

import sys
import json
import yaml

def get_config_file(file_name):
    with open(config_file_name, 'r') as stream:
        return yaml.load(stream)

def get_log_file(file_name):
    with open(log_file_name) as content:
        return json.load(content)

class Checker(object):

    def __init__(self,
                 configurated_machine_statistics,
                 simulated_machine_statistics):
        self.configurated_machine_statistics = configurated_machine_statistics
        self.simulated_machine_statistics = simulated_machine_statistics

config_file_name = sys.argv[1]
config_file = get_config_file(config_file_name)

log_file_name = sys.argv[2]
log_file = get_log_file(log_file_name)

config_machines = config_file['machines']
simulated_machines = log_file['finalstatistics']['machines']

log_string = "{name}, {configurated_value}, {simulated_value}"
config_file_fieldname = ''
log_file_fieldname = ''
checker = Checker(config_machines, simulated_machines, )
checker.print_results()