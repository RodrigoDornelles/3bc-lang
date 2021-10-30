Tutorial em português :brazil:
==============================

3BC é uma linguagem de programação em baixo nível e de fácil aprendizado, que trabalha na forma de uma maquina virtual semelhante a um computador da década de 60, mas com uma arquitetura muito inusitada que possui processadores de apenas **3 bits**.

Apesar de ter um aspeto para ser uma linguagem esotérica, tem uma boa capacidade de uso genérico para resolver problemas computacionais, e certas vantagens com a implementação em embarcados e microcontroladores.

Foi introduzida por um brasileiro no natal de 2020 após complementar um mês de desenvolvimento, sendo um projeto para estudos e também como uma prova conceitual sobre cartões perfurados ser legível e prático tanto para humanos quanto maquinas.

Expressões Literais
-------------------

Não existe nenhuma tipagem na linguagem, apenas dados brutos; Para facilitar a utilização, o interpretador aceita diversas representações destes valores, tais como: 

| Descrição | Representação |
| :-------- | ------------: |
| Caracter ASCII | `'Z'` |
| Decimal positivo | `9` `0d9` `0i9` |
| Decimal negativo | `-9` `-0d9` `-0i9` | 
| Octal positivo/negativo | `0o7` `-0o7` |
| Binário positivo/negativo | `0b1` `-0b1` | 
| HexaDecimal positivo/negativo | `0xF` `-0xF` |
| Gerador de Hash | `:minha_funcao` |
| Vazio ou Zero | `0` `0d0` `0i0` `0o0` `0b0` `0x0` `'\0'` `NILL` |

Estrutura
---------

Um grande ponto para facilitar o aprendizado, é a sua sintaxe muito bem organizada da linguagem. Com uma rápida visualização separada em linhas e colunas, onde destas possui um tamanho fixo de parâmetros, mesmo quando não utilizados.

Uma linha do programa é consequentemente uma instrução, que possui três parâmetros de maneira obrigatória. São separados pela respectivamente ordem de **registrador**, **endereço**, **constante**.

![structure-pt-br ><](/images/structure-pt-br.png)


Sintaxe
-------

### Etiquetas ###

Conhecida como _labels_ são marcações no programa onde podem acontecer saltos condicionais, nenhuma etiqueta pode ser subscrita, e é possível fazer pulos em qualquer direção do algorítimo.

#### Efetuando marcações ####

Quando ambas colunas registrador e endereço existirem valores nulos, qualquer valor constante será considerado demarcação de etiqueta.

```RUBY
NILL NILL 0x01
```

#### Dica de marcação ####

A [Expressão literal](#expressões-literais) gerador de _hash_ tem o intuito de facilitar a organização das _labels_ em seu código, assim não depender de apenas marcações numéricas.

```RUBY
NILL NILL :inicio_do_loop
```
