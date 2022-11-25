#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include "RLEList.h"

// receives a file and returns an RLE list contains all the characters
RLEList asciiArtRead(FILE* in_stream);

//writes the RLE list to out_stream file
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

//writes into the out_stream file the string returned by the function RLEListExportToString of the param list
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
#endif
