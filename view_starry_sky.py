import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_table('starry_sky.txt', sep = ';', header = None )

plt.figure();

plt.plot(data[0],data[1],'o')

plt.savefig('starry_sky.png')