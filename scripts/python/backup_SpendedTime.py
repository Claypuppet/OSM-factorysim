import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def get_dataframe(log_file):
    machine_names = []
    data = [[], [], [], []]
    for machine in log_file["finalStatistics"]["machines"]:
        machine_names.append(machine["name"])
        data[0].append(machine["avgProductionTime"])
        data[1].append(machine["avgIdleTime"])
        data[2].append(machine["avgDownTime"])
        data[3].append(machine["avgConfigureTime"])

    return {"machine_names":machine_names, "data":data}


def generate_chart(log_file):
    dataframe = get_dataframe(log_file)
    machines = dataframe["machine_names"]
    data = dataframe["data"]
    # machines = ('Machine 1', 'Machine 2', 'Machine 3', 'Machine 4', 'Machine 5', 'Machine 6', 'Machine 7', 'Machine 8')
    # segments = 4

    # generate some multi-dimensional data & arbitrary labels
    # data = 3 + 10 * np.random.rand(segments, len(machines))
    # print data

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
    title = log_file["finalStatistics"]["configurationName"] + " (" + log_file["finalStatistics"]["configurationModus"] + ")"
    ax.set_title(title)
    plt.legend(('Idle', 'Broken', 'Configuring', 'Producing'), ncol=4, loc='upper center', bbox_to_anchor=(0.5, -0.15))
    plt.show()