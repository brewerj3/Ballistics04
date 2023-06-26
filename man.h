///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  Ballistics04 - Spr 2023
///
/// @file man.h
/// @version 1.0
///
/// @author Joshua Brewer <brewerj3@hawaii.edu>
/// @date   26_Jun_2023
///////////////////////////////////////////////////////////////////////////////
#ifndef BALLISTICS04_MAN_H
#define BALLISTICS04_MAN_H
#define MAN_MSG_LENGTH 1000

/*
 *  The next two structs are ports used to transfer commands
 *  and replies between the manager and hosts
 */

struct man_port_at_host {  /* Port located at the man */
    int host_id;
    int send_fd;
    int recv_fd;
    struct man_port_at_host *next;
};

struct man_port_at_man {  /* Port located at the host */
    int host_id;
    int send_fd;
    int recv_fd;
    struct man_port_at_man *next;
};

// Main loop for the manager
void man_main();

#endif //BALLISTICS04_MAN_H
