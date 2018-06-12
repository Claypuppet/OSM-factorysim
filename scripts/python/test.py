import yaml

with open("config.yaml", 'r') as stream:
    print(yaml.load(stream))