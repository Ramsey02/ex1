#include <stdlib.h>
#include "RLEList.h"
#define ERROR_INT (-1)
#define THREE 3




struct RLEList_t{
    char character;
    int sequenceNum;
    struct  RLEList_t* next;

};

RLEList RLEListCreate()
{
    RLEList newRLEList = malloc(sizeof(*newRLEList));
    if(!newRLEList)
    {
        return NULL;
    }
    newRLEList->next=NULL;
    newRLEList->sequenceNum=0;
    newRLEList->character=0;
    return newRLEList;
}
void RLEListDestroy(RLEList list)
{
    while (list)
    {
        RLEList toDelete=list;
        list=list ->next;
        free(toDelete);
    }

}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list==NULL|| value==0)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tmpList=list;
    while(tmpList->next!=NULL)
    {
        tmpList=tmpList->next;
    }
    if(tmpList->character==value)
    {
        tmpList->sequenceNum++;
        return RLE_LIST_SUCCESS;
    }
    RLEList newRLEList=RLEListCreate();
    if(!newRLEList)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    newRLEList->character=value;
    newRLEList->sequenceNum=1;
    tmpList->next=newRLEList;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (list==NULL)
    {
        return ERROR_INT;
    }
    RLEList tmpList=list;
    int counter=0;
    while(tmpList!=NULL)
    {
        counter+=tmpList->sequenceNum;
        tmpList=tmpList->next;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index+1>RLEListSize(list)||index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList tmpList=list->next;
    int currentIndex=(tmpList->sequenceNum-1);
    while(currentIndex<index)
    {
        tmpList=tmpList->next;
        currentIndex+=tmpList->sequenceNum;
    }
    if (tmpList->sequenceNum>1)
    {
        tmpList->sequenceNum--;
        return RLE_LIST_SUCCESS;
    }
    RLEList tmpList2=list;
    while (tmpList2->next!=tmpList)
    {
        tmpList2=tmpList2->next;

    }
    tmpList2->next=tmpList->next;
    free(tmpList);
    if(tmpList2->next==NULL) {
        return RLE_LIST_SUCCESS;
    }
    if( tmpList2->next->character==tmpList2->character)
    {
        RLEList tmpList3=tmpList2->next;
        tmpList2->sequenceNum+=tmpList3->sequenceNum;
        tmpList2->next=tmpList3->next;
        free(tmpList3);
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list==NULL)
    {
        if (result!=NULL)
        {
            *result=RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if(index+1>RLEListSize(list)||index<0)
    {
        if (result!=NULL)
        {
            *result=RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    RLEList tmpList=list;
    int currentIndex=tmpList->sequenceNum-1;
    while (currentIndex<index)
    {
        tmpList=tmpList->next;
        currentIndex+=tmpList->sequenceNum;
    }
    if(result!=NULL)
    {
        *result=RLE_LIST_SUCCESS;//??
    }
    return tmpList->character;

}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(map_function==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tmpList=list->next;
    while (tmpList!=NULL)
    {
        tmpList->character=map_function(tmpList->character);
        tmpList=tmpList->next;
    }
    RLEList tmpList1=list->next;
    // free(tmpList);
    if(tmpList1==NULL || tmpList1->next==NULL)
    {
        return RLE_LIST_SUCCESS;
    }
    RLEList tmpList2=tmpList1->next;
    int index=2; //!? TWO define!
    while(tmpList1!=NULL)
    {
        while(tmpList2!=NULL && tmpList2->character==tmpList1->character)
        {
            tmpList1->sequenceNum+=tmpList2->sequenceNum;
            RLEList toDelete=tmpList2;
            tmpList2=tmpList2->next;
            tmpList1->next=tmpList2;
            free(toDelete);
        }
        tmpList1=tmpList2;
        if(tmpList2!=NULL) {
            tmpList2 = tmpList2->next;
        }
        else{
            return RLE_LIST_SUCCESS;
        }
        index++;
    }
    return RLE_LIST_SUCCESS;
}
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list==NULL)
    { //!? need to check with result!!!!!!
    if(result) {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
        return NULL;
    }
    int totalSize= RLEListSize(list);
    char *str=malloc((THREE*totalSize)+1);
    if(str==NULL)
    {
        if(result) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int index=0;
   // if(list->next==NULL)
  //  {
  //      return "";
  //  }
    RLEList tmpList=list->next;
    char* tempSequence= malloc(sizeof (tempSequence)*(3*totalSize-1)); //!? 3
    while(tmpList!=NULL) 
    {
        str[index++] = tmpList->character;
        // char* tempSequence=ReverseNumber(tmpList->sequenceNum);
        sprintf(tempSequence, "%d", tmpList->sequenceNum);

        while (*tempSequence) {
            str[index++] = *(tempSequence++);
        }
       str[index++] = '\n';
        tmpList = tmpList->next;

    }
    if(result) {
        *result = RLE_LIST_SUCCESS;
    }
    str[index++] = '\0';
  // free(tempSequence);

    return str;
}