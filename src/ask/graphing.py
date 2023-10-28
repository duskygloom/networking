import matplotlib.pyplot as plot
from matplotlib.axis import Axis
import numpy, math

def get_amplitude_list(stream: str, amplitude: int = 1) -> list[int]:
    return [amplitude*int(i) for i in stream]

def get_signal(a: float, nu: float, t: int, phi: float = 0) -> float:
    omega = 2 * math.pi * nu
    return a * math.cos(omega*t + phi)

def plot_graph(
    bitsream: str,
    axis: Axis = None,
    frequency: int = 2,
    amplitude: int = 1,
    n_noises: int = 50
):
    amplitudes = get_amplitude_list(bitsream, amplitude)
    x_values = list(numpy.arange(0, len(amplitudes), 0.01))
    noises = [numpy.random.uniform(-amplitude/4, amplitude/4) for i in range(len(x_values))]
    y_values = [get_signal(amplitudes[i//100], frequency, x_values[i])+noises[i] for i in range(len(x_values))]

    for i in range(len(x_values)):
        j = i - 1
        xi = x_values[i]
        yi = y_values[i]
        while j >= 0 and x_values[j] < xi:
            x_values[j+1] = x_values[j]
            y_values[j+1] = y_values[j]
            j -= 1
        x_values[j+1] = xi
        y_values[j+1] = yi
        
    if axis is None:
        plot.plot(x_values, y_values)
    else:
        axis.plot(x_values, y_values)
    
