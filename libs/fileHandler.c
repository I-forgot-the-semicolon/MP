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
    FILE *inputFile = fopen("../databases/clientes.txt", "r");
    if(inputFile != nullptr)
    {
        //tmpClients = malloc(sizeof(Client));
        tmpClients = allocate(sizeof(Client), "Tmp clients Array");

        while(!feof(inputFile))
        {
            //char *tmp = malloc(sizeof(char)*1024);
            char *tmp = allocate(sizeof(char)*1024, "tmp string");
            fgets(tmp, 1024, inputFile);

            if(isValidLine(tmp) && !feof(inputFile))
            {
                (*clientsNumber)++;
                #ifdef DEBUG
                printf("Client number: %d\n", *clientsNumber);
                #endif
                //tmpClients = realloc(tmpClients, sizeof(Client)*(*clientsNumber));

                if (*clientsNumber > 1)
                {
                    tmpClients = reallocate(tmpClients, sizeof(Client) * (*clientsNumber), "Tmp clients array");
                    tmpClients[*clientsNumber - 1].id = *clientsNumber;
                } else
                {
                    tmpClients->id = *clientsNumber;
                }

                sanitize(tmp);

                getClientFromFile(tmp, 0, ClientFieldNumber, tmpClients, *clientsNumber - 1);
            }
            //free(tmp);
            deallocate(tmp, "tmp string");
        }
        fclose(inputFile);
    }
    else
    {
        printf("Error opening client database\n");
        exit(-1);
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
    free(tmpString);
    truncateString(input, pos + 1);

    #ifdef DEBUG
    printf("Field(%d): %s\n", field, tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getClientFromFile(input, field, maxFields, clientArray, clientNumber);
}

int getLastIndex(char *path)
{
    int index = 0;
    FILE *inputFile = fopen(path, "r");
    if(inputFile != nullptr)
    {
        while(!feof(inputFile))
        {
            char *buffer = allocate(sizeof(char)*1024, "tmp string");
            fgets(buffer, 1024, inputFile);
            if(strlen(buffer) > 0)
            {
                index++;
            }
            deallocate(buffer, "Buffer index");
        }
    }
    else
    {
        printf("Error opening client database\n");
        exit(-1);
    }
    return index;
}

void saveClient(Client actualClient)
{
    int clientsNumber = getLastIndex("../databases/clientes.txt");
    printf("Index: %d\n", clientsNumber);
    FILE *inputFile = fopen("../databases/clientes.txt", "r");
    if(inputFile != nullptr)
    {
        //char **fileHolder = malloc(sizeof(char*)*clientsNumber);
        char **fileHolder = allocate(sizeof(char*)*(clientsNumber), "fileholder [x][-]");
        for (int i = 0; i < clientsNumber; i++)
        {
            //fileHolder[i] = malloc(sizeof(char) * 1024);
            fileHolder[i] = allocate(sizeof(char) * 1024, "fileholder [x][x]");
            fgets(fileHolder[i], 1024, inputFile);
            printf("%d: %s", i, fileHolder[i]);
        }

        printf("Actual id: %d\n", actualClient.id);
        char *finalString = toFileStringClient(actualClient);
        strcpy(fileHolder[actualClient.id - 1], finalString);
        deallocate(finalString, "Final path string");


        FILE *outputFile = fopen("../databases/clientes.txt", "w+");
        if(outputFile != nullptr)
        {
            for(int i = 0; i < clientsNumber; i++)
            {
                fputs(fileHolder[i], outputFile);
                printf("%d: %s", i, fileHolder[i]);
            }
            fclose(outputFile);
        }
        else
        {
            printf("Error critico al guardar los datos!\n");
            exit(-2);
        }

        for(int i = 0; i < clientsNumber; i++)
        {
            //free(fileHolder[i]);
            deallocate(fileHolder[i], "fileholder[x][x]");
        }
        //free(fileHolder);
        deallocate(fileHolder, "Fileholder[x][-]");
    }
    else
    {
        printf("Error opening client database\n");
        exit(-1);
    }
}

int saveNewLine(char *path, char *string)
{
    FILE *outputFile = fopen(path, "a");
    if(outputFile != nullptr)
    {
        fputs(string, outputFile);
        fclose(outputFile);
        return okFlag;
    }
    else
    {
        printf("Error critico al guardar los datos!\n");
        return exitFlag;
    }
}


AdminProvider* getAdminsProviders(int *adminsProvidersNumber)
{
    *adminsProvidersNumber = 0;
    AdminProvider *tmpAdminsProviders = nullptr;
    FILE *inputFile = fopen("../databases/adminprov.txt", "r");
    if(inputFile != nullptr)
    {
        //tmpAdminsProviders = malloc(sizeof(AdminProvider));
        tmpAdminsProviders = allocate(sizeof(AdminProvider), "Tmp AdminProvider Array");

        while(!feof(inputFile))
        {
            //char *tmp = malloc(sizeof(char)*1024);
            char *tmp = allocate(sizeof(char)*1024, "tmp string");
            fgets(tmp, 1024, inputFile);
            unsigned int lineLength = strlen(tmp);
            if(isValidLine(tmp) && !feof(inputFile))
            {
                (*adminsProvidersNumber)++;
                #ifdef DEBUG
                printf("Admin/provider number: %d\n", *adminsProvidersNumber);
                #endif
                //tmpAdminsProviders = realloc(tmpAdminsProviders, sizeof(AdminProvider)*(*adminsProvidersNumber));

                if(*adminsProvidersNumber > 1)
                {
                    tmpAdminsProviders = reallocate(tmpAdminsProviders, sizeof(AdminProvider)*(*adminsProvidersNumber), "Tmp Admin providers array");
                    tmpAdminsProviders[*adminsProvidersNumber-1].id = *adminsProvidersNumber;
                }
                else
                {
                    tmpAdminsProviders->id = *adminsProvidersNumber;
                }

                sanitize(tmp);
                //printf("Tmp: %s\n", tmp);

                getAdminsProvidersFromFile(tmp, 0, AdminProviderFieldNumber, tmpAdminsProviders, *adminsProvidersNumber-1);
            }

            //free(tmp);
            deallocate(tmp, "tmp string");
        }
        fclose(inputFile);
    }
    else
    {
        printf("Error opening client database\n");
        exit(-1);
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
    //printf("Final field: %s\n", tmpString);
    free(tmpString);
    truncateString(input, pos + 1);

    //printf("Final string: %s\n", input);
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getAdminsProvidersFromFile(input, field, maxFields, adminsProviderArray, adminProviderNumber);
}

//Products
Product* getProducts(int *products)
{
    *products = 0;
    Product *tmpProducts = nullptr;
    FILE *inputFile = fopen("../databases/products.txt", "r");
    if(inputFile != nullptr)
    {
        //tmpProducts = malloc(sizeof(Product));
        tmpProducts = allocate(sizeof(Product), "Tmp product Array");

        while(!feof(inputFile))
        {
            //char *tmp = malloc(sizeof(char)*1024);
            char *tmp = allocate(sizeof(char)*1024, "tmp string");
            fgets(tmp, 1024, inputFile);
            if(isValidLine(tmp) && !feof(inputFile))
            {
                (*products)++;
                #ifdef DEBUG
                printf("Product number: %d\n", *products);
                #endif
                //tmpAdminsProviders = realloc(tmpAdminsProviders, sizeof(AdminProvider)*(*adminsProvidersNumber));

                if(*products > 1)
                {
                    tmpProducts = reallocate(tmpProducts, sizeof(Product) * (*products), "Tmp Products array");
                    tmpProducts[*products - 1].productId = *products;
                }
                else
                {
                    tmpProducts->productId = *products;
                }

                sanitize(tmp);
                //printf("Tmp: %s\n", tmp);

                getProductFromFile(tmp, 0, ProductFieldNumber, tmpProducts, *products - 1);
            }

            //free(tmp);
            deallocate(tmp, "tmp string");
        }
        fclose(inputFile);
    }
    else
    {
        printf("Error opening client database\n");
        exit(-1);
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
    free(tmpString);
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
    FILE *inputFile = fopen("../databases/carriers.txt", "r");

    if(inputFile != nullptr)
    {
        //tmpAdminsProviders = malloc(sizeof(AdminProvider));
        tmpCarriers = allocate(sizeof(Carrier), "Tmp Carriers Array");

        while(!feof(inputFile))
        {
            //char *tmp = malloc(sizeof(char)*1024);
            char *tmp = allocate(sizeof(char)*1024, "tmp string");
            fgets(tmp, 1024, inputFile);
            unsigned int lineLength = strlen(tmp);
            if(isValidLine(tmp) && !feof(inputFile))
            {
                (*carriersNumber)++;
                #ifdef DEBUG
                printf("Carrier number: %d\n", *carriersNumber);
                #endif
                //tmpAdminsProviders = realloc(tmpAdminsProviders, sizeof(AdminProvider)*(*adminsProvidersNumber));

                if(*carriersNumber > 1)
                {
                    tmpCarriers = reallocate(tmpCarriers, sizeof(AdminProvider)*(*carriersNumber), "Tmp carriers array");
                    tmpCarriers[*carriersNumber-1].id = *carriersNumber;
                }
                else
                {
                    tmpCarriers->id = *carriersNumber;
                }

                sanitize(tmp);
                //printf("Tmp: %s\n", tmp);

                getCarrierFromFile(tmp, 0, CarrierFieldNumber, tmpCarriers, *carriersNumber-1);
            }

            //free(tmp);
            deallocate(tmp, "tmp string");
        }
        fclose(inputFile);
    }
    else
    {
        printf("Error opening carriers database\n");
        exit(-1);
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
    free(tmpString);
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
    FILE *inputFile = fopen("../databases/refunds.txt", "r");
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
                    getRefundFromFile(tmp, 0, RefundFieldNumber, tmpRefunds, *refundsNumber-1);
                }
                free(tmp);
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
    unsigned int pos = getFieldLength(input);
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x00';
    refundArray[refundNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(refundArray[refundNumber].fields[field], tmpString);
    free(tmpString);
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
    FILE *inputFile = fopen("../databases/orders.txt", "r");
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
                    tmpOrders = realloc(tmpOrders, sizeof(Order)*(*ordersNumber));
                    getOrdersFromFile(tmp, 0, OrderFieldNumber, tmpOrders, *ordersNumber-1);
                }
                free(tmp);
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
    unsigned int pos = getFieldLength(input);
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x00';
    orderArray[orderNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(orderArray[orderNumber].fields[field], tmpString);
    free(tmpString);
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
    FILE *inputFile = fopen("../databases/productorders.txt", "r");
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

                    tmpProductOrders = realloc(tmpProductOrders, sizeof(ProductOrder)*(*productOrdersNumber));
                    //8
                    getProductOrdersFromFile(tmp, 0, 9, tmpProductOrders, *productOrdersNumber-1);
                }
                free(tmp);
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
    unsigned int pos = getFieldLength(input);
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x00';
    productOrderArray[productOrderNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(productOrderArray[productOrderNumber].fields[field], tmpString);
    free(tmpString);
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
    FILE *inputFile = fopen("../databases/categories.txt", "r");

    if(inputFile != nullptr)
    {
        //tmpAdminsProviders = malloc(sizeof(AdminProvider));
        tmpCategories = allocate(sizeof(Category), "Tmp Carriers Array");

        while(!feof(inputFile))
        {
            //char *tmp = malloc(sizeof(char)*1024);
            char *tmp = allocate(sizeof(char)*1024, "tmp string");
            fgets(tmp, 1024, inputFile);
            unsigned int lineLength = strlen(tmp);
            if(isValidLine(tmp) && !feof(inputFile))
            {
                (*categoriesNumber)++;
                #ifdef DEBUG
                printf("Category number: %d\n", *categoriesNumber);
                #endif
                if(*categoriesNumber > 1)
                {
                    tmpCategories = reallocate(tmpCategories, sizeof(Category) * (*categoriesNumber), "Tmp carriers array");
                    tmpCategories[*categoriesNumber - 1].categoryID = *categoriesNumber;
                }
                else
                {
                    tmpCategories->categoryID = *categoriesNumber;
                }

                sanitize(tmp);
                //printf("Tmp: %s\n", tmp);

                getCategoriesFromFile(tmp, 0, CategoryFieldNumber, tmpCategories, *categoriesNumber - 1);
            }

            //free(tmp);
            deallocate(tmp, "tmp string");
        }
        fclose(inputFile);
    }
    else
    {
        printf("Error opening carriers database\n");
        exit(-1);
    }

    return tmpCategories;
}

void getCategoriesFromFile(char *input, int field, int maxFields, Category *categoryArray, int categoryNumber)
{
    if(field >= maxFields)
        return;
    unsigned int pos = getFieldLength(input);
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x00';
    categoryArray[categoryNumber].fields[field] = allocate(sizeof(char)*strlen(tmpString), "get categories from file field");
    strcpy(categoryArray[categoryNumber].fields[field], tmpString);
    free(tmpString);
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
    FILE *inputFile = fopen("../databases/discounts.txt", "r");
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
                    tmpDiscounts = realloc(tmpDiscounts, sizeof(Discount)*(*discountsNumber));
                    getDiscountsFromFile(tmp, 0, DiscountFieldNumber, tmpDiscounts, *discountsNumber-1);
                }
                free(tmp);
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
    unsigned int pos = getFieldLength(input);
    char *tmpString = malloc(sizeof(char) * pos + sizeof(char));
    for (int i = 0; i < pos; i++) 
    {
        tmpString[i] = input[i];
    }
    tmpString[pos] = '\x00';
    discountArray[discountNumber].fields[field] = malloc(sizeof(char)*strlen(tmpString));
    strcpy(discountArray[discountNumber].fields[field], tmpString);
    free(tmpString);
    truncateString(input, pos + 1);
    
    #ifdef DEBUG
    printf("Final field: %s\n", tmpString);
    printf("Final string: %s\n", input);
    #endif
    field++;
    getDiscountsFromFile(input, field, maxFields, discountArray, discountNumber);
}