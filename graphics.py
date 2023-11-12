import sys
import matplotlib.pyplot as plt
import numpy as np


global args
args = bool(int(sys.argv[1])), bool(int(sys.argv[2])), bool(int(sys.argv[3])), bool(int(sys.argv[4])), bool(int(sys.argv[5]))


def check(data):
    if sum(data) == 0 or sum([int(i < 10*(10**(-4))) for i in data ]) >= 1:
        return False
    return True

def read_data(index):
    data = []
    with open("res.txt", "r") as file:
        for i in file.readlines():
            data.append(i)
    data = list(map(float, data[index][:-2].split(" ")))
    return data

def make_plot(data, l, c):
    x = [100, 500, 700, 800, 900, 1000, 2000, 3000, 5000, 7000, 10000]

    if check(data):
        plt.plot(x, data, label=l, color=c)

def init(data, index):
    if args[index]:
        return data
    return np.zeros(11)


data0 = []
data1 = []
data2 = []
data3 = []
data4 = []

data0 = read_data(0)
data1 = read_data(1)
data2 = read_data(2)
data3 = read_data(3)
data4 = read_data(4)

data0 = init(data0, 0)
data1 = init(data1, 1)
data2 = init(data2, 2)
data3 = init(data3, 3)
data4 = init(data4, 4)

make_plot(data0, "ins", "green")
make_plot(data1, "bub", "black")
make_plot(data2, "quick", "orange")
make_plot(data3, "sel", "blue")
make_plot(data4, "heap", "red")
plt.legend()
plt.savefig("fig.png")
