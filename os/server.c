#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8085
#define BOARD_SIZE 3

char board[BOARD_SIZE][BOARD_SIZE];
int player_turn = 0; 

void initialize_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_board() {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

int check_win(char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0;
}

int is_board_full() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void send_board(int socket) {
    char board_str[100];
    snprintf(board_str, sizeof(board_str),
             " %c | %c | %c \n"
             "---+---+---\n"
             " %c | %c | %c \n"
             "---+---+---\n"
             " %c | %c | %c \n\n", 
             board[0][0], board[0][1], board[0][2],
             board[1][0], board[1][1], board[1][2],
             board[2][0], board[2][1], board[2][2]);
    send(socket, board_str, strlen(board_str), 0);
}

int main() {
    int server_fd, player1_socket, player2_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    initialize_board();

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 2) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for players to connect...\n");

    if ((player1_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Player 1 connected.\n");
    send(player1_socket, "You are Player 1 (X). Waiting for Player 2...\n", 46, 0);

    if ((player2_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Player 2 connected.\n");
    send(player2_socket, "You are Player 2 (O). Game starting...\n", 38, 0);

    send(player1_socket, "Game started! Your move (row col): ", 34, 0);
    send(player2_socket, "Game started! Waiting for Player 1...\n", 38, 0);

    while (1) {
        int current_player_socket = (player_turn == 0) ? player1_socket : player2_socket;
        int other_player_socket = (player_turn == 0) ? player2_socket : player1_socket;
        char *current_player_symbol = (player_turn == 0) ? "X" : "O";

        int bytes_read = read(current_player_socket, buffer, 1024);
        if (bytes_read <= 0) {
            printf("Player %d disconnected.\n", player_turn + 1);
            break;
        }

        int row = buffer[0] - '0';
        int col = buffer[2] - '0';

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == ' ') {
            board[row][col] = (player_turn == 0) ? 'X' : 'O';
            print_board();

            send_board(player1_socket);  
            send_board(player2_socket);  

            if (check_win(current_player_symbol[0])) {
             send(current_player_socket, "You win!\n", 9, 0);
             send(other_player_socket, "You lose!\n", 10, 0);
             break;
            }

            if (is_board_full()) {
               send(player1_socket, "It's a draw!\n", 13, 0);
               send(player2_socket, "It's a draw!\n", 13, 0);
               break;
            }

            player_turn = 1 - player_turn;
            send(current_player_socket, "Waiting for the other player...\n", 32, 0);
            send(other_player_socket, "Your move (row col): ", 21, 0);
        } else {
            send(current_player_socket, "Invalid move, try again.\n", 25, 0);
        }
    }

    close(player1_socket);
    close(player2_socket);
    close(server_fd);
    return 0;
}
