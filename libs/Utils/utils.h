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
#ifndef _UTILS_
#define _UTILS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../dataTypes.h"
#include "debug.h"

//#define DEBUG

void clearBuffer();
char *toLowerCase(char *str);
unsigned int getFieldLength(char *input);
void truncateString(char *input, unsigned int startPos);
char *copyUntil(const char *sString, unsigned int pos);
char *concatenate(char *a, char *b);
char *concatenateChar(char *a, char b);
bool isValidLine(char *tmp);
void sanitize(char *string);

bool askCorrect();
char *askForField(char *msg, bool confirm);
void askForExit(int *flag);

char *toFileStringClient(Client client);
char *getNextID(int lastID, unsigned int length);

void cleanUpUser(User *user);
void copyClient(Client *dest, Client src);
void copyAdminProvider(AdminProvider *dest, AdminProvider src);
void copyCarrier(Carrier *dest, Carrier src);
#endif