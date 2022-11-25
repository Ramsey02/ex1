#include <stdlib.h>
#include "RLEList.h"
#include <string.h>
#define ERROR_INT -1
char* ReverseNumber(int num);


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
    RLEList tmpList=list;
    int currentIndex=tmpList->sequenceNum-1;
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
    RLEList tmpList=list;
    while (tmpList!=NULL)
    {
        tmpList->character=map_function(tmpList->character);
        tmpList=tmpList->next;
    }
    RLEList tmpList1=list;
    if(tmpList1->next==NULL)
    {
        return RLE_LIST_SUCCESS;
    }
    RLEList tmpList2=tmpList1->next;
    while(tmpList1!=NULL)
    {
        while(tmpList2!=NULL && tmpList2->character==tmpList1->character)
        {
            tmpList1->sequenceNum+=tmpList2->sequenceNum;
            RLEList toDelete=tmpList2;
            tmpList2=tmpList2->next;
            free(toDelete);
        }
        tmpList1->next=tmpList2;
        tmpList1=tmpList1->next;
        tmpList2=tmpList2->next;
    }
    return RLE_LIST_SUCCESS;
}
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list==NULL)
    {
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char *str=malloc(sizeof(*str));
    if(str==NULL)
    {
        *result=RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    int index=0;
    RLEList tmpList=list;
    while(tmpList!=NULL)
    {
        str[index++]=tmpList->character;
        char* tempSequence=ReverseNumber(tmpList->sequenceNum);
        int counter=0;
        int index2=strlen(tempSequence);
        while(counter<index2)
        {
            str[index++]=tempSequence[index2--];
            counter++;
        }
        str[index++]='\n';
        tmpList=tmpList->next;
    }
    *result=RLE_LIST_SUCCESS;
    return str;
}

char* ReverseNumber(int num)
{
    char* result=malloc(sizeof(*result));
    if(result==NULL)
    {
        return NULL;
    }
    int index=0;
    while (num>0)
    {
        char temp=num%10;
        result[index++]=temp;
        num=num/10;
    }
    return result;
}
