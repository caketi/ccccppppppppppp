from collections.abc import Iterable, Iterator

a = [1,2]
iter_rator = iter(a)
print("(List)a is Iterator: ",isinstance(a, Iterator))
print("(List)a is Iterable: ",isinstance(a, Iterable))