#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <future>
#include <thread>

void PrintIntro(){
    std::cout << "**-------COMO JOGAR-------**\n"
    "\nO objetivo do jogo e simples\n"
    "A cada rodada, voce sera oferecido 3 objetos (threads), cada um com uma quantia diferente de pureza\n"
    "Seu objetivo e simplesmente manter seu medidor de pureza acima de 0%. Se ele acabar, GAME OVER\n"
    "A cada objeto apresentado, voce tera 3 escolhas:\n"
    "Colher (Fornecer ao medidor)\n"
    "Consumir (Adicionar aos seus pontos)\n"
    "Ou descartar\n"
    "Lembre-se que o medidor pode ir ate 200% mais caira com o dobro de velocidade ate alcancar 100% novamente\n"
    "Nao ofereca objetos menos puros que o medidor ou ele sofrera uma queda\n"
    "E quanto mais puro o objeto for, mais pontos ele o fornecera\n";
    system("pause");
}

int ObjectGen(){
    int pureza = rand()%100;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return pureza;
}

void PlayGame(int dificuldade){
    int valores[3];
    int pontos = 0;
    int medidor = 75;
    int input1, input2;

    std::cout << "Gerando Objetos...";
    for(int i = 0; i<3; i++){
        auto future = std::async(ObjectGen);
        valores[i] = future.get();
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));

    while(medidor>0){
        system("cls");        
        std::cout << "Medidor: " << medidor << "%\n"
        "Pontuacao: " << pontos << "\n"
        "\nObjeto 1: " << valores[0] << "%\n"
        "\nObjeto 2: " << valores[1] << "%\n"
        "\nObjeto 3: " << valores[2] << "%\n\n"
        "Qual objeto quer selecionar?\n";
        std::cin >> input1;

        while(input1!=1 && input1!=2 && input1!=3){
            std::cout << "\nEntrada invalida, por favor reconfirme sua entrada\n";
            std::cin >> input1;
        }

        std::cout << "\nQual acao deseja efetuar?\n"
        "1. Colher \n2. Consumir \n3. Descartar \n0. Voltar\n";

        std::cin >> input2;

        while(input2!=1 && input2!=2 && input2!=3 && input2!=0){
            std::cout << "\nEntrada invalida, por favor reconfirme sua entrada\n";
            std::cin >> input1;
        }

        switch(input2){
            case 1:
                medidor += valores[input1-1];
                if(medidor>200){
                    medidor = 200;
                }
                if(valores[input1-1]>50){
                    dificuldade -= 2;
                }
                break;
            case 2:
                pontos += valores[input1-1];
                break;
            case 3:
                break;
            case 0:
                continue;
        }

        if(medidor>100){
            medidor -= dificuldade*2;
        }else{
            medidor -= dificuldade;
        }

        dificuldade++;
        auto future = std::async(ObjectGen);
        valores[input1-1] = future.get();
    }
}

int main()
{
    srand(time(NULL));
    PrintIntro();

    PlayGame(3);
    std::cout << "GAME OVER!";
    system("pause");
    return 0;
}