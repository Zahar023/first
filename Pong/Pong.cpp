

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define HEIGHT = 25
#define WIDTH = 80

void output(int** matrix, int n, int m);
void read_numbers(FILE* input, int** numbers);
void check_elements(int** matrix, int** matrix2);
void rewrite(int** matrix, int** matrix2);
void left_top_angle(int* array, int** matrix, int i, int j);
void right_top_angle(int* array, int** matrix, int i, int j);
void left_bottom_angle(int* array, int** matrix, int i, int j);
void right_bottom_angle(int* array, int** matrix, int i, int j);
void top(int* array, int** matrix, int i, int j);
void bottom(int* array, int** matrix, int i, int j);
void right(int* array, int** matrix, int i, int j);
void left(int* array, int** matrix, int i, int j);
void center(int* array, int** matrix, int i, int j);

int main() {
    int nx = 25, ny = 80, time = 0;

    FILE* input = fopen("file2.txt", "r");

    int** array1 = (int**)malloc(nx * sizeof(int*));
    for (int i = 0; i < nx; i++) {
        array1[i] = (int*)malloc(ny * sizeof(int));
    }
    int** array2 = (int**)malloc(nx * sizeof(int*));
    for (int i = 0; i < nx; i++) {
        array2[i] = (int*)malloc(ny * sizeof(int));
    }
    read_numbers(input, array1);
    output(array1, nx, ny);
    while (1) {
        time++;
        if (time == 20000000) {
            printf("\033[0d\033[2J");
            check_elements(array1, array2);
            output(array1, nx, ny);
            rewrite(array1, array2);
            printf("\n");
            time = 0;
        }
    }
    for (int i = 0; i < nx; i++) {
        free(array1[i]);
    }
    free(array1);
    for (int i = 0; i < nx; i++) {
        free(array2[i]);
    }
    free(array2);

    return 0;
}

void rewrite(int** matrix, int** matrix2) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            matrix[i][j] = matrix2[i][j];
        }
    }
}

void check_elements(int** matrix, int** matrix2) {
    int* array = (int*)malloc(9 * sizeof(int));
    int count = 0;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if ((i == 0) && (j == 0)) {
                left_top_angle(array, matrix, i, j);
            }
            else if ((i == 0) && (j == 79)) {
                right_top_angle(array, matrix, i, j);
            }
            else if (i == 0) {
                top(array, matrix, i, j);
            }
            else if ((i == 24) && (j == 0)) {
                left_bottom_angle(array, matrix, i, j);
            }
            else if ((i == 24) && (j == 79)) {
                right_bottom_angle(array, matrix, i, j);
            }
            else if (i == 24) {
                bottom(array, matrix, i, j);
            }
            else if (j == 0) {
                left(array, matrix, i, j);
            }
            else if (j == 79) {
                right(array, matrix, i, j);
            }
            else {
                center(array, matrix, i, j);
            }
            for (int l = 1; l < 9; l++) {
                if (array[l] == 1) {
                    count++;
                }
            }
            if ((array[0] == 0) && (count == 3)) {
                matrix2[i][j] = 1;
            }
            else if ((array[0] == 1) && ((count == 2) || count == 3)) {
                matrix2[i][j] = 1;
            }
            else if ((array[0] == 1)) {
                matrix2[i][j] = 0;
            }
            else if ((array[0] == 0)) {
                matrix2[i][j] = 0;
            }
            count = 0;
        }
    }
    free(array);
}

void left_top_angle(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][j + 1];
    array[2] = matrix[i][79];
    array[3] = matrix[i + 1][j];
    array[6] = matrix[i + 1][j + 1];
    array[4] = matrix[24][j + 1];
    array[5] = matrix[24][j];
    array[7] = matrix[24][79];
    array[8] = matrix[i + 1][79];
}
void right_top_angle(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][0];
    array[2] = matrix[i][j - 1];
    array[3] = matrix[i + 1][j];
    array[6] = matrix[i + 1][0];
    array[4] = matrix[24][0];
    array[5] = matrix[24][j];
    array[7] = matrix[24][j - 1];
    array[8] = matrix[i + 1][j - 1];
}
void left_bottom_angle(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][j + 1];
    array[2] = matrix[i][79];
    array[3] = matrix[0][j];
    array[6] = matrix[0][j + 1];
    array[4] = matrix[i - 1][j + 1];
    array[5] = matrix[i - 1][j];
    array[7] = matrix[i - 1][79];
    array[8] = matrix[0][79];
}
void right_bottom_angle(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][0];
    array[2] = matrix[i][j - 1];
    array[3] = matrix[0][j];
    array[6] = matrix[0][0];
    array[4] = matrix[i - 1][0];
    array[5] = matrix[i - 1][j];
    array[7] = matrix[i - 1][j - 1];
    array[8] = matrix[0][j - 1];
}

void top(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][j + 1];
    array[2] = matrix[i][j - 1];
    array[3] = matrix[i + 1][j];
    array[6] = matrix[i + 1][j + 1];
    array[4] = matrix[24][j + 1];
    array[5] = matrix[24][j];
    array[7] = matrix[24][j - 1];
    array[8] = matrix[i + 1][j - 1];
}
void bottom(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][j + 1];
    array[2] = matrix[i][j - 1];
    array[3] = matrix[0][j];
    array[6] = matrix[0][j + 1];
    array[4] = matrix[i - 1][j + 1];
    array[5] = matrix[i - 1][j];
    array[7] = matrix[i - 1][j - 1];
    array[8] = matrix[0][j - 1];
}
void left(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][j + 1];
    array[2] = matrix[i][79];
    array[3] = matrix[i + 1][j];
    array[6] = matrix[i + 1][j + 1];
    array[4] = matrix[i - 1][j + 1];
    array[5] = matrix[i - 1][j];
    array[7] = matrix[i - 1][79];
    array[8] = matrix[i + 1][79];
}
void right(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][0];
    array[2] = matrix[i][j - 1];
    array[3] = matrix[i + 1][j];
    array[6] = matrix[i + 1][0];
    array[4] = matrix[i - 1][0];
    array[5] = matrix[i - 1][j];
    array[7] = matrix[i - 1][j - 1];
    array[8] = matrix[i + 1][j - 1];
}

void center(int* array, int** matrix, int i, int j) {
    array[0] = matrix[i][j];
    array[1] = matrix[i][j + 1];
    array[2] = matrix[i][j - 1];
    array[3] = matrix[i + 1][j];
    array[6] = matrix[i + 1][j + 1];
    array[4] = matrix[i - 1][j + 1];
    array[5] = matrix[i - 1][j];
    array[7] = matrix[i - 1][j - 1];
    array[8] = matrix[i + 1][j - 1];
}

void read_numbers(FILE* input, int** numbers) {
    fseek(input, 0, SEEK_SET);
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            fscanf(input, "%d", &numbers[i][j]);
        }
    }
}

void output(int** matrix, int lenx, int leny) {
    for (int i = 0; i < lenx; i++) {
        for (int j = 0; j < leny; j++) {
            if (j == 0) {
                if (matrix[i][j] == 0)
                    printf(" ");
                else
                    printf("%d", matrix[i][j]);

            }
            else {
                if (matrix[i][j] == 0)
                    printf(" ");
                else
                    printf("%d", matrix[i][j]);
            }
        }
        if ((i + 1) < lenx) {
            printf("\n");
        }
    }
}
