    //HECHO POR DAVID
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

#include "adminProvider.h"

AdminProvider loginAdminProvider(char *email, char *password, int *pos)
{
  AdminProvider tmpAdminProvider = {0, nullptr};
  bool found = false;

  int adminProviderArraySize = 0;
  AdminProvider *adminProviderArray = getAdminsProviders(&adminProviderArraySize);

    if(adminProviderArray != nullptr)
    {
        for (int i = 0; i < adminProviderArraySize && !found; i++)
        {
            if(strcmp(email, adminProviderArray[i].fields[adminProviderEmail]) == 0 && strcmp(password, adminProviderArray[i].fields[adminProviderPassword]) == 0)
            {
                found = true;
                printf("Username found!\n");
                printf("Password correct!\n");
                copyAdminProvider(&tmpAdminProvider, adminProviderArray[i]);
                *pos = i;
            }
        }
        for(int i = 0; i < adminProviderArraySize; i++)
        {
            for(int j = 0; j < AdminProviderFieldNumber; j++)
                deallocate(adminProviderArray[i].fields[j], "Field from admin provider array...");
        }
        deallocate(adminProviderArray, "admin provider Array");
        //free(adminProviderArray);
    }
    else
    {
        printf("Error critico, clientsArray es nulo.\n");
        exit(-2);
    }
    return tmpAdminProvider;
}

