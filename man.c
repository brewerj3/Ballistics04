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
#include <unistd.h>

#include "man.h"
#include "net.h"

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

void create_gun(struct man_port_at_man *host) {
    char msg[MAN_MSG_LENGTH];
    char reply[MAN_MSG_LENGTH];
    char gunName[100];
    long double shellMass;
    long double boreDiameter;
    long double muzzleVelocity;
    int n;

    printf("Enter gun name as one word\n");
    scanf("%s", gunName);

    printf("Enter mass of shell in kilograms\n");
    scanf("%Lf", &shellMass);

    printf("Enter bore diameter in mm\n");
    scanf("%Lf", &boreDiameter);

    printf("Enter muzzle velocity in m/s\n");
    scanf("%Lf", &muzzleVelocity);

    n = sprintf(msg, "c %s %Lf %Lf %Lf", gunName, shellMass, boreDiameter, muzzleVelocity);
    write(host->send_fd, msg, n);
}

void delete_gun(struct man_port_at_man *host) {
    printf("This is not implemented yet\n");
}

void man_main() {

    struct man_port_at_man *host = NULL;
    host = net_get_man_port();
    char cmd;

    // Enter Loop
    while(1) {
        cmd = man_get_user_cmd();

        // Execute command
        switch (cmd) {
            case 'c':
                create_gun(host);
                break;
            case 'd':
                delete_gun(host);
                break;
            case 'q':
                return;
            default:
                printf("\nInvalid, you entered %c\n\n", cmd);
        }
    }
}