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
    for (int i = 0; i <customerNumber; ++i)
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

