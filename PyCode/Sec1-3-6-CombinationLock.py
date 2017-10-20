#!python3
# -*- coding: utf-8 -*-

## PROG: combo
import os
import random

filename="combo"
finname = filename+'.in'
foutname = filename+'-p.out'

####主算法 
fin = open(finname, 'r')
N = int(fin.readline())
X = list(map(int, fin.readline().split() ))
Y = list(map(int, fin.readline().split() ))
##print(N,X,Y)
fin.close()

delta=[0,0,0]
if(N>5):
    for i in range(3):
        low,high = (X[i], Y[i]) if (X[i] < Y[i]) else (Y[i], X[i])
        sub = high -low
        if 0<=sub<=5:
            delta[i] += 5-sub
        sub = N+low -high
        if 0<=sub<=5:
            delta[i] += 5-sub
    result = 5*5*5*2 - delta[0]*delta[1]*delta[2]             
else: 
    result = N*N*N
    
####主算法END

##结果写入 pout 文件
fout = open(foutname, 'w')
fout.write( str(result) )
fout.close()
