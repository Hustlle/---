#include <stdio.h>
#include <stdlib.h>
#define fieldX 80
#define fieldY 25

void Init(int** field) {
    int i, j = 0;
    int sp;
    printf("Speed: ");
    if (scanf("%d", &sp) == 1 && sp != 0) {
            int **fieldnew;
            fieldnew = (int**) malloc( fieldY * sizeof(int*));
            for (i = 0; i < fieldY; i++) {
                fieldnew[i] = (int*) malloc( fieldX * sizeof(int ));
            }
            int **fielddead;
            fielddead = (int**) malloc( fieldY * sizeof(int*));
            for (i = 0; i < fieldY; i++) {
                fielddead[i] = (int*) malloc( fieldX * sizeof(int ));
            }
            int** fieldold;
            fieldold = (int**) malloc( fieldY * sizeof(int*));
            for (i = 0; i < fieldY; i++) {
                fieldold[i] = (int*) malloc( fieldX * sizeof(int ));
            }

            printfield(field);
            while (1) {
                if (j % 2 == 0) copyfield(field, fieldold);

                birthORkill(field, fieldnew, fielddead);
                clearspace(fielddead);
                clearspace(fieldnew);
                printf("--------------------------------------------------------------------------------\n");
                printfield(field);
                usleep(sp * 10000);
                if(checkfield(field,fieldold) == 1) break;
                j++;
            }


            printf("Game over");
            for (i = 0; i < fieldY; i++) {
                free(field[i]);
            }
            for (i = 0; i < fieldY; i++) {
                free(fieldnew[i]);
            }
            for (i = 0; i < fieldY; i++) {
                free(fielddead[i]);
            }
            free(field);
            free(field);
            free(fielddead);

        } else {
            printf("n/a");
        }
}

int checkfield(int **field, int **fieldold) {
    int i, j, num1 = 0, num2 = 0, num = 0;

    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            if (field[i][j] == 1) num1++;
        }
    }

    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            if (fieldold[i][j] == field[i][j] && field[i][j] == 1) num2++;
        }
    }

    if (num1 == num2) num = 1;

    return num;
}

void printfield(int **field) {
    int i, j;
    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            if (field[i][j] == 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int islife(int **field, int line, int column) {
    if (line < 0 || line >= fieldY || column < 0 || column >= fieldX || field[line][column] != 1) {
        return 0;
    } else {
        return 1;
    }
}

int around(int **field, int Y, int X) {
    int around = 0;
    int xx = fieldX - 1;
    int yy = fieldY - 1;

    if (Y == 0 && X == 0) {
        around += islife(field, Y + yy, X + xx);
        around += islife(field, Y + yy, X);
        around += islife(field, Y + yy, X + 1);
        around += islife(field, Y, X + xx);
        around += islife(field, Y + 1, X + xx);
    } else if (Y == 0 && X == fieldX - 1) {
        around += islife(field, Y + yy, X - 1);
        around += islife(field, Y + yy, X);
        around += islife(field, Y + yy, X - xx);
        around += islife(field, Y, X - xx);
        around += islife(field, Y + 1, X - xx);
    } else if (Y == fieldY - 1 && X == fieldX - 1) {
        around += islife(field, Y - yy, X - 1);
        around += islife(field, Y - yy, X);
        around += islife(field, Y - yy, X - xx);
        around += islife(field, Y, X - xx);
        around += islife(field, Y - 1, X - xx);
    } else if (Y == fieldY - 1 && X == 0) {
        around += islife(field, Y - yy, X + 1);
        around += islife(field, Y - yy, X);
        around += islife(field, Y - yy, X + xx);
        around += islife(field, Y, X + xx);
        around += islife(field, Y - 1, X + xx);
    } else if (X == 0) {
        around += islife(field, Y - 1, X + xx);
        around += islife(field, Y, X + xx);
        around += islife(field, Y + 1, X + xx);
    } else if (Y == 0) {
        around += islife(field, Y + yy, X - 1);
        around += islife(field, Y + yy, X);
        around += islife(field, Y + yy, X + 1);
    } else if (X == fieldX - 1) {
        around += islife(field, Y + 1, X - xx);
        around += islife(field, Y , X - xx);
        around += islife(field, Y - 1, X - xx);
    } else if (Y == fieldY - 1) {
        around += islife(field, Y - yy, X - 1);
        around += islife(field, Y - yy, X);
        around += islife(field, Y - yy, X + 1);
    }

    around += islife(field, Y - 1, X - 1);
    around += islife(field, Y - 1, X);
    around += islife(field, Y - 1, X + 1);
    around += islife(field, Y, X - 1);
    around += islife(field, Y, X + 1);
    around += islife(field, Y + 1, X - 1);
    around += islife(field, Y + 1, X);
    around += islife(field, Y + 1, X + 1);

    return around;
}
void copyfield(int **field, int **fieldold) {
    int i, j;
    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            fieldold[i][j] = field[i][j];
        }
    }
}
void birthORkill(int **field, int **fieldnew, int **fielddead) {
    int i, j;
    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            if (field[i][j] == 0 && around(field, i, j) == 3) {
                fieldnew[i][j] = 1;
            }
        }
    }
    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            if (around(field, i, j) > 3 || around(field, i, j) < 2) {
                fielddead[i][j] = 1;
            }
        }
    }
    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            if (fieldnew[i][j] == 1) {
                field[i][j] = 1;
            }
        }
    }
    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            if (fielddead[i][j] == 1) {
                field[i][j] = 0;
            }
        }
    }
}

