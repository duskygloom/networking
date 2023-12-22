import sys
from arghandler import ArgHandler
from plotter import Plotter

handler = ArgHandler()
args = handler.parse_args(sys.argv[1:])

def main(args):
    plotter = Plotter()
    plotter.setup(
        nsignals=args.nsignal,
        title=args.title,
        xlabel=args.xlabel,
        ylabel=args.ylabel,
        xstep=args.xstep
    )
    plotter.plot(args.data)
    plotter.save(args.figfile)
    plotter.open()

if __name__ == "__main__":
    try:
        main(args)
    except Exception as e:
        print(f"[Error] Unhandled exception: {e}")
