/* 
 * This file is part of the ESIZON distribution.
 * Copyright (c) 2020 Ruben Cordero Ramos.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "utils.h"

void clearBuffer()
{
    while ((getchar()) != '\n'); 
}

int getFieldLength(char *input)
{
    int pos = 0;
    int found = 0;
    for(int i = 0; i < strlen(input) && !found; i++)
    {
        if(input[i] == '/' || input[i] == '\n' || input[i] == EOF || input [i] == '\x00')
        {
            pos = i;
            found = 1;
        }
    }

    pos = found == 0 ? strlen(input) : pos;
    return pos;
}

void truncateString(char *input, int startPos) 
{
    int finalLength = strlen(input) - startPos;
    if (finalLength > 0) 
    {
        #ifdef DEBUG
        printf("final length: %d\n", finalLength);
        #endif
        char *tmp = malloc(sizeof(char) * finalLength + sizeof(char));
        int pos = startPos;
        for (int i = 0; i < finalLength; i++) 
        {
            tmp[i] = input[pos];
            pos++;
        }
        tmp[finalLength] = '\x0';

        input = realloc(input, sizeof(char) * finalLength + sizeof(char));
        for (int i = 0; i < finalLength + 1; i++) 
        {
        input[i] = tmp[i];
        }
    }
}

char *copyUntil(char *sString, int pos)
{
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = sString[i];
    }
    tmpString[pos] = '\x0';
    return tmpString;
}

