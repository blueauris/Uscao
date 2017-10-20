#!python3
# -*- coding: utf-8 -*-

## PROG: Ride
import os
import random

filename="Ride"
finname = filename+'.in'
os.chdir(os.getcwd())
fin = open(finname, 'w')

## 生成测试数据集
##Todo
genData =''
comet=''
n = random.randint(1,6)
for i in range(n):
    comet += chr(random.randint(0,25)+ord('A') )
genData += comet + '\n'

group = ''
n = random.randint(1,6)
for i in range(n):
    group += chr(random.randint(0,25)+ord('A') )
genData += group + '\n'
##END
fin.write(genData)
fin.close()

