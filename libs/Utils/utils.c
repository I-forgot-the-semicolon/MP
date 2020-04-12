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

char *concatenate(char *a, char *b)
{
    unsigned int aSize = strlen(a);
    unsigned int bSize = strlen(b);
    unsigned int finalSize = aSize+bSize;

    a = realloc(a, sizeof(char)*(finalSize+1));

    int bCounter = 0;
    for(unsigned int i = aSize; i < finalSize; i++)
    {
        a[i] = b[bCounter];
        bCounter++;
    }
    a[finalSize] = '\0';

    //printf("Final string: %s\n", a);
    return a;
}

char *concatenateChar(char *a, char b)
{
    unsigned int aSize = strlen(a);
    unsigned int finalSize = aSize+1;
    a = realloc(a, sizeof(char)*(finalSize+1));

    a[finalSize-1] = b;
    a[finalSize] = '\0';
    return a;
}

char *toFileStringClient(Client client)
{
    char *tmp = malloc(sizeof(char)*1);
    tmp[0] = '\x00';

    int field = 0;
    int totalFields = ClientFieldNumber + ClientFieldNumber-1;
    for(int i = 0; i < totalFields; i++)
    {
        printf("i: %d\n", i);
        if(i % 2 == 0)
        {
            tmp = concatenate(tmp, client.fields[field]);
            field++;
        }
        else
        {
            tmp = concatenateChar(tmp, '/');
        }
        printf("-> %s\n", tmp);
    }
    tmp = concatenateChar(tmp, '\n');
    return tmp;
}

unsigned int getFieldLength(char *input)
{
    unsigned int pos = 0;
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

void truncateString(char *input, unsigned int startPos)
{
    int finalLength = strlen(input) - startPos;
    if (finalLength > 0) 
    {
        #ifdef DEBUG
        printf("final length: %d\n", finalLength);
        #endif
        char *tmp = malloc(sizeof(char) * finalLength + sizeof(char));
        unsigned int pos = startPos;
        for (int i = 0; i < finalLength; i++) 
        {
            tmp[i] = input[pos];
            pos++;
        }
        tmp[finalLength] = '\x00';

        input = realloc(input, sizeof(char) * finalLength + sizeof(char));
        for (int i = 0; i < finalLength + 1; i++) 
        {
            input[i] = tmp[i];
        }
    }
}

char *copyUntil(const char *sString, unsigned int pos)
{
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = sString[i];
    }
    tmpString[pos] = '\x00';
    return tmpString;
}

