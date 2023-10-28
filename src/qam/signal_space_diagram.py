from matplotlib.figure import Figure
from matplotlib.axis import Axis
from qam.utils import get_ticks_codes, simple_log

def plot_graph(
        n: int,
        fig: Figure,
        axis: Axis,
        savefile: str
) -> dict[str, int]:
    # calculating size for some graph elements
    log2n = simple_log(2, n)
    linewidth = 0.5*log2n
    markersize = 2*log2n
    fontsize = 3*log2n
    titlefontsize = 5*log2n
    figuresize = n/log2n
    figurepadding = log2n/10
    # setting up axis
    ticks, codes = get_ticks_codes(n)
    axis.set_xticks(ticks)
    axis.set_yticks(ticks)
    axis.set_xlim(xmin=ticks[0]-1.5, xmax=ticks[-1]+1.5)
    axis.set_ylim(ymin=ticks[0]-1.5, ymax=ticks[-1]+1.5)
    axis.tick_params(labelsize=fontsize)
    axis.set_ylabel("LSB", fontdict={"fontsize": fontsize})
    axis.set_xlabel("MSB", fontdict={"fontsize": fontsize})
    axis.set_title(f"{n} QAM\n", fontdict={'fontsize': titlefontsize})
    # plotting X and Y axis
    axis.plot([0, 0], [ticks[0]-1, ticks[-1]+1], linestyle="--", color="gray", linewidth=linewidth)
    axis.plot([ticks[0]-1, ticks[-1]+1], [0, 0], linestyle="--", color="gray", linewidth=linewidth)
    # plotting the signal space
    for i in range(len(ticks)):
        for j in range(len(ticks)):
            axis.plot(ticks[i], ticks[j], marker='o', markersize=markersize)
            axis.annotate(codes[i], xy=(ticks[i], ticks[j]), fontsize=fontsize, xytext=(0, fontsize/2), textcoords='offset points')
            axis.annotate(codes[j], xy=(ticks[i], ticks[j]), fontsize=fontsize, xytext=(fontsize/2, -fontsize), textcoords='offset points')
    # saving figure
    fig.set_figheight(figuresize)
    fig.set_figwidth(figuresize)
    fig.savefig(savefile, bbox_inches="tight", pad_inches=figurepadding)
    # return the mapping used
    return {i: j for i, j in zip(codes, ticks)}
