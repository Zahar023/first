#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8085


int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    while (1) {
        // Получаем сообщение от сервера
        memset(buffer, 0, sizeof(buffer));  // Очистка буфера
        int bytes_read = read(sock, buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0';  // Добавление завершающего нуля
        //int bytes_read = read(sock, buffer, 1024);
        if (bytes_read <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        printf("%s", buffer);

        // Если это запрос хода, отправляем его
        if (strstr(buffer, "Your move") || strstr(buffer, "Invalid move, try again.")) {
            printf("Enter your move (row col): ");
            fgets(buffer, 1024, stdin);
            send(sock, buffer, strlen(buffer), 0);
        }
    }

    close(sock);
    return 0;
}
