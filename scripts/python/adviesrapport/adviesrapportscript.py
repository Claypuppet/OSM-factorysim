import json
import yaml
import numpy

# Open the resultfile
resultfile = open('statistics.json')
resultdata = resultfile.read()
result = json.loads(resultdata)
endResult = result['machineFinalStatistics']

# Open the used configfile
configfile = file('used_config.yaml', 'r')
config = yaml.load(configfile)

# Calculate the amount of tables produced per week
nTotalProducedPerProduct = []
for i in range(len(config['productionLine']['products'])):
  nTotalProducedPerProduct.append({'id': config['productionLine']['products'][i]['id'], 'weeks': []})

for product in nTotalProducedPerProduct:
  for week in result['timeStamps']:
    for producedProduct in week['machines'][-1]['products']:
      if product['id'] is producedProduct['productId']:
        product['weeks'].append(producedProduct['produced'])
  product['totalProduced'] = sum(product['weeks'])
  product['averageProductionPerWeek'] = round(numpy.mean(product['weeks']), 2)
  product['std'] = round(numpy.std(product['weeks']), 2)
  
# Calculate the total downtime and lost products per machine
totalDownTime = 0
nTotalLostProducts = 0
for machine in endResult['machines']:
  totalDownTime += machine['totalDownTime']
  for product in machine['products']:
    nTotalLostProducts += product['totalLost']
totalDownTime = round(float(totalDownTime) / config['simulationInfo']['durationInWeeks'], 2)
nTotalLostProducts = round(float(nTotalLostProducts) / config['simulationInfo']['durationInWeeks'], 2)

# Make the machineEffeciency dict ready for use
machineEffeciency = {}
for machine in config['productionLine']['machines']:
  machineEffeciency[machine['id']] = {'productionTime': 0, 'idleTime': 0, 'configureTime': 0, 'downTime': 0}
  
# Fill the machineEffeciency dict with machine times
for week in result['timeStamps']:
  for machine in week['machines']:
    for product in machine['products']:
      machineEffeciency[machine['id']]['productionTime'] += product['productionTime']
      machineEffeciency[machine['id']]['idleTime'] += product['idleTime']
      machineEffeciency[machine['id']]['configureTime'] += product['configureTime']
      machineEffeciency[machine['id']]['downTime'] += product['downTime']

# Calculate the effeciency of every machine
effeciencies = [] 
for machine in machineEffeciency:
  effeciencies.append(round(float(machineEffeciency[machine]['productionTime']) / (machineEffeciency[machine]['idleTime'] + machineEffeciency[machine]['productionTime']) * 100, 2))

effeciencyDeviations = []
for machine in effeciencies:
  if machine is not max(effeciencies):
    effeciencyDeviations.append(round(max(effeciencies) - machine, 2))

# Print results
print ("Tafels per week per product:")
for product in nTotalProducedPerProduct:
  print("\tId: " + str(product['id']) + ":\tTafels: " + str(product['averageProductionPerWeek']))
  print("\t\tStddev: " + str(product['std']))
print("Downtime per week in uren: " + str(round(totalDownTime/1000/60/60, 2)))
print("Verloren producten per week: " + str(nTotalLostProducts))
print("Gemiddeld rendementverschil in staat tot de meest werkende macihine: " + str(round(numpy.mean(effeciencyDeviations), 2)) + "%")
