#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

int erros = 0;
bool continua = true;

/*Funcao que apresenta o menu do jogo*/
char menu(){
	printf("Bem vindo ao jogo da forca");
	printf("\nEscolha uma opcao: \n");

	printf ("1: Iniciar o jogo\n"
			"2: Sair\n");

	return getch();

}

bool repetiu(char *cadeia, char palpite){
    for(int i = 0; i < strlen(cadeia); i++){
        if(cadeia[i] == palpite){
            return true;
        }
    }
    return false;
}

void dica(int ordem){
    printf("Dica: ");
    switch(ordem){
        case 1: printf("Animal com tromba\n"); break;
        case 2: printf("Animal com corcovas\n"); break;
        case 3: printf("Ave que fala\n"); break;
        case 4: printf("Sem meia fede\n"); break;
        case 5: printf("Sai som ou letra\n"); break;
        case 6: printf("Corta e gira"); break;
        case 7: printf("Assiste ou toca") ;break;
        case 8: printf("Melhor que banheira") ;break;
        case 9: printf("Evita o chiado") ;break;
        case 10:printf("Voce tem entre as pernas") ;break;
        case 11:printf("Eh melhor nao pular") ;break;
        case 12:printf("No predio tem") ;break;
    }
}

bool perdeu(){
   return erros > 5 ? true : false;
}

void chute(char *mostrador, char *keyWord, int ordem){
    int acerto;
    int i;
    //Conta o numero de letras chutado
    int lettersCount = 0;
    char usedLetters[25] = "\0";
    i = 0;

    while(mostrador[i] != '\0'){
        mostrador[i] = '_';
        i++;
    }

    aq:
    system("cls");
    puts(mostrador);

    dica(ordem);
    printf("Chute uma letra: ");
    char palpite;

    acerto = 0;
    outraLetra:
    setbuf(stdin, NULL);
    palpite = tolower(getchar());


    if(!repetiu(usedLetters, palpite) && isalpha(palpite)){
        usedLetters[lettersCount] = palpite;
        lettersCount++;

        //Analisa se a letra chutada pertence a keyWord
        for(int count = 0; keyWord[count] != '\0'; count++){
            if(palpite == keyWord[count]){
                mostrador[count] = palpite;
                acerto++;
            }
        }
        //Se a letra pertence a keyWord, a pessoa recebe 1 acerto
        if(acerto == 0){
            erros++;
        }else{
            acerto = 0;
        }
    }else{
        system("cls");
        printf("Voce ja usou essa letra\n");
        puts(mostrador);
        dica(ordem);
        printf("\nChute outra letra: ");
        goto outraLetra;
    }



   //Contador de letras ausentes
    int contador = 0;
    if(!perdeu()){
    for(int j = 0; j < i; j++){
        if(mostrador[j] == '_'){
            contador++;
            printf("Chute outra letra: ");
            goto aq;
        }
    }

    }else{
        printf("Voce perdeu!");
        return;
    }

    //Se o numero de letras ocultas acabar, o jogador ganhou
    if(contador == 0){
        printf("Voce acertou! A palavra eh %s!\n", mostrador);
    }

    char quer;
    opInvalida:
    printf("\nContinuar jogando?? s/n");
    quer = tolower(getch());
    if(quer == 'n'){
        continua = false;
    }else if(quer == 's'){
        continua = true;
    }else{
        printf("\nDigite uma opcao valida: ");
        goto opInvalida;
    }


}

void jogo(){
    char palavras[12][15] = {"elefante", "camelo", "papagaio",
                            "sapato", "teclado", "canivete",
                            "tela", "chuveiro", "antena",
                            "joelhos", "fogueira", "apartamento"};
    int i = 0;
    while(i < 12){
        int count = 0;
        while(palavras[i][count] != '\0'){
            count++;
        }


        char mostrador[count];
        strcpy(mostrador, palavras[i]);
        chute(mostrador, palavras[i], i+1);

        if(perdeu() || !continua){
            break;
        }

        i++;

    }


}

int main(){
    repete:
	switch(menu()){
        case '1': jogo(); break;
        case '2': return 0;
        default: printf("Opcao invalida!\n\n"); goto repete;
	}

	return 0;
}

