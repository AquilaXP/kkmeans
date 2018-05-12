import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_table('result.txt', sep = ';', header = None )

datan = []

clusters = set(data[2].values.tolist())
clusters = sorted(clusters)

for cl in clusters:
    datan.append(data[ data[2] == cl ]);

for d in datan:
    plt.plot(d[0],d[1],'o')

plt.savefig('result.png')
