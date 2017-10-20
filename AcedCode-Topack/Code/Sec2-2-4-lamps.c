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

/*�㷨��Ҫ:
 *���Ƶ�����״̬�ֱ���1��0��¼,�����еƵ�״̬����һNλ����������¼,��Ϊ״ֵ̬��
  ����ֻ���Ƿ񱻲����ֱ��Ϊ1��0������Ƶĳ�̬ ,���ܲ�����ĩ̬֮���ϵ ���㰴λ���������� �� 0^0=0 0^1=1 1^0=1 1^1=0
  �ǰ�ť1,2,3,4��Ӧ�Ĳ����ֱ�Ϊԭ�Ӳ���a,b,c,d����֪���������Ϊ�ֱ�ȡһ��Nλ������ֵ��ԭ״̬�����
  ��N=12Ϊ��,abcd��Ӧ�������ֱ�Ϊ 111111111111��101010101010��010101010101��100100100100
  ��֪�����������Ƽӷ�����,���㽻���ʺͽ���ʡ��� a+b =b+a  a+b+c = a+(b+c),�ȵ�
  �ǳ�ʼ״̬Ϊ P,����״̬ΪQ,�ֱ����abcd�Ĳ���mnxy��,������ Q= P + m*a + n*b + x*c + y*d

 *���Ƶ����������ԣ�
  1����P��abcd����������������,��С���ڷֱ�Ϊ1��1��2��2��3,��QҲ��������,Ϊ�乫����6������������ʱ,���ΪM�ĵ��� ״̬��M%6�ĵ�����ͬ����ֻ���о�������ǰ�����Ƶ�Ӱ��
  2������������֪,ͬһԭ�Ӳ������ε�Ч���޲��� �� a+a = 0
  3�������ṩ�Ĳ�����,a+b=c, b+c =a, c+a =b, a+b+c =0 
 *������2,����֪�������пɹ鲢,����ԭ�Ӳ����Ĵ����޹ء�������п��ܲ������տɹ鲢��ЧΪ16�ֻ�������,��������3,���״̬�ɽ�һ����Ϊ8�֡������յ������е�״ֻ̬��8��,ÿ״̬�Ŀ��ܲ�������ӦΪ���ֻ�����Ϻ���������ϻ�������չ�õ��Ĳ�����ϣ���������Ϊ��Ĳ����鲢������룩��
  *16�ֻ���������8��״̬���£�
  a     &   bc      ----    000000
  ab d &   cd       ----    001110
    b   &  a c      ----    010101
       d &  abcd    ----    011011
   a  d &    bcd    ----    100100
   ab   &     c     ----    101010
    b d &  a cd     ----    110001
          &  abc    ----    111111

  *�㷨��
  1.�Խṹ��������ʽ��¼����״̬�����Ӧ����
  2.�������ݡ��ж������Ƿ�ì�ܡ�
  3.�б��Ƿ�Ϊ��Ч״̬
  4.��Ϊ��Ч״̬,�б���������Ƿ���Դﵽ��
  �����벽�����ڻ�������,�Ҳ�>=2,��˲��Ȼ�ܱ�ʾΪ2*m+3*n����ʽ,��m��a+a��n��a+b+c�ĵ��ӡ����벽���ܵ�Ч����������,״̬�ɴﵽ�������벽��<��������,����벽�������������Ĳ��Ϊ1ʱ,���벽���Ͳ��ܵ�Ч��������������ͬһ״̬�����л����������޷��ﵽ,���״̬�޷��õ���
  5.���
 */
 
#include <stdio.h>
// global constant
#define N  100

// global variable
int caseN;
int caseC;
int LampOn[7] = {0};            //���Ϊ���ĵƵ�λ��,��λ����
int LampOff[7] = {0};           //���Ϊ��ĵƵ�λ��,��λ����

struct pat
{
    int state[7];    //�����Ƶ�״̬,��λ����
    int op[2];       //��Ӧ����������ԭ�Ӳ���������
} ;
struct pat LightPat[8] = {        //8������״̬����ԭ�Ӳ���������
{ {0,0,0,0,0,0,0},{1,2} },
{ {0,0,0,1,1,1,0},{2,3} },
{ {0,0,1,0,1,0,1},{1,2} },
{ {0,0,1,1,0,1,1},{1,4} },
{ {0,1,0,0,1,0,0},{2,3} },
{ {0,1,0,1,0,1,0},{1,2} },
{ {0,1,1,0,0,0,1},{2,3} },
{ {0,1,1,1,1,1,1},{0,3} }
};

int ansAmount;       //��ĸ���
int ansIndex[9];    //���λ��

// process functions
int getData();
int calculate();
int printAns();
int shutdown();

// tool functions
int isPatFit(int);          //�б�����״̬�ܷ�ƥ������ģʽ
int isReachable(int,int);  //�б����������ܷ�ʵ��


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


