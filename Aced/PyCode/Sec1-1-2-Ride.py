#!python3
# -*- coding: utf-8 -*-

## PROG: Ride
import os
import random

filename="Ride"
finname = filename+'.in'
foutname = filename+'-p.out'


#### Codes Start
def calculate():
    ####主算法
    source = readin()
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
    saveout(result)



def gendata():
    ## 生成测试数据集
    oriData =''

    comet=''
    n = random.randint(1,6)
    for i in range(n):
        comet += chr(random.randint(0,25)+ord('A') )
    oriData += comet + '\n'

    group = ''
    n = random.randint(1,6)
    for i in range(n):
        group += chr(random.randint(0,25)+ord('A') )
    oriData += group + '\n'

    return oriData



#### Codes End
####
#### Template codes start
def genin():
    ##生成 in文件
    fin = open(finname, 'w')
    data = gendata()
    fin.write(data)
    fin.close()

def readin():
    ##读入数据
    fin = open(finname, 'r')
    data = fin.read()
    fin.close()
    return data

def saveout(result):
    ##结果写入 pout 文件
    fout = open(foutname, 'w')
    fout.write(result)
    fout.close()

def printin():
    ##显示 in文件
    fin = open(finname, 'r')
    print("====",finname,":")
    print (fin.read())
    print("====\n")
    fin.close()

def printout():
    ##显示 outp文件
    fout = open( foutname, 'r')
    print("\n====",foutname,":")
    print (fout.read())
    print("====")
    fout.close()


if __name__ == '__main__':
    basepath ="e:\\Code\\usaco\\PyCode"
    os.chdir(basepath)

    if not(os.path.isfile(finname)):
       genin()

    printin()
    calculate()
    printout()
#### Template Codes End