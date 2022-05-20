




def merge_two_sorted(list1, list2):
    ind1 = 0
    ind2 = 0

    out_list = []
    while ind1 < len(list1) or ind2 < len(list2):
        if ind1 == len(list1):
            out_list.append(list2[ind2])
            ind2 += 1
        elif ind2 == len(list2):
            out_list.append(list1[ind1])
            ind1 += 1
        elif list1[ind1] < list2[ind2]:
            out_list.append(list1[ind1])
            ind1 += 1
        else:
            out_list.append(list2[ind2])
            ind2 += 1
    return out_list

def mergesort(l):
    l_div = [[n] for n in l] #Create of list of lists that contain the numbers one by one

    while len(l_div) > 1: #Repeat as long as there are more than two sublists
        ind = 0
        while ind < len(l_div)-1:
            merged = merge_two_sorted(l_div[ind], l_div[ind+1])
            l_div.pop(ind) #Remove l_div[ind]
            l_div.pop(ind) #Remove l_div[ind+1] (indices are decreased because of the previous pop)
            l_div.insert(ind, merged)
            ind += 1

    return l_div[0]


import numpy as np 


l = np.random.choice(range(100), 20)

out = mergesort(l)

print(out)