int adminMenu(User *user)
{
    int flag = loggedFlag;
    AdminProvider actualAdmin = user->adminProviderUser;
    printf("Welcome user: %s\n", user->adminProviderUser.fields[adminProviderEmail]);
    do
    {
        int option;
        printf("Your id is: %i \n", actualAdmin.id);
        printf("1. Profile\n");
        printf("2. Costumer\n");
        printf("3. Providers\n");
        printf("4. Products\n");
        printf("5. Categories\n");
        printf("6. Orders\n");
        printf("7. Carriers\n");
        printf("8. Discounts\n");
        printf("9. Returns\n");
        printf("10. Logout\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                adminProfile(&actualAdmin);
                break;
            case 2:
                adminClient(&actualAdmin);
                break;
            case 3:
                adminProvider(&actualAdmin);
                break;
            case 4:
                adminProduct(&actualAdmin);
                break;
            case 5:
                adminCategory(&actualAdmin);
                break;
            case 6:
                adminOrder(&actualAdmin);
                break;
            case 7:
                adminCarrier(&actualAdmin);
                break;
            case 8:
                adminDiscount(&actualAdmin);
                break;
            case 9:
                adminReturn(&actualAdmin);
            case 10:
                logoutAdmin(&flag);
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while (flag == loggedFlag);

    return flag;
}

void logoutAdmin(int *flag)
{
    bool validOption = false;
    do
    {
        int option;
        printf("1. Exit to login\n");
        printf("2. Exit program\n");
        printf("3. Back\n");
        printf("Select an option: ");
        clearBuffer();
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                validOption = true;
                *flag = loginFlag;
                break;
            case 2:
                validOption = true;
                *flag = exitFlag;
                break;
            case 3:
                validOption = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while (!validOption);
}


void adminProfile(AdminProvider *actualAdmin)
{
    bool back = false;
    bool adminModified = false;
    do
    {
        int option;
        printf("1. View profile\n");
        printf("2. Modify profile\n");
        printf("3. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewAdminProfile(*actualAdmin);
                break;
            case 2:
                modifyAdminProfile(actualAdmin, &adminModified);
                break;
            case 3:
                if(adminModified)
                {
                    printf("Saving...\n");
                    saveAdmin(*actualAdmin);
                    adminModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewAdminProfile(AdminProvider actualAdmin)
{
    printf("#-----------------------------------------------------\n");
    printf("# Name: %s\n", actualAdmin.fields[adminProviderName]);
    printf("# ID: %s\n", actualAdmin.fields[adminProviderId]);
    printf("# Email: %s\n", actualAdmin.fields[adminProviderEmail]);
    printf("# Password: %s\n", actualAdmin.fields[adminProviderPassword]);
    printf("# Type: %s\n", actualAdmin.fields[adminProviderType]);
    printf("#-----------------------------------------------------\n");
}

void modifyAdminProfile(AdminProvider *actualAdmin, bool *adminModified)
{
    int option;
    bool back = false;
    do
    {
        printf("1. Name\n");
        printf("2. ID\n");
        printf("3. Email\n");
        printf("4. Password\n");
        printf("5. Type\n");
        printf("6. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                modifyAdminField(actualAdmin, option, adminModified);
                break;
            case 6:
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void modifyAdminField(AdminProvider *actualAdmin, int field, bool *adminModified)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", actualAdmin->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            *adminModified = strcmp(buffer, actualAdmin->fields[field]) != 0;
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualAdmin->fields[field] = reallocate(actualAdmin->fields[field], sizeof(char)*newSize, "Actual admin modified field");
            strcpy(actualAdmin->fields[field], buffer);
            correct = true;
        }
    } while (!correct);

}
void adminClient(AdminProvider actualAdmin)
{
    bool back = false;
    bool adminClientModified = false;
    do
    {
        int option;
        printf("1. View Client's Information\n");
        printf("2. Modify Client's Information\n");
        printf("3. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewAdminClientProfile(*actualAdmin);
                break;
            case 2:
                modifyAdminClientProfile(actualAdmin, &adminClientModified);
                break;
                //Function to register and unsubscribe clients, also to search info about clients
            case 3:
                if(adminClientModified)
                {
                    printf("Saving...\n");
                    saveClientAdmin(*actualAdmin);
                    adminClientModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewAdminClientProfile(AdminProvider actualAdmin)
{
    int clientNumber;
    Client *clients = getClients(&clientNumber)
    for (int i = 0; i <clientNumber; ++i)
    {
        if(strcmp(actualAdmin->fields[adminProviderId], clients->fields[clientID])==0)
        {
            printf("#-----------------------------------------------------\n");
            printf("# ID: %i\n",clients->fields[clientID]);
            printf("# Name: %s\n",clients->fields[clientName]);
            printf("# Surname: %s\n",clients->fields[clientSurname]);
            printf("# Address: %s\n", clients->fields[clientAddress]);
            printf("# Province: %s\n",clients->fields[clientProvince]);
            printf("# City: %s\n", clients->fields[clientCity]);
            printf("# Email: %s\n", clients->fields[clientEmail]);
            printf("# Password: %s\n",clients->fields[clientPassword]);
            printf("# Wallet: %f\n",clients->fields[clientWallet])
            printf("#-----------------------------------------------------\n");

        }
    }

    for(int i=0; i < clientNumber; i++)
    {
        for(int j=0; j < ClientFieldNumber; j++)
            deallocate(clients[i].fields[j],"Clients");
    }
    deallocate(clients, "Clients");
}

void modifyAdminClientProfile(Client actualClient,int field, bool *adminClientModified) //No estoy seguro de pasarle el "actualclient" ya que se modifica al cliente
{
    //Copy struct to modify
    //Function to register and unsubscribe clients, also to search info about clients
    //Also to modify Information about the clients
    int option;
    bool back = false;
    do
    {
        printf("1. ID\n");
        printf("2. Name\n");
        printf("3. Surname\n");
        printf("4. Address\n");
        printf("5. Province\n");
        printf("6. City\n");
        printf("7. Email\n");
        printf("8. Password\n");
        printf("9. Wallet\n");
        printf("10. Search Client\n");
        printf("11. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                modifyAdminClientField(actualClient, option);
                break;
            case 10:
                //searchClient
            case 11:
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void modifyAdminClientField(Client *actualClient, int field, bool *adminClientModified)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", client->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            *adminClientModified = strcmp(buffer, actualClient->fields[field]) != 0;
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualClient->fields[field] = reallocate(actualClient->fields[field], sizeof(char)*newSize, "Actual admin modified field");
            strcpy(actualAdmin->fields[field], buffer);
            correct = true;
        }
    } while (!correct);
}

void adminProvider(AdminProvider actualAdmin)
{
    bool back = false;
    bool adminProviderProviderModified = false;
    do
    {
        int option;
        printf("1. View Provider's Information\n");
        printf("2. Modify Provider's Information\n");
        printf("3. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewAdminProviderProviderProfile(*actualAdmin);
                break;
            case 2:
                modifyAdminProviderProviderProfile(actualAdmin, &adminProviderProviderModified);
                break;
                //Function to register and unsubscribe providers, also to search info about clients
            case 3:
                if(adminProviderProviderModified)
                {
                    printf("Saving...\n");
                    saveProviderProviderAdmin(*actualAdmin);
                    adminProviderProviderModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewAdminProviderProviderProfile(AdminProvider *actualAdminProvider)
{
    int providerNumber;
    AdminProvider *provider = getProviders(&providerNumber)//Should go a function called 'getProviders'
    for (int i = 0; i <providerNumber; ++i)
    {
        if(strcmp(actualAdmin->fields[adminProviderId], provider->fields[adminProviderId])==0)//
        {
            printf("#-----------------------------------------------------\n");
            printf("# Name: %s\n", actualAdmin.fields[adminProviderName]);
            printf("# ID: %s\n", actualAdmin.fields[adminProviderId]);
            printf("# Email: %s\n", actualAdmin.fields[adminProviderEmail]);
            printf("# Password: %s\n", actualAdmin.fields[adminProviderPassword]);
            printf("# Type: %s\n", actualAdmin.fields[adminProviderType]);
            printf("#-----------------------------------------------------\n");

        }
    }
}

void modifyAdminProviderProviderProfile(AdminProvider *actualAdminProvider, &adminProviderModified)
{
    bool correct = false;
    do
    {
    char buffer[1024];

    printf("The actual value is: %s\n", provider->fields[field]);
    printf("Type the new value: ");
    clearBuffer();
    scanf("%[^\n]", buffer);

    printf("The new value is: %s\n", buffer);
    if(askCorrect())
    {
    *adminAdminProviderModified = strcmp(buffer, actualAdminProvider->fields[field]) != 0;
    unsigned long newSize = strlen(buffer);
    //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
    actualAdminProvider->fields[field] = reallocate(actualAdminProvider->fields[field], sizeof(char)*newSize, "Actual Provider modified field");
    strcpy(actualAdminProvider->fields[field], buffer);
    correct = true;
    }
    } while (!correct);
}

void adminProduct(AdminProvider actualAdmin)
{
    bool back = false;
    bool adminProductModified = false;
    do
    {
        int option;
        printf("1. View Product's Information\n");
        printf("2. Modify Product's Information\n");
        printf("3. Search for a product.\n");
        printf("4. Create a Product List.\n");
        printf("5. Changes about the Providers.\n");
        printf("6. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewProductAdmin(actualAdmin);
                break;
            case 2:
                modifyProductAdmin(actualAdmin, &adminProductModified);
                break;
                //Function to register and unsubscribe clients, also to search info about clients
            case 3:
                searchProductAdmin(actualAdmin);
                break;
            case 4:
                createProductList(actualAdmin);
                break;
            case 5:
                providerChanges(actualAdmin);
                break;
            case 6:
                if(adminProductModified)
                {
                    printf("Saving...\n");
                    saveProductAdmin(*actualAdmin);
                    adminProductModified = false;
                }
                back = true;
                break;

            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewProductAdmin(AdminProvider *actualAdmin)
{
    int productsNumber;
    AdminProvider *products = getProducts(&providerNumber)//Should go a function called 'getProviders'
    for (int i = 0; i <productsNumber; ++i)
    {
        if(strcmp(actualAdmin->fields[adminProviderId], products->fields[adminProviderId])==0)//
        {
            printf("#-----------------------------------------------------\n");

            printf("# ID: %s\n", actualAdmin.fields[productOrderID]);
            printf("# Description: %s\n", actualAdmin.fields[productDescription]);
            printf("# Category: %s\n", actualAdmin.fields[productCategoryID]);
            printf("# Product Manager: %s\n", actualAdmin.fields[productCompanyID]);
            printf("# Stock: \n", actualAdmin.fields[productStock]);
            printf("# Estimated delivery time: \n", actualAdmin.fields[productMaxDaysDelay]);
            pritnf("# Prize: \n", actualAdmin.fields[productPrice]);
            printf("#-----------------------------------------------------\n");

        }
    }
}
void void modifyProductAdmin(AdminProvider actualAdmin, bool adminProductModified)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", products->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            *adminAdminProviderModified = strcmp(buffer, actualAdminProvider->fields[field]) != 0;
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualAdminProvider->fields[field] = reallocate(actualAdminProvider->fields[field], sizeof(char)*newSize, "Actual Product modified field");
            strcpy(actualAdminProvider->fields[field], buffer);
            correct = true;
        }
    } while (!correct);
}

void searchProductAdmin(AdminProvider actualAdmin)
{

}
void createProductList(AdminProvider actualAdmin)
{

}
void providerChanges(AdminProvider actualAdmin)
{

}

void adminCategory(AdminProvider actualAdmin)
{
    bool back = false;
    bool adminCategoryModified = false;
    do
    {
        int option;
        printf("1. View Category Information\n");
        printf("2. Sign up/ Unsusbcribe products from category.\n");
        printf("3. Generate lists of products.\n");
        printf("4. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewAdminCategory(*actualAdmin);
                break;
            case 2:
                signUpDownCategory(actualAdmin, &adminCategoryModified);
                break;
            case 3:
                generateListAdmin(actualAdmin);
                break;
            case 4:
                if(adminProviderProviderModified)
                {
                    printf("Saving...\n");
                    saveCategoryAdmin(*actualAdmin);
                    adminCategoryModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}
void viewAdminCategory(AdminProvider *actualAdmin)
{
    int categoryNumber;
    AdminProvider *category = getCategories(&categoryNumber)//Should go a function called 'getProviders'
    for (int i = 0; i <categoryNumber; ++i)
    {
        if(strcmp(actualAdmin->fields[adminProviderId], products->fields[adminProviderId])==0)//?
        {
            printf("#-----------------------------------------------------\n");
            printf("# ID: %s\n", actualAdmin.fields[categoryID]);
            printf("# Description: %s\n", actualAdmin.fields[categoryDescription]);
            printf("#-----------------------------------------------------\n");

        }
    }
}
void signUpDownCategory(AdminProvider actualAdmin, bool adminCategoryModified)
{

}

void generateListAdmin(AdminProvider actualAdmin)
{

}
void saveCategoryAdmin(AdminProvider *actualAdmin)
{

}

void adminOrder(AdminProvider actualAdmin)
{
    bool back = false;
    bool adminOrderModified = false;
    do
    {
        int option;
        printf("1. View Order Information\n");
        printf("2. Sign up/ Unsusbcribe products from category.\n");
        printf("3. Search for Orders.\n");
        printf("4. Generate Lists of orders.\n");
        printf("5. Modify Order Information.\n");
        printf("4. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewAdminOrder(*actualAdmin);
                break;
            case 2:
                signUpDownOrder(actualAdmin);
                break;
            case 3:
                searchOrderAdmin(actualAdmin);
                break;
            case 3:
                generateListAdmin(actualAdmin);
                break;
            case 4:
                modifyAdminOrder(actualAdmin, &adminOrderModified);
                break;
            case 5:
                assignAdminCarrier(actualAdmin);
                break;
            case 6:
                assignAdminLocker(actualAdmin);
                break;
            case 7:
                if(adminOrderModified)
                {
                    printf("Saving...\n");
                    saveOrderAdmin(*actualAdmin);
                    adminoOrderModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewAdminOrder(AdminProvider *actualAdmin)
{
    int orderNumber;
    AdminProvider *orders = getOrders(&orderNumber)//Should go a function called 'getProviders'
    for (int i = 0; i <orderNumber; ++i)
    {
        if(strcmp(actualAdmin->fields[adminProviderId], orders->fields[adminProviderId])==0)//?
        {
            printf("#-----------------------------------------------------\n");
            printf("# ID: %i\n", actualAdmin.fields[orderID]);
            printf("# Order Date: %s\n", actualAdmin.fields[orderDate]);
            printf("# Client ID: %s\n", actualAdmin.fields[orderClientID]);
            printf("# Delivery Place: %s\n", actualAdmin.fields[orderDeliveryPlace]);
            printf("# Locker ID: %s\n", actualAdmin.fields[orderLockerCode]);
            printf("# Giftcard code: %s\n", actualAdmin.fields[orderGiftDiscount]);
            printf("# Promotional code: %s\n", actualAdmin.fields[orderPromotionalCode]);
            printf("#-----------------------------------------------------\n");

        }
    }

}
void signUpDownOrder(AdminProvider actualAdmin,bool adminOrderModified)
{

}
void searchOrderAdmin(AdminProvider actualAdmin)
{

}
void generateListAdmin(AdminProvider actualAdmin)
{

}
void modifyAdminOrder(AdminProvider actualAdmin,  bool adminOrderModified)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", orders->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            *adminOrderModified = strcmp(buffer, actualAdmin->fields[field]) != 0;
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualAdmin->fields[field] = reallocate(actualAdmin->fields[field], sizeof(char)*newSize, "Actual Product modified field");
            strcpy(actualAdminProvider->fields[field], buffer);
            correct = true;
        }
    } while (!correct);
}
void assignAdminCarrier(AdminProvider actualAdmin)
{

}
void assignAdminLocker(AdminProvider actualAdmin)
{

}
void adminCarrier(AdminProvider actualAdmin)
{
    bool back = false;
    bool adminCarrierModified = false;
    do
    {
        int option;
        printf("1. View Carrier Information.\n");
        printf("2. Sign up/ Unsusbcribe Carriers.\n");
        printf("3. Search for Carriers.\n");
        printf("4. Generate lists of products.\n");
        printf("5. Modify Carrier Information.\n");
        printf("6. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewAdminCarrier(*actualAdmin);
                break;
            case 2:
                signUpDownCarrier(actualAdmin);
                break;
            case 3:
                searchAdminCarrier(actualAdmin);
                break;
            case 4:
                generateListAdmin(actualAdmin);
                break;
            case 5:
                modifyAdminCarrier(actualAdmin, &adminCarrierModified);
                break;
            case 6:
                if(adminProviderProviderModified)
                {
                    printf("Saving...\n");
                    saveCarrierAdmin(*actualAdmin);
                    adminCarrierModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewAdminCarrier(AdminProvider *actualAdmin)
{
    int carrierNumber;
    AdminProvider *carriers = getClients(&carrierNumber)
    for (int i = 0; i <carrierNumber; ++i)
    {
        if(strcmp(actualAdmin->fields[adminProviderId], orders->fields[adminProviderId])==0)//?
        {
            printf("#-----------------------------------------------------\n");
            printf("# Carrier ID: %s\n", actualAdmin.fields[carrierID]);
            printf("# Email: %s\n", actualAdmin.fields[carrierEmail]);
            printf("# Password: %s\n", actualAdmin.fields[carrierPassword]);
            printf("# Company: %s\n", actualAdmin.fields[carrierCompany]);
            printf("# City: %s\n", actualAdmin.fields[carrierCity]);
            printf("#-----------------------------------------------------\n");

        }
    }
}
void signUpDownCarrier(AdminProvider actualAdmin)
{

}
void searchAdminCarrier(AdminProvider actualAdmin)
{

}
void generateListAdmin(AdminProvider actualAdmin)
{

}
void modifyAdminCarrier(AdminProvider actualAdmin,bool adminCarrierModified)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", carriers->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            *adminCarrierModified = strcmp(buffer, actualAdmin->fields[field]) != 0;
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualAdmin->fields[field] = reallocate(actualAdmin->fields[field], sizeof(char)*newSize, "Actual Carrier modified field");
            strcpy(actualAdmin->fields[field], buffer);
            correct = true;
        }
    } while (!correct);
}

void adminDiscount(AdminProvider actualAdmin)
{
    bool back = false;
    bool adminDiscountModified = false;
    do
    {
        int option;
        printf("1. View Discount Information.\n");
        printf("2. Sign up/ Unsusbcribe Discount.\n");
        printf("3. Modify Discount Information.\n");
        printf("4. Generate lists of clients with Discount codes.\n");
        printf("5. Create a New Discount Code.\n");
        printf("6. Back\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                viewAdminDiscount(*actualAdmin);
                break;
            case 2:
                signUpDownDiscount(actualAdmin);
                break;
            case 3:
                modifyAdminDiscount(actualAdmin, &adminDiscountModified);
                break;
            case 4:
                generateListAdmin(actualAdmin);
                break;
            case 5:
                createAdminDiscount(actualAdmin);
                break;
            case 6:
                if(adminProviderProviderModified)
                {
                    printf("Saving...\n");
                    saveDiscountAdmin(*actualAdmin);
                    adminDiscountModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}
void viewAdminDiscount(AdminProvider *actualAdmin)
{
    int discountNumber;
    AdminProvider *discounts = getClients(&discountNumber)
    for (int i = 0; i <discountNumber; ++i)
    {
        if(strcmp(actualAdmin->fields[adminProviderId], discounts->fields[adminProviderId])==0)//?
        {
            printf("#-----------------------------------------------------\n");
            printf("# Discount ID: %s\n", actualAdmin.fields[discountID]);
            printf("# Description: %s\n", actualAdmin.fields[discountDescription]);
            printf("# Type: %s\n", actualAdmin.fields[discountType]);
            printf("# Status: %s\n", actualAdmin.fields[discountStatus]);
            printf("# Amount: %s\n", actualAdmin.fields[discountMoney]);
            printf("# Applicability: %s\n", actualAdmin.fields[discountApply]);
            printf("#-----------------------------------------------------\n");

        }
    }
}
void signUpDownDiscount(AdminProvider actualAdmin)
{

}
void modifyAdminDiscount(AdminProvider actualAdmin,bool adminDiscountModified)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", discounts->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            *adminDiscountModified = strcmp(buffer, actualAdmin->fields[field]) != 0;
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualAdmin->fields[field] = reallocate(actualAdmin->fields[field], sizeof(char)*newSize, "Actual Discount modified field");
            strcpy(actualAdmin->fields[field], buffer);
            correct = true;
        }
    } while (!correct);
}
void generateListAdmin(AdminProvider actualAdmin)
{

}
void createAdminDiscount(AdminProvider actualAdmin)
{

}
void saveDiscountAdmin(AdminProvider *actualAdmin)
{

}