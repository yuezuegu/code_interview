

def swap(arr, i, j):
    tmp = arr[j]
    arr[j] = arr[i]
    arr[i] = tmp    

def quick_step(arr, start_ind, end_ind):
    pivot = arr[start_ind]

    i = start_ind+1
    j = end_ind

    while i < j:
        if arr[i] <= pivot:
            i += 1
        elif arr[j] > pivot:
            j -= 1
        else:
            swap(arr, i, j)

    if arr[j] < pivot:
        swap(arr, j, start_ind)

    return j

def quicksort(arr):
    indices = [(0, len(arr)-1)]

    while len(indices)>0:
        start_ind, end_ind = indices.pop(0)
        mid = quick_step(arr, start_ind, end_ind)

        if mid > start_ind + 1:
            indices.append((start_ind,mid-1))
        
        if mid < end_ind:
            indices.append((mid,end_ind))

import numpy as np 
np.random.seed(0)


l1 = list(np.random.choice(range(10000), 2000))
l2 = l1.copy()


quicksort(l1)
assert l1 == sorted(l2), "Mismatch: {}\n{}".format(l1, sorted(l2))