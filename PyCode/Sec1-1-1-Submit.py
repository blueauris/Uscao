#!python3
# -*- coding: utf-8 -*-

## PROG: test
import os
import random

filename="test"
finname = filename+'.in'
foutname = filename+'-p.out'

####主算法
fin = open(finname, 'r')
source = fin.read()

a,b = map(int, source.split(' ') )
result = str(a + b)

####主算法END

##结果写入 pout 文件
fout = open(foutname, 'w')
fout.write(result)
fin.close()
fout.close()

