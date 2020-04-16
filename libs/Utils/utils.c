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

char *toLowerCase(char *str)
{
    unsigned int length = strlen(str);
    char *tmpString = allocate(sizeof(char)*(length+1), "tmp String to low case");
    tmpString[length] = '\x00';

    for(int i = 0; i < length; i++)
    {
        if(str[i] >= 65 && str[i] <= 90)
            tmpString[i] = str[i]+32;
        else
            tmpString[i] = str[i];
    }
    return tmpString;
}

void cleanUpUser(User *user)
{
    switch (user->userType)
    {
        case client:
            printf("Client!\n");
            for(int i = 0; i < ClientFieldNumber; i++)
            {
                deallocate(user->clientUser.fields[i], "exit user client cleanup");
            }
            break;
        case carrier:
            printf("Carrier!\n");
            for(int i = 0; i < CarrierFieldNumber; i++)
            {
                deallocate(user->carrierUser.fields[i], "exit user carrier cleanup");
            }
            break;
        case admin:
        case provider:
            printf("Admin/Provider!\n");
            for(int i = 0; i < AdminProviderFieldNumber; i++)
            {
                deallocate(user->adminProviderUser.fields[i], "exit user adminprovider cleanup");
            }
            break;
        default:
            break;
    }
    deallocate(user, "User");
}


void copyClient(Client *dest, Client src)
{
    dest->id = src.id;
    dest->wallet = src.wallet;
    for(int i = 0; i < ClientFieldNumber; i++)
    {
        dest->fields[i] = allocate(sizeof(char)*(strlen(src.fields[i])+1), "field in client login");
        strcpy(dest->fields[i], src.fields[i]);
    }
}

void copyAdminProvider(AdminProvider *dest, AdminProvider src)
{
    dest->id = src.id;
    for(int i = 0; i < AdminProviderFieldNumber; i++)
    {
        dest->fields[i] = allocate(sizeof(char) * (strlen(src.fields[i]) + 1), "field in admin provider login");
        strcpy(dest->fields[i], src.fields[i]);
    }
}

void copyCarrier(Carrier *dest, Carrier src)
{
    dest->id = src.id;
    for(int i = 0; i < CarrierFieldNumber; i++)
    {
        dest->fields[i] = allocate(sizeof(char) * (strlen(src.fields[i]) + 1), "field in carrier login");
        strcpy(dest->fields[i], src.fields[i]);
    }
}

bool isValidLine(char *tmp)
{
    bool validLine = false;
    unsigned int lineLength = strlen(tmp);
    for(int i = 0; i < lineLength; i++)
    {
        //if(!iscntrl(tmp[i]))
        if(tmp[i] != '\n' && tmp[i] != '\r')
            validLine = true;
    }
    return validLine && lineLength > 0;
}

char *getNextID(int lastID, unsigned int length)
{
    //char *finalString = malloc(sizeof(char)*6);
    char *tmp = allocate(sizeof(char) * length, "Next ID final string");
    for(int i = 0; i < length; i++)
        tmp[i] = '0';

    printf("Last id: %d\n", lastID);

    unsigned int pos = strlen(tmp) - 1;
    int tmpID = lastID+1;
    while(tmpID > 0)
    {
        tmp[pos] = tmpID % 10 + '0';
        tmpID /= 10;
        pos--;
    }
    printf("Final id: %s\n", tmp);
    return tmp;
}

bool askCorrect()
{
    char answer;
    printf("Is that correct? y/n\n");
    clearBuffer();
    scanf("%c", &answer);
    if(answer == 'y' || answer == 'Y')
    {
        return true;
    }
    return false;
}

char *askForField(char *msg, bool confirm)
{
    char buffer[1024];
    char *dest = nullptr;

    if(confirm)
    {
        bool correct = false;
        do
        {
            printf("%s: ", msg);
            clearBuffer();
            scanf("%[^\n]", buffer);
            //dest = malloc(sizeof(char)*(strlen(buffer)+1));
            dest = allocate(sizeof(char)*(strlen(buffer)+1), "Field dest ask for field");
            if(askCorrect())
            {
                strcpy(dest, buffer);
                correct = true;
            }
            else
            {
                //free(dest);
                deallocate(dest, "Field dest ask for field");
            }
        } while(!correct);
    }
    else
    {
        printf("%s: ", msg);
        scanf("%s", buffer);
        //dest = malloc(sizeof(char)*(strlen(buffer)+1));
        dest = allocate(sizeof(char)*(strlen(buffer)+1), "Field dest");
        strcpy(dest, buffer);
    }

    return dest;
}

void askForExit(int *flag)
{
    char answer;
    printf("Do you want to exit? y/n\n");
    clearBuffer();
    scanf("%c", &answer);
    if(answer == 'y' || answer == 'Y')
    {
        *flag = exitFlag;
    }
}

char *concatenate(char *a, char *b)
{
    unsigned int aSize = strlen(a);
    unsigned int bSize = strlen(b);
    unsigned int finalSize = aSize+bSize;

    //a = realloc(a, sizeof(char)*(finalSize+1));
      a = reallocate(a, sizeof(char)*(finalSize+1), "Concatenate a");

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
    //a = realloc(a, sizeof(char)*(finalSize+1));
     a = reallocate(a, sizeof(char)*(finalSize+1), "Concatenate char 'a'");

    a[finalSize-1] = b;
    a[finalSize] = '\0';
    return a;
}

char *toFileStringClient(Client client)
{
    //char *tmp = malloc(sizeof(char)*1);
    char *tmp = allocate(sizeof(char), "Tmp to file string client");
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

void sanitize(char *string)
{
    #ifdef DEBUG
    printf("Sanitazing...\n");
    #endif
    bool hasToSanitize = false;
    unsigned int stringLength = strlen(string);
    int pos = 0;
    for(int i = 0; i < stringLength; i++)
    {
        if(string[i] == '\n' || string[i] == '\r')
        {
            hasToSanitize = true;
            pos = i;
        }
    }

    if(hasToSanitize)
    {
        string = reallocate(string, sizeof(char)*pos, "sanitize string...");
        string[pos] = '\x00';
        sanitize(string);
    }
}
void truncateString(char *input, unsigned int startPos)
{
    int finalLength = strlen(input) - startPos;
    if (finalLength > 0) 
    {
        #ifdef DEBUG
        printf("final length: %d\n", finalLength);
        #endif
        //char *tmp = malloc(sizeof(char) * finalLength + sizeof(char));
        char *tmp = allocate(sizeof(char) * finalLength + sizeof(char), "tmp truncate string");
        unsigned int pos = startPos;
        for (int i = 0; i < finalLength; i++) 
        {
            tmp[i] = input[pos];
            pos++;
        }
        tmp[finalLength] = '\x00';

        //input = realloc(input, sizeof(char) * finalLength + sizeof(char));
        input = reallocate(input, sizeof(char) * finalLength + sizeof(char), "Input truncate");
        for (int i = 0; i < finalLength + 1; i++)
        {
            input[i] = tmp[i];
        }
        deallocate(tmp, "tmp truncate string");
    }
}

char *copyUntil(const char *sString, unsigned int pos)
{
    //char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    char *tmpString = allocate(sizeof(char) * pos + sizeof(char), "Copy until tmp string");
    for (int i = 0; i < pos; i++)
    {
        tmpString[i] = sString[i];
    }
    tmpString[pos] = '\x00';
    return tmpString;
}

