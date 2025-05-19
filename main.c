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
        // garante que cada linha do tabuleiro seja impressa corretamente 
        printf("\n");
    }
}


//funcao para preencher a matriz de posicao dos navios e colocar no tabuleiro
int preencherMatriz(int xi, int multiplicadorX, int yi, int multiplicadorY, int tamNavio, char tabuleiro[TAMA][TAMA]){
    
    int posicao[tamNavio][2]; // linhas são o tamanho do navio, colunas [0]-->x [1]-->y
    
    //preenche a coluna x com valores de x para cada espaço que o navio ocupa
    for(int i = 0; i < tamNavio; i++){
        posicao[i][0] = xi + (multiplicadorX*i); 
    } 
        
    //preenche a coluna y com valores de y para cada espaço que o navio ocupa
    for(int i = 0; i < tamNavio; i++){
        posicao[i][1] = yi + (multiplicadorY*i);  
        
    } 
    
    //checa para ver se todos os epaços estão livres
    for(int i = 0; i < tamNavio; i++){
        int x = posicao[i][0]; //pega os valores de x de cada espaço que o navio ocupa
        int y = posicao[i][1]; //pega os valores de y de cada espaço que o navio ocupa
        if( tabuleiro[x][y] != '-'){
            return 0;
        }
    }
    
    //preenche os espaços
    for(int i = 0; i < tamNavio; i++){
        int x = posicao[i][0];
        int y = posicao[i][1];
        if( tabuleiro[x][y] == '-'){
            tabuleiro[x][y] = 'N';
        }
    }
    printf("\n");
    return 1;
}

//funcao para mostrar o texto e receber xi, yi e direcao
int mostraTexto(int i, int tamNavio, int *xi, int *yi, char *d){
    printf("\n");
    printf("Navio %i, ocupa %i posições.\n", i+1, tamNavio);
    
    printf("Escolha o número da linha(0 a 7): ");
    scanf("%d", xi);
    if ( *xi < 0 || *xi >= TAMA ) {
        return 0;
    }
    printf("Escolha o número da coluna(0 a 7): ");
    scanf("%d", yi);
    if ( *yi < 0 || *yi >= TAMA ) {
        return 0;
    }
    
    printf("Digite a direção do navio (W, A, S, D): ");
    scanf(" %c", d);
    printf("\n");
    return 1;
}

//funcao para checar para ver se a direçao é aceita e se o navio cabe no tabuleiro
int checkDirecao(char d, int *multiplicadorX, int *multiplicadorY, int xi, int yi, int tamNavio){
    
    //se for para cima
    if(d == 'w' || d == 'W'){ 
        *multiplicadorX = -1; //vai multiplicar a soma para diminuir o x
        *multiplicadorY = 0; //n vai influenciar
        
        //checa para ver se o navio n saiu do tabuleiro
        if( (xi - tamNavio) >= 0 ){
            return 1;
        } else {
            return 0;
        }
    }

    if(d == 's' || d == 'S'){
        *multiplicadorX = 1; //vai multiplicar a soma para aumentar o x
        *multiplicadorY = 0;
        
        if( (xi + tamNavio) < TAMA ){
            return 1;
        } else {
            return 0;
        }
    }
    
    if(d == 'd' || d == 'D'){
        *multiplicadorX = 0;
        *multiplicadorY = 1; //vai multiplicar a soma para aumentar o y
        
        if( (yi + tamNavio) < TAMA ){
            return 1;
        } else {
            return 0;
        }
    }
    
    if(d == 'a' || d == 'A'){
        *multiplicadorX = 0;
        *multiplicadorY = -1; //vai multiplicar a soma para diminuir o y
        
        if( (yi - tamNavio) >= 0 ){
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
    
}


// V2
//funcao para posicionar os navios no tabuleiro.
void posicionarNavios(char tabuleiro[TAMA][TAMA], int jogador){
    int i = 0;
    int tamNavio = 2;
    char d;
    
    printf("Jogador %d, posicione seus %d navios:\n", jogador, NAVIOS);
    mostrarTabuleiro(tabuleiro, 1);
    
    while (i < NAVIOS) {
        int xi = 0, yi = 0;
        int multiplicadorX = 0, multiplicadorY = 0;
        
        if( mostraTexto(i, tamNavio, &xi, &yi, &d) == 1){
            if( checkDirecao(d, &multiplicadorX, &multiplicadorY, xi, yi, tamNavio) == 1 ){
                if( preencherMatriz(xi, multiplicadorX, yi, multiplicadorY, tamNavio, tabuleiro) == 1 ){
                    mostrarTabuleiro(tabuleiro, 1);
                    tamNavio++;
                    i++;
                } else {
                printf("Posição inválida ou ocupada, tente novamente\n");
                mostrarTabuleiro(tabuleiro, 1);
                }
            } else {
                printf("Posição inválida ou ocupada, tente novamente\n");
                mostrarTabuleiro(tabuleiro, 1);
            }
        } else {
            printf("Posição inválida ou ocupada, tente novamente\n");
            mostrarTabuleiro(tabuleiro, 1);
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
