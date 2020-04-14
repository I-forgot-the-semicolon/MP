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
                printf("With id: %d\n", tmpAdminProvider.id);
                printf("Type: boof %s eeeee\n", tmpAdminProvider.fields[adminProviderType]);
                printf("Field length: %d\n", strlen(tmpAdminProvider.fields[adminProviderType]));
                for(int j = 0; j < strlen(tmpAdminProvider.fields[adminProviderType]); j++)
                    printf("char[%d]: %c\n", j, tmpAdminProvider.fields[adminProviderType][j]);

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

void adminMenu(User *user, bool *running, AdminProvider actualAdminProvider)
{

    bool logged = true;

    int optionmenu;
    char awnser;
    do
    {   do
        {
            printf("Hello Provider.\n");
            printf("Input the option that you need.\n");
            printf("1.Profile option.\n");
            printf("2.Product option.\n");
            printf("3.Order options.\n");
            printf("4. Logout");
        } while (optionmenu<1 && optionmenu>4);

        switch (optionmenu)
        {
        case 1:
            profileMenu(actualAdminProvider);
            break;
        case 2:
            //ProductMenu
            break;
        case 3:
            //OrderMenu
            break;
        case 4:
            //LogOutMenu
            break;
        default:
            break;
        }
        printf("Do you want to do something else before leaving?\n");
        clearBuffer();
        scanf("%c",&awnser);
    } while (awnser=='y');
}

void profileMenu(AdminProvider actualAdminProvider)
{
    char awnser;
    int option;
    do
    {
        do
        {
            printf("Please select an option.\n");
            printf("1. Show your Information.\n");
            printf("2.Modify your Information.\n");
            printf("3. Exit the menu.\n");
            
            switch (option)
            {
            case 1:
                ShowAdminProviderInfo(actualAdminProvider);
                break;
            case 2:
                ModifyAdminProviderInfo(actualAdminProvider);
                break;
            case 3:
                //MenuExiting
                break;    
            default:
                break;
            }

            clearBuffer();
            scanf("%i",&option);
        } while (option<1&&option>3);
        
      clearBuffer();  
    } while (awnser=='y');
}

void ShowAdminProviderInfo(AdminProvider actualAdminProvider)
{
    printf("Your info is:\n\n");
    printf("#---------------------------\n");
    printf("Your Name is %s.\n",actualAdminProvider.fields[adminProviderName]);
    printf("Your ID is %i.\n",actualAdminProvider.id);
    printf("Your Email is %s.\n",actualAdminProvider.fields[adminProviderEmail]);
    printf("Your password is %s.\n",actualAdminProvider.fields[adminProviderPassword]);
    printf("The type of user is %s.\n",actualAdminProvider.fields[adminProviderType]);
    printf("#---------------------------\n");

}
void ModifyAdminProviderInfo(AdminProvider actualAdminProvider)
{
    int optionselect;
    int awnser;
    do
    {
        printf("Select an option.\n(1)Modify your Name.\n(2)Modify your Email.\n(3)Modify your Password.\n(4)Exit.\n");
        do
        {
            clearBuffer();   
            scanf("%i",&optionselect);
            switch (optionselect)
            {
            case 1:
                do
                {
                    printf("Input the new Name that you use.\n");
                    clearBuffer();
                    scanf("%s",&actualAdminProvider.fields[adminProviderName]);
                    printf("Your NEW NAME is going to be: %s.\nIs it good?(y/n)\n",actualAdminProvider.fields[adminProviderName]);
                    clearBuffer();
                    scanf("%c",&awnser);
                } while (awnser=='n');    
                break;
            case 2:
                do
                {
                    printf("Input the NEW Email Address that you use.\n");
                    clearBuffer();
                    scanf("%s",&actualAdminProvider.fields[adminProviderEmail]);
                    printf("Your NEW EMAIL ADDRESS  is going to be: %s.\nIs it good?(y/n)\n",actualAdminProvider.fields[adminProviderEmail]);
                    clearBuffer();
                    scanf("%c",&awnser);
                } while (awnser=='n');    
                break;
            case 3:
                do
                {
                    printf("Input the NEW PASSWORD that you use.\n");
                    clearBuffer();
                    scanf("%s",&actualAdminProvider.fields[adminProviderPassword]);
                    printf("Your NEW PASSWORD is going to be: %s.\nIs it good?(y/n)\n",actualAdminProvider.fields[adminProviderPassword]);
                    clearBuffer();
                    scanf("%c",&awnser);
                } while (awnser=='n');    
                break;
            case 4:
                printf("Exiting...");
                break;
            default:
                break;
            }
        } while (optionselect>0&&optionselect<5);
        printf("Do you want to do something else before leaving?(y/n)");
        clearBuffer();
        scanf("%c",&awnser);
    } while (awnser=='y');
    
}

