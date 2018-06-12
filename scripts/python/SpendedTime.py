import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def get_dataframe(log_file):
    machine_names = []
    data = [[], [], [], []]
    for i in range (0, len(log_file["finalStatistics"]["machines"])):
        machine = log_file["finalStatistics"]["machines"][i]
        machine_names.append("Machine " + str(i))
        data[0].append(machine["avgProductionTime"])
        data[1].append(machine["avgIdleTime"])
        data[2].append(machine["avgDownTime"])
        data[3].append(machine["avgConfigureTime"])

    return {"machine_names":machine_names, "data":data}


def generate_chart(log_file):
    dataframe = get_dataframe(log_file)
    machines = dataframe["machine_names"]
    data = dataframe["data"]

    y_pos = np.arange(len(machines))

    fig = plt.figure()
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
    title = "Configuratie 1 (luxe tafels)"
    ax.set_title(title)

    plt.legend((patch_handles[0], patch_handles[1], patch_handles[2], patch_handles[3]), ('productionTime', 'idleTime', 'downTime', 'configureTime'), ncol=4, loc='upper center', bbox_to_anchor=(0.5, -0.15))
    plt.show()