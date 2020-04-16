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



#ifndef _PROVIDER_
#define _PROVIDER_

#include<string.h>
#include "../fileHandler.h"

AdminProvider loginAdminProvider(char *email, char *password, int *pos);
void adminMenu(User *user);
void adminProfile(AdminProvider actualAdmin);
void adminClient(AdminProvider actualAdmin);
void adminProvider(AdminProvider actualAdmin);
void adminProduct(AdminProvider actualAdmin);
void adminCategory(AdminProvider actualAdmin);
void adminOrder(AdminProvider actualAdmin);
void adminCarrier(AdminProvider actualAdmin);
void adminDiscount(AdminProvider actualAdmin);
void adminReturn(AdminProvider actualAdmin);
void logoutAdmin(int *flag);
void adminProfile(AdminProvider *actualAdmin);
void viewAdminProfile(AdminProvider actualAdmin);
void modifyAdminField(AdminProvider *actualAdmin, int field, bool *adminModified);
void saveAdmin(AdminProvider *actualAdmin);
void adminClient(AdminProvider actualAdmin);
void viewAdminClientProfile(AdminProvider *actualAdmin);
void modifyAdminClientProfile(Client actualClient,int field, bool *adminClientModified);
void saveClientAdmin(AdminProvider *actualAdmin);
void modifyAdminClientField(Client *actualClient, int field, bool *adminClientModified);

#endif