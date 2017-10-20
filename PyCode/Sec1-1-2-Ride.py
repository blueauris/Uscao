#!python3
# -*- coding: utf-8 -*-

## PROG: Ride
import os
import random

filename="Ride"
finname = filename+'.in'
foutname = filename+'-p.out'

####主算法 
fin = open(finname, 'r')
source = fin.read()

comet, group = source.split()
comet_code = 1
for ch in comet:
    comet_code = comet_code * (ord(ch)-ord('A')+1) %47
group_code = 1
for ch in group:
    group_code = group_code * (ord(ch)-ord('A')+1) %47
if comet_code == group_code:
   result ="GO"
else:
     result = "STAY"
####主算法END

##结果写入 pout 文件
fin.close()
fout = open(foutname, 'w')
fout.write(result)
fout.close()
