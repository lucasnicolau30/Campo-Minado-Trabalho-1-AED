#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MINA -1

// Função para alocar a matriz de inteiros (campo minado)
int** alocaMatriz(int n){
    int **mat = malloc(n * sizeof(int *)); // Aloca memória para as linhas
    if (mat == NULL){
        printf("Erro na alocação de memória para a matriz\n");
        exit(1); // Finaliza o programa em caso de erro
    }
    for(int i = 0; i < n; i++){
        mat[i] = malloc(n * sizeof(int)); // Aloca memória para cada linha
        if (mat[i] == NULL){
            printf("Erro na alocação de memória para a linha %d da matriz\n", i);
            exit(1); // Finaliza o programa em caso de erro
        }
    }
    return mat; // Retorna o ponteiro para a matriz alocada
}

// Função para alocar a matriz auxiliar (máscara do campo minado , qual o usuário irá ver ao jogar)
char** alocaMascara(int n){
    char **mascara = malloc(n * sizeof(char *)); // Aloca memória para as linhas
    if (mascara == NULL){
        printf("Erro na alocação de memória para a máscara\n");
        exit(1); // Finaliza o programa em caso de erro
    }
    for(int i = 0; i < n; i++){
        mascara[i] = malloc(n * sizeof(char)); // Aloca memória para cada linha
        if (mascara[i] == NULL){
            printf("Erro na alocação de memória para a linha %d da máscara\n", i);
            exit(1); // Finaliza o programa em caso de erro
        }
    }
    return mascara; // Retorna o ponteiro para a máscara alocada
}

// Função para inicializar a matriz com 0 (campo minado original)
void inicializaMatriz(int **mat, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = 0; // Inicializa cada célula com 0
        }
    }
}

// Função para inicializar a máscara (matriz auxiliar) com '#'
void inicializaMascara(char **mascara, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mascara[i][j] = '#'; // Inicializa cada célula com '#'
        }
    }
}

// verifica quantas minas tem próximas as posições que não tem minas
void atualizaContagemAdjacente(int **mat, int n){
    for(int x = 0; x < n; x++){
        for(int y = 0; y < n; y++){
            if(mat[x][y] == MINA){
                continue;
            }

            int acum = 0; 
            // Verifica as posições adjacentes
            if(x + 1 < n && mat[x + 1][y] == MINA) acum++; // Célula abaixo
            if(x - 1 >= 0 && mat[x - 1][y] == MINA) acum++; // Célula acima
            if(y + 1 < n && mat[x][y + 1] == MINA) acum++; // Célula à direita
            if(y - 1 >= 0 && mat[x][y - 1] == MINA) acum++; // Célula à esquerda
            if(x - 1 >= 0 && y - 1 >= 0 && mat[x - 1][y - 1] == MINA) acum++; // Diagonal superior esquerda
            if(x - 1 >= 0 && y + 1 < n && mat[x - 1][y + 1] == MINA) acum++; // Diagonal superior direita
            if(x + 1 < n && y - 1 >= 0 && mat[x + 1][y - 1] == MINA) acum++; // Diagonal inferior esquerda
            if(x + 1 < n && y + 1 < n && mat[x + 1][y + 1] == MINA) acum++; // Diagonal inferior direita

            mat[x][y] = acum;
        }
    }
}

void adicionaMinas(int **mat, int n, int minas){
    int cont = 0;
    srand(time(NULL)); // gerador aleatório a partir do relógio
    while(cont < minas){
        int x = rand() % n;
        int y = rand() % n;
        if(mat[x][y] != MINA){
            mat[x][y] = MINA; 
            cont++; 
        }
    }
    atualizaContagemAdjacente(mat, n);
}

// imprime a matriz orinal apenas em casos de derrota
void imprimeMatriz(int **mat, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(mat[i][j] == -1){
                printf("%d ", mat[i][j]); // Exibe as minas como -1 
            } else {
                printf(" %d ", mat[i][j]); // Exibe os outros valores
            }
        }
		 // Há esse if e else para manter a matriz totalmente reta ao exibir as coordenadas com -1 
        printf("\n");
    }
}

void imprimeMascara(char **mascara, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%c ", mascara[i][j]); 
        }
        printf("\n");
    }
}

int main() {
    char nivel[100];
    int n = 0, minas = 0;

    while (1){ 
        printf("Escolha uma das dificuldades a seguir: facil , medio ou dificil.\n");
        scanf("%99s", nivel);

        if(strcmp(nivel, "facil") == 0){
            n = 10; minas = 3;
            break; 
        } 
		  else if(strcmp(nivel, "medio") == 0){
            n = 20; minas = 6;
            break; 
        } 
		  else if(strcmp(nivel, "dificil") == 0){
            n = 30; minas = 9;
            break;
        } 
		  else{
            printf("Dificuldade inválida! Tente novamente.\n");
            continue; 
        }
    }

    int **mat = alocaMatriz(n);
    inicializaMatriz(mat, n);
    adicionaMinas(mat, n, minas);

    char **mascara = alocaMascara(n); 
    inicializaMascara(mascara, n); 
	 imprimeMascara(mascara, n);
	 printf("Bem-Vindo ao Jogo!! \n");			
	
    int jogoAtivo = 1;
    while(jogoAtivo){
        printf("Digite as coordenadas dessa maneira: (linha, coluna): ");
        int linha, coluna;
        scanf("%d,%d", &linha, &coluna); 
        // Ajusta para índices para começar em 0,0
        linha--;
        coluna--;
        // Verifica se as coordenadas são válidas
        if(linha < 0 || linha >= n || coluna < 0 || coluna >= n){
        	printf("Coordenadas inválidas! Tente novamente.\n");
        } 
		  else if(mascara[linha][coluna] != '#') {
        	printf("Você já revelou essa posição! Tente outra.\n");
        } 
		  else{
        	// Ação do jogador
         if(mat[linha][coluna] == MINA){ // caso derrota
         	imprimeMatriz(mat, n);
				printf("Você encontrou uma mina! Game over.\n");
            jogoAtivo = 0;
            } 
			else{
         	mascara[linha][coluna] = '0' + mat[linha][coluna]; // Atualiza a máscara com o número de minas adjacente da matriz original
			   imprimeMascara(mascara, n);
            // Verifica se o jogador ganhou
            int casasDescobertas = 0;
            for (int i = 0; i < n; i++) {
             for (int j = 0; j < n; j++) {
             	if (mascara[i][j] != '#' && mat[i][j] != MINA) {
               	casasDescobertas++;
               }
              }
             }
       	   if(casasDescobertas == (n * n - minas)){ // caso vitória
            	imprimeMascara(mascara, n); 
            	printf("Você acertou todas as casas sem minas! Parabéns!\n");
					if(strcmp(nivel, "facil") == 0){
						printf("Agora que venceu no nível fácil por que não jogar no médio?");
            		break; 
        			}
					else if(strcmp(nivel, "medio") == 0){
            		printf("Agora que venceu no nível médio por que não jogar no dificil?");
						break; 
        			}
					else if(strcmp(nivel, "dificil") == 0){
						printf("Impressionante!! Nem o nível mais difícil foi capaz de te parar , espere novos níveis");
            		break; 
        			}
            	jogoAtivo = 0;
            }
           }
        	}
    	}
	
    for(int i = 0; i < n; i++){
        free(mat[i]);
        free(mascara[i]);
    }
    free(mat);
    free(mascara);

    return 0;
}
