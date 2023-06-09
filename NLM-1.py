from itertools import count
import math
import random
from re import A
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.animation import PillowWriter
#from matplotlib._version import get_versions as mplv
import makeData
import numpy as np
import copy



def initialize(dimensional, n):
    
    vector = [[0 for i in range(dimensional)] for j in range(n)]
    
    for i in range(n):
        for j in range(dimensional):
            vector[i][j] = round(random.uniform(-5.0, 5.0), 3)
            
    return vector

def function(x,y):# N次元　ｄ次元のデータのＥを求める
    
    n = len(x)
    p = [0 for i in range(2)]
    q = [0 for i in range(2)]
    sum_a = 0.0
    sum_b = 0.0
    
    for i in range(n):
        for j in range(i+1, n):
            p[0] = x[i]
            p[1] = x[j]
            dist_d = distance(p)
            q[0] = y[i]
            q[1] = y[j]
            dist_l = distance(q)
            
            sum_a += dist_d
            
            sum_b += ((dist_d - dist_l) ** 2) / dist_d
    
    return sum_b / sum_a



def distance(p):# p = [x....N],[x....N]の２個の点、N次元のデータの距離を求める
    
    dimensional = len(p[0])
    ans = [0]*dimensional
    sum = 0.0

    p[0] = np.array(p[0])
    p[1] = np.array(p[1])

    return np.linalg.norm(p[0]-p[1])
"""
    for i in range(dimensional):
        for j in range(2):
            if j == 0:
                ans[i] = p[j][i]
            else:
                ans[i] -= p[j][i]
        sum += ans[i]**2
        
    return math.sqrt(sum)
"""



def autodifferen(func, x, y):#自動偏微分
    
    h = 0.00001
    
    n = len(y)
    dimensional = len(y[0])
    tmp = [[0 for i in range(dimensional)] for j in range(n)]
    ans = [0] * (n*dimensional)
    count = 0
    
    """for i in range(n):
       for j in range(dimensional):
          tmp[i][j] = y[i][j]
"""
    tmp = copy.deepcopy(y)
    
    for i in range(n):
        for j in range(dimensional):
             tmp[i][j] = y[i][j] + h
             ans[count] = differential(func, x, y, tmp, h)
             tmp[i][j] = y[i][j]
             count += 1
    
    return ans


def differential(func, x, y, tmp, h):#微分
    
    fx = (func(x, tmp) - func(x, y)) / h
     
    return fx


def extreme(x, y):#最急降下法

    print(x)
    print(y)
    
    a = 10
    esp = 1.e-8#helix 4 #circle 8 stl 5
    ess = 1.e-15#helix 7 #circle 10
    err = 0.0
    tmp = 0.0
    
    nn = 0
    m = 100000

    
    #plt.xlim(-10,10)
    #plt.ylim(-10,10)
    
    n = len(y)
    dimensional = len(y[0])
    
    ims = []
    ytmps = []
    xtmps = []
    while True:
        nn += 1
        dy = autodifferen(function, x, y)
        count = 0
        for i in range(n):
            for j in range(dimensional):
                y[i][j] -= a * dy[count]

                if count % 2 == 0:
                    xtmp = y[i][j]
                    xtmps.append(xtmp)
                else:
                    ytmp = y[i][j]
                    ytmps.append(ytmp)
                count += 1
        
        if nn % 15 == 0:#helix 30 circle 10 stl 100
            im = plt.scatter(xtmps, ytmps, c="blue")
            ims.append([im])
        ytmps = []
        xtmps = []

        tmp = err
        err = abs(function(x,y))
        print(nn,err)
        if nn>m:
            break
        if err < esp:
            break
        if nn != 0 and abs(tmp - err) < ess:
            break
    
    
    
    return x, y, ims


n = 30
dimensional = 3
i_d = 2
#x0 = straightline(dimensional, n)
#x0 = circule() #n=9
#x0 = makeData.heiix(n) #n=15
#x0 = try4() #n=4
#x0 = cube()#n=27
#x0 = cube_5()
x0 = makeData.cube_9()

n = len(x0)
dimensional = len(x0[0])
y0 = initialize(i_d, n)
#y0 = [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0]
fig = plt.figure()
p = extreme(x0, y0)

print(p[0])

ans_x = initialize(1, n)
ans_y = initialize(1, n)

for i in range(len(p[1])):
    for j in range(len(p[1][0])):
        p[1][i][j] = round(p[1][i][j],4)
        if j == 0:
            pass
            #ans_x[i] = p[1][i][j]
        else:
            pass
            #ans_y[i] = p[1][i][j]

                
    
    print(p[1][i])

ani = animation.ArtistAnimation(fig, p[2], interval=1, repeat_delay=1000)
plt.show()
ani.save('cube9_004.gif',writer='imagemagick')




