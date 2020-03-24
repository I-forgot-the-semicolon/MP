#include "client.h"

Client loginClient(char *email, char *password, int *pos)
{
    Client tmpClient;
    bool found = false;

    int clientsArraySize;
    Client *clientsArray = getClients(&clientsArraySize);

    for (int i = 0; i < clientsArraySize && !found; i++) 
    {
        //printf("%s -> %s\n", email, carriersArray[i].fields[carrierEmail]);
        if(strcmp(email, clientsArray[i].fields[clientEmail]) == 0 && strcmp(password, clientsArray[i].fields[clientPassword]) == 0)
        {
            printf("Username found!\n");
            printf("Password correct!\n");
            tmpClient = clientsArray[i];
            found = true;
            *pos = i;     
        }
    }

    free(clientsArray);
    return tmpClient;
}

void clientMenu(User *user, bool *running)
{
    Client actualClient = user->clientUser;
    printf("Welcome user: %s\n", user->clientUser.fields[clientEmail]);
    bool logged = true;
    do
    {
        int option;
        printf("1. Profile\n");
        printf("2. Products\n");
        printf("3. Discounts\n");
        printf("4. Orders\n");
        printf("5. Returns\n");
        printf("6. Logout\n");

        printf("Select an option: ");
        scanf("%d", &option);

        if(option == 6)
            logged = false;

    } while (logged);
    
}