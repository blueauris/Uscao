#!python3
# -*- coding: utf-8 -*-

## PROG: combo
import os
import random

filename="combo"
finname = filename+'.in'
os.chdir(os.getcwd())
fin = open(finname, 'w')

## 生成测试数据集
N= random.randint(1,100)
L1=[]
L2=[]

for i in range(0,3):
    x= random.randint(1,N)
    L1.append(str(x))
for i in range(0,3):
    x= random.randint(1,N)
    L2.append(str(x))
genData = str(N)+'\n'+' '.join(L1)+'\n'+' '.join(L2)+'\n'
##END

fin.write(genData)
fin.close()
