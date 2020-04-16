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
#include "Utils/utils.h"
#include "Utils/debug.h"

void flowController()
{
    int flag = NOP;
    int loginFlag;
    do
    {
        //User *user = malloc(sizeof(User));
        User *user = allocate(sizeof(User), "User");

        loginFlag = login(user);

        if(loginFlag == wrongLogin)
        {
            char answer;
            printf("Do you want to create a new account? y/n\n");
            clearBuffer();
            scanf("%c", &answer);
            if(answer == 'y' || answer == 'Y')
            {
                flag = signUpNewClient();
            }
            askForExit(&flag);
        }
        else
        {
            flag = redirectUser(user);
        }
        cleanUpUser(user);
    } while(flag != exitFlag);
    showMemory();
}

int redirectUser(User *user)
{
    int flag = NOP;
    switch (user->userType)
    {
        case client:
            flag = clientMenu(user);
            break;
        case carrier:
            printf("Welcome carrier: %s\n", user->carrierUser.fields[carrierEmail]);
            break;
        case admin:
            printf("Welcome admin: %s\n", user->adminProviderUser.fields[carrierEmail]);
            break;
        case provider:
            printf("Welcome provider: %s\n", user->adminProviderUser.fields[carrierEmail]);
            break;
        default:
            break;
    }
    return flag;
}

int login(User *user)
{
    char *username = askForField("Username",false);
    char *password = askForField("Password",false);


    int pos = wrongLogin;
    int mode = 0;

    printf("Searching...\n");
    while(pos < 0 && mode < 4)
    {
        switch (mode)
        {
            case client:
                printf("Searching in client\n");
                user->clientUser = loginClient(username, password, &pos);
                user->userType = client;
                break;
            case carrier:
                user->carrierUser = loginCarrier(username, password, &pos);
                user->userType = carrier;
                break;
            case admin:
            case provider:
                user->adminProviderUser = loginAdminProvider(username, password, &pos);
                if(user->adminProviderUser.fields[adminProviderType] != nullptr)
                {
                    user->userType = (strcmp(user->adminProviderUser.fields[adminProviderType], "admin") == 0) ? admin : provider;
                }
                break;
            default:
                break;
        }
        mode++;
    }
    
    if(pos >= 0)
    {
        printf("Login correct, welcome %s\n", username);
    }
    else
    {
        user->userType = none;
        printf("Invalid email or password\n");
    }

    //free(username);
    //free(password);
    deallocate(username, "Username");
    deallocate(password, "Password");

    printf("Returning %d\n", pos);
    return pos;
}