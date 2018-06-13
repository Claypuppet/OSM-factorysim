# For this script to work, install pyyaml
import yaml

configfile = file('configs.yaml', 'r')
configs = yaml.load(configfile)

print("Welcome to the config creator!")

config={'simulationInfo':{}, 
	'productionLine':{
		'name': configs['name'],
		'products': configs['products'],
		'machines':[]
	}
}	

config['simulationInfo']['name'] = raw_input("Simulation name?")
config['simulationInfo']['durationInWeeks'] = int(raw_input("Simulation duration in weeks?"))
config['simulationInfo']['startHourOfWorkDay'] = int(raw_input("Starting hour?"))
config['simulationInfo']['workDayDurationInHours'] = int(raw_input("Working hours per day?"))
config['simulationInfo']['local'] = True if int(raw_input("local?")) else False
config['simulationInfo']['randomSeed'] = int(raw_input("Seed? (0 for none)"))

print("Select 0 for a cheap machine and 1 for an expensive machine!")

for machineset in configs['machinesets']:
	choice = int(raw_input("Choose a " + machineset['name']))

	machine = {
		'id': machineset['id'],
		'name': machineset['name'],
		'initializationDurationInSeconds': machineset['machines'][choice]['initializationDurationInSeconds'],
		'meanTimeBetweenFailureInHours': machineset['machines'][choice]['meanTimeBetweenFailureInHours'],
		'reparationTimeStddevInMinutes': machineset['machines'][choice]['reparationTimeStddevInMinutes'],
		'postProcessInfo': machineset['machines'][choice]['postProcessInfo'],
		'configurations': machineset['machines'][choice]['configurations'],
		
	}

	config['productionLine']['machines'].append(machine)

yamlfile = file("config_"+config['simulationInfo']['name']+".yaml", "w")
yaml.dump(config, yamlfile)

print yaml.dump(config)

