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

AdminProvider loginProvider(char *email, char *password, int *pos);
void adminProviderMenu(User *user, bool *running, AdminProvider actualAdminProvider);
void profileMenu(AdminProvider actualAdminProvider);
void ShowAdminProviderInfo(AdminProvider actualAdminProvider);
void ModifyAdminProviderInfo(AdminProvider actualAdminProvider);
#endif