#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMA 8
#define NAVIOS 3

//funçao para criar o tabuleiro.
void criarTabuleiro(char tabuleiro[TAMA][TAMA]) {
    for (int i = 0; i < TAMA; i++) {
        for (int j = 0; j < TAMA; j++) {
            tabuleiro[i][j] = '-';
        }
    }
}
//função para mostrar o tabuleiro para o usuario e esconder os navios criados se jagador E chamarmos mostrarTabuleiro(tabuleiro, 0) se for 1 ele mostra os N.
void mostrarTabuleiro(char tabuleiro[TAMA][TAMA], int mostrarNavios) {
    //aqui mostra a parte de cima da tabela
    printf("  0 1 2 3 4 5 6 7\n");
    for (int i = 0; i < TAMA; i++) {
        //exibe o número da linha antes de imprimir os elementos.
        printf("%d ", i);
        for (int j = 0; j < TAMA; j++) {
            //verificar se na posição tem um navio N se tiver ele esconde o navio com "_"
            if (!mostrarNavios && tabuleiro[i][j] == 'N') {
                printf("- ");
            } else {
                printf("%c ", tabuleiro[i][j]);
            }
        }
        // garante que cada linha do tabuleiro seja impressa corretamente.
        printf("\n");
    }
}
//funcao para posicionar os navios no tabuleiro.
void posicionarNavios(char tabuleiro[TAMA][TAMA], int jogador) {
    int x, y, i = 0;
    printf("Jogador %d, posicione seus %d navios:\n", jogador, NAVIOS);
    while (i < NAVIOS) {
        printf("Navio %d - Digite linha e coluna (0 a 7): ", i + 1);
        scanf("%d %d", &x, &y);
        
        if (x >= 0 && x < TAMA && y >= 0 && y < TAMA && tabuleiro[x][y] == '-') {
            tabuleiro[x][y] = 'N';
            i++;
        } else {
            printf("Posição invalida ou ocupada. Tente novamente.\n");
        }
    }
}



int main(){
    char tabuleiro1[TAMA][TAMA];
    char tabuleiro2[TAMA][TAMA];
    int modo, dificuldade;
    int jogador = 1;
    int fim = 0;
    int x, y;
    // usado apenas para o PC lembrar os acertos
    // int memoria[2] = {-1, -1}; 

    // Inicializa a semente com o tempo atual para que o rand() funcione sempre trocando os números aleatórios sem repetir o mesmo padrão.
    srand(time(NULL));
    //
    criarTabuleiro(tabuleiro1);
    criarTabuleiro(tabuleiro2);
    //enquanto for diferente de 1 ou 2 ele continua o loop 
    while(modo != 1 && modo != 2){
        printf("=== BATALHA NAVAL ===\n");
        printf("1 - Jogador vs Jogador\n2 - Jogador vs PC\nEscolha o modo: ");
        scanf("%d", &modo);
        //se for diferente ele mostra na tela a mensagem.
        if (modo !=2 && modo !=1){
            printf("Por favor digite um numero valido para selecao:\n");
        }
    }
        if(modo == 2) {
            printf("Nível de dificuldade:\n1 - Fácil\n2 - Difícil\nEscolha: ");
            scanf("%d", &dificuldade);
        }
    //chamar a função para e criar os navios
        posicionarNavios(tabuleiro1, 1);



    return 0;
}
