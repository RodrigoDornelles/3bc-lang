Tutorial em português :brazil:
==============================

Introdução
----------
3BC é uma linguagem de programação em baixo nível e de fácil aprendizado, que trabalha na forma de uma maquina virtual semelhante a um computador da década de 60, mas com uma arquitetura muito inusitada que possui processadores de apenas **3 bits**.

Apesar de ter um aspeto para ser uma linguagem esotérica, tem uma boa capacidade de uso genérico para resolver problemas computacionais, e certas vantagens com a implementação em embarcados e microcontroladores.

Foi introduzida por um brasileiro no natal de 2020 após complementar um mês de desenvolvimento, sendo um projeto para estudos e também como uma prova conceitual sobre cartões perfurados ser legível e prático tanto para humanos quanto maquinas.


Guia rápido
-----------

### Expressões Literais ###

Não existe nenhuma tipagem na linguagem, apenas dados brutos; Para facilitar a utilização, o interpretador aceita diversas representações destes valores, tais como: 

| Descrição | Representação |
| :-------- | ------------: |
| Caracter ASCII | `'Z'` |
| Decimal positivo | `9` `0d9` `0i9` |
| Decimal negativo | `-9` `-0d9` `-0i9` | 
| Octal positivo/negativo | `0o7` `-0o7` |
| Binário positivo/negativo | `0b1` `-0b1` | 
| HexaDecimal positivo/negativo | `0xF` `-0xF` |
| Gerador de Hash | `"nao_use_como_texto"` |
| Vazio ou Zero | `0` `0d0` `0i0` `0o0` `0b0` `0x0` `'\0'` `NILL` |
