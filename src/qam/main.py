import sys, webbrowser
import matplotlib.pyplot as plot
from qam.utils import is_valid_n, is_valid_stream
from qam.signal_space_diagram import plot_graph
from qam.bit_stream_to_symbols import get_symbols_from_stream

savefile = "_qam_graph.png"

if __name__ == "__main__":
    n = int(input("n: "))
    if not is_valid_n(n):
        print("Invalid value of n: n must be a power of 4.")
        sys.exit(0)
    savefile = str(n) + savefile
    stream = input("Bit stream: ").strip()
    if not is_valid_stream(stream):
        print("Invalid stream: stream must have only 0s and 1s.")
        sys.exit(0)
    fig, axis = plot.subplots()
    mapping = plot_graph(n, fig, axis, savefile)
    print(f"{n} QAM symbol mapping: {mapping}")
    input("Press Enter to view the signal space. ")
    webbrowser.open(savefile)
    symbols = get_symbols_from_stream(stream, n)
    print("Symbols:", symbols)
