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

#define NAME_LENGTH 100
#define TENMILLISEC 10000

char man_get_user_cmd() {
    char cmd;

    // Enter loop
    while (1) {
        // Display command options
        printf("\n Commands \n");
        printf("   (c) Create a new gun and name it\n");
        printf("   (l) List all known host guns\n");
        printf("   (d) Delete a gun by supplying its name\n");
        printf("   (q) Quit\n");
        printf("   Enter Command\n");
        do {
            cmd = getchar();
        } while (cmd == ' ' || cmd == '\n'); // Remove junk from stdin

        // Ensure valid command
        switch (cmd) {
            case 'q':
            case 'c':
            case 'd':
                return cmd;
            default:
                printf("Invalid: you entered %c\n\n", cmd);
        }
    }
}

void create_gun(struct man_port_at_man *host) {
    char msg[MAN_MSG_LENGTH];
    char reply[MAN_MSG_LENGTH];
    char gunName[NAME_LENGTH];
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

    n = sprintf(msg, "c %s %Lf %Lf %Lf", gunName, shellMass, boreDiameter, muzzleVelocity);    // Format msg
    write(host->send_fd, msg, n);                                                               // send msg to host

    n = 0;
    while (n <= 0) {    // Wait for reply from host
        usleep(TENMILLISEC);                                    // Sleep for ten milliseconds
        n = read(host->recv_fd, reply, MAN_MSG_LENGTH);   // Check for reply
    }
    reply[n] = '\0';
    printf("%s\n", reply);
}

void delete_gun(struct man_port_at_man *host) {
    char msg[MAN_MSG_LENGTH];
    char reply[MAN_MSG_LENGTH];
    char gunName[NAME_LENGTH];
    int n;
    printf("Enter Gun name as one word\n");
    scanf("%s", gunName);

    n = sprintf(msg, "d %s", gunName);      // Format gunName into msg
    write(host->send_fd, reply, n);

    n = 0;
    while (n <= 0) {    // Wait for reply from host
        usleep(TENMILLISEC);
        n = read(host->recv_fd, reply, MAN_MSG_LENGTH);
    }
    reply[n] = '\0';
    printf("%s\n", reply);
}

void list_gun(struct man_port_at_man *host) {   // @TODO Implement list_gun, should make the host send a list of all gun names to manager
    printf("This is not implemented yet\n");
}

void man_main() {

    struct man_port_at_man *host = NULL;
    host = net_get_man_port();
    char cmd;

    // Enter Loop
    while (1) {
        cmd = man_get_user_cmd();   // Get user input

        // Execute command
        switch (cmd) {
            case 'c':   // Create a gun
                create_gun(host);
                break;
            case 'd':   // Delete a gun with its name
                delete_gun(host);
                break;
            case 'l':   // List all the guns the host knows
                list_gun(host);
                break;
            case 'q':   // Quit the manager
                return;
            default:
                printf("\nInvalid, you entered %c\n\n", cmd);
        }
    }
}