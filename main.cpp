#include <iostream>
#include <ctime>
#include <string>


using namespace std;

void menu();

void clean(){
    system("CLS");
}

void iniciaTab(char tabuleiro[10][10], char mascara[10][10]){

    int linha, coluna;
    for (linha = 0; linha < 10; linha++){
        for(coluna =0; coluna < 10; coluna++){
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

void marcacao(){
    int cont;
    for(cont = 0; cont <10; cont++){
        if(cont == 0){
            cout << "     ";
        }
        cout << cont << " ";
    }
    cout <<"\n";

    for(cont = 0; cont <10; cont++){
        if(cont == 0){
            cout << "     ";
        }
        cout << "| ";
    }
    cout <<"\n";
}

void imprimeTab(char tabuleiro[10][10], char mascara[10][10], bool gabarito){

    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0};
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0};
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0};

    int linha, coluna;
    for (linha = 0; linha < 10; linha++){
        cout << linha << " - ";
        for(coluna = 0; coluna < 10; coluna++){
            switch (mascara[linha][coluna]) {
            case 'A':
                cout << blue << " " << mascara[linha][coluna] << normal;
                break;
            case 'P':
                cout << green << " " << mascara[linha][coluna] << normal;
                break;
            default:
                cout << " " << mascara[linha][coluna];
                break;
            }
        }
        cout << endl;
    }

    if(gabarito == true){
        for (linha = 0; linha < 10; linha++){
            for(coluna = 0; coluna < 10 ; coluna++){
                cout << " " << tabuleiro[linha][coluna];
            }
            cout << endl;
        }
    }
}


void barcosTab(char tabuleiro[10][10]){
    int qtde = 10;
    int qtdeBarcos = 0;

    while (qtdeBarcos < qtde){

        int linBarco = rand() % 10;
        int colBarco = rand () % 10;

        if (tabuleiro[linBarco][colBarco] == 'A'){

            tabuleiro[linBarco][colBarco] = 'P';
            qtdeBarcos++;
        }
    }
}

void verifPontuacao(char tabuleiro[10][10], int linhaDig, int colunaDig, int *pontos, string *mensagem){
    switch (tabuleiro[linhaDig][colunaDig]) {
    case 'P':
        *pontos +=10;
        *mensagem = "Você acertou um barco pequeno";
        break;
    case 'A':
        *mensagem = "Você acertou a agua";
        break;
    }
}

void jogo(string nickname){

    char tabuleiro[10][10], mascara[10][10];
    int linhaDig, colunaDig;
    int pontos = 0;
    int tentativas = 0, maxTent = 5;
    int opcao; ///opcao pós jogo

    string mensagem = "Bem vindo a Batalha Naval";

    iniciaTab(tabuleiro,mascara);
    barcosTab(tabuleiro);


    while (tentativas < maxTent){
        clean ();

        marcacao ();

        imprimeTab (tabuleiro, mascara, false);

        cout << "\n Pontos:  " << pontos << "  Tentativas: " << maxTent - tentativas << endl;

        cout << mensagem << endl;

        linhaDig = -1;
        colunaDig = -1;

        while ((linhaDig < 0 || colunaDig < 0 ) || (linhaDig > 9 || colunaDig >9)) {
            cout << nickname << ", Digite uma linha: ";
            cin >> linhaDig;
            cout << nickname << ", Digite uma coluna: ";
            cin >> colunaDig;
        }

        verifPontuacao (tabuleiro, linhaDig, colunaDig, &pontos, &mensagem);

        mascara[linhaDig][colunaDig] = tabuleiro[linhaDig][colunaDig];

        tentativas++;

        }

    cout << "Fim de Jogo, o que deseja fazer ?"<< endl;
    cout << "\n1- Jogar novamente \n2- Ir para o menu \n3- Sair" << endl;
    cin >> opcao;

    switch (opcao) {
    case 1:
        jogo(nickname);
        break;
    case 2:
        menu ();
        break;
    }
}


void menu(){
    int opcao = 0;
    string nickname;

    while (opcao < 1 || opcao > 3){
        clean();

        cout << "Bem vindo ao Jogo" << endl;
        cout << "1 - Jogar \n2- Sobre \n3- Sair" << endl;
        cout << "Escolha uma opção e tecle ENTER: " << endl;

        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Qual seu nickname? ";
            cin >> nickname;
            jogo(nickname);
            break;
        case 2:
            cout << "Jogo de Batalha Naval feito em C++" << endl;
            break;
        case 3:
            cout << "Até mais!! \n\n Saindo........" << endl;
            break;
        }
    }
}

int main(){
    srand ( (unsigned)time(NULL) );
    menu();
    return 0;
}
