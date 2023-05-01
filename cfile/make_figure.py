import matplotlib.pyplot as plt

f = open('data.txt', 'r')

dimension = int(f.readline())
size = int(f.readline())

dataX = [0 for i in range(size)]
dataY = [0 for i in range(size)]

for i in range(size):
    dataX[i] = float(f.readline())
    dataY[i] = float(f.readline())

f.close()

figure = plt.axes()
plt.title("tmp")
plt.xlabel('x')
plt.ylabel('y')
figure.grid()
plt.xlim(-15.0,15.0)
plt.ylim(-15.0,15.0)
plt.scatter(dataX, dataY, s=5,color="blue")
plt.savefig('figure001.jpg')