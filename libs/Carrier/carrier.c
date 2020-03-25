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

//David
void CarrierMenu(User *user, bool *runing, Client actualClient)
{
    Carrier actualCarrier = user->carrierUser;
    bool looged = true;

    int OptionSelect;
    printf("Hi, %s\n", actualCarrier.fields[carrierEmail]);
    printf("1.Profile Options.\n");
    printf("2.Distribution Options.\n");
    printf("3.Return Options.\n");
    printf("Select an option.\n");
    do
    {
       scanf("%i",&OptionSelect);
        switch (OptionSelect)
        {
        case 1:
        ProfileMenu(actualCarrier);
        break;
        case 2:
        DistributionMenu(actualCarrier,actualClient);
        break;
        case 3:
        //ReturnMenu(carrier);
        break;    
        default:
        break;
        }
    } while (looged);
    
    
}
//David
void ProfileMenu(Carrier actualCarrier)
{
    char awnser[1];
    int optionSelect;
    printf("Select which option you need.\n");
    printf("1. Show Profile Info.\n");
    printf("2.Modify Profile Info.\n");
    printf("3. Leave Menu.\n");
    do
    {  
        do
        {
            scanf("%i",&optionSelect);
            
        } while (optionSelect>0||optionSelect<4);

        switch (optionSelect)
            {
            case 1:
               ShowCarrierInfo(actualCarrier);
                break;
            case 2:
                ModifyCarrierInfo(actualCarrier);
            default:
                break;
            }

            printf("Do you want to do something else befoer leaving?\n");
            scanf("%s",&awnser);

    } while (awnser[0]!='y');
}
//David
void ShowCarrierInfo(Carrier actualCarrier)
{

    printf("Your info is:\n\n");
    printf("#---------------------------\n");
    printf("Email: %s", actualCarrier.fields[carrierEmail]);
    printf("The company that the Carriers work for: %s\n", actualCarrier.fields[carrierCompany]);
    printf("The city of the business that work for:%s\n", actualCarrier.fields[carrierCity]);    
    printf("#---------------------------\n");
}

//  DAVID
void ModifyCarrierInfo(Carrier actualCarrier)
{
    int optionSelect;
    char anwser[1];
    printf("Please select the field that you want to modify.\n");
    printf("1. Email.\n");
    printf("2.The company.\n");
    printf("3.The city.\n");
    scanf("%i",&optionSelect);
    switch (optionSelect)
    {
    case 1:
        do
        {
            printf("Modifying Email.\n");
            printf("Add your new Email account.\n");
            scanf("%s",actualCarrier.fields[carrierEmail]);
            printf("Is that correct?(y/n).\n");
            scanf("%c",&anwser);
        } while (anwser[0]!='y');
        break;
    case 2:
        do
        {
            printf("Modifying The Company.\n");
            printf("Modify the name of the company.\n");
            scanf("%s",actualCarrier.fields[carrierCompany]);
            printf("Is that correct?(y/n).\n");
            scanf("%c",&anwser);
        } while (anwser[0]!='y');

        break;
    case 3:
        do
        {
            printf("Modifying The City.\n");
            printf("Change the name of the City.\n");
            scanf("%s",actualCarrier.fields[carrierEmail]);
            printf("Is that correct?(y/n).\n");
            scanf("%c",&anwser);
        } while (anwser[0]!='y');
        break;
    default:
        break;
    }

}
//David
void DistributionMenu(Carrier actualCarrier, Client actualClient)
{
    int optionSelect;
    char awnser[1];
    printf("Select the one of the following options.\n");
    printf("1. To show order information.\n");
    printf("2. To modify order information.\n");
    printf("3. To leave the menu.\n");

    do
    {
        do
        {
            scanf("%i",&optionSelect);
        } while (optionSelect>0||optionSelect<4);

        switch (optionSelect)
        {
        case 1:
            ShowDistributionInfo(actualCarrier,actualClient);
            break;
        case 2:
            ModifyDistributionInfo(actualCarrier, actualClient);
            break;
        case 3:
            break;
        default:
            break;
        }
        printf("Do you want something else before leaving?\n");
    } while (awnser[0]=='y');
    
    
    

}