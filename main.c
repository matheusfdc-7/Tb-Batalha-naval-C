#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMA 8
#define NAVIOS 3

int memoria[64][2]; // 64 é numero total de espaços, coluna 0 é x, coluna 1 é y
int acertos[9][2]; // 9 é o maximo de acertos com navios de 4, 3 e 2
int erros[55][2]; // 64-9 = 55
int cont = 0, contAcertos = 0, contErros = 0;
int chutes = 0;
int errou = 0;

// funcao para limpar o terminal
void limparTerminal(){
    system("cls");
}

//funcao para criar o tabuleiro
void criarTabuleiro(char tabuleiro[TAMA][TAMA]) {
    for (int i = 0; i < TAMA; i++) {
        for (int j = 0; j < TAMA; j++) {
            tabuleiro[i][j] = '-';
        }
    }
}

//função para mostrar o tabuleiro para o usuario e esconder os navios criados;
void mostrarTabuleiro(char tabuleiro[TAMA][TAMA], int mostrarNavios) {
    //aqui mostra a parte de cima da tabela
    printf("  0 1 2 3 4 5 6 7\n");

    for (int i = 0; i < TAMA; i++) {
        //exibe o numero da linha antes de imprimir os elementos.
        printf("%d ", i);

        for (int j = 0; j < TAMA; j++) {
            //verificar se na posicao tem um navio N se tiver ele esconde o navio com "_"
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

    int posicao[tamNavio][2]; // linhas são cada espaço que o navio vai ocupar, colunas [0]-->x [1]-->y

    //preenche a coluna x com valores de x para cada espaço que o navio ocupa
    for(int i = 0; i < tamNavio; i++){
        posicao[i][0] = xi + (multiplicadorX*i);
    }

    //preenche a coluna y com valores de y para cada espaço que o navio ocupa
    for(int i = 0; i < tamNavio; i++){
        posicao[i][1] = yi + (multiplicadorY*i);

    }

    //checa para ver se todos os epaços estao livres
    for(int i = 0; i < tamNavio; i++){
        int x = posicao[i][0]; //pega os valores de x de cada espaço que o navio ocupa
        int y = posicao[i][1]; //pega os valores de y de cada espaço que o navio ocupa
        if( tabuleiro[x][y] != '-'){
            return 0;
        }
    }

    //preenche os espacos
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

//funcao para checar para ver se a direçao eh aceita e se o navio cabe no tabuleiro
int checkDirecao(char d, int *multiplicadorX, int *multiplicadorY, int xi, int yi, int tamNavio){

    //se for para cima
    if(d == 'w' || d == 'W'){
        *multiplicadorX = -1; //vai multiplicar a soma para diminuir o x
        *multiplicadorY = 0; //nao vai influenciar

        //checa para ver se o navio nao saiu do tabuleiro
        if( (xi - tamNavio + 1) >= 0 ){
            return 1;
        } else {
            return 0;
        }
    }

    //se for para baixo
    if(d == 's' || d == 'S'){
        *multiplicadorX = 1; //vai multiplicar a soma para aumentar o x
        *multiplicadorY = 0;

        if( (xi + tamNavio - 1) < TAMA ){
            return 1;
        } else {
            return 0;
        }
    }

    // se for para a direita
    if(d == 'd' || d == 'D'){
        *multiplicadorX = 0;
        *multiplicadorY = 1; //vai multiplicar a soma para aumentar o y

        if( (yi + tamNavio - 1) < TAMA ){
            return 1;
        } else {
            return 0;
        }
    }

    // se ofr para esquerda
    if(d == 'a' || d == 'A'){
        *multiplicadorX = 0;
        *multiplicadorY = -1; //vai multiplicar a soma para diminuir o y

        if( (yi - tamNavio + 1) >= 0 ){
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

//função para colocar os navios automaticamente no codigo:
void colocarNaviosAleatorios(char tabuleiro[TAMA][TAMA]) {
    int i = 0;
    int tamNavio = 2;
    while (i < NAVIOS) {
        int xi = rand() % TAMA;
        int yi = rand() % TAMA;
        int direcao = rand() % 4;
        int multiplicadorX = 0, multiplicadorY = 0;
        char d;

        switch (direcao) {
            case 0: d = 'W'; break;
            case 1: d = 'S'; break;
            case 2: d = 'A'; break;
            case 3: d = 'D'; break;
        }

        if (checkDirecao(d, &multiplicadorX, &multiplicadorY, xi, yi, tamNavio)) {
            if (preencherMatriz(xi, multiplicadorX, yi, multiplicadorY, tamNavio, tabuleiro)) {
                tamNavio++;
                i++;
            }
        }
    }
}

// funcao para checar se as posicoes sao validas
int checaPosicaoValida (int x, int y, char tabuleiro[TAMA][TAMA], int memoria[64][2], int cont) {

    if(tabuleiro != NULL && memoria == NULL) {
        if( x >= 0 && x < TAMA ){
            if( y >= 0 && y < TAMA ){
                for(int i = 0; i < cont; i++){
                    if( tabuleiro[x][y] != '-'){
                        return 0;
                    }
                }
                return 1;
            }
        }

        return 0;
    }

    if( tabuleiro == NULL && memoria != NULL) {

        for( int i = 0; i <= cont; i++){
            if( memoria[i][0] == x  && memoria[i][1] == y ){
                return 0;
            }
        }

        if( x >= 0 && x < TAMA ){
            if( y >= 0 && y < TAMA ){
                return 1;
            }
        }
        return 0;
    }


    return 0;

}

//funcao para posicionar os navios no tabuleiro.
void posicionarNavios(char tabuleiro[TAMA][TAMA], int jogador, int automatico){

    if (automatico) {
        colocarNaviosAleatorios(tabuleiro);
        printf("Navios do jogador %d foram posicionados automaticamente.\n", jogador);
        mostrarTabuleiro(tabuleiro, 1);
        return;
    }

    int i = 0; // controla o while
    int tamNavio = 2; // tamanho do menor navio
    char d; // direcao do navio

    printf("Jogador %d, posicione seus %d navios:\n", jogador, NAVIOS);
    mostrarTabuleiro(tabuleiro, 1);

    while (i < NAVIOS) {
        int xi = 0, yi = 0; // linha e coluna inicial do navio
        int multiplicadorX = 0, multiplicadorY = 0; // vao fazer x e y variarem

        printf("\n");
        printf("Navio %i, ocupa %i posições.\n", i+1, tamNavio);

        printf("Escolha o número da linha(0 a 7): ");
        scanf("%d", &xi);

        printf("Escolha o número da coluna(0 a 7): ");
        scanf("%d", &yi);

        printf("Digite a direção do navio (W, A, S, D): ");
        scanf(" %c", &d);
        printf("\n");

        if( checaPosicaoValida(xi, yi, tabuleiro, NULL, tamNavio) == 1) { // checa se as posicoes sao validas

            if( checkDirecao(d, &multiplicadorX, &multiplicadorY, xi, yi, tamNavio) == 1 ){ //altera o multiplicador

                if( preencherMatriz(xi, multiplicadorX, yi, multiplicadorY, tamNavio, tabuleiro) == 1 ){ // preenche o tabuleiro

                    mostrarTabuleiro(tabuleiro, 1);
                    tamNavio++; // aumenta o tamanho do navio
                    i++;

                } else {
                printf("Posição inválida ou ocupada, tente novamente1\n");
                mostrarTabuleiro(tabuleiro, 1);
                }
            } else {
                printf("Posição inválida ou ocupada, tente novamente2\n");
                mostrarTabuleiro(tabuleiro, 1);
            }
        } else {
            printf("Posição inválida ou ocupada, tente novamente1\n");
            mostrarTabuleiro(tabuleiro, 1);
        }

    }

}

//função para atacar ele vai pecorrer o tabuleiro e verificar onde tem um Navio "N" se tizer marca X e retorna 1 indicando que o ataque deu certo;
int atacar(char tabuleiro[TAMA][TAMA], int x , int y){
    if (tabuleiro[x][y]== 'N'){
        tabuleiro[x][y] = 'X';
        return 1;
    } else if (tabuleiro[x][y] == '-'){
        tabuleiro[x][y] = 'O';
    }
    return 0;
}

int logicaCPU(char tabuleiro[TAMA][TAMA]){
    int x, y;

    // ataca aleatoriamente
    if( contAcertos == 0 ){ // só vai entrar aqui se ainda não tiveram acertos ou se houve erros demais

        //gera posicoes aleatorias ate achar uma valida
        do {
            x = rand() % TAMA;
            y = rand() % TAMA;
        } while ( checaPosicaoValida(x, y, NULL, memoria, cont) != 1 );

        //armazena essas posições
        memoria[cont][0] = x;
        memoria[cont][1] = y;
        printf("%i, %i\n", memoria[cont][0], memoria[cont][1]);

        // registra se o ataque foi acerto ou erro
        if( atacar(tabuleiro, x, y ) == 1 ){
            acertos[contAcertos][0] = x;
            acertos[contAcertos][1] = y;
            
            // atualiza contadores
            contAcertos++;
            cont++;
            return 1;

        } else {
            erros[contErros][0] = x;
            erros[contErros][1] = y;

            // atualiza contadores
            contErros++;
            cont++;
            return 0;
        }


    }  else {

        // ataca baseado no  ultimo acerto
        // gera posicoes e direcoes diferentes até encontrar uma valida
        do {
            // determina como base o ultimo acerto que houve
            x = acertos[contAcertos-1][0];
            y = acertos[contAcertos-1][1];
            
            // determina a direção em que a CPU vai continuar atacando
            int d = rand() % 4; // sorteia uma direção aleatória

            switch (d)
            {
                case 1: // para baixo
                x = x + 1; // x aumenta, y se mantem constante
                break;

                case 2: // para cima
                x = x - 1; // x diminui, y se mantem constante
                break;

                case 3: // para a direita
                y = y + 1; // y aumenta, x se mantem constante
                break;

                case 4: // para a direita
                y = y - 1; // y diminui, x se mantem constante
                break;

            }

            // quebra o while se tiver muitos chutes invalidos
            chutes++;
            if( chutes >=10 ){
                break;
            }

        } while ( checaPosicaoValida(x, y, NULL, memoria, cont) != 1) ;

            // se houver muitos chutes invalidos, escolhe um x e y aleatorio
            if( chutes >= 10 || errou >= 4){
                chutes = 0; // zera a variavel para o proximo uso
                errou = 0;

                // gera posicoes aleatorias ate encontrar uma valida
                do {
                    x = rand() % TAMA;
                    y = rand() % TAMA;
                } while(checaPosicaoValida(x, y, NULL, memoria, cont) != 1);

            }

            // grava as posicoes do ataque
            memoria[cont][0] = x;
            memoria[cont][1] = y;
            printf("%i, %i\n", memoria[cont][0], memoria[cont][1]);

            if( atacar(tabuleiro, x, y) == 1 ){
                acertos[contAcertos][0] = x;
                acertos[contAcertos][1] = y;
                
                errou = 0; //zera variavel para reutilizar
                // atualiza os contadores
                contAcertos++;
                cont++;
                return 1;
            } else {
                erros[contErros][0] = x;
                erros[contErros][1] = y;

                errou++;
                
                // atualiza os contadores
                contErros++;
                cont++;
                return 0;
            }
        }

}

//função para contar quantos Navios restão no tabuleiro;
int contNavios(char tabuleiro[TAMA][TAMA]){
    int contador = 0;
    for (int i = 0; i < TAMA; i++){
        for (int j = 0; j < TAMA; j++){
            if (tabuleiro[i][j] == 'N'){
                contador ++;
            }
        }
    }
    return contador;
}

//função menu;
int menu(){

    char tabuleiro1[TAMA][TAMA];
    char tabuleiro2[TAMA][TAMA];

    int modo, dificuldade;
    // modo = 1 --> jogador vs jogador
    // modo = 2 --> jogador vs computador

    int automatico1 = 0, automatico2 = 0;
    int jogador = 1;
    int fim = 0;
    int x, y;

    // usado apenas para o PC lembrar os acertos
    //int memoria[2] = {-1, -1};

    // Inicializa a semente com o tempo atual para que o rand() funcione sempre trocando os números aleatórios sem repetir o mesmo padrão.
    srand(time(NULL));

    criarTabuleiro(tabuleiro1); // tabuleiro do jogador 1
    criarTabuleiro(tabuleiro2); // tabuleiro do jogador 2 ou CPU
    limparTerminal();

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

    printf("Jogador 1 deseja posicionar os navios automaticamente? (1 = sim, 0 = nao): ");
    scanf("%d", &automatico1);

    if (modo == 1) {
        printf("Jogador 2 deseja posicionar os navios automaticamente? (1 = sim, 0 = nao): ");
        scanf("%d", &automatico2);
    }

    //chamar a função para e criar os navios
    posicionarNavios(tabuleiro1, 1, automatico1);
    if (modo == 2){
        colocarNaviosAleatorios(tabuleiro2);
    } else {
        posicionarNavios(tabuleiro2, 2, automatico2);
    }

    // continua enquanto fim for diferente de 1
    while (!fim){

        printf("\n--- Jogador %d ---\n", jogador);
        if (jogador == 1 || modo == 1) {
            //se o jogador for o 1 e o modo 1 ele mostra tabuleiro do jogador 2 ou 1 e assim do 1 ou 2, o zero no final e para dizer a funcao esconder os navios.
            mostrarTabuleiro(jogador == 1 ? tabuleiro2 : tabuleiro1, 0);
        }

        // se o modo == 2 e for a vez do jogador 2, é a vez da CPU jogar
        if (modo == 2 && jogador == 2){

            if( logicaCPU(tabuleiro1) == 1 ){
                printf("BOOM! Seu navio foi acertado!\n");
            } else {
                printf("Agua! Seus navios estão a salvo!\n");
            }

            // conta quantos navios tem para ver se o jogo acabou
            if ( contNavios(tabuleiro1) == 0 ){
                printf("\nComputador venceu\n");
                fim = 1;
            } else {
                mostrarTabuleiro(tabuleiro1, 1);
            }

        } else { // se não for modo 2, pede as coordenadas para o ataque

            printf("Digite linha e coluna para atacar: ");
            scanf("%d %d", &x, &y);

            //verifica se for menor que zero ou maior que o tamanho da matriz ele retorna erro;
            if (x < 0 || x >= TAMA || y < 0 || y >= TAMA){
                printf("Cordenadas Invalidas.\n");
                continue;
            }

            //verifica a vez de jogar se for do jogador 1 ele entrar aqui;
            if (jogador == 1){

                //verifica se no tabuleiro do jogador 2, voce ja atacou o mar ou acertou um navio;
                if (tabuleiro2[x][y] == 'X' || tabuleiro2[x][y] == 'O'){
                    printf("Posicao ja atacada.\n");
                    continue;
                }

                //aqui chama a funcao atacar, a funcao ataca no tabuleiro 2 na posição dita pelo usuario x e y.
                if (atacar(tabuleiro2, x ,y)){
                   printf("BOOM! Voce acertou!\n");
                }else{
                    printf("Agua! Voce errou...\n");
                }

                if (contNavios(tabuleiro2) == 0){
                    printf("\nJogador 1 venceu\n");
                    fim = 1;
                }

            //jogador 2:
            } else {
                if (tabuleiro1[x][y] == 'X' || tabuleiro1[x][y] == 'O'){
                    printf("Posicao ja atacada.\n");
                    continue;
                }
                if (atacar(tabuleiro1, x ,y)){
                    printf("BOOM! Voce acertou!\n");
                }else{
                    printf("Agua! Voce errou...\n");
                }
               if (contNavios(tabuleiro1) == 0){
                    printf("\nJogador 2 venceu\n");
                    fim = 1;
                }
            }
        }

        //se o jogo não acabou então
        if (!fim) {
            //isso eh um if e else que garante que o jogador sempre vai alternar enquanto o jogo não terminar
            jogador = (jogador == 1) ? 2 : 1;
        }
    }

    // pergunta se o jogador quer jogar de novo, retorna o resultado para main
    int jogarNovamente;
    printf("Jogar novamente? (1 = sim, 0 = nao): ");
    scanf("%d", &jogarNovamente);
    return jogarNovamente;
}

void reiniciaVars(){
    cont = 0;
    contAcertos = 0;
    contErros = 0;
}

int main(){
    // loop para jogar novamente limpando o terminal com a o outra função se a resposta for sim (1);
    while ( menu() == 1 ) {
        limparTerminal();
        reiniciaVars();
    }
    printf("Obrigado por jogar!\n");

    return 0;
}
