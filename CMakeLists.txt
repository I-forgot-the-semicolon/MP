cmake_minimum_required(VERSION 3.15)
project(MP)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs)
include_directories(libs/Admin)
include_directories(libs/Carrier)
include_directories(libs/Client)
include_directories(libs/AdminProvider)
include_directories(libs/Utils)

add_executable(MP
        main.c
        libs/Admin/admin.c
        libs/Admin/admin.h
        libs/Carrier/carrier.c
        libs/Carrier/carrier.h
        libs/Client/client.c
        libs/Client/client.h
        libs/AdminProvider/adminProvider.c
        libs/AdminProvider/adminProvider.h
        libs/Utils/utils.c
        libs/Utils/utils.h
        libs/Product/product.c
        libs/Product/product.h
        libs/controller.c
        libs/controller.h
        libs/dataTypes.h
        libs/fileHandler.c
        libs/fileHandler.h
        libs/Utils/debug.c
        libs/Utils/debug.h)
