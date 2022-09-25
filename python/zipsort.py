from typing import List


def sortPeople(names: List[str], heights: List[int]) -> List[str]:
    return [name for _, name in sorted(zip(heights, names), reverse=True)]


names = ["Ma", "j", "ee"]
heights = [111, 100, 101]
res = sortPeople(names, heights)
print(res)


def longestSubarray(nums: List[int]) -> int:
    # & -- 1->0  子数组&的结果不会超过其中任意一个元素
    mx = max(nums)
    ans = cnt = 0
    for x in nums:
        if x == mx:
            cnt += 1
            ans = max(ans, cnt)
        else:
            cnt = 0
    return ans


def goodIndices(nums: List[int], k: int) -> List[int]:
    n = len(nums)
    ans = []
    dec = [1] * n
    # >=  i(k个)  <=
    for i in range(n-2, k, -1):
        if nums[i] <= nums[i+1]:
            dec[i] = dec[i+1] + 1
    inc = [1] * n
    for i in range(1, n-k):
        if inc[i-1] >= k and dec[i+1] >= k:
            ans.append(i)
        if nums[i-1] >= nums[i]:
            inc[i] += inc[i-1] + 1
        # else:
        #     inc = 1
    return ans

    # [2,1,1,1,3,4,1]
print(goodIndices([2, 1, 1, 1, 3, 4, 1], 2))

# Q1 https://leetcode.cn/problems/sort-the-people/solution/python-yi-xing-by-endlesscheng-xnvy/
# Q2 https://leetcode.cn/problems/longest-subarray-with-maximum-bitwise-and/solution/nao-jin-ji-zhuan-wan-by-endlesscheng-75dq/
# Q3 https://leetcode.cn/problems/find-all-good-indices/solution/d-by-endlesscheng-kya3/
# # Q4 https://leetcode.cn/problems/number-of-good-paths/solution/bing-cha-ji-by-endlesscheng-tbz8/
def numberOfGoodPaths(vals: List[int], edges: List[List[int]]) -> int:
    n = len(vals)
    g = [[] for _ in range(n)]
    for x,y in edges:
        g[x].append(y)
        g[y].append(x)
    
    fa = list(range(n))
    def find(x: int) -> int:
        if fa[x] != x:
            fa[x] = find(fa[x])
        return fa[x]

# size[x]表示x所处的连通块内节点值等于vals[x]的节点个数
    size = [1] * n 
# 单个节点也是一条合法路径
    ans = n
    for val_x, x in sorted(zip(vals, range(n))):
        #从小到大排序，val_x是当前可合并的连通块中最大节点值
        fx = find(x) # x所处集合的代表
        for y in g[x]:
            fy = find(y)
            if fy == fx or vals[fy] > val_x: 
                continue
            if vals[fy] == val_x:
                ans += size[fy] * size[fx]
                size[fx]+=size[fy]
            fa[fy] = fx #合并，小的挂到大的
    return ans

# 滑动窗口
def minimumRecolors(blocks: str, k: int) -> int:
    ans = cnt_w = blocks[:k].count('W') #统计第一个窗口白块的数量
    for in_, out in zip(blocks[k:], blocks):
        cnt_w += (in_=='W') - (out=='W')
        ans = min(ans, cnt_w)
    return ans