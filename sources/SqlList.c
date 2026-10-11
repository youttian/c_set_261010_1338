#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "SqlList.h"

SqList InitList(void){        //输入一个未初始化的sqlist型变量的指针
    SqList L = {NULL, 0, 0};
    L.elem = (ElemType*)malloc(List_Init_Size * sizeof(ElemType));
    if(!L.elem){
        L.length = 0;
        L.listsize = 0;
        return L;
    }
    else{
        L.length = 0;
        L.listsize = List_Init_Size;
        return L;
    }
}

Status DestroyList(SqList *L){
    if(!L->elem) free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

Status ListInsert(SqList *L, int i, ElemType e){
    if(i<1 || i>L->length+1) return ERROR;

    if(L->listsize <= L->length + 1){    //数组空间不足就扩容
        if(L->listsize > INT_MAX - Listcrement) return OVERFLOW;
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