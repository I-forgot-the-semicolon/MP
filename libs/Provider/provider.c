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