


import numpy as np


def dist(x1, x2):
    diff = x1 - x2
    return np.sqrt(np.matmul(diff, diff.transpose()))

#X: no_samples x no_features
def kmeans(X, K, max_no_iter):
    #initialize centers 
    centers = [X[k] for k in K]

    no_samples, no_feature = X.shape

    y_pred = [0 for i in range(no_samples)]
    
    iter_cnt = 0
    while iter_cnt < max_no_iter:
        #Assignments
        for i in range(no_samples):
            x = X[i]

            y_pred[i] = np.argmin([dist(x, centers[k]) for k in K])

        #Recalculate the centers
        centers = [np.zeros_like(X[0]) for k in range(K)]
        total_no = [0 for k in range(K)]
        for i in range(no_samples):
            center[y_pred[i]] += X[i]
            total_no[y_pred[i]] += 1

        center = [center[i]/total_no[i] for i in range(K)]

        iter_cnt += 1

    return centers









def merge_sorted(l1, l2):
    ptr1 = 0
    ptr2 = 0

    out = []
    while ptr1 < len(l1) or ptr2 < len(l2):
        num1 = l1[ptr1]
        num2 = l2[ptr2]

        if num1 < num2:
            out.append(num1)
            ptr1 += 1
        else:
            out.append(num2)
            ptr2 += 1

    while ptr1 < len(l1):
        out.append(l1[ptr1])
        ptr1 += 1

    while ptr2 < len(l2):
        out.append(l2[ptr2])
        ptr2 += 1

    return out

def mergesort(arr):
    arr_leaf = [[a] for a in arr]

    while len(arr_leaf)>1:
        i = 0
        while i < len(arr_leaf)-1:
            merged = merge_sorted(arr_leaf[i], arr_leaf[i+1]) 
            arr_leaf = arr_leaf[:i] + [merged] + arr_leaf[i+2:]
            i += 1

    return arr_leaf[0]