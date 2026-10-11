#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "SqlList.h"

extern Status CreatList(SqList *L);
extern void PrintList(SqList *L);
extern Status Union(SqList La, SqList Lb, SqList *Lc);
extern Status Intersection(SqList La, SqList Lb, SqList *Lc);
extern Status Difference(SqList La, SqList Lb, SqList *Lc);
extern Status Complement(SqList La, SqList *Lc);
extern void creatMenu();

int main(){
    int choice = 1;
    SqList L1, L2, result;
    L1=InitList();
    L2=InitList();
    result=InitList();
    
    while(1){
        creatMenu();
        if(scanf("%d",&choice) != 1){
            while(getchar() != '\n'){}
            printf("输入非法，请重新输入。\n");
            continue;
        }
        while(getchar() != '\n'){}

        switch(choice){
        case 1:
            ClearList(&L1);                       
            printf("请输入集合A的元素（小写字母，回车结束）:");
            CreatList(&L1);
            printf("A=");
            PrintList(&L1);
            break;
        case 2:
            ClearList(&L2);                       
            printf("请输入集合B的元素（小写字母，回车结束）:");
            CreatList(&L2);
            printf("B=");
            PrintList(&L2);
            break;
        case 3:
            Union(L1, L2, &result);
            printf("结果为:");
            PrintList(&result);
            ClearList(&result);
            break;
        case 4:
            Intersection(L1, L2, &result);
            printf("结果为:");
            PrintList(&result);
            ClearList(&result);
            break;
        case 5:
            Difference(L1, L2, &result);
            printf("结果为:");
            PrintList(&result);
            ClearList(&result);
            break;
        case 6:
            Difference(L2, L1, &result);
            printf("结果为:");
            PrintList(&result);
            ClearList(&result);
            break;
        case 7:
            Complement(L1, &result);
            printf("结果为:");
            PrintList(&result);
            ClearList(&result);
            break;
        case 8:
            Complement(L2, &result);
            printf("结果为:");
            PrintList(&result);
            ClearList(&result);
            break;
        case 9:
            printf("程序退出\n");
            DestroyList(&L1);
            DestroyList(&L2);
            DestroyList(&result);
            return OK;
            break;
        default:
            printf("输入非法，请重新输入。\n");
            break;
        }
    }
    return OK;
}

void creatMenu(){
    printf("=======开始菜单=======\n");
    printf("1.构建集合A\n");
    printf("2.构建集合B\n");
    printf("3.求A、B的并集\n");
    printf("4.求A、B的交集\n");
    printf("5.求A与B的差集\n");
    printf("6.求B与A的差集\n");
    printf("7.求A的补集\n");
    printf("8.求B的补集\n");
    printf("9.退出程序\n");
    printf("======================\n");
    printf("请输入数字:");
}

Status CreatList(SqList *La){
    int c;
    SqList L = InitList();

    while((c = getchar()) != '\n'){    //逐个获取stdio缓冲区的字符，缓冲区无残留
        const char universe[27] = "abcdefghijklmnopqrstuvwxyz";
        int found1 = 0;
        int ufound2 = 1;
        
        for(int i=0 ; i<26 ; i++){    //过滤不合法元素
            if(c == universe[i]){
                found1 = 1;  //是合法元素
                break;
            }
        }

        if(found1){
            for(int i=0 ; i<L.length ; i++){  //过滤重复元素
                if(c == L.elem[i]){
                    ufound2 = 0;   //未发现，为新元素
                    break;
                }
            }

            if(ufound2) ListInsert(&L , L.length+1 , c);
        }
    }
    
    if(La->elem != NULL) DestroyList(La);
    *La = L;
    return OK;
}

void PrintList(SqList *La){
    if(La->length == 0) 
        printf("空集\n");
    else{
        printf("{");
        for(int i=0 ; i<La->length-1 ; i++)
            printf("%c,",La->elem[i]);
        printf("%c}\n",La->elem[La->length-1]);
    }
}

Status Union(SqList La, SqList Lb, SqList *Lc){
    for(int i=0 ; i<La.length ; i++){
        ListInsert(Lc , Lc->length+1 , La.elem[i]);
    }

    for(int i=0 ; i<Lb.length ; i++){
        if(!LocateElem(Lc, Lb.elem[i]))
        ListInsert(Lc , Lc->length+1 , Lb.elem[i]);
    }
    return OK;
}

Status Intersection(SqList La, SqList Lb, SqList *Lc){
    for(int i=0 ; i<La.length ; i++){
        if(LocateElem(&Lb, La.elem[i]))
        ListInsert(Lc , Lc->length+1 , La.elem[i]);
    }
    return OK;
}

Status Difference(SqList La, SqList Lb, SqList *Lc){
    for(int i=0 ; i<La.length ; i++){
        if(!LocateElem(&Lb, La.elem[i]))
        ListInsert(Lc , Lc->length+1 , La.elem[i]);
    }
    return OK;
}

Status Complement(SqList La, SqList *Lc){
    const char universe[27] = "abcdefghijklmnopqrstuvwxyz";
    SqList L = InitList();
    memcpy(L.elem , universe , sizeof(universe)-1);
    L.length = 26;/*'\0'是字符常量为int型4字节，char c='\0';  c占1字节*/
    Difference(L, La, Lc);//printf("%zu",sizeof(universe));PrintList(&L);
    DestroyList(&L);
    return OK;
}