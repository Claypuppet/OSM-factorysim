import sys
import json

import SpendedTime

def get_log_file(file_name):
    with open(log_file_name) as content:
        return json.load(content)

log_file_name = sys.argv[1]
log_file = get_log_file(log_file_name)

SpendedTime.generate_chart(log_file)
