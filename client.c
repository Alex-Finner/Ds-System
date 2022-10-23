#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    
    int net_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sv, cl;
    sv.sin_port = htons((atoi(argv[2])));
    sv.sin_family = AF_INET;
    sv.sin_addr.s_addr = inet_addr(argv[1]);

    int len = sizeof(struct sockaddr_in);
    connect(net_socket, (struct sockaddr *)&sv, len);

    int fd, res=0;
    int n, key;

    recv(net_socket, &n, sizeof(int), 0);
    int arr[n];

    recv(net_socket, arr, sizeof(arr), 0);

    recv(net_socket, &key, sizeof(int), 0);

    printf("Inputs received from server\n");

    for (int i=0; i<n; i++) {
        if (arr[i] == key) {
            res = 1;
            break;
        }
    }

    write(net_socket, &res, sizeof(int));
    printf("Response sent to server\n");

    close(net_socket);

    return 0;
}
