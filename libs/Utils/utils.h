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
#include "dataTypes.h"

//#define DEBUG

void clearBuffer();
unsigned int getFieldLength(char *input);
void truncateString(char *input, unsigned int startPos);
char *copyUntil(const char *sString, unsigned int pos);
char *concatenate(char *a, char *b);
char *concatenateChar(char *a, char b);

char *toFileStringClient(Client client);
#endif