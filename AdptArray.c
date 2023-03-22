#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"
typedef struct AdptArray_
{
    PElement * ElemArr;
    int size;
    DEL_FUNC Delete;
    COPY_FUNC Copy;
    PRINT_FUNC Print;
}AdptArray; 
PAdptArray CreateAdptArray(COPY_FUNC CopyFunc, DEL_FUNC DeleteFunc,PRINT_FUNC PrintFunc){
    PAdptArray  Arr = (PAdptArray) malloc(sizeof(AdptArray));
    if (!Arr)
    {
        return NULL;
    }
    
    Arr->Copy = CopyFunc;
    Arr->Delete = DeleteFunc;
    Arr-> Print = PrintFunc;
    Arr->size = 0;
    Arr ->ElemArr =NULL;
    return Arr;
}
void DeleteAdptArray(PAdptArray Arr)
{
    for (int i = 0; i < Arr->size; i++)
    {
        if (Arr->ElemArr[i]!=NULL)
        {
            
            Arr->Delete(Arr->ElemArr[i]);
        }
        
    }
    free(Arr);
}
void PrintDB(PAdptArray Arr){
     for (int i = 0; i < Arr->size; i++)
    {
        if (Arr->ElemArr[i])
        {
            Arr->Print(Arr->ElemArr[i]);
        }
        
    }
}
int GetAdptArraySize(PAdptArray Arr){
    if (Arr==NULL)
    {
        return -1;
    }
    return Arr->size;
}

PElement GetAdptArrayAt(PAdptArray Arr, int Place){
    printf("hey");
    if (Arr == NULL|| Arr ->size <= Place)
    {
        return NULL;
    }
    return Arr->Copy(Arr->ElemArr[Place]);

}
Result SetAdptArrayAt(PAdptArray Arr, int Place, PElement Element){
if (!Arr)
{
    return FAIL;
}
if (Arr->size<=Place){
    PElement *NewElemArr = (PElement*) calloc(sizeof(PElement),(Place+1));
    if (NewElemArr==NULL)
    {
        return FAIL;
    }
    
    for (int i=0; i < Arr->size; i++)
    {
        NewElemArr[i]= Arr->ElemArr[i];
    }
    free(Arr->ElemArr);
    Arr->ElemArr= NewElemArr;
    Arr->size=Place +1;
}
if (Arr->ElemArr[Place]!=NULL)
{
    Arr->Delete(Arr->ElemArr[Place]);
}
Arr->ElemArr[Place] = Arr->Copy(Element);
return SUCCESS;
}