#!python3
# -*- coding: utf-8 -*-

## PROG: test
import os
import random

filename="test"
finname = filename+'.in'
foutname = filename+'-p.out'


#### Codes Start
def calculate():
    source = readin()
    a,b = map(int, source.split(' ') )
    result = str(a + b)
    saveout(result)


def gendata():
    ## 生成测试数据集
    a= random.randint(1,1024)
    b= random.randint(1,1024)
    oriData = str(a)+' '+str(b)
    return oriData

#### Codes End



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