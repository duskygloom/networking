import matplotlib.pyplot as plot
import numpy

import webbrowser

class Plotter:
    def __init__(self):
        self.figure, self.axis = plot.subplots()
        self.figfile = None

    def setup(
            self, 
            nsignals: int, 
            title: str, 
            xlabel: str, 
            ylabel: str,
            xstep: float
    ):
        fig = self.figure
        axis = self.axis
        fig.set_figwidth(nsignals/xstep)
        fig.set_figheight(3)
        axis.set_title(title)
        axis.set_ylabel(ylabel)
        axis.set_yticks((-2, -1, 0, 1, 2))
        axis.set_ylim(-2.5, 2.5)
        axis.set_xlabel(xlabel)
        xticks = numpy.arange(0, nsignals, xstep)
        axis.set_xticks(xticks)
        axis.set_xlim(-xstep, nsignals+xstep)
        axis.set_xticklabels([round(i, 4) for i in xticks])
        axis.plot([0, nsignals], [0, 0], linestyle="dashed", color="gray")

    def plot(self, datafile: str):
        f = open(datafile, "r")
        xy = [float(i) for i in f.read().split()]
        f.close()
        x = xy[::2]
        y = xy[1::2]
        self.axis.plot(x, y)

    def save(self, figfile: str):
        self.figure.savefig(figfile, bbox_inches="tight", pad_inches=0.4)
        self.figfile = figfile

    def open(self):
        if self.figfile:
            webbrowser.open(self.figfile)
