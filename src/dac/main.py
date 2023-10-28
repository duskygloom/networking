import os, webbrowser
from dac.analog_graph import *

graph_file = "graph.svg"
peak_signal = 2
noises_number = 100

bits_str = input("Binary: ").strip()
is_valid = True
for i in bits_str:
    if i != '0' and i != '1':
        is_valid = False
        break

if bits_str == "":
    print("No binary recieved.")

elif not is_valid:
    print("Invalid binary.")

else:
    bits = get_signals(bits_str, peak_value=peak_signal)

    x, y = get_digital_wave_points(bits)
    nx, ny = get_noisy_points(bits, n_noises=noises_number)

    alt_bits = get_alternate_signals(bits)
    dalt_x, dalt_y = get_digital_wave_points(alt_bits)
    # alt_nx, alt_ny = get_noisy_points(dalt_y, x_values=dalt_x, n_noises=noises_number)

    # plot.style.use("dark_background")
    fig, axis = plot.subplots(2)
    fig.subplots_adjust(hspace=0.6)
    axis[0].set_title(f"Noisy signal (NRZ-L): {bits_str}", loc="left")
    axis[1].set_title(f"Noisy signal (Manchester): {bits_str}", loc="left")

    plot_line_from_points(bits, fig=fig, axis=axis[0], show_points=True, hide_line=True, graph_color="black", plot_zero_line=True)
    digital = plot_line_from_points(y, x_values=x, fig=fig, axis=axis[0], show_points=False, graph_color="violet", plot_zero_line=False)
    noisy = plot_line_from_points(ny, x_values=nx, fig=fig, axis=axis[0], show_points=False, graph_color="purple", plot_zero_line=False)
    
    plot_line_from_points(bits, fig=fig, axis=axis[1], show_points=True, hide_line=True, graph_color="black", plot_zero_line=True)
    digital_alt = plot_line_from_points(dalt_y, x_values=dalt_x, fig=fig, axis=axis[1], show_points=False, graph_color="violet", plot_zero_line=False)
    # noisy_alt = plot_line_from_points(alt_ny, x_values=alt_nx, fig=fig, axis=axis[1], show_points=False, graph_color="purple", plot_zero_line=False)

    fig.legend((digital, noisy), ("Digital signal", "Noisy signal"))
    fig.savefig(graph_file)
    print(f"Figure saved to {os.path.join(os.path.abspath('.'), graph_file)}")
    input("Press Enter to view the figure in browser. ")
    webbrowser.open(os.path.join(os.path.abspath('.'), graph_file))
