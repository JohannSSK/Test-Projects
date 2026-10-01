#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc!=3){
        printf(
            "Usage: program_name ip_address ports");
        return 1;
    }

    int client_fd,status;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    char *error;
    struct timespec t0, t1;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 300000;    // 300 ms


    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        fflush(stdout);
        return -1;
    }

    int max_ports = atoi(argv[2]);


    for (int PORT = 1; PORT <= max_ports; PORT++){

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }


    if (setsockopt(client_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0) {
        printf("setsockopt failed\n");
        close(client_fd);
        return -1;
    }


    serv_addr.sin_port = htons(PORT);


    clock_gettime(CLOCK_MONOTONIC, &t0);
        status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        error = strerror(errno);
    clock_gettime(CLOCK_MONOTONIC, &t1);

        long ms = (t1.tv_sec - t0.tv_sec) * 1000
                + (t1.tv_nsec - t0.tv_nsec) / 1000000;


    if (status < 0) {
        printf("port %d: %s after %ld ms \n\n",PORT, error, ms);

    } else {
        printf("\nConnection Successful. Port %d is open\n", PORT);
    }

    // closing the connected socket
    close(client_fd);
    }
    return 0;
}
