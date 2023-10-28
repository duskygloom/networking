from qam.utils import get_ticks_codes, simple_log

def get_substreams(stream: str, n: int) -> str:
    '''returns list of sub-streams of length log2(n)'''
    n_bits = simple_log(2, n)
    # get prepended stream
    remainder = len(stream) % n_bits
    to_prepend = n_bits*(int(bool(remainder))) - remainder
    prep_stream = '0'*to_prepend + stream
    substreams = []
    for i in range(0, len(prep_stream), n_bits):
        substreams.append(prep_stream[i : i+n_bits])
    return substreams

def get_symbols_from_stream(stream: str, n: int) -> list[tuple[int]]:
    '''get MSB and LSB values from the stream'''
    substreams = get_substreams(stream, n)
    n_bits = simple_log(2, n) // 2
    ticks, codes = get_ticks_codes(n)
    symbols = [(
            ticks[codes.index(i[:n_bits])], 
            ticks[codes.index(i[n_bits:])]
        ) for i in substreams]
    return symbols
