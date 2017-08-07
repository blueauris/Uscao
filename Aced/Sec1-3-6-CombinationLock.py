#!python3
# -*- coding: utf-8 -*-

## PROG: combo
import os
import random

filename="combo"
finname = filename+'.in'
foutname = filename+'-p.out'


#### Codes Start
def calculate():
    fin = open(finname, 'r')
    N = int(fin.readline())
    X = list(map(int, fin.readline().split() ))
    Y = list(map(int, fin.readline().split() ))
    print(N,X,Y)
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
    fout = open(foutname, 'w')
    fout.write( str(result) )
    fout.close()


def gendata():
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
    oriData = str(N)+'\n'+' '.join(L1)+'\n'+' '.join(L2)+'\n'
    return oriData

#### Codes End


#### Template codes start
def genin():
    ##生成 in文件
    fin = open(finname, 'w')
    genData=gendata()
    fin.write(genData)    
    fin.close()


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
    # basepath ="e:\\Code\\usaco\\PyCode"
    basepath = os.getcwd()
    os.chdir(basepath)
    if not(os.path.isfile(finname)):
       genin()

#    printin()
    calculate()
#    printout()
#### Template Codes End