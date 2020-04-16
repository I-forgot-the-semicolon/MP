#include "product.h"

void showProductCategory(char *id)
{
    int categoriesNumber;
    Category *categories = getCategories(&categoriesNumber);

    bool categoryFound = false;
    for(int j = 0; j < categoriesNumber && !categoryFound; j++)
    {
        if(strcmp(id, categories[j].fields[categoryID]) == 0)
        {
            printf("\tCategory:\t%s.\n", categories[j].fields[categoryDescription]);
            categoryFound = true;
        }
    }

    for(int i = 0; i < categoriesNumber; i++)
    {
        for(int j = 0; j < CategoryFieldNumber; j++)
            deallocate(categories[i].fields[j], "Field from categories array...");
    }
    deallocate(categories, "Categories Array");
}

void showProductCompany(char *id)
{
    int providersNumber;
    AdminProvider *adminProviders = getAdminsProviders(&providersNumber);

    bool providerFound = false;
    for(int j = 0; j < providersNumber && !providerFound; j++)
    {
        if(strcmp(id, adminProviders[j].fields[adminProviderId]) == 0)
        {
            printf("\tCompany:\t%s.\n", adminProviders[j].fields[adminProviderName]);
            providerFound = true;
        }
    }

    for(int i = 0; i < providersNumber; i++)
    {
        for(int j = 0; j < AdminProviderFieldNumber; j++)
            deallocate(adminProviders[i].fields[j], "Field from categories array...");
    }
    deallocate(adminProviders, "Categories Array");
}

void searchProductByName()
{
    bool found = false;
    int productsNumber, actualCounter = 0;
    Product *products = getProducts(&productsNumber);

    char *productName = askForField("Product name", false);
    char *lowCaseProductName = toLowerCase(productName);
    deallocate(productName, "Product name");

    for(int i = 0; i < productsNumber; i++)
    {
        char *tmpLowCaseDescription = toLowerCase(products[i].fields[productDescription]);
        //printf("Comparing %s with %s\n", lowCaseProductName, tmpLowCaseDescription);
        if(strstr(tmpLowCaseDescription, lowCaseProductName) != nullptr)
        {
            actualCounter++;
            printf("[%d]\tProduct:\t%s.\n", actualCounter, products[i].fields[productDescription]);
            showProductCategory(products[i].fields[productCategoryID]);
            printf("\tPrice:\t\t%s€\n", products[i].fields[productPrice]);
            printf("\tStock:\t\t%s.\n", products[i].fields[productStock]);
            //printf("\tCompany:\t%s\n", products[i].fields[productCompanyID]);
            showProductCompany(products[i].fields[productCompanyID]);
            printf("\tDelivery in less than %s days\n\n", products[i].fields[productMaxDaysDelay]);
            found = true;
        }
        deallocate(tmpLowCaseDescription, "tmp low case description");
    }
    deallocate(lowCaseProductName, "Product name");

    if(!found)
        printf("Nothing found!\n");

    for(int i = 0; i < productsNumber; i++)
    {
        for(int j = 0; j < ProductFieldNumber; j++)
            deallocate(products[i].fields[j], "Field from product array...");
    }
    deallocate(products, "Products Array");
}

void showProductByCategory(char *id)
{
    bool found = false;
    int productsNumber, actualCounter = 0;
    Product *products = getProducts(&productsNumber);

    /*for(int i = 0; i < productsNumber; i++)
    {
        if(strcmp(id, products[i].fields[productCategoryID]) == 0)
        {
            actualCounter++;
            printf("[%d]\tProduct:\t%s.\n", actualCounter, products[i].fields[productDescription]);
            showProductCategory(products[i].fields[productCategoryID]);
            printf("\tPrice:\t\t%s€\n", products[i].fields[productPrice]);
            printf("\tStock:\t\t%s.\n", products[i].fields[productStock]);
            showProductCompany(products[i].fields[productCompanyID]);
            printf("\tDelivery in less than %s days\n\n", products[i].fields[productMaxDaysDelay]);
            found = true;
        }
    }

    if(!found)
        printf("Nothing found!\n");*/

    for(int i = 0; i < productsNumber; i++)
    {
        for(int j = 0; j < ProductFieldNumber; j++)
            deallocate(products[i].fields[j], "Field from product array...");
    }
    deallocate(products, "Products Array");
}

void searchProductByCategory()
{
    int categoriesNumber;
    Category *categories = getCategories(&categoriesNumber);

    bool back = false;
    do
    {
        int option;
        for(int i = 0; i < categoriesNumber; i++)
        {
            printf("%d. %s\n", i+1, categories[i].fields[categoryDescription]);
        }
        printf("%d. Back\n", categoriesNumber+1);
        printf("Select an option: ");
        clearBuffer();
        scanf("%d", &option);

        if(option >= 1 && option <= categoriesNumber)
        {
            showProductByCategory(categories[option-1].fields[categoryID]);
        }
        else
        {
            if(option == categoriesNumber+1)
                back = true;
            else
                printf("Invalid option...\n");
        }
    } while(!back);

    for(int i = 0; i < categoriesNumber; i++)
    {
        for(int j = 0; j < CategoryFieldNumber; j++)
            deallocate(categories[i].fields[j], "Categories array field");
    }
    deallocate(categories, "Categories array");
}