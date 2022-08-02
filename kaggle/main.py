
import pandas as pd
import matplotlib.pyplot as plt

traindata = pd.read_csv("house_prices/data/train.csv")

y = traindata['SalePrice'].to_numpy()
x = traindata['GrLivArea'].to_numpy()

plt.scatter(x,y)
plt.show()


print(traindata.head())
#print(traindata.info())