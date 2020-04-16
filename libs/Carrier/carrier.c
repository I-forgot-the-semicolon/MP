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
  Carrier tmpCarrier = {0, nullptr};
  bool found = false;

  int carriersArraySize = 0;
  Carrier *carriersArray = getCarriers(&carriersArraySize);

    if(carriersArray != nullptr)
    {
        for (int i = 0; i < carriersArraySize && !found; i++)
        {
            if(strcmp(email, carriersArray[i].fields[carrierEmail]) == 0 && strcmp(password, carriersArray[i].fields[carrierPassword]) == 0)
            {
                found = true;
                printf("Username found!\n");
                printf("Password correct!\n");
                copyCarrier(&tmpCarrier, carriersArray[i]);
                printf("With id: %d\n", tmpCarrier.id);
                *pos = i;
            }
        }

        for(int i = 0; i < carriersArraySize; i++)
        {
            for(int j = 0; j < CarrierFieldNumber; j++)
                deallocate(carriersArray[i].fields[j], "Field from client array...");
        }
        deallocate(carriersArray, "Clients Array");
        //free(clientsArray);
    }
    else
    {
        printf("Error critico, carrier Array es nulo.\n");
        exit(-2);
    }
    return tmpCarrier;
}

int carrierMenu(User *user)
{
    int flag = loggedFlag;
    Carrier actualCarrier = user->carrierUser;
    printf("Welcome user: %s\n", user->carrierUser.fields[carrierEmail]);
    do
        {
            int option;
            printf("Your id is: %d \n", actualCarrier.id);
            printf("1. Profile\n");
            printf("2. Deliver\n");
            printf("3. Returns\n");
            printf("4. Logout\n");
            printf("Select an option: ");
            scanf("%d", &option);

            switch (option)
            {
                case 1:
                    carrierProfile(&actualCarrier);
                    break;
                case 2:
                    deliverMenu(&actualCarrier);
                    break;
                case 3:
                    //returnMenu(&actualCarrier);
                    break;
                case 4:
                    logoutCarrier(&flag);
                    break;
                default:
                    printf("Invalid option\n");
                    break;
            }
        } while (flag == loggedFlag);

    return flag;
}

void logoutCarrier(int *flag)
{
    int option;
    printf("1. Exit to login\n");
    printf("2. Exit program\n");
    printf("3. Back\n");
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
        case 3:
            break;
        default:
            printf("Invalid option\n");
            break;
        }
}

void carrierProfile(Carrier *actualCarrier)
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
                viewCarrierProfile(actualCarrier);
                break;
            case 2:
                modifyCarrierProfile(actualCarrier);
                break;
            case 3:
                //saveCarrier(actualCarrier);
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewCarrierProfile(Carrier *actualCarrier)
{
    printf("#-----------------------------------------------------\n");
    printf("# ID: %s\n", actualCarrier->id);
    printf("# Company: %s\n",actualCarrier->fields[carrierCompany]);
    printf("# City: %s\n", actualCarrier->fields[carrierCity]);
    printf("# Email: %s\n", actualCarrier->fields[carrierEmail]);
    printf("# Password: %s\n", actualCarrier->fields[carrierPassword]);
    printf("#-----------------------------------------------------\n");
}

