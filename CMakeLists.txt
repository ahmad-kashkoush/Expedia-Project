cmake_minimum_required(VERSION 3.24)
project(Expedia_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Expedia_Project main.cpp Utilities.h User.h Itenirary.h Testing.h PaymentCard.h Customer.h CustomerManager.h CustomerView.h ExpediaBackend.h)
