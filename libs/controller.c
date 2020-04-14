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
        if(loginFlag == wrongUsernameFlag)
        {
            char answer;
            printf("Do you want to create a new account? y/n\n");
            clearBuffer();
            scanf("%c", &answer);
            if(answer == 'y' || answer == 'Y')
            {
                flag = signUpNewClient();
            }
            else
            {
                askForExit(&flag);
            }
        }
        else
        {
            if(loginFlag == wrongPasswordFlag)
            {
                printf("Wrong password\n");
                askForExit(&flag);
            }
            else
            {
                flag = redirectUser(user);
            }
        }
        cleanUpUser(user);
    } while(flag != exitFlag);

}

void askForExit(int *flag)
{
    char answer;
    printf("Do you want to exit? y/n\n");
    clearBuffer();
    scanf("%c", &answer);
    if(answer == 'y' || answer == 'Y')
    {
        *flag = exitFlag;
    }
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
            break;
        case provider:
            break;
        default:
            break;
    }
    return flag;
}

int login(User *userArray)
{
    char *username = nullptr;
    char *password = nullptr;

    username = askForField("Username", username, false);
    password = askForField("Password", password, false);

    int pos = -1;
    int mode = client;

    printf("Searching...\n");
    while(pos < 0 && mode < 4)
    {
        switch (mode)
        {
            case client:
                printf("Searching in client\n");
                userArray->clientUser = loginClient(username, password, &pos);
                userArray->userType = client;
                break;
            case carrier:
                //printf("Searching in carrier\n");
                //userArray->carrierUser = loginCarrier(username, password, &pos);
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
    
    if(pos >= 0)
    {
        printf("Login correct, welcome %s\n", username);
    }
    else
    {
        printf("Invalid email or password\n");
    }

    //free(username);
    //free(password);
    deallocate(username, "Username");
    deallocate(password, "Password");

    printf("Returning %d\n", pos);
    return pos;
}