from itertools import combinations
from fractions import Fraction

def bipartitions(seq):
    """
    Yield all unordered 2-way partitions of `seq` (which must contain
    unique items).  Each partition is returned as a pair of *lists*.
    """
    items = list(seq)
    smallest = min(items)                # canonical anchor
    n = len(items)

    for r in range(1, n):
        for subset in combinations(items, r):
            if smallest not in subset:   # skip the mirror image
                continue
            other = [x for x in items if x not in subset]
            yield list(subset), other

def reachable_numbers(numbers):
    if len(numbers) == 1:
        return set(numbers)

    partitions = bipartitions(numbers)
    result = set()
    for left, right in partitions:
        results_left_tree = reachable_numbers(left)
        results_right_tree = reachable_numbers(right)

        for l in results_left_tree:
            for r in results_right_tree:
                result.add(l + r)
                result.add(l * r)
                result.add(l - r)
                result.add(r - l)
                if r != 0:
                    result.add(l / r)
                if l != 0:
                    result.add(r / l)
    return result

cases = int(input())

for _ in range(cases):
    numbers = [int(x) for x in input().split()]
    results = reachable_numbers([Fraction(x) for x in numbers])

    only_integers = set([x for x in results if x.denominator == 1 and x > 0])
    print(len(only_integers))
