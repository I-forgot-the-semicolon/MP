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
    Client *tmpClients = nullptr;
    FILE *inputFile = fopen("clientes.txt", "r");
    if(inputFile != nullptr)
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
    AdminProvider *tmpAdminsProviders = nullptr;
    FILE *inputFile = fopen("adminprov.txt", "r");
    if(inputFile != nullptr)
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
    Product *tmpProducts = nullptr;
    FILE *inputFile = fopen("products.txt", "r");
    if(inputFile != nullptr)
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
    else
    {
        printf("Error opening!\n");
    }
    return tmpProducts;
}

void getProductFromFile(char *input, int field, int maxFields, Product* productArray, int productNumber)
{
    if(field >= maxFields)
        return;

    unsigned int pos = getFieldLength(input);
    char *tmpString = copyUntil(input, pos);

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
    Carrier *tmpCarriers = nullptr;
    FILE *inputFile = fopen("carriers.txt", "r");
    if(inputFile != nullptr)
    {
        tmpCarriers = malloc(sizeof(Carrier));
        if(tmpCarriers != nullptr)
        {
            while(!feof(inputFile))
            {
                char *tmp = malloc(sizeof(char)*1024);
                if(tmp != nullptr)
                {
                    fgets(tmp, 1024, inputFile);
                    if(strlen(tmp) > 0)
                    {
                        #ifdef DEBUG
                        printf("Nueva linea!\n");
                        #endif
                        (*carriersNumber)++;
                        #ifdef DEBUG
                        printf("size: %d\n", *carriersNumber);
                        #endif
                        tmpCarriers = realloc(tmpCarriers, sizeof(Carrier)*(*carriersNumber));
                        getCarrierFromFile(tmp, 0, 5, tmpCarriers, *carriersNumber-1);
                        free(tmp);
                    }
                }
                else
                {
                    printf("Error allocating memory\n");
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
                    #ifdef DEBUG
                    printf("Nueva linea!\n");
                    #endif
                    (*refundsNumber)++;
                    #ifdef DEBUG
                    printf("size: %d\n", *refundsNumber);
                    #endif
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

Order* getOrders(int *ordersNumber)
{
    *ordersNumber = 0;
    Order *tmpOrders = nullptr;
    FILE *inputFile = fopen("orders.txt", "r");
    if(inputFile != nullptr)
    {
        tmpOrders = malloc(sizeof(Order));
        if(tmpOrders != nullptr)
        {
            while(!feof(inputFile))
            {
                char *tmp = malloc(sizeof(char)*1024);
                fgets(tmp, 1024, inputFile);
                if(strlen(tmp) > 0)
                {
                    #ifdef DEBUG
                    printf("Nueva linea!\n");
                    #endif
                    (*ordersNumber)++;
                    #ifdef DEBUG
                    printf("size: %d\n", *refundsNumber);
                    #endif
                    tmpOrders = realloc(tmpOrders, sizeof(Order)*(*ordersNumber));
                    getOrdersFromFile(tmp, 0, 7, tmpOrders, *ordersNumber-1);
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
    return tmpOrders;
}

void getOrdersFromFile(char *input, int field, int maxFields, Order* orderArray, int orderNumber)
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
    orderArray[orderNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(orderArray[orderNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getOrdersFromFile(input, field, maxFields, orderArray, orderNumber);
}

ProductOrder* getProductOrders(int *productOrdersNumber)
{
    *productOrdersNumber = 0;
    ProductOrder *tmpProductOrders = nullptr;
    FILE *inputFile = fopen("productorders.txt", "r");
    if(inputFile != nullptr)
    {
        tmpProductOrders = malloc(sizeof(ProductOrder));
        if(tmpProductOrders != nullptr)
        {
            while(!feof(inputFile))
            {
                char *tmp = malloc(sizeof(char)*1024);
                fgets(tmp, 1024, inputFile);
                if(strlen(tmp) > 0)
                {
                    #ifdef DEBUG
                    printf("Nueva linea!\n");
                    #endif
                    (*productOrdersNumber)++;
                    #ifdef DEBUG
                    printf("size: %d\n", *refundsNumber);
                    #endif
                    tmpProductOrders = realloc(tmpProductOrders, sizeof(ProductOrder)*(*productOrdersNumber));
                    getProductOrdersFromFile(tmp, 0, 9, tmpProductOrders, *productOrdersNumber-1);
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
    return tmpProductOrders;
}

void getProductOrdersFromFile(char *input, int field, int maxFields, ProductOrder* productOrderArray, int productOrderNumber)
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
    productOrderArray[productOrderNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(productOrderArray[productOrderNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getProductOrdersFromFile(input, field, maxFields, productOrderArray, productOrderNumber);
}

Category* getCategories(int *categoriesNumber)
{
    *categoriesNumber = 0;
    Category *tmpCategories = nullptr;
    FILE *inputFile = fopen("categories.txt", "r");
    if(inputFile != nullptr)
    {
        tmpCategories = malloc(sizeof(Category));
        if(tmpCategories != nullptr)
        {
            while(!feof(inputFile))
            {
                char *tmp = malloc(sizeof(char)*1024);
                fgets(tmp, 1024, inputFile);
                if(strlen(tmp) > 0)
                {
                    #ifdef DEBUG
                    printf("Nueva linea!\n");
                    #endif
                    (*categoriesNumber)++;
                    #ifdef DEBUG
                    printf("size: %d\n", *refundsNumber);
                    #endif
                    tmpCategories = realloc(tmpCategories, sizeof(Category)*(*categoriesNumber));
                    getCategoriesFromFile(tmp, 0, 2, tmpCategories, *categoriesNumber-1);
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
    return tmpCategories;
}

void getCategoriesFromFile(char *input, int field, int maxFields, Category *categoryArray, int categoryNumber)
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
    categoryArray[categoryNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(categoryArray[categoryNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getCategoriesFromFile(input, field, maxFields, categoryArray, categoryNumber);
}

Discount* getDiscounts(int *discountsNumber)
{
    *discountsNumber = 0;
    Discount *tmpDiscounts = nullptr;
    FILE *inputFile = fopen("discounts.txt", "r");
    if(inputFile != nullptr)
    {
        tmpDiscounts = malloc(sizeof(Discount));
        if(tmpDiscounts != nullptr)
        {
            while(!feof(inputFile))
            {
                char *tmp = malloc(sizeof(char)*1024);
                fgets(tmp, 1024, inputFile);
                if(strlen(tmp) > 0)
                {
                    #ifdef DEBUG
                    printf("Nueva linea!\n");
                    #endif
                    (*discountsNumber)++;
                    #ifdef DEBUG
                    printf("size: %d\n", *refundsNumber);
                    #endif
                    tmpDiscounts = realloc(tmpDiscounts, sizeof(Discount)*(*discountsNumber));
                    getDiscountsFromFile(tmp, 0, 6, tmpDiscounts, *discountsNumber-1);
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
    return tmpDiscounts;
}

void getDiscountsFromFile(char *input, int field, int maxFields, Discount *discountArray, int discountNumber)
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
    discountArray[discountNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(discountArray[discountNumber].fields[field], tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getDiscountsFromFile(input, field, maxFields, discountArray, discountNumber);
}