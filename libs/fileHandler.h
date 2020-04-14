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

#ifndef _FILEHANDLER_
#define _FILEHANDLER_
//#define DEBUG

#include <string.h>
#include "Utils/utils.h"
#include "dataTypes.h"
#include "debug.h"

int getLastIndex(char *path);
int saveNewLine(char *path, char *string);

Client* getClients(int *clientsNumber);
void getClientFromFile(char *input, int field, int maxFields, Client *clientArray, int clientNumber);
void saveClient(Client actualClient);

AdminProvider* getAdminsProviders(int *adminsProvidersNumber);
void getAdminsProvidersFromFile(char *input, int field, int maxFields, AdminProvider *adminsProviderArray, int adminProviderNumber);

Product* getProducts(int *productsNumber);
void getProductFromFile(char *input, int field, int maxFields, Product *productArray, int productNumber);

Carrier* getCarriers(int *carriersNumber);
void getCarrierFromFile(char *input, int field, int maxFields, Carrier *carrierArray, int carrierNumber);

Refund* getRefunds(int *refundsNumber);
void getRefundFromFile(char *input, int field, int maxFields, Refund *refundArray, int refundNumber);

Order* getOrders(int *ordersNumber);
void getOrdersFromFile(char *input, int field, int maxFields, Order *orderArray, int orderNumber);

ProductOrder* getProductOrders(int *productOrdersNumber);
void getProductOrdersFromFile(char *input, int field, int maxFields, ProductOrder *productOrderArray, int productOrderNumber);

Product* getProducts(int *productsNumber);
void getProductsFromFile(char *input, int field, int maxFields, Product *productArray, int productNumber);

Category* getCategories(int *categoriesNumber);
void getCategoriesFromFile(char *input, int field, int maxFields, Category *categoryArray, int categoryNumber);

Discount* getDiscounts(int *discountsNumber);
void getDiscountsFromFile(char *input, int field, int maxFields, Discount *discountArray, int discountNumber);


#endif