#include "8859_1_character_set.h"

int get8859_1_character(int unicode)
{
   if( unicode > 0 && unicode <= 127)
                          return unicode;
   else if( unicode > 161 && unicode <= 255)
                          return unicode;

    return -1;
}
