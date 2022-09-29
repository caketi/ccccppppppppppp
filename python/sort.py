def bubbleSort(nums: list) -> list:
    n = len(nums)
    for i in range(n-1):
        flag = False
        for j in range(n-i-1):
            if nums[j] > nums[j+1]:
                flag = True
                nums[j], nums[j+1] = nums[j+1], nums[j]
        if not flag:
            break
    return nums

def selectionSort(nums:list) -> list:
    n = len(nums)
    for i in range(n):
        cur_ind  = i
        for j in range(i+1, n):
            if nums[j] < nums[cur_ind]:
                cur_ind = j
        if cur_ind != i:
            nums[cur_ind], nums[i] = nums[i], nums[cur_ind]
    return nums

nums = [4, 3, 1, 0]
# print(bubbleSort(nums[::-1]))
print(selectionSort(nums))
