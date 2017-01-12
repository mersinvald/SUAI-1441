#include <stdio.h>
#include "log.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <memory.h>
#include <time.h>

/*
struct config_s {
    int port;
    char* log_file;

    int verbosity;
};

typedef struct config_s Config;

Config parse_args(int argc, char** argv){
    Config input = 0;

    char* arg;
    int   s;
    while((s = getopt(argc, argv, "")) != -1){

    }
}
*/

int main(int argc, char** argv)
{
    // FILE *null = fopen("/dev/null", "rw");
    // log_to_file(null);
    log_o("Initializing Server");
    //error("Some shit happened!");

    int ERROR_CODE = 0;
    int sockfd;
    ushort port;
    uint cli_len;
    struct sockaddr_in serv_addr, cli_addr;

    int n;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd < 0) {
        error("ERROR opening socket");
        ERROR_CODE = 1;
        goto exit;
    }
    log_o("Opened inet UDP socket");

    memset((char*)&serv_addr, 0, sizeof(serv_addr));
    port = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        error("ERROR binding socket");
        ERROR_CODE = 2;
        goto close_sock;
    }
    log_o("Socket binded to %u:%u", serv_addr.sin_addr, serv_addr.sin_port);

    double unix_time;
    while(1){
        memset(&buffer, '\0', sizeof(buffer));
        cli_len = (int)sizeof(struct sockaddr_in);
        n = recvfrom(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr*) &cli_addr, &cli_len);
        if(n < 0){
            error("Couldn't reveive datagram");
            goto close_sock;
        }

        while(buffer[strlen(buffer)-1] == '\n'){
            buffer[strlen(buffer)-1] = '\0';
        }

        if(strcmp(buffer, "quit") == 0){
            log_o("Got \'quit\' - shutting down the server");
            memset(&buffer, '\0', sizeof(buffer));
            strcpy(buffer, "Shutting down...");
            n = sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr*) &cli_addr, cli_len);
            if(n < 0){
                error("Couldn't send datagram to client");
            }
            goto close_sock;
        }
        else {
            memset(&buffer, '\0', sizeof(buffer));
            unix_time = getUnixTime();
            sprintf(buffer, "%lf", unix_time);
            n = sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr*) &cli_addr, cli_len);
            if(n < 0){
                error("Couldn't send datagram to client");
            }
        }
    }

close_sock:
    log_o("Closing socket");
    close(sockfd);
exit:
    log_o("Exiting with code %i", ERROR_CODE);
    return ERROR_CODE;
}

