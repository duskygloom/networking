import matplotlib.pyplot as plot
import webbrowser
from wireless.graphing import *

amplitude = 1
frequency = 2
graph_file = "wireless_graph.svg"

if __name__ == "__main__":
    bitstream = input("Bit stream: ")
    fig, axes = plot.subplots()
    axes.set_xticks([i for i in range(len(bitstream)+1)])
    axes.set_yticks([i for i in range(-amplitude, amplitude+1)])
    axes.set_title("Bit stream: " + bitstream)
    plot_graph(bitstream, axis=axes, amplitude=amplitude, frequency=frequency)
    fig.set_figheight(2)
    fig.set_figwidth(len(bitstream)*3)
    fig.savefig(graph_file)
    webbrowser.open(graph_file)
