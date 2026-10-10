#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "SqlList.h"

const char universe[27] = "abcdefghijklmnopqrstuvwxyz";

Status InitList(SqList *L){        //输入一个未初始化的sqlist型变量的指针
    L->elem = (ElemType*)malloc(List_Init_Size * sizeof(ElemType));
    if(!L->elem) return OVERFLOW;
    else{
        L->length = 0;
        L->listsize = List_Init_Size;
        return OK;
    }
}

Status DestroyList(SqList *L){
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

Status ListInsert(SqList *L, int i, ElemType e){
    if(i<1 || i>L->length+1) return ERROR;

    if(L->listsize <= L->length + 1){    //数组空间不足就扩容
        if(L->listsize > MAXINT - Listcrement) return OVERFLOW;
        int newsize = L->listsize + Listcrement;
        ElemType *list = (ElemType*)realloc(L->elem,newsize * sizeof( ElemType));
        if(list) L->elem = list;
        else return OVERFLOW;
        L->listsize = newsize;
    }

    for(int j = L->length ; j>=i ; j--){
        L->elem[j] = L->elem[j-1];
    }

    L->elem[i-1] = e;
    L->length++;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e){
    if(i<1 || i>L->length) return ERROR;
    *e = L->elem[i-1];          //把值赋给指针所指地址，从而带出

    for(int j=i ; j<L->length ; j++){
        L->elem[j-1] = L->elem[j];
    }

    L->length--;
    return OK;
}

Status LocateElem(SqList *L, ElemType e){
    for(int i=0 ; i<L->length ; i++){
        if(e == L->elem[i]) return i+1;
    }
    return 0;
}

Status GetElem(SqList *L, int i, ElemType *e){
    if(i<1 || i>L->length) return ERROR;

    *e = L->elem[i-1];
    return OK;
}

Status ClearList(SqList *L){      //不会更改数组空间
    L->length = 0;
    return OK;
}

Status ListEmpty(SqList *L){
    if(L->length == 0) return EQUAL;
    else return ERROR; 
}

Status ListLength(SqList *L){
    return L->length;
}

Status CreatList(SqList *La){
    SqList L = {NULL, 0, 0};
    InitList(&L);

    int c;
    while((c = getchar()) != EOF && c != '\n'){    //逐个获取stdio缓冲区的字符，缓冲区无残留
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
    if(La->length == 0) printf("空集\n");
    printf("{");
    for(int i=0 ; i<La->length-1 ; i++){
        printf("%c,",La->elem[i]);
    }
    printf("%c}",La->elem[La->length-1]);
    printf("\n");
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
    SqList L = { NULL, 0, 0 };
    InitList(&L);
    memcpy(L.elem , universe , sizeof(universe));
    L.length = 26;
    Difference(L, La, Lc);
    DestroyList(&L);
    return OK;
}