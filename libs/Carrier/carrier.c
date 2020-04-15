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
    Carrier actualCarrier = user->actualCarrier;
    printf("Welcome user: %s\n", user->clientUser.fields[clientEmail]);
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
                    returnMenu(&actualCarrier);
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

void carrierProfile(Client *actualCarrier)
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
                viewProfile(actualCarrier);
                break;
            case 2:
                modifyProfile(actualCarrier);
                break;
            case 3:
                saveClient(*actualCarrier);
                back = true;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while(!back);
}

void viewProfile(Carrier *actualCarrier)
{
    printf("#-----------------------------------------------------\n");
    printf("# ID: %s\n", actualCarrier->id);
    printf("# Company: %s\n",actualCarrier->fields[carrierCompany]);
    printf("# City: %s\n", actualCarrier->fields[carrierCity]);
    printf("# Email: %s\n", actualCarrier->fields[carrierEmail]);
    printf("# Password: %s\n", actualCarrier->fields[carrierPassword]);
    printf("#-----------------------------------------------------\n");
}

void modifyProfile(Carrier *actualCarrier)
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
                modifyField(actualCarrier,option);
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

void modifyField(Carrier *actualCarrier, int field)
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
void deliverMenu(ProductOrder *actualProductOrder, Locker *actualLocker, Order *actualOrder)
{
    int option;
    bool back = false;

    printf("Select an option\n");
    printf("1.View Deliver Info\n");
    printf("2. Modify Deliver Info\n");
    printf("3. Modify Locker Info\n");
    printf("4.Exit\n");

    scanf("%i",&option);
    switch (option)
    {
        case 1:
            viewDeliver(actualProductOrder, actualOrder);
            break;
        case 2:
            modifyDeliver(actualProductOrder, actualOrder);
            break;
        case 3:
            modifyLockerInfo(actualProductOrder, actualLocker);
            break;
        case 4:
            back = true;
            break;
        default:
            printf("Invalid option.\n");
            break;
    }

}

void viewDeliver(ProductOrder *actualProductOrder, Order *actualOrder)
{
    printf("#-----------------------------------------------------\n");
    printf("# OrderID: %i\n", actualProductOrder->fields[orderID]);
    printf("# ProductID: %i\n",actualProductOrder->fields[productOrderID]);
    printf("# Unit Number: %i\n",actualProductOrder->fields[productOrderUnitNumber]);
    printf("# Locker Code: %i\n", actualProductOrder->fields[orderLockerCode]);
    printf("# Deliver Date: %i\n", actualProductOrder->deliveryDate);
    printf("# Deliver Place: %s\n", actualOrder->fields[orderDeliveryPlace]);
    printf("#-----------------------------------------------------\n");

}
void modifyDeliver (ProductOrder *actualProductOrder, Order *actualOrder)
{
    int option;
    bool back = false;
    do
    {
        printf("1. OrderID\n");
        printf("2. ProductID\n");
        printf("3. Unit Number\n");
        printf("4. Locker Code\n");
        printf("5. Deliver Date\n");
        printf("6. Deliver Place\n");

        printf("Select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                modifyField(actualProductOrder,option);
                break;
            case 5:
            case 6:
                modifyField(actualOrder,option);
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
void modifyLockerInfo(ProductOrder *actualProductOrder, Locker *actualLocker)
{

}