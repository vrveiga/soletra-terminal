#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORDS 500
#define MAX_WORD_SIZE 30

typedef struct { //estrutura que contem informacoes sobre o jogo
    char list[MAX_WORD_SIZE/*-4?*/][MAX_WORDS][MAX_WORD_SIZE]; //sla porra
    /*guarda em cada indice a quantidade de palavras com tal tamanho
    como o numero minimo de palavras é 4, o indice 0 corresponde a 4 letras e assim por diante*/
    int size[MAX_WORD_SIZE]; 
    int found[MAX_WORD_SIZE];
    int falta; //quantidade de palavras validas
} WordList;


/*
Guarda as informações da struct WordList que serão utilizadas na execução do jogo
através da verificação das palavras no arquivo valid_words.txt
Parâmetros: 
    *wordlist - estrutura que contem informacoes sobre o jogo
*/
void inicio(WordList* wordlist) {
    bool valid_let[30] = {}; //tabela hash de letras validas ou não
    char first_let; 

    for (int i = 0; i < 7; i++) {
        char c;
        scanf(" %c", &c);

        if (i == 0) { //guarda primeira letra
            first_let = c; 
        }

        valid_let[c - 'A'] = true; //marca as letras validas para '1'
    }

    FILE *file = fopen("valid_words.txt", "r");
    if (file == NULL) {
        printf("ERRO!\n");
        exit(1);
    }

    char s[MAX_WORD_SIZE];
    //O loop a seguir verifica todas as palavras validas possiveis e as guarda na estrutura list
    while (fscanf(file, " %s", s) != EOF) { //faz a leitura de cada palavra do arquivo

        int sz = strlen(s); //tamanho da palavra
        bool ok = true; //
        bool has_first = false;

        for (int i = 0; i < sz; i++) {
            if (valid_let[s[i] - 'A'] == false) { //verifica se as letras da palavras sao todas validas
                ok = false; //guarda a informação da palavra não ser valida
                break;
            }

            if (s[i] == first_let) { //verifica se a palavra tem a letra obrigatoria
                has_first = true; 
            }
        }

        if (ok && has_first) { //se a palavra for valida
            //guarda a palavra na estrutura list
            //entendi não man
            strcpy(wordlist->list[sz-4][wordlist->size[sz-4]], s);
            wordlist->size[sz-4]++; //guarda na lista a informacao sobre a quantidade de palavras com certo tamanho
            wordlist->falta++; //quantidade de palavras validas
        }
    }

    fclose(file);
}

bool busca_binaria(char wordlist[MAX_WORDS][MAX_WORD_SIZE], int size, char word[]) {
    int l = 0, r = size - 1;

    while (l <= r) {
        int m = (l + r) / 2;
        int cmp = strcmp(word, wordlist[m]);

        if (cmp == 0) {
            return true;
        } else if (cmp > 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return false;
}

void palavra(WordList* wordlist) {
    // ATENÇÃO!!! Estou tomando como verdade que o jogador não vai
    // colocar uma palavra correta mais de uma vez!!!
    char word[50];
    scanf(" %40s", word);
    int sz = strlen(word);

    if (sz >= MAX_WORD_SIZE) {
        printf("palavra invalida\n");
        return;
    }

    if (busca_binaria(wordlist->list[sz-4], wordlist->size[sz-4], word)) {
        printf("sucesso + 1\n");
        wordlist->found[sz-4]++;
        wordlist->falta--;

        if (wordlist->falta == 0) {
            printf("parabens! voce encontrou todas as palavras\n");
            exit(0);
        }
    } else {
        printf("palavra invalida\n");
    }
}

void progresso(WordList* wordlist) {
    printf("progresso atual:\n");
    for (int i = 0; i < MAX_WORD_SIZE; i++) {
        if (wordlist->size[i] == 0) continue;
        printf("(%d letras) ", i + 4);
        printf("%d palavra(s) encontrada(s) / %d palavra(s) faltando\n", wordlist->found[i], wordlist->size[i] - wordlist->found[i]);
    }
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
    exit(0);
}

int main() {
    //aloca struct wordlist
    WordList* wordlist = malloc(sizeof(WordList));
    if (wordlist == NULL) {
        printf("ERRO!\n");
        exit(1);
    }

    //define informacoes iniciais da struct 
    for (int i = 0; i < MAX_WORD_SIZE; i++) {
        wordlist->size[i] = 0;
        wordlist->found[i] = 0;
    }
    wordlist->falta = 0;

    
    char op[15]; //string da operacao 
    //loop que executa alguma funcao do programa de acordo com a instrucao fornecida
    while(scanf(" %s", op) != EOF) {
        if (!strcmp(op, "inicio")) {
            inicio(wordlist);
        } else if (!strcmp(op, "palavra")) {
            palavra(wordlist);
        } else if (!strcmp(op, "progresso")) {
            progresso(wordlist);
        } else if (!strcmp(op, "solucao")) {
            solucao(wordlist);
        }
    }


    free(wordlist);

    return 0;
}