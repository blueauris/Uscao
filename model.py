#!python3
# -*- coding: utf-8 -*-

## PROG: QUE_NAME
import os
import random

filename="QUE_NAME"
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
    genData ='Hello'
    ##TODO:




    ##END
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