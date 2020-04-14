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

#ifndef _DATATYPES_
#define _DATATYPES_

#define nullptr NULL
#define bool int
#define true 1
#define false 0

// Atoms structs
typedef struct
{
    int day;
    int month;
    int year;
} Date;

enum userType {client = 3, carrier = 2, admin = 0, provider = 1, none = 4};

enum flags {loginFlag, saveFlag, exitFlag, loggedFlag, NOP, okFlag, errorFlag};
enum loginFlags {wrongLogin = -1};

//Custom structs

typedef struct 
{
    int pos;
    int id;
    char *username;
    int type;
    bool changed;
} Session;

typedef struct 
{
    int id;
    float wallet;
    char *fields[9];
} Client;
#define ClientFieldNumber 9

enum ClientFields {clientID, clientName, clientSurname, clientAddress, 
                   clientCity, clientProvince, clientEmail, clientPassword, clientWallet};

typedef struct 
{
    int id;
    char *fields[5];
} Carrier;
#define CarrierFieldNumber 5

enum CarrierFields {carrierID, carrierEmail, carrierPassword, carrierCompany, carrierCity};


typedef struct 
{
    int orderId;
    int productId;
    Date refundDate;
    Date acceptDate;
    Date expirationDate;
    char *fields[7];
} Refund;
#define RefundFieldNumber 7

enum RefundFields {refundOrderId, refundProductId, refundDate, 
                    refundReason, refundState, refundAcceptDate, refundExpirationDate};

typedef struct 
{
    int id;
    char *fields[5];
} AdminProvider;
#define AdminProviderFieldNumber 5

enum AdminProviderFields {adminProviderId, adminProviderName, adminProviderEmail, 
                            adminProviderPassword, adminProviderType};

typedef struct 
{
    int productId;
    int categoryId;
    int companyId;
    int stock;
    int maxDaysDelay;
    float price;
    char *fields[7];
} Product;
#define ProductFieldNumber 7

typedef struct 
{
    int orderID;
    int clientID;
    int lockerCode;
    Date orderDate;
    char *fields[7];
} Order;
#define OrderFieldNumber 7

enum OrderFields {orderID, orderDate, orderClientID, orderDeliveryPlace, orderLockerCode,
                  orderGiftDiscount, orderPromotionalCode};

typedef struct 
{
    int orderID;
    int productID;
    int unitNumber;
    int carrierID;
    int lockerCode;
    Date deliveryDate;
    float buyPrice;
    Date returnDate;
    char *fields[8];
} ProductOrder;
#define ProductOrderFieldNumber 8

enum ProductOrderFields {productOrderID, productOrderProductID, productOrderUnitNumber,
                         productOrderDeliveryDate, productOrderOrderStatus, productOrderCarrierID,
                         productOrderLockerCode, productOrderReturnDate};


typedef struct 
{
    int categoryID;
    char *fields[2];
} Category;
#define CategoryFieldNumber 2
enum CategoryFields {categoryID, categoryDescription};


typedef struct 
{
    int discountID;
    int discountMoney;
    char *fields[6];
} Discount;
#define DiscountFieldNumber 6

enum DiscountFields {discountID, discountDescription, discountType, discountStatus,
                     discountMoney, discountApply};

typedef struct 
{
    int clientID;
    int discountID;
    Date assignDate;
    Date caducityDate;
    bool Applied;
    char *fields[5];
} DiscountClient;
#define DiscountClientFieldNumber 5

enum DiscountClientFields {discountClientID, discountClientDiscountID, discountClientAssignDate, 
                            discountClientCaducityDate, discountClientApplied};

typedef struct 
{
    int lockerID;
    int totalSpace;
    int busySpace;
    char *fields[6];
} Locker;
#define LockerFieldNumber 6

enum LockerFields {lockerID, lockerCity, lockerProvice, lockerPosition, lockerTotalSpace,
                   lockerBusySpace};

typedef struct 
{
    int lockerID;
    int SpaceID;
    int lockerCode;
    Date busyDate;
    Date caducityDate;
    char *fields[6];
} LockerSpace;
#define LockerSpaceFieldNumber 6

enum LockerSpaceFields {lockerSpaceLockerID, lockerSpaceID, lockerSpaceCode, lockerSpaceStatus, 
                        lockerSpaceBusyDate, lockerSpaceCaducityDate};

//------------------
typedef struct
{
    Client clientUser;
    Carrier carrierUser;
    AdminProvider adminProviderUser;
    int userType;
} User;

#endif
