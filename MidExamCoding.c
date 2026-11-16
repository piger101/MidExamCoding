#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static const int EVERYTHING_OK = 0;
static const int POINTER_LIKE = 1;
static const int STRING_LIKE = 2;
static const int FLOAT_LIKE = 3;

int CheckSuspiciousIntArray(int a[], int n){
    //检查疑似指针
    for(int i=0;i<n;i++){
        if(a[i]<0x100000){continue;}
        int count=0;
        int has_bad_number=0;
        for(int j=0;j<n;j++){
            if(-0x10000<=a[i]-a[j]&&a[i]-a[j]<=0x10000){
                count+=1;
                if(
                    //#1_begin------------
                    a[i]%4!=0&&a[i] >= 0x100000          // <--第1空, 请填写一个适当的判断条件, 本行上方切勿插入空行
                    //#1_end==============
                ){
                    has_bad_number=1;
                    break;
                }
            }
        }
        if(count>=2&&has_bad_number==0){
            return i*4+POINTER_LIKE;
        }
    }
    //检查疑似字符串
    for(int i=0;i<n;i++){
        int count=0;
        for(int j=0;j<4;j++){
            int char_j=(a[i]>>(j*8))&0xff;
            //#2_begin------------
            count += ((char_j >= 32 && char_j <= 126) || char_j == 9 || char_j == 10) ? 1 : 0;                  // <--第2空, 请适当地更新count变量, 本行上方切勿插入空行
            //#2_end==============
        }
        if(count>=4){
            return i*4+STRING_LIKE;
        }
    }
    //检查疑似浮点
    int count=0;
    for(int i=0;i<n;i++){
        if(
            (a[i]&0x7fffffff)==0||
            //#3_begin------------
            ((a[i]&0x7fffffff)>>23) >=120&&((a[i]&0x7fffffff)>>23) <= 134  // <--第3空, 请适当地补全条件判断, 本行上方切勿插入空行
            //还可以写成：(a[i]&0x7fffffff) >= (120<<23) && (a[i]&0x7fffffff) <= (134<<23)
            //#3_end==============
        ){
            count++;
        }
    }
    if(count>=n){
        return FLOAT_LIKE;
    }else{
        return EVERYTHING_OK;
    }
}

//负责评测及展示结果的代码，可以不用完全理解
void CheckMemoryAndFormatResult(const void* mem,size_t size){
    int n=size/sizeof(int);
    assert((size_t)n*sizeof(int)==size);
    int a[n];
    memcpy(a,mem,size);
    printf("CheckSuspiciousIntArray({");
    for(int i=0;i<n;i++){
        if(i>0){printf(",");}
        printf("%d",a[i]);
    }
    printf("},%d) returned ",n);
    int ret=CheckSuspiciousIntArray(a,size/sizeof(int));
    if(ret==EVERYTHING_OK){
        printf("EVERYTHING_OK\n");
    }else if((ret&3)==POINTER_LIKE){
        printf("%d*4+POINTER_LIKE\n",ret>>2);
    }else if((ret&3)==STRING_LIKE){
        printf("%d*4+STRING_LIKE\n",ret>>2);
    }else if(ret==FLOAT_LIKE){
        printf("FLOAT_LIKE\n");
    }else{
        printf("bad value %d\n",ret);
    }
}

int main(){
    int pointers[]={1,2,3,0x4000fc,0x4000e0};
    CheckMemoryAndFormatResult(pointers,sizeof(pointers));
    char string[]="Hello world";
    CheckMemoryAndFormatResult(string,sizeof(string));
    float floats[]={1.5, -0.3, 99.0, -0.077777};
    CheckMemoryAndFormatResult(floats,sizeof(floats));
    int simple_ints[]={-7,42,65536,77};
    CheckMemoryAndFormatResult(simple_ints,sizeof(simple_ints));
    return 0;
}
