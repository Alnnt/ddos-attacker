//
// Created by Alnnt on 2024/4/21.
//
#include <stdio.h>
#include <stdlib.h>
#include "environment.h"

const char *USAGE_STR =
        "Usage: win_da.exe [-options] [args...]\n"
        "It includes:\n"
        "\t-address <ip>\tTarget Address\n"
        "\t-port <port>\tIf you don't specify or specify 0, it will traverse and attack all ports\n"
        "\t-log\t\tPrint udp packet info.\n"
        "\t-thread <count>\tNum of attacker thread. Default is 1, maybe 5 is a great count.\n"
        "\t-hide\t\tSilent run\n";

const char *REQUIRE_ARGS_STR = "require args.\n";

void CheckAndThrowArgsException(int *i, int argc, const char *str);

void ProcessCommandLine(int argc, char **argv) {
    for (int i = 0; i < argc; ++i) {
        if (!strcmp("-address", argv[i])) {
            CheckAndThrowArgsException(&i, argc, REQUIRE_ARGS_STR);
            ADDRESS_IP = argv[i];

        } else if (!strcmp("-port", argv[i])) {
            CheckAndThrowArgsException(&i, argc, REQUIRE_ARGS_STR);
            ADDRESS_PORT = atoi(argv[i]);

        } else if (!strcmp("-hide", argv[i])) {
            ShowWindow(GetConsoleWindow(), SW_HIDE);

        } else if (!strcmp("-log", argv[i])) {
            LOG = true;

        } else if (!strcmp("-thread", argv[i])) {
            CheckAndThrowArgsException(&i, argc, REQUIRE_ARGS_STR);
            THREAD_COUNT = atoi(argv[i]);
        }
    }

    if (ADDRESS_IP == NULL) {
        printf("%s", USAGE_STR);
        exit(1);
    }
}

void CheckAndThrowArgsException(int *i, int argc, const char *str) {
    if (++*i == argc) {
        printf("%s", str);
        exit(1);
    }
}