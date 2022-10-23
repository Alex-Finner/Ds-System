#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    int net_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sv, cl;
    sv.sin_port = htons(0);
    sv.sin_family = AF_INET;
    sv.sin_addr.s_addr = inet_addr("0.0.0.0");

    int len = sizeof(struct sockaddr_in);
    bind(net_socket, (struct sockaddr *)&sv, len);

    len = sizeof(struct sockaddr_in);
    getsockname(net_socket, (struct sockaddr *)&sv, &len);
    printf("Port: %d\n", ntohs(sv.sin_port));

    listen(net_socket, 10);

    int fd, res;

    while (1) {
        len = sizeof(struct sockaddr_in);
        fd = accept(net_socket, (struct sockaddr *)&cl, &len);
        printf("\nNew client connected\n");

        int n;
        printf("Enter array size: ");
        scanf(" %d", &n);

        write(fd, &n, sizeof(int));

        int arr[n];
        printf("Enter array elements: ");
        for (int i=0; i<n; i++)
            scanf(" %d", &arr[i]);

        write(fd, arr, sizeof(arr));

        int key;
        printf("Enter element: ");
        scanf(" %d", &key);

        write(fd, &key, sizeof(int));
        recv(fd, &res, sizeof(int), 0);

        if (res)
            printf("Element %d is present in array\n", key);
        else 
            printf("Element %d NOT present in array\n", key);

        close(fd);

    }
    
    close(net_socket);

    return 0;
}

