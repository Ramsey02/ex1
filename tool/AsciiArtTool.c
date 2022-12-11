#include <stdlib.h>

#include "../RLEList.h"

#include "AsciiArtTool.h"

#include <string.h>

 

RLEList asciiArtRead(FILE* in_stream)

{ //!?

    char c;

    RLEList list =RLEListCreate();

    if(!list)

    {

        RLEListDestroy(list);

        return NULL;

    }

    c= fgetc(in_stream);

    while(c!=EOF)

    {

        RLEListAppend(list,c);

        c= fgetc(in_stream);

    }

    return list;

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

        // fprintf(out_stream,"%c",'\n');

    return RLE_LIST_SUCCESS;

}

 

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)

{

    if (list==NULL)

    {

        return RLE_LIST_NULL_ARGUMENT;

    }

    char* exportString=RLEListExportToString(list,NULL);

    if(exportString==NULL)

    {

        return RLE_LIST_NULL_ARGUMENT;

    }

  //  int exportLength=(int)strlen(exportString);

    // fputs(RLEListExportToString(list,NULL),out_stream);

    // asciiArtPrint(list,out_stream);

    fprintf(out_stream,"%s",exportString); //!?

    // fprint("\n",out_stream);

    free(exportString);

    return RLE_LIST_SUCCESS;

}