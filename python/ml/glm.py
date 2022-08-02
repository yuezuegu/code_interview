import numpy as np
import matplotlib.pyplot as plt

import torch
import math
import torch.nn as nn

torch.random.manual_seed(0)
np.random.seed(0)

def gaussian(x, mu, sigma):
    if not isinstance(x, torch.Tensor):
        x = torch.tensor(x, dtype=torch.float32)

    return torch.exp(-0.5*torch.pow( (x-mu)/sigma ,2)) / (math.sqrt(2*math.pi))*sigma

def bernoulli(x, p, sigma):
    if not isinstance(x, torch.Tensor):
        x = torch.tensor(x, dtype=torch.float32)

    return torch.pow(p, x) * torch.pow(1-p, 1-x)    

def logit_func(x):
    if not isinstance(x, torch.Tensor):
        x = torch.tensor(x, dtype=torch.float32)
    return torch.log(x / (1-x))

def logistic_func(x):
    if not isinstance(x, torch.Tensor):
        x = torch.tensor(x, dtype=torch.float32)
    return 1. / ( 1 + torch.exp(-x) )     


def identity(x):
    return x

inverse_funcs = {
    torch.log: torch.exp,
    torch.exp: torch.log,
    logit_func: logistic_func,
    logistic_func: logit_func,
    identity: identity
}

class LinearModel(nn.Module):
    def __init__(self, no_features) -> None:
        super().__init__()

        self.weights = torch.normal(mean=0, std=0.1, size=(no_features+1,1))

    def forward(self, x):
        if not isinstance(x, torch.Tensor):
            x = torch.tensor(x, dtype=torch.float32)

        x_ = torch.concat([x, torch.ones_like(x)], dim=1)  
        return torch.matmul(x_, self.weights)

    def least_square(self, x, y):
        if not isinstance(x, torch.Tensor):
            x = torch.tensor(x, dtype=torch.float32)
        if not isinstance(y, torch.Tensor):
            y = torch.tensor(y, dtype=torch.float32)

        x_ = torch.concat([x, torch.ones_like(x)], dim=1)  
        x_T = torch.transpose(x_, 0, 1)
        x_inv = torch.linalg.inv(torch.matmul(x_T,x_))
        self.weights = torch.matmul(torch.matmul(x_inv, x_T), y)

    def plot(self, x_range):
        x = np.linspace(x_range[0], x_range[1], num=100).reshape([-1,1])
        y = self(x)
        plt.plot(x, y.detach().numpy(), color="tab:red")
        plt.show()        


# See https://towardsdatascience.com/generalized-linear-models-9cbf848bb8ab
class GLM(nn.Module):
    def __init__(self, no_features, link_func, distrib_func, lr) -> None:
        super().__init__()

        self.weights = nn.Parameter(torch.normal(mean=0, std=0.1, size=(no_features+1,1)), requires_grad=True)
        self.link_func = link_func
        self.linkfn_inv = inverse_funcs[self.link_func]
        self.distrib_func = distrib_func

        self.optimizer = torch.optim.SGD(self.parameters(), lr=lr)

    def forward(self, x):
        if not isinstance(x, torch.Tensor):
            x = torch.tensor(x, dtype=torch.float32)

        x_ = torch.concat([x, torch.ones_like(x)], dim=1)
        z = torch.matmul(x_, self.weights)
        mu = self.linkfn_inv(z)
        return mu

    def probs(self, x, y):
        mu = self(x)
        sigma = 1.
        return self.distrib_func(y, mu, sigma)

    def maximum_likelihood(self, x, y):
        p = self.probs(x, y)
        return torch.sum(-torch.log(p))

    def fit(self, x, y, no_steps):
        for i in range(no_steps):
            self.optimizer.zero_grad()

            loss = self.maximum_likelihood(x, y)
            print("loss: {}".format(loss.item()))
            loss.backward()

            self.optimizer.step()

    def plot(self, x_range):
        x = np.linspace(x_range[0], x_range[1], num=100).reshape([-1,1])
        mu = self(x)
        plt.plot(x, mu.detach().numpy(), color="tab:red")
        plt.show()

def test_least_square():
    x = np.random.uniform(low=-1, high=2, size=(100,1))
    y = np.random.normal(loc=x, scale=0.5)

    plt.title("Least Square")
    plt.xlim([np.min(x), np.max(x)])
    plt.ylim([np.min(y), np.max(y)])
    plt.scatter(x, y)

    lm = LinearModel(no_features=1)
    lm.least_square(x, y)

    lm.plot([np.min(x), np.max(x)])

def test_identity():
    x = np.random.uniform(low=-1, high=2, size=(100,1))
    y = np.random.normal(loc=x, scale=0.5)

    plt.title("Maximum Likelihood - Identity")
    plt.xlim([np.min(x), np.max(x)])
    plt.ylim([np.min(y), np.max(y)])
    plt.scatter(x, y)

    link_func = identity
    distrib_func = gaussian
    glm = GLM(no_features=1, link_func=link_func, distrib_func=distrib_func, lr=1e-3)
    glm.fit(x, y, no_steps=100)

    glm.plot([np.min(x), np.max(x)])

def test_logarithmic():
    x = np.random.uniform(low=-1, high=2, size=(100,1))
    y = np.random.normal(loc=np.exp(x), scale=0.5)

    plt.title("Maximum Likelihood - Exponential")
    plt.xlim([np.min(x), np.max(x)])
    plt.ylim([np.min(y), np.max(y)])
    plt.scatter(x, y)

    link_func = torch.log
    distrib_func = gaussian
    glm = GLM(no_features=1, link_func=link_func, distrib_func=distrib_func, lr=1e-4)
    glm.fit(x, y, no_steps=100)

    glm.plot([np.min(x), np.max(x)])

def test_logistic():
    x = np.random.uniform(low=-2, high=2, size=(100,1))
    y = np.where(x<np.random.normal(loc=0, scale=0.2, size=x.shape), np.zeros_like(x), np.ones_like(x))

    plt.title("Maximum Likelihood - Logistic")
    plt.xlim([np.min(x), np.max(x)])
    plt.ylim([np.min(y), np.max(y)])
    plt.scatter(x, y)

    link_func = logit_func
    distrib_func = bernoulli
    glm = GLM(no_features=1, link_func=link_func, distrib_func=distrib_func, lr=1e-3)
    glm.fit(x, y, no_steps=100)

    glm.plot([np.min(x), np.max(x)])

if __name__=="__main__":
    test_identity()
    test_least_square()
    test_logarithmic()
    test_logistic()