void modifyCarrierProfile(Carrier *actualCarrier)
{
    int option;
    bool back = false;
    do
    {
        printf("1. ID\n");
        printf("2. Company\n");
        printf("3. City\n");
        printf("4. Email\n");
        printf("5. Password\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                modifyCarrierField(actualCarrier, option);
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

void modifyCarrierField(Carrier *actualCarrier, int field)
{
    bool correct = false;
    do
    {
        char buffer[1024];

        printf("The actual value is: %s\n", actualCarrier->fields[field]);
        printf("Type the new value: ");
        clearBuffer();
        scanf("%[^\n]", buffer);

        printf("The new value is: %s\n", buffer);
        if(askCorrect())
        {
            unsigned long newSize = strlen(buffer);
            //actualClient->fields[field] = realloc(actualClient->fields[field], sizeof(char)*newSize);
            actualCarrier->fields[field] = reallocate(actualCarrier->fields[field], sizeof(char)*newSize, "Actual carrier modified field");
            strcpy(actualCarrier->fields[field], buffer);
            correct = true;
        }
    } while (!correct);

}

int searchCarrier(Carrier actualCarrier, Carrier *carrierArray, const char *textToSearch)
{
    return 0;

}
void deliverMenu(Carrier *actualCarrier)
{
    int option;
    bool back = false;

    printf("Select an option\n");
    printf("1.View Deliver Info\n");
    printf("2. Modify Deliver Info\n");
    printf("3. Confirm Deliver\n");
    printf("4. Modify Locker Info\n");
    printf("5.Exit\n");

    scanf("%i",&option);
    switch (option)
    {
        case 1:
            viewDeliver(actualCarrier);
            break;
        case 2:
            modifyDeliver(actualCarrier);
            break;
        case 3:
            confirmDeliver(actualCarrier);
            break;
        case 4:
            viewLockerInfo(actualCarrier);
            break;
        case 5:

        case 6:
            back = true;
            break;
        default:
            printf("Invalid option.\n");
            break;
    }

}

void viewDeliver(Carrier *actualCarrier)
{
    int deliversNumber;
    ProductOrder *productOrder = getProductOrders(&deliversNumber);
    for(int i=0; i< deliversNumber; i++)
    {
        if(strcmp(actualCarrier->fields[carrierID], productOrder->fields[productOrderCarrierID])==0)
        {
            printf("#-----------------------------------------------------\n");
            printf("# OrderID: %i\n",productOrder->fields[productOrderID] );
            printf("# ProductID: %i\n",productOrder->fields[productOrderID]);
            printf("# Unit Number: %i\n",productOrder->fields[productOrderUnitNumber]);
            printf("# Carrier ID: %i\n", productOrder->fields[carrierID]);
            printf("# Locker Code: %i\n",productOrder->fields[productOrderLockerCode]);
            printf("# Delivery Date: %i\n", productOrder->fields[productOrderDeliveryDate]);
            printf("#-----------------------------------------------------\n");
        }

    }

    for(int i=0; i < deliversNumber; i++)
    {
        for(int j=0; j < ProductOrderFieldNumber; j++)
            deallocate(productOrder[i].fields[j],"ProductOrders");
    }
    deallocate(productOrder, "ProductOrders");
}
void modifyDeliver (Carrier *actualCarrier)
{
    //Copy struct to modify
    int option;
    bool back = false;
    do
    {
        printf("1. OrderID\n");
        printf("2. ProductID\n");
        printf("3. Unit Number\n");
        printf("4. CarrierID\n");
        printf("5. Locker Code\n");
        printf("6. Deliver Date\n");
        printf("7. Deliver Place\n");
        printf("8. Exit\n");
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
                modifyCarrierField(actualCarrier, option);
                break;
            case 8:
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}


void confirmDeliver(Carrier *actualCarrier)
{
    //Confirm Deliver Status

}
void viewLockerInfo(Carrier *actualCarrier)
{
   /*int lockersNumber;
   Locker *locker = getLockers(&lockersNumber);
   //Create function
   for(int i = 0; i < lockersNumber; i++)
   {
       printf("#-----------------------------------------------------\n");
       printf("#The Locker info: \n");
       printf("#Locker ID: %s\n", locker[i].fields[lockerID]);
       printf("#Locker City: %s\n", locker[i].fields[lockerCity]);
       printf("#Locker Provice: %s\n", locker[i].fields[lockerProvice]);
       printf("#Locker Position: %s\n", locker[i].fields[lockerPosition]);
       printf("#Total Space: %s\n", locker[i].fields[lockerTotalSpace]);
       printf("#Locker Busy Space: %s\n", locker[i].fields[lockerBusySpace]);
       printf("#-----------------------------------------------------\n");
   }

    for(int i=0; i < lockersNumber; i++)
    {
        for(int j=0; j < LockerFieldNumber; j++)
            deallocate(locker[i].fields[j],"Locker");
    }
    deallocate(locker, "Locker");*/
}

void modifyLockerInfo(Carrier *actualCarrier)
{
    //Copy struct to modify

    int option;
    bool back = false;
    do
    {
        printf("1. Locker ID\n");
        printf("2. Locker City\n");
        printf("3. Locker Provice\n");
        printf("4. Total Space\n");
        printf("5. Locker Code\n");
        printf("6. Locker Busy Space\n");
        printf("7. Exit\n");
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
                modifyCarrierField(actualCarrier, option);
                break;
            case 7:
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}