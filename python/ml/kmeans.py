




from sklearn.datasets import make_blobs

import matplotlib
import matplotlib.pyplot as plt
plt.ion()

import numpy as np 

np.random.seed(123)

colors = ["#4EACC5", "#FF9C34", "#4E9A06", "m"]

def euclidean(x1, x2):
    diff = x1-x2
    return np.sqrt(np.matmul(diff, diff.transpose()))

def kmeans(X, no_clusters, no_iter):
    no_samples, no_features = X.shape

    Vmean = X[np.random.choice(range(no_samples), no_clusters, replace=False)]
    y_pred = np.zeros((no_samples,)).astype(int)

    iter_cnt = 0
    while iter_cnt < no_iter:
        for i in range(no_samples):
            x = X[i,:]
            
            dist = []
            for c in range(no_clusters):
                dist.append(euclidean(x, Vmean[c,:]))

            y_pred[i] = np.argmin(dist)

        plot(X, y_pred, centers=Vmean, iter=iter_cnt)

        Vmean = np.zeros((no_clusters, no_features))
        tot_no = [0 for i in range(no_clusters)]
        for i in range(no_samples):
            x = X[i,:]

            Vmean[y_pred[i]] += x
            tot_no[y_pred[i]] += 1
        
        for c in range(no_clusters):
            Vmean[c] = Vmean[c] / tot_no[c]

        iter_cnt += 1

def kmeans_vectorized(X, no_clusters, no_iter):
    no_samples, no_features = X.shape

    Vmean = X[np.random.choice(range(no_samples), no_clusters, replace=False)]

    iter_cnt = 0
    while iter_cnt < no_iter:
        X_ = np.repeat(np.expand_dims(X, 1), no_clusters, axis=1)
        diff = X_ - Vmean
        y_pred = np.argmin(np.sum(np.power(diff, 2), axis=2), axis=1)

        plot(X, y_pred, centers=Vmean, iter=iter_cnt)

        Vmean = np.array([np.mean(X[np.where(y_pred==c), :], axis=1).squeeze() for c in range(no_clusters)])

        iter_cnt += 1

def plot(X, y, centers=None, iter=0):
    plt.clf()

    col = [colors[y[i]] for i in range(X.shape[0])]

    plt.scatter(X[:, 0], X[:, 1], c=col, marker=".", s=10)

    if centers is not None:
        plt.scatter(centers[:, 0], centers[:, 1], c="b", s=50)

    plt.title("iter {}".format(iter))
    plt.xticks([])
    plt.yticks([])
    plt.show()
    plt.pause(1)
    
X, y_true = make_blobs(
    centers=3, n_samples=500, n_features=2, shuffle=True, random_state=40
)

kmeans_vectorized(X, 3, 5)
