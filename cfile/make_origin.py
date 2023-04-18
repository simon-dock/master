import numpy as np
import matplotlib.pyplot as plt
from sympy import primitive

def sigmoid(x):
    return 1/(1+np.exp(-x))

def der_sigmoid(x):
    return x*(1-x)

def squared_error(z, t):
    return (z-t)**2/2

#np.random.seed(20220512)


 
lr = 0.7
I, H, O = 3, 2, 1
dataNumber = 100

inputs = np.array(([1,0,0],[1,0,1],[1,1,0],[1,1,1]))
teachers = np.array([0,1,1,0])

hiddens = np.zeros(H)
output = np.zeros(O)

S = np.random.normal(0.0, 0.1, (I,H))
W = np.random.normal(0.0, 0.1, (H+1,O))

datalist = []

datalist.append(str(len(W)+len(S)*len(S[0]))+"\n")
datalist.append(str(dataNumber)+"\n")

for k in range(dataNumber):
    count = 0
    
    hiddens = np.zeros(H)
    output = np.zeros(O)

    S = np.random.normal(0.0, 0.1, (I,H))
    W = np.random.normal(0.0, 0.1, (H+1,O))

    while(1):

        i = np.random.randint(0,4)
        count += 1
        error = 0
        input = inputs[i]
        teacher = teachers[i]
        hiddens = np.dot(input, S)
        hiddens = sigmoid(hiddens)
        hiddens_tmp = np.concatenate([[1],hiddens])
        output = np.dot(hiddens_tmp,W)
        output = sigmoid(output)
        error = squared_error(output,teacher)
        r = (teacher - output)*output*(1-output)
        delta_w =  lr * r * hiddens_tmp
        r_dash =  r * W[1:].T* hiddens * (1-hiddens)
        delta_s =  lr * r_dash.T * input
        delta_w = delta_w.reshape(H+1,O)
        delta_s = delta_s.T
        W += delta_w
        S += delta_s 
        
        if count > 10000:
            break
    
    for i in range(len(W)):
        datalist.append(str(W[i][0])+"\n")
    for i in range(len(S)):
        for j in range(len(S[0])):
            if dataNumber - 1 == k and len(S) - 1 == i and len(S[0]) - 1 == j:
                datalist.append(str(S[i][j]))
            else:
                datalist.append(str(S[i][j])+"\n")
                
    print("finish " + str(k+1))
        

f = open('origin.txt', 'w')
f.writelines(datalist)
f.close()
