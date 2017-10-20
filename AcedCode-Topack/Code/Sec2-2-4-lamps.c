/*
ID: pallas21
LANG: C
TASK:lamps
*/

/*2-2-4-lamps.c
 *USACO solutions
 *Copyright (c) 2008-2012, BlueAuris
 *All rights reserved
 *UpdateDate :2011- 07- 09
 */

/*算法提要:
 *将灯的亮暗状态分别以1、0记录,则所有灯的状态可用一N位二进制数记录,称为状态值。
  将单只灯是否被操作分别记为1、0。考察灯的初态 ,接受操作与末态之间关系 满足按位异或运算规律 即 0^0=0 0^1=1 1^0=1 1^1=0
  记按钮1,2,3,4对应的操作分别为原子操作a,b,c,d。可知四项操作即为分别取一个N位二进制值与原状态数异或。
  以N=12为例,abcd对应操作数分别为 111111111111、101010101010、010101010101、100100100100
  可知连续操作类似加法运算,满足交换率和结合率。即 a+b =b+a  a+b+c = a+(b+c),等等
  记初始状态为 P,结束状态为Q,分别进行abcd四操作mnxy次,则满足 Q= P + m*a + n*b + x*c + y*d

 *可推导得以下特性：
  1：因P及abcd各操作具有周期性,最小周期分别为1、1、2、2、3,故Q也有周期性,为其公倍数6。即正常操作时,编号为M的灯泡 状态与M%6的灯泡相同。故只需研究操作对前六个灯的影响
  2：由运算特性知,同一原子操作两次等效于无操作 即 a+a = 0
  3：本题提供的操作中,a+b=c, b+c =a, c+a =b, a+b+c =0 
 *由特性2,可推知操作序列可归并,且与原子操作的次序无关。因此所有可能操作最终可归并等效为16种基本操作,又因特性3,结果状态可进一步简化为8种。即最终灯泡序列的状态只有8种,每状态的可能操作序列应为两种基本组合和在这两组合基础上拓展得到的操作组合（增加作用为零的操作组并乱序插入）。
  *16种基本操作和8种状态如下：
  a     &   bc      ----    000000
  ab d &   cd       ----    001110
    b   &  a c      ----    010101
       d &  abcd    ----    011011
   a  d &    bcd    ----    100100
   ab   &     c     ----    101010
    b d &  a cd     ----    110001
          &  abc    ----    111111

  *算法：
  1.以结构体数组形式记录所有状态及其对应操作
  2.读入数据。判断亮灭是否矛盾。
  3.判别是否为有效状态
  4.如为有效状态,判别操作步数是否可以达到。
  若读入步数大于基础步数,且差>=2,则此差必然能表示为2*m+3*n的形式,即m个a+a和n个a+b+c的叠加。读入步数能等效到基础步数,状态可达到。当读入步数<基础步数,或读入步数减基础步数的差仅为1时,读入步数就不能等效到基础步数。若同一状态的所有基础步数都无法达到,则此状态无法得到。
  5.输出
 */
 
#include <stdio.h>
// global constant
#define N  100

// global variable
int caseN;
int caseC;
int LampOn[7] = {0};            //标记为亮的灯的位置,首位留空
int LampOff[7] = {0};           //标记为灭的灯的位置,首位留空

struct pat
{
    int state[7];    //六个灯的状态,首位留空
    int op[2];       //相应基本操作中原子操作的数量
} ;
struct pat LightPat[8] = {        //8个最终状态及其原子操作的数量
{ {0,0,0,0,0,0,0},{1,2} },
{ {0,0,0,1,1,1,0},{2,3} },
{ {0,0,1,0,1,0,1},{1,2} },
{ {0,0,1,1,0,1,1},{1,4} },
{ {0,1,0,0,1,0,0},{2,3} },
{ {0,1,0,1,0,1,0},{1,2} },
{ {0,1,1,0,0,0,1},{2,3} },
{ {0,1,1,1,1,1,1},{0,3} }
};

int ansAmount;       //解的个数
int ansIndex[9];    //解的位置

// process functions
int getData();
int calculate();
int printAns();
int shutdown();

// tool functions
int isPatFit(int);          //判别所给状态能否匹配现有模式
int isReachable(int,int);  //判别所给步数能否实现


//----------------------main function--------------//
int main ()
{
    getData();
    calculate();
//    testScene();
    printAns();
    return 0;
}
//----------------------main function ends--------//


//--- process functions --------------------------//
int getData()
{
    int digit = 0;
    FILE *fin;
    fin  = fopen ("lamps.in", "r");
    fscanf(fin, "%d%*c", &caseN);
    fscanf(fin, "%d%*c", &caseC);
    while(1){
        fscanf(fin, "%d", &digit);
        if(digit == -1) break;
        digit %= 6;
        digit = (digit ==0)?6:digit;
        LampOn[digit] = 1;
    }
    fscanf(fin, "%*c");
    while(1){
        fscanf(fin, "%d", &digit);
        if(digit == -1) break;
        digit %= 6;
        digit = (digit ==0)?6:digit;
        LampOff[digit] = 1;
    }
    fclose(fin);
    return 0;
}

int calculate()
{
    int i = 0;
    for(i=1; i<=6; ++i){
        if( LampOn[i] ==1 & LampOff[i] == 1){
            ansAmount = 0;
            return 0;
        }
    }
    ansAmount = 0;
    for( i=0; i<8; ++i){
        if( isPatFit(i) ){
            if( isReachable(caseC, i) ){
//              printf("index = %d\n",i);
                ++ansAmount;
                ansIndex[ansAmount] = i;
            }
       }
    }
    return 0;
}

int printAns()
{
    int i,j,k,ch,ans;
    FILE *fout;
    fout = fopen ("lamps.out", "w");

    if( ansAmount == 0 ){
        fprintf(fout,"IMPOSSIBLE\n");
    }
    
    for( i=1; i<=ansAmount; ++i){
        ans = ansIndex[i];
//        printf("ans = %d      ",ans);
        for( j=1; j<=caseN; ++j){
            k =(j%6==0?6:j%6);
            ch = LightPat[ans].state[k];
            fprintf(fout,"%d",ch);
        }
        fprintf(fout,"\n");
    }
        
    fclose(fout);
    return 0;
}

//--- process functions end-----------------------//

//--- tool functions -----------------------------//
int isPatFit(int index)
{
    int i;
    int result = 1;
    for( i=1; i<7; ++i){
        if(LightPat[index].state[i] == 0 ){
            if( LampOn[i] == 1 ){
                result = 0;
                break;
            }
        }
        else{
            if( LampOff[i] == 1 ){
                result = 0;
                break;
            }
        }
    }
    return result;
}

int isReachable(int c, int index)
{
    int c1,c2;
    c1 = LightPat[index].op[0];
    c2 = LightPat[index].op[1];
    if (c<c1) return 0;
    if( c==c1 || c==c2 ||(c-c1)>=2 || (c-c2)>=2 ){
        return 1;
    }
    else return 0;
}
//---tool functions end---------------------------//


