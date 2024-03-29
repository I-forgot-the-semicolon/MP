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

#ifndef _CARRIER_
#define _CARRIER_

#include <string.h>
#include "../fileHandler.h"

Carrier loginCarrier(char *email, char *password, int *pos);
void CarrierMenu(User *user);
void carrierProfile(Carrier *actualCarrier);
void logoutCarrier(int *flag);
void viewCarrierProfile(Carrier *actualCarrier);
void modifyCarrierProfile(Carrier *actualCarrier);
void modifyCarrierField(Carrier *actualCarrier, int field);
int searchCarrier(Carrier actualCarrier, Carrier *carrierArray, const char *textToSearch);
void deliverMenu(Carrier *actualCarrier);
void viewDeliver(Carrier *actualCarrier);
void modifyDeliver (Carrier *actualCarrier);
void confirmDeliver(Carrier *actualCarrier);
void modifyLockerInfo(Carrier *actualCarrier);
void confirmDeliver(Carrier *actualCarrier);
void returnMenu(Carrier *actualCarrier);
void viewLockerInfo(Carrier *actualCarrier);
void ShowDistributionMenu(ProductOrder actualProductOrder);

#endif