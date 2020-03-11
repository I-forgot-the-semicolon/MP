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

#include "fileHandler.h"


Client* getClients(int *clientsNumber)
{
    *clientsNumber = 0;
    Client *tmpClients = NULL;
    FILE *inputFile = fopen("clientes.txt", "r");
    if(inputFile != NULL)
    {
        tmpClients = malloc(sizeof(Client));
        while(!feof(inputFile))
        {
            char *tmp = malloc(sizeof(char)*1024);
            fgets(tmp, 1024, inputFile);
            if(strlen(tmp) > 0)
            {
                (*clientsNumber)++;
                tmpClients = realloc(tmpClients, sizeof(Client)*(*clientsNumber));
                getClientFromFile(tmp, 0, 9, tmpClients, *clientsNumber-1);
                free(tmp);
            }
        }
        fclose(inputFile);
    }
    return tmpClients;
}

/*
 *  Funcion recursiva, usada para obtener cada campo de una cadena original
 *  la cadena original se va recortando hasta que se supera el maximo de campos
 */
void getClientFromFile(char *input, int field, int maxFields, Client* clientArray, int clientNumber) 
{
    if(field >= maxFields)
        return;
    unsigned int pos = getFieldLength(input);
    char *tmpString = copyUntil(input, pos);
    /*char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x0';*/
    clientArray[clientNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(clientArray[clientNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getClientFromFile(input, field, maxFields, clientArray, clientNumber);
}


AdminProvider* getAdminsProviders(int *adminsProvidersNumber)
{
    *adminsProvidersNumber = 0;
    AdminProvider *tmpAdminsProviders = NULL;
    FILE *inputFile = fopen("adminprov.txt", "r");
    if(inputFile != NULL)
    {
        tmpAdminsProviders = malloc(sizeof(AdminProvider));
        while(!feof(inputFile))
        {
            char *tmp = malloc(sizeof(char)*1024);
            fgets(tmp, 1024, inputFile);
            if(strlen(tmp) > 0)
            {
                (*adminsProvidersNumber)++;
                tmpAdminsProviders = realloc(tmpAdminsProviders, sizeof(AdminProvider)*(*adminsProvidersNumber));
                getAdminsProvidersFromFile(tmp, 0, 5, tmpAdminsProviders, *adminsProvidersNumber-1);
                free(tmp);
            }
        }
        fclose(inputFile);
    }
    return tmpAdminsProviders;
}

void getAdminsProvidersFromFile(char *input, int field, int maxFields, AdminProvider* adminsProviderArray, int adminProviderNumber)
{
    if(field >= maxFields)
        return;

    unsigned int pos = getFieldLength(input);
    char *tmpString = copyUntil(input, pos);
    adminsProviderArray[adminProviderNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(adminsProviderArray[adminProviderNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getAdminsProvidersFromFile(input, field, maxFields, adminsProviderArray, adminProviderNumber);
}

//Products
Product* getProducts(int *productsNumber)
{
    *productsNumber = 0;
    Product *tmpProducts = NULL;
    FILE *inputFile = fopen("adminprov.txt", "r");
    if(inputFile != NULL)
    {
        tmpProducts = malloc(sizeof(Product));
        while(!feof(inputFile))
        {
            char *tmp = malloc(sizeof(char)*1024);
            fgets(tmp, 1024, inputFile);
            if(strlen(tmp) > 0)
            {
                (*productsNumber)++;
                tmpProducts = realloc(tmpProducts, sizeof(Product)*(*productsNumber));
                getProductFromFile(tmp, 0, 7, tmpProducts, *productsNumber-1);
                free(tmp);
            }
        }
        fclose(inputFile);
    }
    return tmpProducts;
}

void getProductFromFile(char *input, int field, int maxFields, Product* productArray, int productNumber)
{
    if(field >= maxFields)
        return;

    unsigned int pos = getFieldLength(input);
    char *tmpString = copyUntil(input, pos);
    /*
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x0';*/
    productArray[productNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(productArray[productNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif

    field++;
    getProductFromFile(input, field, maxFields, productArray, productNumber);
}

//Carriers

Carrier* getCarriers(int *carriersNumber)
{
    *carriersNumber = 0;
    Carrier *tmpCarriers = NULL;
    FILE *inputFile = fopen("carriers.txt", "r");
    if(inputFile != NULL)
    {
        tmpCarriers = malloc(sizeof(Carrier));
        if(tmpCarriers != NULL)
        {
            while(!feof(inputFile))
            {
                char *tmp = malloc(sizeof(char)*1024);
                if(tmp != nullptr)
                {
                    fgets(tmp, 1024, inputFile);
                    if(strlen(tmp) > 0)
                    {
                        printf("Nueva linea!\n");
                        (*carriersNumber)++;
                        printf("size: %d\n", *carriersNumber);
                        tmpCarriers = realloc(tmpCarriers, sizeof(Carrier)*(*carriersNumber));
                        getCarrierFromFile(tmp, 0, 5, tmpCarriers, *carriersNumber-1);
                        free(tmp);
                    }
                }
                else
                {
                    printf("Error reserving memory\n");
                }
                
            }
            fclose(inputFile);
        }
        
    }
    else
    {
        printf("Error opening!\n");
    }
    
    return tmpCarriers;
}

void getCarrierFromFile(char *input, int field, int maxFields, Carrier* carrierArray, int carrierNumber)
{
    if(field >= maxFields)
        return;

    unsigned int pos = getFieldLength(input);
    char *tmpString = copyUntil(input, pos);
    carrierArray[carrierNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(carrierArray[carrierNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getCarrierFromFile(input, field, maxFields, carrierArray, carrierNumber);
}

#pragma region Refund
Refund* getRefunds(int *refundsNumber)
{
    *refundsNumber = 0;
    Refund *tmpRefunds = nullptr;
    FILE *inputFile = fopen("refunds.txt", "r");
    if(inputFile != nullptr)
    {
        tmpRefunds = malloc(sizeof(Refund));
        if(tmpRefunds != nullptr)
        {
            while(!feof(inputFile))
            {
                char *tmp = malloc(sizeof(char)*1024);
                fgets(tmp, 1024, inputFile);
                if(strlen(tmp) > 0)
                {
                    printf("Nueva linea!\n");
                    (*refundsNumber)++;
                    printf("size: %d\n", *refundsNumber);
                    tmpRefunds = realloc(tmpRefunds, sizeof(Refund)*(*refundsNumber));
                    getRefundFromFile(tmp, 0, 7, tmpRefunds, *refundsNumber-1);
                    free(tmp);
                }
            }
        }  
        fclose(inputFile); 
    }
    else
    {
        printf("Error opening!\n");
    }
    
    return tmpRefunds;
}

void getRefundFromFile(char *input, int field, int maxFields, Refund* refundArray, int refundNumber)
{
    if(field >= maxFields)
        return;
    int pos = getFieldLength(input);
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x0';
    refundArray[refundNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(refundArray[refundNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getRefundFromFile(input, field, maxFields, refundArray, refundNumber);
}
#pragma endregion

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