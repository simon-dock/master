from itertools import count
import math
import random
from re import A
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.animation import PillowWriter
#from matplotlib._version import get_versions as mplv

def cube():

    vector = [[0 for i in range(3)] for j in range(27)]

    cou = 0

    for aa in range(-1,2):
        for bb in range(-1,2):
            for cc in range(-1,2):
                vector[cou] = [aa,bb,cc]
                cou += 1

    return vector

def try4():

    vector = [[0 for i in range(3)] for j in range(4)]

    vector = [[1,1,1], [-1,-1,1], [1,-1,-1] , [-1,1,-1]]

    return vector

def cube_5():

    vector = [[0 for i in range(4)] for j in range(5)]

    vector = [[1,1,1,1], [-1,-1,1,1], [1,-1,-1, 1] , [-1,1,-1,1], [-1,1,1,-1]]

    return vector

def cube_6():

    vector = [[0 for i in range(5)] for j in range(6)]

    vector = [[1,1,1,1,1], [-1,-1,1,1,1], [1,-1,-1,1,1], [-1,1,-1,1,1], [-1,1,1,-1,1], [-1,1,1,1,-1]]

    return vector

def cube_7():

    vector = [[0 for i in range(6)] for j in range(7)]

    vector = [[1,1,1,1,1,1], [-1,-1,1,1,1,1], [1,-1,-1,1,1,1], [-1,1,-1,1,1,1], [-1,1,1,-1,1,1], [-1,1,1,1,-1,1], [-1,1,1,1,1,-1]]

    return vector

def cube_8():

    vector = [[0 for i in range(7)] for j in range(8)]

    vector = [[1,1,1,1,1,1,1], [-1,-1,1,1,1,1,1], [1,-1,-1,1,1,1,1], [-1,1,-1,1,1,1,1], [-1,1,1,-1,1,1,1], [-1,1,1,1,-1,1,1], [-1,1,1,1,1,-1,1], [-1,1,1,1,1,1,-1]]

    return vector

def cube_9():

    vector = [[0 for i in range(8)] for j in range(9)]

    vector = [[1,1,1,1,1,1,1,1], [-1,-1,1,1,1,1,1,1], [1,-1,-1,1,1,1,1,1], [-1,1,-1,1,1,1,1,1], [-1,1,1,-1,1,1,1,1], [-1,1,1,1,-1,1,1,1], [-1,1,1,1,1,-1,1,1], [-1,1,1,1,1,1,-1,1], [-1,1,1,1,1,1,1,-1]]

    return vector


def cube_l():

    vector = [[0 for i in range(3)] for j in range(27)]

    cou = 0

    for aa in range(-1,2):
        for bb in range(-1,2):
            for cc in range(-1,2):
                if bb == -1:
                    b = -3
                if bb == 1:
                    b = 3
                if bb == 0:
                    b=0
                vector[cou] = [aa,b,cc]
                cou += 1

    return vector
    

def straightline(dimensional, n):
    
    vector = [[0 for i in range(dimensional)] for j in range(n)]
    direction = [0 for i in range(dimensional)]
    a = [1, -1]
    
    for i in range(dimensional):
        vector[0][i] = round(random.uniform(-2.0, 2.0), 3)
        direction[i] = random.choice(a)
    
    for i in range(1, n):
        for j in range(dimensional):
            vector[i][j] = round(vector[i-1][j] + direction[j], 3)
        
    return vector

def circule():
    vector = [[0 for i in range(2)] for j in range(9)]

    PI = 3.14159265358979323846

    vector[8][0]= round(random.uniform(-2.0, 2.0), 3)
    vector[8][1]= round(random.uniform(-2.0, 2.0), 3)

    vector[0][0] = vector[8][0]+2.5
    vector[0][1] = vector[8][1]

    vector[1][0] = vector[8][0] + math.cos(PI/4)*2.5
    vector[1][1] = vector[8][1] + math.sin(PI/4)*2.5

    vector[2][0] = vector[8][0]
    vector[2][1] = vector[8][1]+2.5

    vector[3][0] = vector[8][0] - math.cos(PI/4)*2.5
    vector[3][1] = vector[8][1] + math.sin(PI/4)*2.5

    vector[4][0] = vector[8][0]-2.5
    vector[4][1] = vector[8][1]

    vector[5][0] = vector[8][0] - math.cos(PI/4)*2.5
    vector[5][1] = vector[8][1] - math.sin(PI/4)*2.5

    vector[6][0] = vector[8][0]
    vector[6][1] = vector[8][1]-2.5

    vector[7][0] = vector[8][0] + math.cos(PI/4)*2.5
    vector[7][1] = vector[8][1] - math.sin(PI/4)*2.5

    return vector


def heiix(n):
    vector = [[0 for i in range(3)] for j in range(n)]

    for i in range(n):
        vector[i][2] = (math.sqrt(2)/2)*i
        vector[i][0] = math.cos(vector[i][2])
        vector[i][1] = math.sin(vector[i][2])

    return vector