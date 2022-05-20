
import matplotlib.pyplot as plt
from sklearn import datasets
import numpy as np

class PCA:
    def __init__(self) -> None:
        self.no_component = 2

    def find_components(self, X):
        X = X - np.mean(X, axis=0) #Center the features

        cov = np.cov(X)
        e, v = np.linalg.eig(cov)

        e, v = np.real(e[:self.no_component]), np.real(v[:,:self.no_component])
        return e, v


data = datasets.load_iris()

pca = PCA()
e, v = pca.find_components(data['data'])

colors = {0: 'red', 1: 'blue', 2:'green'}
for i, d in enumerate(v):
    plt.scatter(d[0], d[1], c=colors[data['target'][i]])

plt.xlabel("Component-1")
plt.ylabel("Component-2")
plt.show()
