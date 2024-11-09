#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORDS 500
#define MAX_WORD_SIZE 30

typedef struct {
    char list[5][MAX_WORDS][MAX_WORD_SIZE];
    int size[5];
    int found[5];
} WordList;

void inicio(WordList* wordlist) {
    bool valid_let[30] = {};
    char first_let;

    for (int i = 0; i < 7; i++) {
        char c;
        scanf(" %c", &c);

        if (i == 0) {
            first_let = c;
        }

        valid_let[c - 'A'] = true; 
    }

    FILE *file = fopen("valid_words.txt", "r");
    if (file == NULL) {
        printf("ERRO!\n");
        exit(1);
    }

    char s[MAX_WORD_SIZE];
    while (fscanf(file, " %s", s) != EOF) {

        int sz = strlen(s);
        bool ok = true, has_first = false;

        for (int i = 0; i < sz; i++) {
            if (valid_let[s[i] - 'A'] == false) {
                ok = false;
                break;
            }

            if (s[i] == first_let) {
                has_first = true;
            }
        }

        if (ok && has_first) {
            strcpy(wordlist->list[sz-4][wordlist->size[sz-4]], s);
            wordlist->size[sz-4]++;
        }
    }

    fclose(file);
}

void solucao(WordList* wordlist) {
    printf("para encerrar o jogo estavam faltando as palavras:\n");
    
    printf("(4 letras) ");
    for (int i = 0; i < wordlist->size[0]; i++) {
        if (i == wordlist->size[0] - 1) {
            printf("%s\n", wordlist->list[0][i]);
            break;
        }
        printf("%s, ", wordlist->list[0][i]);
    }

    printf("(5 letras) ");
    for (int i = 0; i < wordlist->size[1]; i++) {
        if (i == wordlist->size[1] - 1) {
            printf("%s\n", wordlist->list[1][i]);
            break;
        }
        printf("%s, ", wordlist->list[1][i]);
    }

    printf("(6 letras) ");
    for (int i = 0; i < wordlist->size[2]; i++) {
        if (i == wordlist->size[2] - 1) {
            printf("%s\n", wordlist->list[2][i]);
            break;
        }
        printf("%s, ", wordlist->list[2][i]);
    }

    printf("(7 letras) ");
    for (int i = 0; i < wordlist->size[3]; i++) {
        if (i == wordlist->size[3] - 1) {
            printf("%s\n", wordlist->list[3][i]);
            break;
        }
        printf("%s, ", wordlist->list[3][i]);
    }

    printf("(8 letras) ");
    for (int i = 0; i < wordlist->size[4]; i++) {
        if (i == wordlist->size[4] - 1) {
            printf("%s\n", wordlist->list[4][i]);
            break;
        }
        printf("%s, ", wordlist->list[4][i]);
    }

    printf("fim!\n");
}

int main() {
    WordList* wordlist = malloc(sizeof(WordList));
    if (wordlist == NULL) {
        printf("ERRO!\n");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        wordlist->size[i] = 0;
        wordlist->found[i] = 0;
    }

    char op[15];
    while(scanf(" %s", op) != EOF) {
        if (!strcmp(op, "inicio")) {
            inicio(wordlist);
        } else if (!strcmp(op, "palavra")) {

        } else if (!strcmp(op, "progresso")) {
            
        } else if (!strcmp(op, "solucao")) {
            solucao(wordlist);
        }
    }

    return 0;
}