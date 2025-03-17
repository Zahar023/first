#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2048

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE + 14];  
    int n;

    while ((n = read(client_sock, buffer, BUFFER_SIZE)) > 0) {
        buffer[n] = '\0';
        printf("Получено сообщение от клиента: %s\n", buffer);

        if (strlen(buffer) + 13 >= sizeof(response)) {
            fprintf(stderr, "Ошибка: сообщение слишком длинное и будет обрезано.\n");
            strncpy(response, buffer, sizeof(response) - 14);
            response[sizeof(response) - 14] = '\0';
        } else {
            snprintf(response, sizeof(response), "%s - ответ", buffer);
        }

        write(client_sock, response, strlen(response));
    }

    close(client_sock);
    exit(0);
}
int main() {
    int sockfd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    signal(SIGCHLD, SIG_IGN); 

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.109.135");
    server_addr.sin_port = htons(0); 

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);

    socklen_t len = sizeof(server_addr);
    getsockname(sockfd, (struct sockaddr *)&server_addr, &len);
    printf("Сервер запущен на порту: %d\n", ntohs(server_addr.sin_port));

    while (1) {
        if ((client_sock = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
            perror("accept failed");
            continue;
        }

        if (fork() == 0) {
            close(sockfd);
            handle_client(client_sock);
        } else {
            close(client_sock);
        }
    }

    close(sockfd);
    return 0;
}
