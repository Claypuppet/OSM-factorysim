import os
import json
import yaml

logs_directory = './logs'
log_file_name = 'statistics.json'
config_file_name = 'used_config.yaml'
result_file_name = 'quality_check.txt'

def get_config_file(file_name):
    with open(file_name, 'r') as stream:
        return yaml.load(stream)

def get_log_file(file_name):
    with open(file_name) as content:
        return json.load(content)

def getTotalTimeForMachineProduct(log_file, machine_id):
    totalTime = 0
    for timestamp in log_file['timeStamps']:
        for machine in timestamp['machines']:
            if machine['id'] == machine_id:
                for product in machine['products']:
                    totalTime += product['idleTime']
                    totalTime += product['downTime']
                    totalTime += product['configureTime']
                    totalTime += product['productionTime']
    return totalTime

def checkMeanTimeBetweenFailure(config_file, log_file):
    string = "{name}, {configurated_value}, {simulated_value}\n"
    config_machines = config_file['productionLine']['machines']
    log_machines = log_file['machineFinalStatistics']['machines']

    log = ''
    log += 'Mean time between failure checks:\n'
    log += 'machine_name, configured_value, simulated_value\n'
    for config_machine in config_machines:
        for simulated_machine in log_machines:
            if config_machine['id'] == simulated_machine['id']:
                mtbf = float(getTotalTimeForMachineProduct(log_file, config_machine['id'])) / float(simulated_machine['totalTimesBroken']) / 1000 / 60 / 60
                data = {'name':config_machine['name'],
                        'configurated_value':config_machine['meanTimeBetweenFailureInHours'],
                        'simulated_value':mtbf}
                log += string.format(**data)
    return log + '\n'

def checkReparationTime(config_file, log_file):
    string = "{name}, {configurated_value}, {simulated_value}, {configured_stddev}\n"
    config_machines = config_file['productionLine']['machines']
    log_machines = log_file['machineFinalStatistics']['machines']

    log = ''
    log += 'Reparation time checks:\n'
    log += 'machine_name, configurated_value, simulated_value, configured_stddev\n'
    for config_machine in config_machines:
        for simulated_machine in log_machines:
            if config_machine['id'] == simulated_machine['id']:
                data = {}
                data['name'] = config_machine['name']
                data['configurated_value'] = config_machine['reparationTimeInMinutes']
                total_down_time = simulated_machine['totalDownTime']
                times_broken = simulated_machine['totalTimesBroken']
                data['simulated_value'] = float(total_down_time) / float(times_broken) / 1000.0 / 60.0  if total_down_time > 0 and times_broken > 0 else 0
                data['configured_stddev'] = config_machine['reparationTimeStddevInMinutes']
                log += string.format(**data)
    return log + '\n'

def checkPropportion(config_file, log_file):
    string = "{name}, {configurated_value}, {simulated_value}\n"
    simulated_statisticks = log_file['machineFinalStatistics']

    simulated_products = {
        'total_proportion':sum([int(simulated_statisticks['totalEndProducts'][i]) for i in simulated_statisticks['totalEndProducts']]),
        'products': [{"id":int(key), "proportion":value} for key, value in simulated_statisticks['totalEndProducts'].iteritems()]
    }

    configurated_products = {
        'total_proportion': sum([i['proportion'] for i in config_file['productionLine']['products']]),
        'products': config_file['productionLine']['products']
    }

    log = ''
    log += 'product propportion checks:\n'
    log += 'product_name, configured_proportion, simulated_proportion\n'
    for simulated_product in simulated_products['products']:
        for configured_product in configurated_products['products']:
            if simulated_product['id'] == configured_product['id']:
                data = {}
                data['name'] = configured_product['name']
                data['configurated_value'] = float(configured_product['proportion']) / float(configurated_products['total_proportion'])
                data['simulated_value'] = float(simulated_product['proportion']) / float(simulated_products['total_proportion'])
                log += string.format(**data)
    return log + '\n'

def main():
    for file_or_foldername in os.listdir(logs_directory):
        file_or_folderpath = os.path.join(logs_directory, file_or_foldername)
        if os.path.isdir(file_or_folderpath):
            log_file = get_log_file(os.path.join(file_or_folderpath, log_file_name))
            config_file = get_config_file(os.path.join(file_or_folderpath, config_file_name))

            log = ''
            log += checkMeanTimeBetweenFailure(config_file, log_file)
            log += checkReparationTime(config_file, log_file)
            log += checkPropportion(config_file, log_file)

            filepath = os.path.join(file_or_folderpath, result_file_name)

            print 'hallo'
            with open(filepath, "w") as text_file:
                text_file.write(log)

if __name__ == '__main__':
    main()