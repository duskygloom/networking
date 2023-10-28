from matplotlib.figure import Figure
from matplotlib.axes import Axes
from matplotlib.lines import Line2D
import matplotlib.pyplot as plot
import numpy

def get_signals(binary_str: str, peak_value: int) -> list[int]:
    return [(-peak_value)*(-1)**int(i) for i in binary_str]

def sort_two_lists(
    list_a: list[int|float], 
    list_b: list[int|float]
):
    '''sorts list_a and list_b according to increasing order of list_a'''
    i, j = 1, 0
    stop = len(list_a)
    while (i < stop):
        j = i-1
        while (j >= 0):
            # sorting
            if list_a[i] < list_a[j]:
                temp = list_a[i]
                list_a[i] = list_a[j]
                list_a[j] = temp
                temp = list_b[i]
                list_b[i] = list_b[j]
                list_b[j] = temp
                i -= 1
            # removing duplicate values
            elif list_a[i] == list_a[j]:
                list_b[j] = list_b[i]
            j -= 1
        i += 1

def get_alternate_signals(bits: list[int]) -> list[int]:
    alternate_bits = []
    for i in bits:
        alternate_bits.append(bits[i])
        alternate_bits.append(-bits[i])
    return alternate_bits

def get_noisy_points(
    y_values: list[int|float], 
    x_values: list[int|float] | None = None,
    original_length: int | None = None,
    noises: list[float] | None = None,
    n_noises: int = 200,
    max_noise: int = 1,
    min_noise: int = -1
) -> (list[int|float], list[int|float]):
    if x_values is None:
        x_values = list(range(len(y_values)))
    if original_length is None:
        original_length = len(x_values)
    if noises is None:
        noises = [numpy.random.uniform(min_noise, max_noise) for i in range(n_noises)]
    else:
        n_noises = len(noises)
    noisy_x = x_values.copy()
    noisy_y = y_values.copy()
    for i in range(len(noises)):
        x_value = (original_length / n_noises) * i
        noisy_x.append(x_value)
        noisy_y.append(noises[i] + y_values[x_values.index(int(x_value))])
    sort_two_lists(noisy_x, noisy_y)
    return noisy_x, noisy_y

def get_digital_wave_points(
    y_values: list[int|float],
    x_values: list[int|float] | None = None,
) -> (list[int|float], list[int|float]):
    if x_values is None:
        x_values = range(0, len(y_values))
    digital_x = []
    digital_y = []
    for i in range(len(y_values)):
        digital_y.append(y_values[i])
        digital_y.append(y_values[i])
        digital_x.append(x_values[i])
        digital_x.append(x_values[i]+1)
    return (digital_x, digital_y)

def plot_line_from_points(
    y_values: list[int|float], 
    x_values: list[int|float] | None = None, 
    fig: Figure | None = None,
    axis: Axes | None = None,
    show_points: bool = False,
    point_gap: int = 1,
    hide_line: bool = False,
    zero_line_color: str = "gray",
    graph_color: str = "purple",
    plot_zero_line: bool = False
) -> Line2D | None:
    line = None
    if x_values is None:
        x_values = range(0, len(y_values), point_gap)
    if fig is None or axis is None:
        fig, axis = plot.subplots()
    axis.set_xlabel("Time")
    axis.set_ylabel("Signal")
    if plot_zero_line:
        axis.plot([0, len(y_values)//point_gap], [0, 0], linestyle="dashed", color=zero_line_color)
    if not hide_line:
        line = axis.plot(x_values, y_values, color=graph_color)
    if show_points:
        axis.scatter(x=x_values, y=y_values, color=graph_color, s=16)
    start, end = axis.get_xlim()
    axis.set_xticks(numpy.arange(0, end, 1))
    start, end = axis.get_ylim()
    axis.set_yticks(numpy.arange(int(start), end, 1))
    if line is not None:
        return line[0]
