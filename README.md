# Sobre
O trabalho desenvolvido foi realizado para a disciplina de Introdução à Ciência de Computação II (SCC0201) ministrada pelo docente Diego Raphael Amancio.

# Decisões de projeto
A resolução do problema proposto foi desenvolvida a partir da busca das palavras validas no arquivo valid_words.txt e da organização dessas palavras verificadas como pertencentes a solução, bem como informações sobre elas em uma estrutura de dados chamada WordList. A organização inicial dos dados na estrutura facilita o acesso às palavras válidas sem ocupar espaço significativo na memória, possibilitando um código mais eficiente e conciso.

Ademais, durante o programa, a verificação de validade de uma entrada é feita utilizando o algoritmo de **busca binária**, otimizando o tempo de busca para **O(log⁡n)** em comparação a uma abordagem de busca linear que seria **O(n)**.

## Wordlist
Para otimizar a memória, os campos relacionados ao tamanho das palavras são ajustados com base em um deslocamento de 4 unidades, pois o menor tamanho de palavra é 4. Dessa forma, palavras de 4 letras têm tamanho representado por 0, palavras de 5 letras por 1, e assim por diante.  
A estrutura possui quatro campos e são eles respectivamente:

### char list[MAX_WORD_SIZE][MAX_WORDS][MAX_WORD_SIZE] 
A estrutura pode ser interpretada como uma matriz de strings que contem as palavras validas contidas na solução, as linhas agrupam a palavras por tamanho e as colunas servem para armazenar as strings de cada tamanho em ordem alfabética, de forma a possibilitar a realização do algoritmo de busca binária fixada alguma linha. Essa organização permite acessar rapidamente palavras de um tamanho específico e realizar busca binária, otimizando a eficiência temporal.

### int size[MAX_WORD_SIZE] 
A estrutura é uma lista que guarda em cada índice (ajustado) a quantidade de palavras contidas na solução com tal tamanho (4 letras correspondem ao índice 0 e assim por diante). Podemos interpretar a lista como uma tabela hash perfeita em que a função usa o tamanho da palavra para armazenar uma informação, permitindo o acesso indexado à quantidade de palavras de cada tamanho, visto que será uma informação importante para várias funções do programa.

### int found[MAX_WORD_SIZE]
A estrutura é uma lista que guarda em cada índice a quantidade de palavras com tal tamanho **já encontradas pelo usuário** e segue a mesma lógica de índices ajustados da estrutura anterior, simplificando o acesso a essas informações de maneira otimizada.

### int falta 
Variável que armazena a quantidade de palavras validas contidas na solução que ainda não foram encontradas pelo usuário, permitindo determinar quando todas as soluções foram identificadas.

# Busca Binária
O algoritmo foi implementado na função "busca_binaria" e opera em alguma linha (determinada pelo tamanho da palavra) da estrutura "list", uma vez fixada a linha, o algoritmo irá buscar nas colunas a palavra fornecida pelo usuário. Podemos abstrair a estrutura utilizada como um vetor de strings organizadas em ordem alfabética. Como não estamos lidando com números, a função "strcmp" da biblioteca "strings.h" é utilizada para comparar palavras de forma lexicográfica e, através do retorno da função, é possível determinar se a busca deve continuar na metade superior ou inferior do vetor. 

Essa abordagem reduz o tempo de busca para **O(log⁡n)**, sendo eficiente mesmo para grandes conjuntos de palavras.

# Implementação
Além da função de busca binária, a resolução do problema foi realizada utilizando 4 funções principais, além da main, para executar as operações conforme os comandos de entrada:

## inicio
Guarda as informações na struct WordList que serão utilizadas na execução do jogo através da leitura das palavras validas no arquivo valid_words.txt, utiliza a entrada do usuário (letras fornecidas) para filtrar as palavras pertencentes a solução e agrupá-las por tamanho.

## palavra
Realiza a verificação da validez da palavra inserida pelo usuário, a validação ocorre utilizando a busca binária através da função **"busca_binaria"**, que é aplicada em uma linha específica da matriz "list" com base no tamanho da palavra, otimizando o tempo de busca em comparação com abordagens lineares.

## progresso
Imprime o progresso do usuário até o momento de acordo com as especificações do projeto. A estrutura "list" ajuda a organizar as palavras por tamanho, e o vetor "size" ajuda a pular tamanhos sem palavras. 

## solucao
Imprime a solução de acordo com as especificações do projeto. A estrutura "list" ajuda a organizar as palavras por tamanho, e o vetor "size" ajuda a pular tamanhos sem palavras. A função **"printa_linha"** é usada para imprimir cada grupo de palavras com tamanho idêntico de acordo com as especificações do projeto.
