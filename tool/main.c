#include "../RLEList.h"
#include <string.h>
#include "AsciiArtTool.h"
#define SPACE ' '
#define AT_SIGN '@'
char invertingMap (char c);

 
int main(int argc, char **argv)
{
    if (argc!=4)
    {
        return 0;
    }
    FILE *inputFile= fopen(argv[2],"r");
    if(!inputFile)
    {
        return 0;
    }
    FILE *outputFile=fopen(argv[3],"w");
    if(!outputFile)
    {
        fclose(inputFile);
        return 0;
    }
    RLEList artList=asciiArtRead(inputFile);
    if (strcmp(argv[1],"-e")==0)
    {
        if(asciiArtPrintEncoded(artList,outputFile)!=RLE_LIST_SUCCESS)
        //!? is it better to put this into a function
        {
            fclose(inputFile);
            fclose(outputFile);
            RLEListDestroy(artList);
            return 0;
        }
    }
    if (strcmp(argv[1],"-i")==0)
    {
        RLEListMap(artList,invertingMap);
        if(asciiArtPrint(artList,outputFile)!=RLE_LIST_SUCCESS)
        {
            fclose(inputFile);
            fclose(outputFile);
            return 0;
        }
    }
    RLEListDestroy(artList);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}


char invertingMap (char character)
{
    if(character==SPACE) return AT_SIGN;
    if(character==AT_SIGN) return SPACE;
    return character;
}