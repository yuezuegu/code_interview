

from sklearn import datasets
from sklearn.model_selection import train_test_split
import numpy as np


classes = [0, 1]

def accuracy(y_true, y_pred):
    accuracy = np.sum(y_true == y_pred) / len(y_true)
    return accuracy

def entropy(y):
    entr = 0
    for c in classes:
        p = np.sum(y==c) / y.shape[0]
        if p > 0:
            entr += p*np.log2(p)
    return -1*entr

def information_gain(x,y):
    curr_entropy = entropy(y)

    lowest_entropy = curr_entropy
    best_thresh = None
    for thresh in np.unique(x):
        left_ind = np.where(x<=thresh)
        right_ind = np.where(x>thresh)
        left_entropy = entropy(y[left_ind])
        right_entropy = entropy(y[right_ind])

        child_entropy = len(left_ind)/len(x) * left_entropy + len(right_ind)/len(x) * right_entropy

        if child_entropy < lowest_entropy:
            lowest_entropy = child_entropy
            best_thresh = thresh
    gain = curr_entropy - lowest_entropy

    return gain, best_thresh


class Node:
    def __init__(self, feat_ind, threshold, parent) -> None:
        self.feat_ind = feat_ind
        self.threshold = threshold
        self.parent = parent
        self.left = None 
        self.right = None




class Tree:
    def __init__(self) -> None:
        pass




data = datasets.load_breast_cancer()
X, y = data.data, data.target

feat = 0

x = X[:,feat]
gain, best_thresh = information_gain(x,y)


exit()