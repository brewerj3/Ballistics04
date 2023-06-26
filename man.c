///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  Ballistics04 - Spr 2023
///
/// @file man.c
/// @version 1.0
///
/// @author Joshua Brewer <brewerj3@hawaii.edu>
/// @date   26_Jun_2023
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include "man.h"

char man_get_user_cmd() {
    char cmd;

    // Enter loop
    while(1) {
        // Display command options
        printf("\n Commands \n");
        do{
            cmd = getchar();
        } while (cmd == ' ' || cmd == '\n'); // Remove junk from stdin

        // Ensure valid command
        switch (cmd) {
            case 'q':
            case 'c':
                return cmd;
            default:
                printf("Invalid: you entered %c\n\n",cmd);
        }
    }
}

void create_gun() {
    printf("This is not implemented yet\n");
}

void man_main() {
    char cmd;

    // Enter Loop
    while(1) {
        cmd = man_get_user_cmd();

        // Execute command
        switch (cmd) {
            case 'c':
                create_gun();
                break;
            case 'q':
                return;
            default:
                printf("\nInvalid, you entered %c\n\n", cmd);
        }
    }
}