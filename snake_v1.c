/*
BCC - UNESP - 2020
Arissa Yoshida & Gabriel Henrique Garcia
Snake Game Versão 1.0.1
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define L 20
#define C 30

#define SNAKE_COLOR 0xf
#define BORDER_COLOR 0xc
#define GRID_COLOR 0x8
#define FRUIT_COLOR 0xe

//--------- INTERFACE ----------//
void gotoxy(int,int);
void cursor(int);
void titulo (int,int);
void caixa_s (int,int,int,int);

int setcolor(char);
//------------------------------//

//Sempre que reiniciar essa função atualiza
void inicio(int *c_head,int *c_tail,int *c_x,int *c_y,int *c_posi,int *tecla_anterior,int campo[L][C]){
    *tecla_anterior = 'd';
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

void mapa(int *c_head,int *c_tail,int *c_x,int *c_y,int *c_posi,int campo[L][C],int *jogo,int *ponto){
    int i,j;
    for(i=0;i<=C+1;i++){
    	setcolor(BORDER_COLOR);
        printf("%c",220);
    }printf("\n");
    for(i=0;i<L;i++){
        printf("%c",219);
        for(j=0;j<C;j++){
            if(campo[i][j]==0){
           		setcolor(GRID_COLOR);
                printf(" ");
            }else if(campo[i][j]>0 && *c_head!=campo[i][j]){
                setcolor(SNAKE_COLOR);
                printf("%c",177);
            }else if(*c_head==campo[i][j]){
              	setcolor(SNAKE_COLOR);
                printf("%c",178);
            }else if(campo[i][j]==-10){
              	setcolor(FRUIT_COLOR);
                printf("%c",227);
            }
        }
        setcolor(BORDER_COLOR);
        printf("%c\n",219);
    }
    for(i=0;i<=C+1;i++){
        printf("%c",223);
    }
    printf("\n\nPontos:%d",*ponto);
   
	setcolor(0xf);
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

void cobrinha(int *c_head,int *c_tail,int *c_x,int *c_y,int *c_posi,int *tecla_anterior,int campo[L][C],int *p_x,int *p_y,int *jogo,int *ponto){
    int tecla = Tecla_Pressionada();
    int x,y;
    x =  *c_x;
    y = *c_y;
    int head = *c_head;
    tecla = tolower(tecla);
    if(tecla=='p'){
    	pausa();
	}
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
    if(campo[x][y]!=0 && campo[x][y]!=-10){
	*jogo=1;
	}
    head++;
    campo[x][y] = head;
    *c_head =head;
    *c_x = x;
    *c_y = y;
    *tecla_anterior = tecla;
     int i,j; 
     //Funcao que remove o c_tail sempre que a cobrinha anda um passo, uma parte de tras dela "some"
   for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            if(campo[i][j] == *c_tail){
                campo[i][j]=0;
            }
        }
    }
    
   
    int tail = *c_tail;
    //Se a posição com o valor de *c_head estiver em cima da posição da fruta, ela diminui um de *c_tail.
	int pontos = *ponto;
	if(x == *p_x && y == *p_y){
    	tail-=2;
    	pontos+=10;
	}
     *ponto = pontos;
    tail ++;
    *c_tail = tail;
      
    
}


void adcionar_ponto(int campo[L][C],int *p_x,int *p_y){
    int rand_x;
    int rand_y;
    srand(time(NULL));
    do{
        rand_x = rand()%(L-1) + 1;
        rand_y = rand()%(C-1) + 1;
    }while(campo[rand_x][rand_y]!=0);
    campo[rand_x][rand_y] = -10;
	*p_x = rand_x;
	*p_y = rand_y;
}
void pausa(){
	int tecla=0;
	while(tecla!='p'){
		tecla = Tecla_Pressionada();
	}
}
    
main(){
	cursor(0);
	titulo(38,7);
    int c_head,c_tail;
    int c_x,c_y,c_posi;
    int tecla_anterior;
    int campo[L+1][C+1];//Matriz com todas as posições
    int i,j;
    int okay=1;
    int p_x,p_y;//Localização da "fruta"
    int jogo =0;
    int ponto;
	inicio(&c_head,&c_tail,&c_x,&c_y,&c_posi,&tecla_anterior,campo);
    ponto =0;
	while(jogo==0){
        okay =0;
        mapa(&c_head,&c_tail,&c_x,&c_y,&c_posi,campo,&jogo,&ponto);
       	Atualiza_Tela(); 
        cobrinha(&c_head,&c_tail,&c_x,&c_y,&c_posi,&tecla_anterior,campo,&p_x,&p_y,&jogo,&ponto);
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
            adcionar_ponto(campo,&p_x,&p_y);
        }
        Sleep(50);
	}	
	system("pause");
}

void titulo(int x, int y) {
	setcolor(0xc);
	caixa_s(x,x+28,y,y+9);
	setcolor(0xf);
	gotoxy(x+2,y+1); printf("%c%c%c%c %c   %c %c%c%c%c %c  %c %c%c%c%c",220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
	gotoxy(x+2,y+2); printf("%c%c%c%c %c%c%c %c %c%c%c%c %c%c%c  %c%c%c%c",219,220,220,220,219,223,220,219,219,220,220,219,219,220,223,219,220,220,220);
	gotoxy(x+2,y+3); printf("%c%c%c%c %c  %c%c %c  %c %c %c%c %c%c%c%c",220,220,220,219,219,223,219,219,219,219,223,220,219,220,220,220);
	setcolor(0x8);
	gotoxy(x+12,y+4); printf("1.0.1");
	
	gotoxy(x+6,y+6); 
	setcolor(0xc); printf("By: ");
	setcolor(0xf); printf("Toki & Zastim");
	
	gotoxy(x+10,y+8); printf("(W A S D)");
	gotoxy(0,0);
}

void gotoxy(int x, int y) {
 	COORD pos = {x, y};
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


void cursor (int x) { // mostra ou não o cursor do prompt
	switch (x) {
		case 0: {
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}

void caixa_s (int xmin, int xmax, int ymin, int ymax) {
	int i;
	gotoxy(xmin, ymin); printf("%c", 218); for (i = xmin + 1 ; i <= xmax - 1 ; i++) { gotoxy(i, ymin); printf("%c",196); }
	gotoxy(xmin, ymax); printf("%c", 192); for (i = xmin + 1 ; i <= xmax - 1 ; i++) { gotoxy(i, ymax); printf("%c",196); }
	gotoxy(xmax, ymin); printf("%c", 191); for (i = ymin + 1 ; i <= ymax - 1 ; i++) { gotoxy(xmin, i); printf("%c",179); }
	gotoxy(xmax, ymax); printf("%c", 217); for (i = ymin + 1 ; i <= ymax - 1 ; i++) { gotoxy(xmax, i); printf("%c",179); }
}

int setcolor(char color)
{
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleTextAttribute(h, color);
}
