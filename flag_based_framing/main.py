import sys, random

flag    = "011110"

MIN_STREAM_LENGTH   = 30
MAX_STREAM_LENGTH   = 60

def generate_random_bitstream(filename: str):
    n = random.randint(MIN_STREAM_LENGTH, MAX_STREAM_LENGTH);
    f = open(filename, "w")
    for i in range(n):
        f.write(str(int(random.randint(0, 20) > 5)))
    f.close()

def tx(txstream: str) -> (str, str):
    '''
        Takes input bit stream as argument.
        Returns modified stream.
    '''
    rxstream = ""
    change = ""
    for bit in txstream:
        rxstream += bit
        change += " "
        if (rxstream[-4:] == "0111"):
            rxstream += "0"
            change += "^"
    rxstream += flag
    change += "-"*len(flag)
    return rxstream, change

def rx(rxstream: str) -> str:
    '''
        Takes modified stream as argument.
        Returns original stream.
    '''
    buffer = ""
    txstream = ""
    for i in range(len(rxstream)):
        bit = rxstream[i]
        if (buffer == "0111" and bit == "0"):
            buffer = buffer[1:] + bit
        elif (buffer == "0111"):
            return txstream[:-4]
        elif len(buffer) < len(flag)-2:
            buffer += bit
            txstream += bit
        else:
            buffer = buffer[1:] + bit
            txstream += bit
    return txstream

if __name__ == "__main__":
    if (len(sys.argv) < 2):
        print("Missing bitstream file.")
        print(f"Usage: {sys.argv[0]} <filename>")
        sys.exit(0)
    generate_random_bitstream(sys.argv[1])
    f = open(sys.argv[1], "r")
    stream = f.read()
    f.close()
    print(f"Original stream     : {stream}")
    stuff, change = tx(stream)
    print(f"Transmitted stream  : {stuff}")
    print(f"Bit stuffing        : {change}")
    unstuff = rx(stuff)
    print(f"Received stream     : {unstuff}")
    print(f"\nOverhead = {len(stuff)-len(stream)}")

