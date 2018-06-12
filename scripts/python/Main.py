import sys
import json
import yaml

def get_config_file(file_name):
    with open(config_file_name, 'r') as stream:
        return yaml.load(stream)

def get_log_file(file_name):
    with open(log_file_name) as content:
        return json.load(content)

def checkMeanTimeBetweenFailure(config_file, log_file):
    string = "{name}, {configurated_value}, {simulated_value}"
    config_machines = config_file['productionLine']['machines']
    log_machines = log_file['finalStatistics']['machines']

    print 'Mean time between failure checks:'
    print 'machine_name, configured_value, simulated_value'
    for config_machine in config_machines:
        for simulated_machine in log_machines:
            if config_machine['id'] == simulated_machine['id']:
                data = {'name':config_machine['name'],
                        'configurated_value':config_machine['meanTimeBetweenFailureInHours'],
                        'simulated_value':simulated_machine['MTBFinHours']}
                print string.format(**data)
    print

def checkReparationTime(config_file, log_file):
    string = "{name}, {configurated_value}, {simulated_value}, {configured_stddev}"
    config_machines = config_file['productionLine']['machines']
    log_machines = log_file['finalStatistics']['machines']

    print 'Reparation time checks:'
    print 'machine_name, configurated_value, simulated_value, configured_stddev'
    for config_machine in config_machines:
        for simulated_machine in log_machines:
            if config_machine['id'] == simulated_machine['id']:
                data = {}
                data['name'] = config_machine['name']
                data['configurated_value'] = config_machine['reparationTimeInMinutes']
                down_time = simulated_machine['avgDownTime']
                total_down_time = simulated_machine['MTBFinHours'] # TODO : change name
                data['simulated_value'] = total_down_time / times_broken / 1000 / 60 if down_time > 0 and times_broken > 0 else 0
                data['configured_stddev'] = config_machine['reparationTimeStddevInMinutes']
                print string.format(**data)
    print

def checkPropportion(config_file, log_file):
    string = "{name}, {configurated_value}, {simulated_value}"
    machines = log_file['finalStatistics']['machines']
    last_simulated_machine = machines[len(machines)-1] # inpakmachine

    simulated_products = {'total_proportion':sum(last_simulated_machine['totalProducedProducts'].values()),
                          'products':[{'id':int(key), 'proportion':value} for key, value in last_simulated_machine['totalProducedProducts'].iteritems()]}

    configurated_products = {'total_proportion': sum([i['proportion'] for i in config_file['productionLine']['products']]),
                             'products':config_file['productionLine']['products']}

    print 'product propportion checks:'
    print 'product_name, configured_proportion, simulated_proportion'
    for simulated_product in simulated_products['products']:
        for configured_product in configurated_products['products']:
            if simulated_product['id'] == configured_product['id']:
                data = {}
                data['name'] = configured_product['name']
                data['configurated_value'] = float(configured_product['proportion']) / float(configurated_products['total_proportion'])
                data['simulated_value'] = float(simulated_product['proportion']) / float(simulated_products['total_proportion'])
                print string.format(**data)
    print



config_file_name = sys.argv[1]
config_file = get_config_file(config_file_name)

log_file_name = sys.argv[2]
log_file = get_log_file(log_file_name)

checkMeanTimeBetweenFailure(config_file, log_file)
checkReparationTime(config_file, log_file)
checkPropportion(config_file, log_file)

# print "Workday duration, {configurated_value}, {simulated_value}"
# print "Production each minute, {configurated_value}, {simulated_value}"
