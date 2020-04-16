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

#include "client.h"

Client loginClient(char *email, char *password, int *pos)
{
    Client tmpClient = {0, 0, nullptr};
    bool found = false;

    int clientsArraySize = 0;
    Client *clientsArray = getClients(&clientsArraySize);

    if(clientsArray != nullptr)
    {
        for (int i = 0; i < clientsArraySize && !found; i++)
        {
            if(strcmp(email, clientsArray[i].fields[clientEmail]) == 0 && strcmp(password, clientsArray[i].fields[clientPassword]) == 0)
            {
                found = true;
                printf("Username found!\n");
                printf("Password correct!\n");
                copyClient(&tmpClient, clientsArray[i]);
                printf("With id: %d\n", tmpClient.id);
                *pos = i;
            }
        }

        for(int i = 0; i < clientsArraySize; i++)
        {
            for(int j = 0; j < ClientFieldNumber; j++)
                deallocate(clientsArray[i].fields[j], "Field from client array...");
        }
        deallocate(clientsArray, "Clients Array");
        //free(clientsArray);
    }
    else
    {
       printf("Error critico, clientsArray es nulo.\n");
       exit(-2);
    }
    return tmpClient;
}

int signUpNewClient()
{
    int index = getLastIndex("../databases/clientes.txt");

    Client newClient = {0, 0, nullptr};
    newClient.fields[clientID] = getNextID(index, 6);
    newClient.fields[clientName] = askForField("Name", true);
    newClient.fields[clientSurname] = askForField("Last Name", true);
    newClient.fields[clientAddress] = askForField("Address", true);
    newClient.fields[clientCity] = askForField("City", true);
    newClient.fields[clientProvince] = askForField("Province", true);
    newClient.fields[clientEmail] = askForField("Email", true);
    newClient.fields[clientPassword] = askForField("Password", true);
    newClient.fields[clientWallet] = allocate(sizeof(char)*5, "New client wallet");
    strcpy(newClient.fields[clientWallet], "0");

    char *finalString = toFileStringClient(newClient);
    int flag = saveNewLine("../databases/clientes.txt", finalString);

    deallocate(finalString, "Final String new client");

    for(int i = 0; i < 9; i++)
    {
        deallocate(newClient.fields[i], "New client field");
    }

    if(flag == okFlag)
        printf("Cuenta creada correctamente!\n");
    return flag;
}

int clientMenu(User *user)
{
    int flag = loggedFlag;
    Client actualClient = user->clientUser;
    printf("Welcome user: %s\n", user->clientUser.fields[clientEmail]);
    do
    {
        int option;
        printf("Your id is: %d \n", actualClient.id);
        printf("1. Profile\n");
        printf("2. Products\n");
        printf("3. Discounts\n");
        printf("4. Orders\n");
        printf("5. Returns\n");
        printf("6. Logout\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                clientProfile(&actualClient);
                break;
            case 2:
                clientProducts(&actualClient);
                break;
            case 6:
                logoutClient(&flag);
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while (flag == loggedFlag);

    return flag;
}

void logoutClient(int *flag)
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

void clientProfile(Client *actualClient)
{
    bool back = false;
    bool clientModified = false;
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
                viewProfile(*actualClient);
                break;
            case 2:
                modifyProfile(actualClient, &clientModified);
                break;
            case 3:
                if(clientModified)
                {
                    printf("Saving...\n");
                    saveClient(*actualClient);
                    clientModified = false;
                }
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewProfile(Client actualClient)
{
    printf("#-----------------------------------------------------\n");
    printf("# Name: %s\n", actualClient.fields[clientName]);
    printf("# Surname: %s\n", actualClient.fields[clientSurname]);
    printf("# Address: %s\n", actualClient.fields[clientAddress]);
    printf("# City: %s\n", actualClient.fields[clientCity]);
    printf("# Province: %s\n", actualClient.fields[clientProvince]);
    printf("# Email: %s\n", actualClient.fields[clientEmail]);
    printf("# Password: %s\n", actualClient.fields[clientPassword]);
    printf("# Wallet: %s\n", actualClient.fields[clientWallet]);
    printf("#-----------------------------------------------------\n");
}

void modifyProfile(Client *actualClient, bool *clientModified)
{
    int option;
    bool back = false;
    do
    {
        printf("1. Name\n");
        printf("2. Surname\n");
        printf("3. Address\n");
        printf("4. City\n");
        printf("5. Province\n");
        printf("6. Email\n");
        printf("7. Password\n");
        printf("8. Wallet\n");
        printf("9. Back\n");

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
                modifyField(actualClient, option, clientModified);
                break;
            case 9:
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void clientProducts(Client *actualClient)
{
    bool back = false;
    bool clientModified = false;
    do
    {
        int option;
        printf("1. Search by name\n");
        printf("2. Search by category\n");
        printf("3. Back\n");

        printf("Select an option: ");
        clearBuffer();
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                searchProductByName();
                break;
            case 2:
                searchProductByCategory();
                break;
            case 3:
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void modifyField(Client *actualClient, int field, bool *clientModified)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", actualClient->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            *clientModified = strcmp(buffer, actualClient->fields[field]) != 0;
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualClient->fields[field] = reallocate(actualClient->fields[field], sizeof(char)*newSize, "Actual client modified field");
            strcpy(actualClient->fields[field], buffer);
            correct = true;
        }
    } while (!correct);

}

