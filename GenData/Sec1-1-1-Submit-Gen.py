#!python3
# -*- coding: utf-8 -*-

## PROG: test
import os
import random

filename="test"
finname = filename+'.in'
os.chdir(os.getcwd())
fin = open(finname, 'w')
## ���ɲ������ݼ�
##Todo
a= random.randint(1,1024)
b= random.randint(1,1024)
genData = str(a)+' '+str(b)
##END
fin.write(genData)
fin.close()