from typing import List
from collections import *
from itertools import *
# https://blog.csdn.net/qq_43401035/article/details/119253871
# itertools.pairwise创建一个迭代器，返回从 iterable 获取的连续重叠对。 
# # 注：输出迭代器中 2-tuples 的数量将比输入的数量少一个。
# pairwise('ABCDEFG')  # AB BC CD DE EF FG
# # 注：如果输入的可迭代对象小于两个值，则该值为空。
# pairwise('A')  # (Empty)
# 6225.差值数组不同的字符串 返回差值不同的字符串
def oddString(words: List[str]) -> str:
    g = defaultdict(list)
    for s in words:
        t = tuple(ord(x) - ord(y) for x,y in pairwise(s)) 
        g[t].append(s)
    x, y = g.values()
    return x[0] if len(x) == 1 else y[0]
print(oddString(["adc", "wzy", "abc"]))
print(oddString(["adc", "wzy", "dga"]))

# 6228.距离字典两次编辑以内的单词
def twoEditWords(queries: List[str], dictionary: List[str]) -> List:
    ans = []
    for q in queries:
        for s in dictionary:
            if sum(x != y for x, y in zip(q,s)) <= 2:
                ans.append(q)
                break
    return ans
print(twoEditWords(["word", "note", "ants", "wood"], ["wood","joke","moat"]))
# 6227.第二大的元素
from sortedcontainers import SortedList
def sge2(nums: List[int], k = 2) -> List[int]:
    ans = [-1] * len(nums)
    s = SortedList() 
    for _, i in sorted((-x, i) for i,x in enumerate(nums)):
        j = s.bisect_right(i) + k -1
        if j < len(s) : ans[i] = nums[s[j]]
        s.add(i)
    return ans
def secondGreaterElement(nums: List[int]) -> List[int]:
    ans = [-1] * len(nums)
    s = [] # 存储遍历过的数
    t = [] # 存储遍历过，且这个数右侧发现了比它大的数
    for i, x in enumerate(nums):
        while t and nums[t[-1]] < x:
            ans[t.pop()] = x
        j = len(s) - 1
        while j >= 0 and nums[s[j]] < x:
            j -= 1
        t += s[j+1:]
        del s[j+1:]
        s.append(i)
    return ans
print(secondGreaterElement([2,4,0,9,6]))