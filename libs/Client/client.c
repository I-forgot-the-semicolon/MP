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