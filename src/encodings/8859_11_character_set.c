#include "8859_11_character_set.h"

int get8859_11_character(int unicode)
{
    if  ( unicode >= 0 && unicode <= 126)
        return unicode;
    else if  ( unicode == 160)
        return 160;
    else if  ( unicode >= 3585 && unicode <= 3642)
        return unicode -3424;
    else if  ( unicode >= 3647 && unicode <= 3675)
        return unicode -3425;



    return -1;
}
