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
                printf("Username found!\n");
                printf("Password correct!\n");
                tmpClient = clientsArray[i];
                printf("With id: %d\n", tmpClient.id);
                found = true;
                *pos = i;
            }
        }
        free(clientsArray);
    }
    else
    {
       printf("Error critico, clientsArray es nulo.\n");
       exit(-2);
    }
    return tmpClient;
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
    int option;
    printf("1. Exit to login\n");
    printf("2. Exit program\n");
    printf("Select an option: ");
    scanf("%d", &option);
    switch (option)
    {
        case 1:
                *flag = loginFlag;
                break;
        case 2:
                *flag = exitFlag;
                break;
        default:
                printf("Invalid option\n");
                break;
    }
}

void clientProfile(Client *actualClient)
{
    bool back = false;
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
                modifyProfile(actualClient);
                break;
            case 3:
                saveClient(*actualClient);
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

void modifyProfile(Client *actualClient)
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
                modifyField(actualClient, option);
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


void modifyField(Client *actualClient, int field)
{
    bool correct = false;
    do
    {
        char buffer[1024];
        char answer;

        printf("The actual value is: %s\n", actualClient->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        printf("Is that correct? y/n: ");
        clearBuffer();
        scanf("%c", &answer);

        if(answer == 'y')
        {
            unsigned long newSize = strlen(buffer);
            actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            strcpy(actualClient->fields[field], buffer);
            correct = true;
        }
    } while (!correct);

}

int searchClient(Client actualClient, Client *clientArray, const char *textToSearch)
{
    return 0;
}