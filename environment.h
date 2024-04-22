//
// Created by Alnnt on 2024/4/21.
//

#ifndef DDOS_ATTACKER_ENVIRONMENT_H
#define DDOS_ATTACKER_ENVIRONMENT_H

#include <winsock.h>
#include <stdbool.h>

#define NULL_PORT 0

extern char *ADDRESS_IP;
extern u_short ADDRESS_PORT;
extern bool LOG;
extern u_int THREAD_COUNT;

#endif //DDOS_ATTACKER_ENVIRONMENT_H
