#!python3
# -*- coding: utf-8 -*-

## PROG: QUE_NAME
import os
import random

filename="QUE_NAME"

finname = filename+'.in'
foutname = filename+'.outp'
result='Hello world'
print(result)

####主算法
fin = open(finname, 'r')
##TODO:







##TODOEND 
##结果写入 pout 文件
fin.close()
fout = open(foutname, 'w')
fout.write(result)
fout.close()
