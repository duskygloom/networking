import math

def is_valid_stream(stream: str) -> bool:
    for i in stream:
        if i != '0' and i != '1':
            return False
    return True

def simple_log(base: int, number: int) -> int:
    '''returns -1 if number does not have an integral log value'''
    result = 0
    while number % base == 0:
        result += 1
        number /= base
    number_is_one = int(number == 1)
    return -1 * (not number_is_one) + result * (number_is_one)

def is_valid_n(n: int) -> bool:
    result = simple_log(4, n)
    return result >= 0

def get_ticks_codes(n: int) -> (list[int], list[str]):
    n_ticks = int(math.sqrt(n))
    n_bits = simple_log(2, n)
    ticks = [tick for tick in range(1-n_ticks, n_ticks, 2)]
    graycodes = [int_to_graycode(i, n_bits//2) for i in range(n_ticks)]
    return (ticks, graycodes)

def int_to_graycode(n: int, padding: int = None) -> str:
    binary = ""
    # int to binary
    while n > 0:
        binary = str(n % 2) + binary
        n //= 2
    # pad with zeroes
    if padding is not None:
        binary = (padding-len(binary))*'0' + binary
    # binary to graycode
    graycode = binary[0]
    for i in range(len(binary)-1):
        graycode += str((int(binary[i]) + int(binary[i+1])) % 2)      # xor
    return graycode
