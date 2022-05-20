








def twosum(arr, target):
    arr_sorted = sorted(arr)
    unique = set()

    id1 = 0
    id2 = len(arr)-1

    while id1 < id2:
        val1 = arr_sorted[id1]
        val2 = arr_sorted[id2]

        if val1 + val2 == target:
            t = (val1, val2) if val1 < val2 else (val2, val1)
            if t not in unique:
                unique.add(t)
            id1 += 1
            id2 -= 1
        elif val1 + val2 > target:
            id2 -= 1
        else:
            id1 += 1

    return unique 


import numpy as np
np.random.seed(0)

arr_len = 1000
target = 0
arr = np.random.choice(range(-100,100), arr_len)


unique = set()
cnt = 0
for i in range(arr_len):
    val1 = arr[i]
    for j in range(i+1, arr_len):
        val2 = arr[j]

        if val1 + val2 == target:
            t = (val1, val2) if val1 < val2 else (val2, val1)

            if  t not in unique:
                unique.add(t)

res = twosum(arr, target)
print(res)
assert sorted(unique, key=lambda x: x[0]) == sorted(res, key=lambda x: x[0])


