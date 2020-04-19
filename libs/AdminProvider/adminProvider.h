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
void viewAdminProviderProviderProfile(AdminProvider *actualAdminProvider);
void modifyAdminProviderProviderProfile(AdminProvider *actualAdminProvider, bool adminProviderModified);
void viewProductAdmin(AdminProvider *actualAdmin);
void modifyProductAdmin(AdminProvider actualAdmin, bool adminProductModified);
void searchProductAdmin(AdminProvider actualAdmin);
void saveProductAdmin(AdminProvider *actualAdmin);
void searchProductAdmin(AdminProvider actualAdmin);
void createProductList(AdminProvider actualAdmin);
void providerChanges(AdminProvider actualAdmin);
void viewAdminCategory(AdminProvider *actualAdmin);
void signUpDownCategory(AdminProvider actualAdmin, bool adminCategoryModified);
void generateListAdmin(AdminProvider actualAdmin);
void saveCategoryAdmin(AdminProvider *actualAdmin);
void viewAdminOrder(AdminProvider *actualAdmin);
void signUpDownOrder(AdminProvider actualAdmin,bool adminOrderModified);
void searchOrderAdmin(AdminProvider actualAdmin);
void generateListAdmin(AdminProvider actualAdmin);
void modifyAdminOrder(AdminProvider actualAdmin);
void assignAdminCarrier(AdminProvider actualAdmin);
void assignAdminLocker(AdminProvider actualAdmin);
void saveOrderAdmin(AdminProvider *actualAdmin);
void viewAdminOrder(AdminProvider *actualAdmin);
void signUpDownOrder(AdminProvider actualAdmin);
void searchOrderAdmin(AdminProvider actualAdmin);
void generateListAdmin(AdminProvider actualAdmin);
void modifyAdminOrder(AdminProvider actualAdmin, bool adminOrderModified);
void assignAdminCarrier(AdminProvider actualAdmin);
void assignAdminLocker(AdminProvider actualAdmin);
void viewAdminCarrier(AdminProvider *actualAdmin);
void signUpDownCarrier(AdminProvider actualAdmin);
void searchAdminCarrier(AdminProvider actualAdmin);
void generateListAdmin(AdminProvider actualAdmin);
void modifyAdminCarrier(AdminProvider actualAdmin,bool adminCarrierModified);
void saveCarrierAdmin(AdminProvider *actualAdmin);
void viewAdminDiscount(AdminProvider *actualAdmin);
void signUpDownDiscount(AdminProvider actualAdmin);
void modifyAdminDiscount(AdminProvider actualAdmin,bool adminDiscountModified);
void generateListAdmin(AdminProvider actualAdmin);
void saveDiscountAdmin(AdminProvider *actualAdmin);
void createAdminDiscount(AdminProvider actualAdmin);
#endif