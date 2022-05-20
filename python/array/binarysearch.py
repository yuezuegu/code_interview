

def binary(arr, target, start, end):
    if start >= end:
        return -1

    #Find median
    mid_ind = (start+end-1)//2
    median = arr[mid_ind]

    if target == median:
        return first_occur(arr, target, start, mid_ind+1) #Find the first occurance with another binary search
    elif target < median:
        return binary(arr, target, start=start, end=mid_ind)
    else:
        return binary(arr, target, start=mid_ind+1, end=end)


def first_occur(arr, target, start, end):
    if start == end-1:
        return start if arr[start] == target else -1

    mid_ind = (start+end-1) // 2 + 1
    median = arr[mid_ind]

    if median == target: # if midval == target, recurse mid:end
        if arr[mid_ind-1] != target:
            return mid_ind
        return first_occur(arr, target, start, mid_ind)
    else: # else recurse with start:mid
        return first_occur(arr, target, mid_ind+1, end)


import numpy as np
np.random.seed(0)


for t in range(1000):
    gt = np.random.randint(low=1, high=1000)
    arr = [0 for i in range(gt)] + [1 for i in range(1000-gt)]

    ret = no_consec(arr, 1, 0, len(arr))
    assert gt == ret, "{} \t {}".format(gt, ret)

for t in range(10000):
    arr = sorted(list(np.random.choice(range(1000), 500)))
    target = np.random.choice(range(1000), 500)[0]

    gt = -1
    for i, n in enumerate(arr):
        if n == target:
            gt = i
            break

    res = binary(arr, target, 0, len(arr))
    assert gt == res, "{} \t {}".format(gt, res)
