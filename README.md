# Sobre
O trabalho desenvolvido foi realizado para a disciplina de Introdução à Ciência de Computação II (SCC0201) ministrada pelo docente Diego Raphael Amancio.


# Decisoes de projeto
A resolução do problema proposto foi desenvolvida a partir da busca das palavras validas no arquivo valid_words.txt e da organização dessas palavras verificadas como validas bem como informações sobre elas em um estrura de dados chamada WordList, além disso na operação de verificação de uma entrada válida utilizamos busca binaria para otimização.
A organização inicial dos dados na estrutura facilita o acesso as palavras válidas sem ocupar espaço significativo na memória possibilitando um código mais eficiente e conciso.
<!-- Optamos por percorrer o arquivo apenas uma vez e já delimitar as palavras válidas mesmo que a operação tenha custo O(n), dado que se fossemos realizar uma busca binária no arquivo em toda verificação se uma palavra é valida a troca de informacao entre o SSD/HD e a memoria RAM ao carregar os buffers poderiam deixar o programa lento, mesmo que a complexidade assintótica seja O(logn) para cada operação. Além disso, a memória utilizada para armazenar as palavras válidas é baixa e ao armazenar outras informacoes como. deixa pra lá 
 -->
## Wordlist
Para otimizar a memória todos os campos que contém informações sobre o tamanho das palavras foram decrecidas 4 unidades, isso porque a menor quantidade de letras em uma palavra é 4, portanto uma palavra de 4 letras tem tamanho 0, uma de 5 letras tem tamanho 1 e assim por diante.  
A estrutura possui quatro campos e são eles respectivamente:

### char list[MAX_WORD_SIZE][MAX_WORDS][MAX_WORD_SIZE] 
A estrutura pode ser interpretada como uma matriz de strings que contem as palavras validas, as linhas agrupam a palavras por tamanho e as colunas servem para armazenar as strings de cada tamanho em ordem alfabética. 

### int size[MAX_WORD_SIZE] 
A estrutura é uma lista que guarda em cada indice a quantidade de palavras com tal tamanho, como mencionado anteriomente já que o numero minimo de letras é 4, o indice 0 corresponde a palavras de 4 letras e assim por diante. Podemos interpretar a lista como uma tabela hash perfeita em que a função usa do tamanho da palavra para armazenar uma informação.

### int found[MAX_WORD_SIZE]
A estrutura é uma lista que guarda em cada indice a quantidade de palavras com tal tamanho **ja encontradas pelo usuario** e segue a mesma lógica da estrutura anterior.

### int falta 
A variável armazena a quantidade de palavras validas ainda não encontradas pelo usuário.

# Implementação
A resolução do problema foi realizada utilizando 4 funções principais além da main, cada uma delas contém as operações realizadas de acordo com os comandos de entrada e são executadas através de um switch case, são elas:

## inicio
Guarda as informações na struct WordList que serão utilizadas na execução do jogo através da busca das palavras validas no arquivo valid_words.txt baseando na entrada do usuario (letras fornecidas).

## palavra
Realiza a verificação da validez da palavra inserida pelo usuario, caso seja valida, as informacoes na struct wordlist são atualizadas. A busca é feita inicialmente delimitando a linha na matriz "list" em que a palavra se encontra através de seu tamanho e realizando uma busca binária através da função **"busca_binaria"** (para otimizacao do algoritmo) nas colunas com a linha fixada.  

## progresso
Imprime o progresso do usuario até o momento de acordo com as especificações do projeto. A estrutura "list" (em WordList) ajuda a agrupar as palavras em tamanho para a impressão, e o vetor "size" (em WordList) ajuda a pular tamanhos que não tenham palavras. 

## solucao
Imprime a solução de acordo com as especificações do projeto. A estrutura "list" (em WordList) ajuda a agrupar as palavras em tamanho para a impressão, e o vetor "size" (em WordList) ajuda a pular tamanhos que não tenham palavras. A função **"printa_linha"** é usada para imprimir cada grupo de palavras com certo tamanho de acordo com as especificações do projeto.