#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORDS 500
#define MAX_WORD_SIZE 30

typedef struct {
    char list[MAX_WORD_SIZE][MAX_WORDS][MAX_WORD_SIZE];
    int size[MAX_WORD_SIZE];
    int found[MAX_WORD_SIZE];
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

void printa_linha(WordList* wordlist, int word_size) {
    printf("(%d letras) ", word_size);
    for (int i = 0; i < wordlist->size[word_size - 4]; i++) {
        if (i == wordlist->size[word_size - 4] - 1) {
            printf("%s\n", wordlist->list[word_size - 4][i]);
            break;
        }
        printf("%s, ", wordlist->list[word_size - 4][i]);
    }
} 

void solucao(WordList* wordlist) {
    printf("para encerrar o jogo estavam faltando as palavras:\n");
    
    for (int i = 0; i < MAX_WORD_SIZE; i++) {
        if (wordlist->size[i] == 0) continue;
        printa_linha(wordlist, i + 4);
    }

    printf("fim!\n");
}

int main() {
    WordList* wordlist = malloc(sizeof(WordList));
    if (wordlist == NULL) {
        printf("ERRO!\n");
        exit(1);
    }

    for (int i = 0; i < MAX_WORD_SIZE; i++) {
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