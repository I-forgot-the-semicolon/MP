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