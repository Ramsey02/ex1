#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include "../RLEList.h"

/** receives a file and returns an RLE list contains all the characters 
 * @param in_stream- the file that contain the photo that we want to capsule
 * @return RLE list contains all the characters 
*/
RLEList asciiArtRead(FILE* in_stream);

/** print the photo  to out_stream file
 *  @param out_stream - the file that we want to put the photo in
 *  @param list - RLE list contain al the  characters in the photo
 * @return -
 * RLE_LIST_NULL_ARGUMENT if the list is NULL 
 * RLE_LIST_SUCCESS  if the function sucssed 
 * 
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/** writes into the out_stream file the string returned by the function RLEListExportToString of the param list
 * @param list  list contain the chars from the photo
 * @param out_stream - the file wich we want to write the capsuled photo in
 * @return –
 *  RLE_LIST_NULL_ARGUMENT if one if the param NULL
 *  RLE_LIST_SUCCESS –if the function sucssed 
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
#endif