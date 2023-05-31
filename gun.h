///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  Ballistics04 - Spr 2023
///
/// @file gun.h
/// @version 1.0
///
/// @author Joshua Brewer <brewerj3@hawaii.edu>
/// @date   31_May_2023
///////////////////////////////////////////////////////////////////////////////
#ifndef BALLISTICS04_GUN_H
#define BALLISTICS04_GUN_H

struct GunStruct {
    long double shellDiameter;
    long double muzzleVelocity;
    long double massOfShell;
    int tableIndex;
    char *Name;
};

#endif //BALLISTICS04_GUN_H
