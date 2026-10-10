#ifndef SQLLIST_H
#define SQLLIST_H
#define ERROR 0
#define OK 1
#define OVERFLOW -1
#define EQUAL 1
#define List_Init_Size 100
#define Listcrement 10

extern const char universe[27];

typedef char ElemType;

typedef int Status;

typedef struct {
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status InitList(SqList *L);
Status DestroyList(SqList *L);
Status ListInsert(SqList *L, int i, ElemType e);
Status ListDelete(SqList *L, int i, ElemType *e);
Status LocateElem(SqList *L, ElemType e);
Status GetElem(SqList *L, int i, ElemType *e);
Status ClearList(SqList *L);
Status ListEmpty(SqList *L);
Status ListLength(SqList *L);
Status CreatList(SqList *L);
void PrintList(SqList *L);
Status Union(SqList La, SqList Lb, SqList *Lc);
Status Intersection(SqList La, SqList Lb, SqList *Lc);
Status Difference(SqList La, SqList Lb, SqList *Lc);
Status Complement(SqList La, SqList *Lc);

#endif