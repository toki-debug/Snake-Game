/*
BCC - UNESP - 2020
Arissa Yoshida & Gabriel Henrique Garcia
Snake Game Versão 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define L 20
#define C 30

//Sempre que reiniciar essa função atualiza
void inicio(int *c_head,int *c_tail,int *c_x,int *c_y,int *c_posi,int *tecla_anterior,int campo[L][C]){
    *tecla_anterior = 'a';
	int i,j;
    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            //Zerando o campo por onde o jogo irá acontecer
            campo[i][j]=0;
        }
    }
    //posição incial
    *c_x = 15;
    *c_y = 10;
    //Configuração incial de tamanho da cobra
    *c_head =5;
    *c_tail =1;

 // Variavel para posicionar os valores da cobra na matriz
	int num = *c_y;
    for(i=0;i<*c_head;i++){
       num++;
        campo[*c_x][num-*c_head] = i+1; //Fazendo isso, a cobrinha irá iniciar na posição horizontal
    }

}

void mapa(int *c_head,int *c_tail,int *c_x,int *c_y,int *c_posi,int campo[L][C]){
    int i,j;
    for(i=0;i<=C+1;i++){
        printf("%c",220);
    }printf("\n");
    for(i=0;i<L;i++){
        printf("%c",219);
        for(j=0;j<C;j++){
            if(campo[i][j]==0){
           
                printf("-");
            }else if(campo[i][j]>0 && *c_head!=campo[i][j]){
                
                printf("%c",177);
            }else if(*c_head==campo[i][j]){
              
                printf("%c",178);
            }else if(campo[i][j]==-10){
              
                printf("%c",254);
            }
        }
        printf("%c\n",219);
    }
    for(i=0;i<=C+1;i++){
        printf("%c",223);
    }
   

}

void Atualiza_Tela(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);
}


//Função para pegar os valores de teclado
int Tecla_Pressionada(){
    if(kbhit()){ //A função kbhit() pega o valor da tecla pressionada a todo momento
        return getch(); 
        //A função getch() pega o valor da ultima tecla pressionada quando a função Tecla_Pressionada() é chamada
    }else{
        return -1;
    }
}

void cobrinha(int *c_head,int *c_tail,int *c_x,int *c_y,int *c_posi,int *tecla_anterior,int campo[L][C]){
    int tecla = Tecla_Pressionada();
    int x,y;
    x =  *c_x;
    y = *c_y;
    int head = *c_head;
    tecla = tolower(tecla);
    
    if(tecla!='d'&&tecla!='w'&&tecla!='a'&&tecla!='s'){
        tecla = *tecla_anterior;
    }
    //printf("%d",tecla);
    //Retorna a tecla como lower case(Garantindo execução tanto para 'a' quanto para 'A') 
    if(tecla == 'd'){
        //Leste
        y++;
        if(y==C){
            y = 0;
        }
    }else if(tecla =='a'){
        //Oeste
        y--;
        if(y==-1){
            y = C-1;
        }
    }else if(tecla =='w'){
        //Norte
       x--;
       if(x==-1){
            x = L-1;
        }
    }else if(tecla=='s'){
        //Sul
        x++;
        if(x==L){
            x = 0;
        }
    }
    head++;
    campo[x][y] = head;
    *c_head =head;
    *c_x = x;
    *c_y = y;
    *tecla_anterior = tecla;
    int i,j;   
    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            if(campo[i][j] == *c_tail){
                campo[i][j]=0;
            }
        }
    }
    int tail = *c_tail;
    tail ++;
    *c_tail = tail;
}

void adcionar_ponto(int campo[L][C]){
    int rand_x;
    int rand_y;
    srand(time(NULL));
    do{
        rand_x = rand()%L + 1;
        rand_y = rand()%C + 1;
    }while(campo[rand_x][rand_y]!=0);
    campo[rand_x][rand_y] = -10;

}
    

main(){
    int c_head,c_tail;
    int c_x,c_y,c_posi;
    int tecla_anterior;
    int campo[L+1][C+1];//Matriz com todas as posições
    int i,j;
    int okay=1;
    inicio(&c_head,&c_tail,&c_x,&c_y,&c_posi,&tecla_anterior,campo);
	while(1){
        okay =0;
        mapa(&c_head,&c_tail,&c_x,&c_y,&c_posi,campo);
       	Atualiza_Tela(); 
        cobrinha(&c_head,&c_tail,&c_x,&c_y,&c_posi,&tecla_anterior,campo);
        for(i=0;i<L;i++){
            for(j=0;j<C;j++){
                if(campo[i][j]==-10){
                    okay = 1;
                    i=L;
                    break;
                }
            }
        }
        if(okay!=1){
            adcionar_ponto(campo);
        }
        Sleep(100);
	}	
	
   
}
