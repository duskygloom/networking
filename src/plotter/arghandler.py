import argparse

class ArgHandler(argparse.ArgumentParser):
    def __init__(
            self, 
            name: str = "Plotter", 
            description: str = "Plot using matplotlib."
    ):
        super().__init__(prog=name, description=description)
        self.setup()

    def setup(self):
        # default values
        default_title = "GRAPH"
        default_xlabel = "X-axis"
        default_ylabel = "Y-axis"
        default_xstep = 1.0
        default_figfile = "graph.svg"
        # adding arguments
        self.add_argument(
            "-d", "--data", 
            required=True, 
            metavar="file",
            help="file where x and y values are stored"
        )
        self.add_argument(
            "-n", "--nsignal",
            required=True,
            type=int,
            metavar="value",
            help="length of signal bitstream"
        )
        self.add_argument(
            "-t", "--title",
            default=default_title,
            type=str,
            metavar="name",
            help=f"title of the graph, default: '{default_title}'"
        )
        self.add_argument(
            "-x", "--xlabel",
            default=default_xlabel,
            type=str,
            metavar="name",
            help=f"label of X-axis, default: '{default_xlabel}'"
        )
        self.add_argument(
            "-y", "--ylabel",
            default=default_ylabel,
            type=str,
            metavar="name",
            help=f"label of Y-axis, default: '{default_ylabel}'"
        )
        self.add_argument(
            "-s", "--xstep",
            default=default_xstep,
            type=float,
            metavar="value",
            help=f"step value for the range of xticks, default: {default_xstep}"
        )
        self.add_argument(
            "-f", "--figfile",
            default=default_figfile,
            type=str,
            metavar="file",
            help=f"file where the graph is stored, default: {default_figfile}"
        )
