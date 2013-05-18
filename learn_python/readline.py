import numpy as np
from StringIO import StringIO

#extract the lines including threes to the new file
prefile=open("./line.txt","r")
postfile=open("./threes.txt","a")
alllines=prefile.readlines()
prefile.close()
for line in alllines:
	if int(line[-2])==2:
		postfile.write(line)
postfile.close()

#output the context in the file in the way of matrix
filename="./line.txt"
array = np.genfromtxt(filename,dtype=None,usecols=range(0,5),delimiter=",")
print array
print type(array)

#output the context in the new file in the way of matrix
filename3="./threes.txt"
array3 = np.genfromtxt(filename3, dtype = None, usecols = range(0,6), delimiter = ",")
print array3
print type(array3)
