# A 2048 Game
#
# Design: persude code
# Loop:
#   Read input from user
#   upate matrix based on input
#      input = left | right | up | down
#      move all the nonempty grids to the top
#          for each col: move col j to the top
#                        combine all numbers
#      generate a 2 or 4 in the empty grids
#   if cannot update again, FAILED
#   else if check 2048, WIN
#        else display matrix, continue

import random
import math


# global variable
N = 4
Matrix = [ [0 for i in range(N) ] for j in range(N)]

# init the matrix
def InitMatrix():
    tmpList = range(0, N*N)
    random.shuffle(tmpList)
    a = tmpList[0]
    b = tmpList[1]
    ai = a / N
    aj = a % N
    bi = b / N
    bj = b % N
    Matrix[ai][aj] = 2
    Matrix[bi][bj] = random.randint(1, 2) * 2

# check whether we have come to an endlock matrix
def IsDeadMatrix():
    for i in range(N):
        for j in range(N):
            if Matrix[i][j] == 0:
                return False

    for i in range(N):
        for j in range(N):
            if (i-1 >= 0 and Matrix[i][j] == Matrix[i-1][j]) or \
               (i+1 < N  and Matrix[i][j] == Matrix[i+1][j]) or \
               (j-1 >= 0 and Matrix[i][j] == Matrix[i][j-1]) or \
               (j+1 < N  and Matrix[i][j] == Matrix[i][j+1]):
                   return False
    return True

# check whether find 2048 in current matrix
def Make2048():
    for i in range(N):
        for j in range(N):
            if Matrix[i][j] == 2048:
                return True
    return False

# display matrix
def PrintMatrix():
    for i in range(N):
        for j in range(N):
            print Matrix[i][j],
        print ''

InitMatrix()
while True:
    PrintMatrix()
    ch = raw_input("please enter the a character:")
    if ch == "q" or ch == "Q":
        break;
    elif ch == "w" or ch == "W":
        break;
    elif ch == "s" or ch == "S":
        break;
    elif ch == "a" or ch == "A":
        break;
    elif ch == "d" or ch == "D":
        break;
    UpdateMatrix()
    if IsDeadMatrix() == True:
        print "FAILED"
        break
    elif Make2048() == True:
        print "WIN"
        break
    else:
        PrintMatrix()
