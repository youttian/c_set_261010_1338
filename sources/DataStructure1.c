#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "SqlList.h"

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

int main(){
    SqList L1={NULL, 0, 0}, L2={NULL, 0, 0};
    int choice = 1;
    
    while(1){
        creatMenu();
        if(scanf("%d",&choice) != 1){
            while(getchar() != '\n' && !feof(stdin)){}
            printf("输入非法，请重新输入。\n");
            continue;
        }
        while(getchar() != '\n' && !feof(stdin)){}

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
            SqList U = { NULL, 0, 0 };
            InitList(&U);
            Union(L1, L2, &U);
            printf("结果为:");
            PrintList(&U);
            DestroyList(&U);
            break;
        case 4:
            SqList I = { NULL, 0, 0 };
            InitList(&I);
            Intersection(L1, L2, &I);
            printf("结果为:");
            PrintList(&I);
            DestroyList(&I);
            break;
        case 5:
            SqList D1 = { NULL, 0, 0 };
            InitList(&D1);
            Difference(L1, L2, &D1);
            printf("结果为:");
            PrintList(&D1);
            DestroyList(&D1);
            break;
        case 6:
            SqList D2 = { NULL, 0, 0 };
            InitList(&D2);
            Difference(L2, L1, &D2);
            printf("结果为:");
            PrintList(&D2);
            DestroyList(&D2);
            break;
        case 7:
            SqList C1 = { NULL, 0, 0 };
            InitList(&C1);
            Complement(L1, &C1);
            printf("结果为:");
            PrintList(&C1);
            DestroyList(&C1);
            break;
        case 8:
            SqList C2 = { NULL, 0, 0 };
            InitList(&C2);
            Complement(L2, &C2);
            printf("结果为:");
            PrintList(&C2);
            DestroyList(&C2);
            break;
        case 9:
            printf("程序退出\n");
            DestroyList(&L1);
            DestroyList(&L2);
            return OK;
            break;
        default:
            printf("输入非法，请重新输入。\n");
            break;
        }
    }
    return OK;
}