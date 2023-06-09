///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  Ballistics04 - Spr 2023
///
/// @file net.c
/// @version 1.0
///
/// @author Joshua Brewer <brewerj3@hawaii.edu>
/// @date   26_Jun_2023
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#include "net.h"
#include "man.h"


#define PIPE_READ 0
#define PIPE_WRITE 1

static struct man_port_at_man *g_man_man_port = NULL;
static struct man_port_at_host *g_man_host_port = NULL;

struct man_port_at_man *net_get_man_port() {
    return (g_man_man_port);
}

void create_man_ports(struct man_port_at_man **p_man, struct man_port_at_host **p_host) {
    int fd0[2];
    int fd1[2];
    struct man_port_at_man *p_m;
    struct man_port_at_host *p_h;

    p_m = (struct man_port_at_man *) malloc(sizeof(struct man_port_at_man));
    p_m->host_id = 0;

    p_h = (struct man_port_at_host *) malloc(sizeof(struct man_port_at_host));
    p_h->host_id = 0;

    pipe(fd0);  // Create a pipe
    // Make the pipe nonblocking at both ends
    fcntl(fd0[PIPE_WRITE], F_SETFL, fcntl(fd0[PIPE_WRITE], F_GETFL) | O_NONBLOCK);
    fcntl(fd0[PIPE_READ], F_SETFL, fcntl(fd0[PIPE_READ], F_GETFL) | O_NONBLOCK);
    p_m->send_fd = fd0[PIPE_WRITE];
    p_h->recv_fd = fd0[PIPE_READ];

    pipe(fd1); // Create a pipe
    // Make the pipe nonblocking at both ends
    fcntl(fd1[PIPE_WRITE], F_SETFL, fcntl(fd1[PIPE_WRITE], F_GETFL) | O_NONBLOCK);
    fcntl(fd1[PIPE_READ], F_SETFL, fcntl(fd1[PIPE_READ], F_GETFL) | O_NONBLOCK);
    p_h->send_fd = fd1[PIPE_WRITE];
    p_m->recv_fd = fd1[PIPE_READ];

    p_m->next = *p_man;
    *p_man = p_m;

    p_h->next = *p_host;
    *p_host = p_h;
}

int net_init() {
    create_man_ports(&g_man_man_port, &g_man_host_port);
}