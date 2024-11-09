#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_SIZE 10

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
    while (fscanf(file, "%s", s) != EOF) {
        for (int i = 0; i < 30; i++) printf("%d %d\n", i, valid_let[i]);

        int sz = strlen(s);
        bool ok = true, has_first = false;
        printf("%s\n", s);

        for (int i = 0; i < sz; i++) {
            printf("%c ", s[i]);
            printf("%d\n", s[i] - 'A');

            if (valid_let[s[i] - 'A'] == false) {
                printf("NAO E BOM\n");
                ok = false;
                break;
            }

            if (s[i] == first_let) {
                printf("E PRIMEIRA LETRA\n");
                has_first = true;
            }
        }

        if (ok && has_first) {
            printf("%s\n", s);
            strcpy(s, wordlist->list[sz-4][wordlist->size[sz-4]]);
            wordlist->size[sz-4]++;
        }

        for (int i = 0; i < 30; i++) printf("%d %d\n", i, valid_let[i]);
    }

    fclose(file);
}

void solucao(WordList* wordlist) {
    printf("para encerrar o jogo estavam faltando as palavras:\n");
    
    printf("(4 letras) ");
    for (int i = 0; i < wordlist->size[0]; i++) {
        if (i == wordlist->size[0] - 1) {
            printf("%s\n", wordlist->list[0][i]);
        }
        printf("%s, ", wordlist->list[0][i]);
    }
}

int main() {
    char op[15];
    scanf("%s", op);

    WordList* wordlist = malloc(sizeof(WordList));
    if (wordlist == NULL) {
        printf("ERRO!\n");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        wordlist->size[i] = 0;
        wordlist->found[i] = 0;
    }

    printf("antes\n");

    if (!strcmp(op, "inicio")) {
        inicio(wordlist);
        printf("depois\n");
    } else if (!strcmp(op, "palavra")) {

    } else if (!strcmp(op, "progresso")) {
        
    } else if (!strcmp(op, "solucao")) {
        solucao(wordlist);
    }

    return 0;
}