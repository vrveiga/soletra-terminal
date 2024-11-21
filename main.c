#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORDS 500
#define MAX_WORD_SIZE 30

typedef struct { //estrutura que contem informacoes sobre o jogo
    /*matriz de strings que contem as palavras validas, as linhas representam o tamanho da palavra 
    e as colunas servem para armazenar as strings de mesmo tamanho em ordem alfabetica*/
    char list[MAX_WORD_SIZE][MAX_WORDS][MAX_WORD_SIZE]; 
    /*guarda em cada indice a quantidade de palavras com tal tamanho
    como o numero minimo de letras é 4, o indice 0 corresponde a 4 letras e assim por diante*/
    int size[MAX_WORD_SIZE]; 
    /*guarda em cada indice a quantidade de palavras com tal tamanho JA ENCONTRRADAS
    como o numero minimo de palavras é 4, o indice 0 corresponde a 4 letras e assim por diante*/
    int found[MAX_WORD_SIZE];
    int falta; //quantidade de palavras validas
} WordList;


/*
Guarda as informações na struct WordList que serão utilizadas na execução do jogo
através da verificação das palavras no arquivo valid_words.txt baseando na entrada do usuario
Parâmetros: 
    *wordlist - estrutura que armazena informacoes sobre o jogo
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
    while (fscanf(file, " %s", s) != EOF) { //faz a leitura de todas palavras do arquivo

        int sz = strlen(s); //tamanho da palavra
        bool ok = true; 
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
            /*copia a palavra (string) na estrutura list, o primeiro indice é o tamanho da palavra,
            o segundo a quantidade de palavras com esse tamanho até o momento */
            strcpy(wordlist->list[sz-4][wordlist->size[sz-4]], s);
            wordlist->size[sz-4]++; //atualiza a informacao sobre a quantidade de palavras com certo tamanho
            wordlist->falta++; //atualiza a quantidade de palavras validas
        }
    }

    fclose(file);
}

/*
Realiza o algoritmo de busca binária nas palavras de certo tamanho
Parâmetros: 
    wordlist[MAX_WORDS][MAX_WORD_SIZE] - lista das colunas da matriz de strings com alguma linha (tamanho das palavras) fixada
    size - tamanho das palavras que serão pesquisadas
    word - palavra que será buscada
Retorno:
    true - caso a busca seja bem sucedida
    false - caso a busca não seja bem sucedida
*/
bool busca_binaria(char wordlist[MAX_WORDS][MAX_WORD_SIZE], int size, char word[]) {
    int l = 0; //inicio da lista
    int r = size - 1; //fim da lista

    while (l <= r) { //enquanto inicio for maior que o fim 
        int m = (l + r) / 2; //meio da lista
        int cmp = strcmp(word, wordlist[m]);

        if (cmp == 0) { //caso a palavra tenha sido encontrada
            return true;
        } else if (cmp > 0) { //restabelece o inicio e o fim com base na logica da busca binaria
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return false; //palavra nao foi encontrada 
}


/*
Realiza a verificação da validez da palavra inserida pelo usuario,
caso seja valida, as informacoes na struct wordlist são atualizadas
Parâmetros: 
    *wordlist - ponteiro para estrutura que armazena informacoes sobre o jogo
*/
void palavra(WordList* wordlist) {
    // ATENÇÃO!!! Estou tomando como verdade que o jogador não vai
    // colocar uma palavra correta mais de uma vez!!!
    char word[50];
    scanf(" %40s", word);
    int sz = strlen(word);

    if (sz >= MAX_WORD_SIZE) { //verificacao se a palavra é válida evitando erros
        printf("palavra invalida\n");
        return;
    }

    //realiza busca binaria na linha da matriz que contem as palavras validas com o mesmo tamanho da palavra inserida pelo usuario 
    if (busca_binaria(wordlist->list[sz-4], wordlist->size[sz-4], word)) {
        printf("sucesso + 1\n");
        wordlist->found[sz-4]++; //atualiza a lista de palavras achadas com base no tamanho
        wordlist->falta--; 

        if (wordlist->falta == 0) { //caso todas as palavras tenham sido encontradas
            printf("parabens! voce encontrou todas as palavras\n");
            exit(0);
        }
    } else { //se a palavra inserida não é valida
        printf("palavra invalida\n");
    }
}

/*
Imprime o progresso do usuario até o momento de acordo com as especificações do projeto
Parâmetros: 
    *wordlist - ponteiro para estrutura que armazena informacoes sobre o jogo
*/
void progresso(WordList* wordlist) {
    printf("progresso atual:\n");
    for (int i = 0; i < MAX_WORD_SIZE; i++) { //percorre linhas (baseada no tamanho) da matriz de palavras validas  
        if (wordlist->size[i] == 0) continue; //caso nao haja palavras com esse tamanho
        printf("(%d letras) ", i + 4); //imprime tamanho da palavra
        //imprime demais informações das palavras do mesmo tamanho
        printf("%d palavra(s) encontrada(s) / %d palavra(s) faltando\n", wordlist->found[i], wordlist->size[i] - wordlist->found[i]);
    }
}

/*
Imprime todas as palavras de tamanho word_size que são validas
Parâmetros: 
    *wordlist - ponteiro para estrutura que armazena informacoes sobre o jogo
    word_size - tamanho das palavras que serão imprimidas
*/
void printa_linha(WordList* wordlist, int word_size) {
    printf("(%d letras) ", word_size); 
    //percorre as colunas da matriz de strings com a linha word_size-4 (tamanho das palavras) fixada
    for (int i = 0; i < wordlist->size[word_size - 4]; i++) { 
        if (i == wordlist->size[word_size - 4] - 1) { //caso seja a ultima palavra a impressão é diferente
            printf("%s\n", wordlist->list[word_size - 4][i]);
            break;
        }
        printf("%s, ", wordlist->list[word_size - 4][i]); //printa palavra 
    }
} 


/*
Imprime a solução de acordo com as especificações do projeto
Parâmetros: 
    *wordlist - ponteiro para estrutura que armazena informacoes sobre o jogo
*/
void solucao(WordList* wordlist) {
    printf("para encerrar o jogo estavam faltando as palavras:\n");
    
    for (int i = 0; i < MAX_WORD_SIZE; i++) { //percorre linhas (baseada no tamanho) da matriz de palavras validas  
        if (wordlist->size[i] == 0) continue; //caso nao haja palavras com esse tamanho
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