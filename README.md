<div align="center">
  <h1>Words Finder</h1>
  <p>Trabalho Final da disciplina de Algoritimos e Estrutura de Dados</p>
</div>

## O que o programa faz

Programa que recebe como entrada dois valores: um arquivo '.txt' e uma string que pode ser 'arvore' ou 'lista' e representa a estrutura de dados que deve ser utilizada (arvore ou lista). A partir disso, o programa armazena na estrutura escolhida todas as palavras do arquivo, mostra na tela informações relevantes sobre ele (como sua quantidade de linhas e palavras) e fica à disposição do usuário para realizar buscas por palavras no arquivo, retornando em quais linhas as palavras buscadas se encontram (caso existam) e também o tempo levado pela busca.

## Como usar
- Tendo baixado o código, rode os seguintes comandos no terminal (dentro da pasta do arquivo):
```
$ gcc -o ep1.exe ep1.c
 ```
 ```
 $ ./ep1.exe texto.txt estrutura
 ```
Sendo que 'texto.txt' deve ser substituído pelo arquivo real em que se deseja realizar a busca (caso o arquivo se encontre em outra pasta, é necessário especificar o caminho para o arquivo), assim como 'estrutura' deve ser substituído pela estrutura que se deseja utilizar (podendo ela ser 'lista' ou 'arvore').
- Posteriormente, basta digitar:
 ```
 > busca palavraBusca
 ```
para que o programa realize a busca no arquivo em questão (no caso do exemplo acima, a palavra buscada seria 'palavraBusca').
- Quando desejar encerrar a execução do programa, basta digitar 'fim'.

## Observações
- O programa desconsidera pontuação na busca.
- Palavras que contém '/', '-' ou '_' são separadas na hora de serem guardadas na estrutura (por exigência da proposta do trabalho), ou seja, a palavra 'guarda-chuva' seria dividida em 'guarda' e 'chuva' na hora de sere armazenada, o que faz com que a busca por 'guarda-chuva' nunca seja correspondida.
- A busca é case insensitive: versões maiúsculas e minúsculas de um caracteres são consideradas iguais.
- A busca é sempre feita considerando palavras inteiras (por exemplo, se no arquivo texto existem as palavras “algorithm” e “algorithms”, e uma busca é feita pela palavra “algorithm”, as ocorrências da palavra no plural não devem ser consideradas).
