#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 0 
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(server_addr);
    getsockname(sockfd, (struct sockaddr *)&server_addr, &len);
    printf("Сервер запущен на порту: %d\n", ntohs(server_addr.sin_port));

    while (1) {
        int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';

        printf("Получено сообщение от клиента %s:%d: %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        char response[BUFFER_SIZE];
        int response_length = snprintf(response, sizeof(response), "%s - ответ", buffer);

        if (response_length >= sizeof(response)) {
            fprintf(stderr, "Ошибка: ответ слишком длинный и был обрезан.\n");
            response[sizeof(response) - 1] = '\0'; 
        }

        sendto(sockfd, response, strlen(response), MSG_CONFIRM, (const struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}
