import sys
from arghandler import ArgHandler
from plotter import Plotter

handler = ArgHandler()
args = handler.parse_args(sys.argv[1:])

plotter = Plotter()
plotter.setup(
    nsignals=args.nsignal,
    title=args.title,
    xlabel=args.xlabel,
    ylabel=args.ylabel,
)
plotter.plot(args.data)
plotter.save(args.figfile)
plotter.open()
