# Sobre
O trabalho desenvolvido foi realizado para a disciplina de Introdução à Ciência de Computação II (SCC0201) ministrada pelo docente Diego Raphael Amancio.


# Decisoes de projeto
A resolução do problema proposto foi desenvolvida a partir da busca das palavras validas no arquivo valid_words.txt e da organização dessas palavras verificadas como validas bem como informações sobre elas em um estrura de dados chamada WordList, além disso na operação de verificação de uma entrada válida utilizamos busca binaria para otimização.
## Wordlist
A estrutura possui quatro campos e são eles respectivamente:

### char list[MAX_WORD_SIZE][MAX_WORDS][MAX_WORD_SIZE] 
Matriz de strings que contem as palavras validas, as linhas representam o tamanho da palavra e as colunas servem para armazenar mais de uma string por linha

### int size[MAX_WORD_SIZE] 
Guarda em cada indice a quantidade de palavras com tal tamanho como o numero minimo de palavras é 4, o indice 0 corresponde a 4 letras e assim por diante

### int found[MAX_WORD_SIZE]
guarda em cada indice a quantidade de palavras com tal tamanho JA ENCONTRRADAS como o numero minimo de palavras é 4, o indice 0 corresponde a 4 letras e assim por diante

#### int falta 
Quantidade de palavras validas



