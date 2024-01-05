bitsfile    = "bitstream.dat"
flag        = "011110"

def tx(txstream: str) -> str:
    '''
        Takes input bit stream as argument.
        Returns modified stream.
    '''
    rxstream = ""
    for bit in txstream:
        rxstream += bit
        if (rxstream[-4:] == "0111"):
            rxstream += "0"
    rxstream += flag
    return rxstream

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
    f = open(bitsfile, "r")
    stream = f.read()
    f.close()
    print(f"Tx                  : {stream}")
    stuff = tx(stream)
    print(f"Tx after stuffing   : {stuff}")
    unstuff = rx(stuff)
    print(f"Rx after unstuffing : {unstuff}")
    print(f"\nOverhead = {len(stuff)-len(stream)}")
