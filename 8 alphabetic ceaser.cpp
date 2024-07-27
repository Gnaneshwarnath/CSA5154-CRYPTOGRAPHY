#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dict[26] = {0};
    int i, j, k, len = strlen(key);
    char current;

    // Fill key table with key
    for (i = 0, k = 0; i < len; i++) {
        current = toupper(key[i]);
        if (current != 'J' && dict[current - 'A'] == 0) {
            keyTable[k / SIZE][k % SIZE] = current;
            dict[current - 'A'] = 1;
            k++;
        }
    }

    // Fill remaining letters
    for (i = 0; i < 26; i++) {
        if (i != 9 && dict[i] == 0) { // Skip 'J'
            keyTable[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}

void search(char keyTable[SIZE][SIZE], char a, char b, int pos[]) {
    int i, j;

    if (a == 'J') a = 'I';
    if (b == 'J') b = 'I';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                pos[0] = i;
                pos[1] = j;
            }
            if (keyTable[i][j] == b) {
                pos[2] = i;
                pos[3] = j;
            }
        }
    }
}

void encrypt(char str[], char keyTable[SIZE][SIZE]) {
    int i, pos[4];

    for (i = 0; i < strlen(str); i += 2) {
        search(keyTable, str[i], str[i + 1], pos);

        if (pos[0] == pos[2]) {
            str[i] = keyTable[pos[0]][(pos[1] + 1) % SIZE];
            str[i + 1] = keyTable[pos[2]][(pos[3] + 1) % SIZE];
        } else if (pos[1] == pos[3]) {
            str[i] = keyTable[(pos[0] + 1) % SIZE][pos[1]];
            str[i + 1] = keyTable[(pos[2] + 1) % SIZE][pos[3]];
        } else {
            str[i] = keyTable[pos[0]][pos[3]];
            str[i + 1] = keyTable[pos[2]][pos[1]];
        }
    }
}

void prepareText(char str[], char prepared[]) {
    int i, j = 0;

    for (i = 0; i < strlen(str); i++) {
        if (str[i] != ' ') {
            prepared[j++] = toupper(str[i]);
        }
    }
    prepared[j] = '\0';

    for (i = 0; i < j; i += 2) {
        if (prepared[i] == prepared[i + 1]) {
            for (j = strlen(prepared) + 1; j > i + 1; j--) {
                prepared[j] = prepared[j - 1];
            }
            prepared[i + 1] = 'X';
        }
    }

    if (strlen(prepared) % 2 != 0) {
        prepared[strlen(prepared)] = 'X';
        prepared[strlen(prepared) + 1] = '\0';
    }
}

int main() {
    char key[SIZE * SIZE], str[100], prepared[100], keyTable[SIZE][SIZE];

    printf("Enter key: ");
    gets(key);
    printf("Enter text to encrypt: ");
    gets(str);

    generateKeyTable(key, keyTable);
    prepareText(str, prepared);
    encrypt(prepared, keyTable);

    printf("Encrypted text: %s\n", prepared);

    return 0;
}
