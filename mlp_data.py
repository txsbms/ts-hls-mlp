from keras.datasets import mnist

(X_train, y_train), (X_test, y_test) = mnist.load_data()
f = open("cppvars.dat", "w")

#print(len(X_train[1]) * len(X_train[1][0]))

for i in range(5000):
    for j in range(len(X_train[i])):
        for k in range(len(X_train[i][j])):
            f.write(str(X_train[i][j][k]) + "\n")
    f.write(str(y_train[i]) + '\n')
    