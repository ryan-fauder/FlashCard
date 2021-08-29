# Flash Card

Projeto de Flash Cards com Coleções desenvolvido na linguagem C.

O usuário pode criar e nomear coleções, onde as cartas podem ser inseridas. Conforme o Spaced Repetition System (SRS), é importante revisar conceitos com períodos espaçados de tempo para consolidar esse conhecimento. Nesse sentido, o projeto desenvolvido baseia-se nesse sistema. As cartas possuem um intervalo de tempo para que precisem ser jogadas novamente e, assim, auxiliar na rentenção do conhecimentos.

## Como começar?

Primeiramente realize um:
```bash
  git clone
```
Em seguida, abra um terminal na pasta em que está o código do programa e execute:

```bash
  ./main -help
```

## Comandos:

### Coleções:

- create (nome): Cria uma coleção com nome informado;
- view (colecao): Visualizar todas as cartas de uma coleção;
- remove (colecao): Remove uma coleção;

### Cartas:

- new (nome_colecao): Cria uma carta;
- edit (nome_colecao): Editar uma carta;
- del (nome_colecao): Apagar uma carta;

### Treino:

- playall: Treina-se com todas cartas atrasadas;
- playonly (nome_colecao): Treina-se com todas as cartas atrasadas da coleção informada;
- play (nome_colecao): Treina-se com todas as cartas da coleção informada;

## Desenvolvedor:

- Ryan Fernandes Auder Lopes