void clearspace(int **field) {
    int i, j;
    for (i = 0; i < fieldY; i++) {
        for (j = 0; j < fieldX; j++) {
            field[i][j] = 0;
        }
    }
}






// ВСЁ ЧТО НИЖЕ НЕ ТРОГАТЬ СУКА!!!!!!!!!!!!!!!
// ЛОМАЙ СВОЁ МОЁ НЕ ТРОГАЙ !!!!!!!!!!!!!!!!!!










//  функция вывода поля

int output(int** field) {
    for (int i = 0; i < fieldY; i++)
    {
        for (int j = 0; j < fieldX; j++)
        {
            if (field[i][j] == 1)
            {
                printf("0");
            } else {
                printf(" ");
            }

        }
        printf("\n");
    }
    return 0;
}

//  создание поля с последующей его передачей

int** CreateField() {
    int** field = malloc(fieldY * sizeof(int*));
    for (int i = 0; i < fieldY; i++)
    {
        field[i] = malloc(fieldX * sizeof(int));
        for (int j = 0; j < fieldX; j++)
        {
            field[i][j] = 0;
        }

    }
    return field;
}

//  открытие и считывание файла

int FileJob(char* name, int** field) {
    FILE *fp;
    int a, b;
    int count = 0;
    if ((fp = fopen(name, "r")) == NULL)
    {
        printf("Никита не забудь перекинуть файлы \n");
        count++;
    } else {
        while (fscanf(fp, "%d %d", &a, &b) != EOF)
        {
            printf("%d %d \n", a, b);
            field[a][b] = 1;
        }
        fclose(fp);
    }
    return count;
}

//  выбор режима игры

int StartProgramm() {
    int** field = CreateField();
    char* name = malloc(sizeof(char));
    int value;
    printf("enter game mode :");
    printf("\e[H\e[2J\e[3J");
    if (scanf("%d", &value) == 1)
    {
        switch (value)
        {
        case 1:
        name = "start1.txt";
            break;

        case 2:
        name = "start2.txt";
            break;

        case 3:
        name = "start3.txt";
            break;

        case 4:
        name = "start4.txt";
            break;

        case 5:
        name = "start5.txt";
            break;

        case 6:
        CreateField();
            break;

        default:
        printf("n/a");
            break;
        }

        if (FileJob(name, field) == 0) {
            Init(field);
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}

int main() {
    StartProgramm();
    return 0;
}
