#include <stdlib.h>
#include "RLEList.h"
#include <string.h>
#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* in_stream)
{ //!?
    RLEList ArtList=RLEListCreate();
    char* tmpStr[1];
    char tmpLetter;
    while(fgets(tmpStr, 1, in_stream) != NULL)
    {
        tmpLetter=(char)tmpStr;
        RLEListAppend(ArtList,tmpLetter);
    }
    return ArtList;
}
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if (list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int length=RLEListSize(list);
    int index=0;
    while(index<length)
    {
        fprintf(out_stream,"%c",RLEListGet(list,index++,NULL));
    }
    return RLE_LIST_SUCCESS;
}
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if (list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    fputs(RLEListExportToString(list,NULL),out_stream);
    return RLE_LIST_SUCCESS;
}