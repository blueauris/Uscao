#!python3
# -*- coding: utf-8 -*-

## PROG: wormhole
import os
import random

filename="wormhole"
finname = filename+'.in'
foutname = filename+'.outp'
result='Hello world'

#### Codes Start
def calculate():
    ####主算法
    ##TODO:
    print(result)






    ##END
#### Codes End



#### Template codes start
def genInFile():
    fin = open(finname, 'w')

    ## 生成测试数据集
    genData =''

    N = random.randint(1, 6)*2
    #print(N)
    genData += str(N)+'\n'
    for i in range(0, N):
        x = random.randint(1, 1000)
        y = random.randint(1, 1000)
        #print(x,y)
        genData += str(x)+' '+str(y)+'\n'

    #print(genData)
    fin.write(genData)
    fin.close()


def saveOutFile(result):
    ##结果写入 pout 文件
    fout = open(foutname, 'w')
    fout.write(result)
    fout.close()


if __name__ == '__main__':
##    basepath ="e:\\Code\\usaco\\PyCode"
    os.chdir(os.getcwd())
    if not(os.path.isfile(finname)):
       genInFile()

    calculate()
    saveOutFile(result)
#### Template Codes End