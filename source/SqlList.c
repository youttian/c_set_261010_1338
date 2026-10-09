#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "SqlList.h"

Status InitList(SqList *L){
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

    if(L->listsize <= L->length + 1){
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
    *e = L->elem[i-1];

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

Status ClearList(SqList *L){
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

Status CreatList(SqList *L){
    int c;

    while((c = getchar()) != EOF && c != '\n'){
        int found1 = 0;
        int ufound2 = 1;
        int loletr[26] = {'a','b','c','d','e','f','g','h','i','j','k','l',
            'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        for(int i=0 ; i<26 ; i++){
            if(c == loletr[i]){
                found1 = 1;
                break;
            }
        }

        if(found1){
            for(int i=0 ; i<L->length ; i++){
                if(c == L->elem[i]){
                    ufound2 = 0;
                    break;
                }
            }

            if(ufound2) ListInsert(L , L->length+1 , c);
        }
    }

    return OK;
}

void PrintList(SqList *L){
    if(L->length == 0) printf("空集\n");
    for(int i=0 ; i<L->length ; i++){
        printf("%c ",L->elem[i]);
    }
    printf("\n");
}