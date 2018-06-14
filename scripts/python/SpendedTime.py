import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def get_dataframe(log_file, product_id):
    machine_names = []
    data = [[], [], [], []]

    for machine in log_file["machineFinalStatistics"]["machines"]:
        for product in machine["products"]:
            if product['productId'] == product_id:
                machine_names.append(machine['name'])
                data[0].append(product["avgProductionTime"])
                data[1].append(product["avgIdleTime"])
                data[2].append(product["avgDownTime"])
                data[3].append(product["avgConfigureTime"])

    return {"machine_names":machine_names, "data":data}


def generate_chart(config_file, log_file):
    product_id = 2

    dataframe = get_dataframe(log_file, product_id=product_id)
    machines = dataframe["machine_names"]
    data = dataframe["data"]

    y_pos = np.arange(len(machines))

    fig = plt.figure(figsize=(8, 5), dpi=80)
    ax = fig.add_subplot(111)
    ax.invert_yaxis()

    patch_handles = []
    left = np.zeros(len(machines))  # left alignment of data starts at zero
    for i, d in enumerate(data):
        patch_handles.append(ax.barh(y_pos, d,
                                     align='center',
                                     left=left))
        # accumulate the left-hand offsets
        left += d

    ax.set_yticks(y_pos)
    ax.set_yticklabels(machines)
    ax.set_xlabel('Tijdsduur')

    product_name = 'NULL'
    for product in config_file['productionLine']['products']:
        if int(product['id']) == product_id:
            product_name = product['name']

    title = 'Configuratie: ' + config_file['name'] + ' (' + product_name + ')'
    ax.set_title(title, loc='left')
    ax.get_xaxis().set_visible(False)

    plt.legend((patch_handles[0], patch_handles[1], patch_handles[2], patch_handles[3]), ('productionTime', 'idleTime', 'downTime', 'configureTime'), ncol=3, loc='upper center', bbox_to_anchor=(0.5, -0.05))
    plt.show()