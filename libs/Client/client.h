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

#ifndef _CLIENT_
#define _CLIENT_

#include <string.h>
#include "../Utils/utils.h"
#include "../fileHandler.h"

Client loginClient(char *email, char *password, int *pos);
int signUpNewClient();

int clientMenu(User *user);
void clientProfile(Client *actualClient);
void viewProfile(Client actualClient);
void modifyProfile(Client *actualClient);
void modifyField(Client *actualClient, int field);
void logoutClient(int *flag);

int searchClient(Client actualClient, Client *clientArray, const char *textToSearch);

#endif