#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include "log.h"

int main(int argc, char** argv)
{
    log_o("Starting client");
    int ERROR_CODE = 0;

    int cli_fd;
    struct sockaddr_in cli_addr, serv_addr;

    cli_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(cli_fd < 0){
        ERROR_CODE = 1;
        error("Could not create socket. Aborting...");
        goto exit;
    }
    log_o("Created UDP socket");

    memset((char*)&serv_addr, '\0', sizeof(serv_addr));
    memset((char*)&cli_addr, '\0', sizeof(cli_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(atoi(argv[1])+1);
    cli_addr.sin_addr.s_addr = htons(INADDR_ANY);

    if(bind(cli_fd, (struct sockaddr*) &cli_addr, sizeof(cli_addr)) < 0){
        ERROR_CODE = 2;
        error("Couldn't bind client socket to port %i", atoi(argv[1]+1));
        goto close_client;
    }
    log_o("Socket binded to %u:%u", cli_addr.sin_addr.s_addr, cli_addr.sin_port);

    if(connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        ERROR_CODE = 3;
        error("Couldn't connect to server");
        goto close_client;
    }
    log_o("Connected to server %u:%u", serv_addr.sin_addr.s_addr, serv_addr.sin_port);

    char buffer[256];
    int n;

    while(1){
        memset(&buffer, '\0', sizeof(buffer));

        fputs("Enter message: ", stdout);
        fgets(buffer, sizeof(buffer), stdin);

        n = send(cli_fd, buffer, sizeof(buffer), 0);
        if(n <= 0){
            ERROR_CODE = 3;
            error("Couldn't send message to server");
            goto close_client;
        }

        memset(&buffer, '\0', sizeof(buffer));
        n = recv(cli_fd, buffer, sizeof(buffer), 0);
        if(n <= 0){
            ERROR_CODE = 4;
            error("Couldn't reveive message from server");
            goto close_client;
        }

        fprintf(stdout, "Server response: %s\n", buffer);
    }

close_client:
    log_o("Closing socket");
    close(cli_fd);
exit:
    log_o("Exiting with code %i", ERROR_CODE);
    return ERROR_CODE;
}

