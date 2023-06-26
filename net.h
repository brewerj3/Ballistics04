///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  Ballistics04 - Spr 2023
///
/// @file net.h
/// @version 1.0
///
/// @author Joshua Brewer <brewerj3@hawaii.edu>
/// @date   26_Jun_2023
///////////////////////////////////////////////////////////////////////////////
#ifndef BALLISTICS04_NET_H
#define BALLISTICS04_NET_H

struct man_port_at_man *net_get_man_port(); // Return the manager ports

int net_init(); // initialize the ports between manager and host

#endif //BALLISTICS04_NET_H
