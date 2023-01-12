import hashlib

from typing import Optional, Set

def get_three(md5_hex: str) -> Optional[str]:
    for i in range(0, len(md5_hex) - 2):
        if all(c == md5_hex[i] for c in md5_hex[i + 1:i +3]):
            return md5_hex[i]
    return None

def get_fives(md5_hex: str) -> Set[str]:
    result = set()
    for i in range(0, len(md5_hex) - 4):
        if all(c == md5_hex[i] for c in md5_hex[i + 1:i +5]):
            result.add(md5_hex[i])
    return result


def get_hex(val: str, iterations: int):
    result = hashlib.md5(val.encode('utf-8')).hexdigest()
    for _ in range(iterations):
        result = hashlib.md5(result.encode('utf-8')).hexdigest()
    return result

def solve(salt: str, iterations: int, target: int):
    md5_hexes = []
    fives = []
    while len(md5_hexes) < 1000:
        md5_hexes.append(get_hex(f'{salt}{len(md5_hexes)}', iterations=iterations))
        fives.append(get_fives(md5_hexes[-1]))

    result = []
    while len(result) < 64:
        md5_hexes.append(get_hex(f'{salt}{len(md5_hexes)}', iterations=iterations))
        fives.append(get_fives(md5_hexes[-1]))
        current = len(md5_hexes) - 1000
        three = get_three(md5_hexes[current])
        if three is None:
            continue
        if any(three in f for f in fives[current + 1:]):
            result.append(current)
    return result[-1]

salt = 'cuanljph'
print('Part 1: ', solve(salt, iterations=0, target=64))
print('Part 2: ', solve(salt, iterations=2016, target=64))
