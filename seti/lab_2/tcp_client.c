#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define BUFFER_SIZE 2048  

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <IP адрес сервера> <номер порта>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int i, count = 5;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }


    for (i = 1; i <= count; i++) {
        snprintf(buffer, sizeof(buffer), "Сообщение от ПЕРВОГО %d", i);
        write(sockfd, buffer, strlen(buffer));
        printf("Отправлено: %s\n", buffer);

        int n = read(sockfd, buffer, BUFFER_SIZE);
        buffer[n] = '\0';
        printf("Получен ответ от сервера: %s\n", buffer);

        sleep(i);
    }

    close(sockfd);
    return 0;
}
