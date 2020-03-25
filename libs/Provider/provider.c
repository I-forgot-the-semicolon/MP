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


#include "provider.h"
//HECHO POR DAVID
AdminProvider loginProvider(char *email, char *password, int *pos)
{
  AdminProvider tmpAdminprovider;
  bool found = false;

  int AdminProviderArraySize;
  AdminProvider *AdminProviderArray = getAdminsProviders(&AdminProviderArraySize);

  for (int i = 0; i < AdminProviderArraySize && !found; i++) 
  {
      //printf("%s -> %s\n", email, AdminProviderArray[i].fields[AdminProviderEmail]);
        if(strcasecmp(email, AdminProviderArray[i].fields[adminProviderEmail]) == 0 && strcmp(password, AdminProviderArray[i].fields[adminProviderPassword]) == 0)
        {
            printf("Username found!\n");
            printf("Password correct!\n");
            tmpAdminprovider = AdminProviderArray[i];
            found = true;
            *pos = i;     
        }
    }

    free(AdminProviderArray);
    return tmpAdminprovider;
}

void adminProviderMenu(User *user, bool *running, AdminProvider actualAdminProvider)
{
    AdminProvider actualAdminProvider = user->adminProviderUser;

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
    printf("Your ID is %i.\n",actualAdminProvider.id);
    printf("The company that the Aministrator/Provider works for: %s\n", actualAdminProvider.fields[adminProviderName]);
    printf("Your Email is %s.\n",actualAdminProvider.fields[adminProviderEmail]);
    printf("Your password is %s.\n",actualAdminProvider.fields[adminProviderPassword]);
    printf("The type of user is %s.\n",actualAdminProvider.fields[adminProviderType]);
    printf("#---------------------------\n");

}
void ModifyAdminProviderInfo(AdminProvider actualAdminProvider)
{
    
}