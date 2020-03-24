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

#include "carrier.h"


Carrier loginCarrier(char *email, char *password, int *pos) 
{
  Carrier tmpCarrier;
  bool found = false;

  int carriersArraySize;
  Carrier *carriersArray = getCarriers(&carriersArraySize);

  for (int i = 0; i < carriersArraySize && !found; i++) 
  {
      //printf("%s -> %s\n", email, carriersArray[i].fields[carrierEmail]);
        if(strcasecmp(email, carriersArray[i].fields[carrierEmail]) == 0 && strcmp(password, carriersArray[i].fields[carrierPassword]) == 0)
        {
            printf("Username found!\n");
            printf("Password correct!\n");
            tmpCarrier = carriersArray[i];
            found = true;
            *pos = i;     
        }
    }

    free(carriersArray);
    return tmpCarrier;
}

void CarrierMenu(Carrier *user, bool *runing)
{
    Carrier actualCarrier = user->carrierUser;
    bool looged = true
    int OptionSelect;
    printf("Hi, %s\n",user->carrierUser.fields[carrierEmail]);
    printf("Select the option that you want.\n");
    printf("1.Profile Options.\n");
    printf("1.Distribution Options.\n");
    printf("1.Return Options.\n");

    scanf("%i",&OptionSelect);
    switch (OptionSelect)
    {
    case 1:
        ProfileMenu(carrier);
        break;
    case 2:
        DistributionMenu(carrier);
        break;
    case 3:
        ReturnMenu(carrier);
        break;    
    default:
        break;
    }
}

Carrier ProfileMenu(carrier)
{
    int optionselect;
    printf("Please, select the option that the user wants.\n");
    printf("1. Show & Modify Carrier Info.\n");
    printf("2. Modify Carrier Info.\n");
    printf("3. Exit.\n");
    scanf("%i",&optionselect);
    do
    {
        switch (optionselect)
        {
        case 1:
            ShowCarrierInfo(carrierID, carrierEmail, carrierCompany, carrierCity);

        break;

        case 2:
            ModifyCarrierInfo(carrierID, carrierEmail, carrierCompany, carrierCity);
        break;

        default: 
        break;
        }

    } while (optionselect>0 && optionselect<3);
}

Carrier ShowCarrierInfo(int *carrierID, char *carrierEmail, char *carrierCompany, char *carrierCity)
{
    do
    {
        char optionSelect[1];
        printf("Your info is:\n\n");
        printf("ID: %i",carrierID);
        printf("Email: %s",carrierEmail);
        printf("The company that the Carriers work for: %s\n",carrierCompany);
        printf("The city of the business that work for:%s\n",carrierCity);
        printf("Do you want to modify something about your profile?(y/n)\n");
        scanf("%c",&optionSelect);
        ModifyCarrierInfo(carrierID, carrierEmail, carrierCompany, carrierCity);
    } while (strcmp('y',optionSelect)==1);
    
}

Carrier ModifyCarrierInfo(int *carrierID, char *carrierEmail, char *carrierCompany, char *carrierCity)
{
    printf("To modify a fie");
}