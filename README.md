# Jogo Campo Minado em C

## Descrição

Este é uma implementação simples do clássico jogo Campo Minado, escrita em C. O jogo permite que os usuários escolham um nível de dificuldade (fácil, médio ou difícil) e, em seguida, gera uma grade com minas escondidas. Os jogadores devem revelar células sem acertar uma mina, e o jogo fornece a quantidade de minas adjacentes para cada célula revelada.

## Recursos

- Níveis de dificuldade selecionáveis:
  - Fácil (grade 10x10, 3 minas)
  - Médio (grade 20x20, 6 minas)
  - Difícil (grade 30x30, 9 minas)
- Exibe o número de minas adjacentes para cada célula.
- O jogo termina quando uma mina é revelada ou todas as células seguras são descobertas.
- Gerenciamento de memória para arrays dinâmicos.

## Começando

### Pré-requisitos

- Um compilador C (por exemplo, GCC)

### Compilação

Para compilar o programa, execute o seguinte comando no seu terminal:

```bash
gcc -o campo_minado gcccampo_minado_LucasNicolau.c

Após compilar, execute o jogo com o seguinte comando:

./campo_minado

Escolha a dificuldade do jogo: (facil, medio ou dificil).
facil
# # # # # # # # # # 
# # # # # # # # # # 
...
Bem-Vindo ao Jogo!!
Digite as coordenadas (linha, coluna): 1,1
0 1 1 # # ...
...
Você encontrou uma mina! Game over.
