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

#include "controller.h"

void flowController(bool* running)
{
    int flag;
    do
    {
        User *user = malloc(sizeof(User));
        bool loginCorrect = false;
    
        do
        {
            loginCorrect = login(user);
            if(!loginCorrect)
            {
                char *answer = malloc(sizeof(char));
                printf("Do you want to exit? y/n\n");
                scanf("%s", answer);
                if(*answer == 'y' || *answer == 'Y')
                {
                    *running = false;
                }       
                free(answer);
            }
        } while (!loginCorrect && *running);
    
        if(loginCorrect)    
            flag = redirectUser(user, running);

        free(user);

    } while(flag != exitFlag);
    
    
}

int redirectUser(User *user, bool *running)
{
    int flag;
    switch (user->userType)
    {
        case client:
            flag = clientMenu(user, running);
            break;
        case carrier:
            printf("Welcome carrier: %s\n", user->carrierUser.fields[carrierEmail]);
            break;
        case admin:
            break;
        case provider:
            break;
        default:
            break;
    }
    return flag;
}

bool login(User *userArray)
{
    char buffer[1024];
    char *username;
    char *password;

    printf("Username: ");
    scanf("%s", buffer);
    username = malloc(sizeof(char)*strlen(buffer));
    strcpy(username, buffer);

    printf("Password: ");
    scanf("%s", buffer);
    password = malloc(sizeof(char)*strlen(buffer));
    strcpy(password, buffer);

    int pos = -1;
    int mode = client;

    printf("Searching...\n");
    while(pos == -1 && mode < 4)
    {
        switch (mode)
        {
            case client:
                printf("Searching in client\n");
                userArray->clientUser = loginClient(username, password, &pos);
                userArray->userType = client;
                break;
            case carrier:
                printf("Searching in carrier\n");
                userArray->carrierUser = loginCarrier(username, password, &pos);
                userArray->userType = carrier;
                break;
            case admin:
                userArray->userType = admin;
                break;
            case provider:
                userArray->userType = provider;
                break;
            default:
                break;
        }
        printf("Searching: %d\n", mode);
        mode++;
    }
    
    if(pos != -1)
    {
        printf("Login correct, welcome %s\n", username);
    }
    else
    {
        printf("Invalid email or password\n");
    }
    
    free(username);
    free(password);
    return pos != -1 ? true : false;
}