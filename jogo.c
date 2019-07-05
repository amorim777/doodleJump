#include <stdint.h>

#include <stdlib.h>
#include "driverlib/systick.h"

#include "jogo.h"
#include "Nokia5110.h"
#include "bitmaps.h"
#include "botoes.h"
#include <stdbool.h>

static int i = 0,k=0,j=0,z=0;

//botoes
static int estado_botao, estado_anterior = 1;

//DOODLE
static int x_doodle = 63 - 21 - 2, y_doodle = 37;
static int SCORE = 0,bg=0,MORTE=0;


#define ESQUERDA 34
#define MEIO 17
#define DIREITA 0

//CENARIO
//posicao array par X e impar Y
static int x_y_barra[10] = {6, ESQUERDA,
                            23, MEIO,
                            40, DIREITA,
                            57, MEIO,
                            74, ESQUERDA
                            };

static int posX_barra=8;// no array  x_barra valor entre 0 e 8 SEMPRE PAR
static int tempo_sys = 37000, ju =0;

void ope(void){}  //DEBUG

void loading(int qtd_pulos){
    for(k = 0; k < qtd_pulos; k++){
        for(i=0; i < 360; i++){
            Nokia5110_PrintBMP2(42,0,pula_doodle_Bitmap,31,48);
            Nokia5110_PrintBMP2(7+((int)(i/30)*2),17,open_doodle_Bitmap,13,11);
            Nokia5110_DisplayBuffer();
            Nokia5110_ClearBuffer();
        }
        for(i=360; i > 0; i--){
                Nokia5110_PrintBMP2(42,0,pula_doodle_Bitmap,31,48);
                Nokia5110_PrintBMP2(7+((int)(i/30)*2),17,open_doodle_Bitmap,13,11);
                Nokia5110_DisplayBuffer();
                Nokia5110_ClearBuffer();
        }
    }

}


int menu(void){

    estado_botao = start_buttons();

    if(estado_botao == 3){
        if(estado_anterior == 1){
            return 0; //play no jogo
        }
     }

    if(estado_anterior == 1){
        pisca_play();
    }else if(estado_anterior == 2){
        pisca_help();
    }else if(estado_anterior == 3){
        start_help(); //play no help
    }


    if(estado_botao != 0){
        estado_anterior = estado_botao;
    }

    return 1;

}

void pisca_play(void){
    if(i > 100){
        Nokia5110_DrawFullImage(home_Bitmap);
        i++;
        if(i > 200){
            i = 0;
        }
    }else if(i <= 100){
        Nokia5110_DrawFullImage(home2_Bitmap);
        i++;
    }
}

void pisca_help(void){
    if(i > 100){
        Nokia5110_DrawFullImage(home_Bitmap);
        i++;
        if(i > 200){
            i = 0;
        }
    }else if(i <= 100){
        Nokia5110_DrawFullImage(home3_Bitmap);
        i++;
    }
}

void start_help(void){

    Nokia5110_DrawFullImage(help_Bitmap);


}


void mov_esquerda(void){
    ju = 1;
    if(y_doodle < 37){
        y_doodle+=3;
    }
}

void mov_direita(void){
    ju = 0;
    if(y_doodle > 2){
        y_doodle-=3;
    }
}

void trataBotoes(void){
    estado_botao = start_buttons();

    if(estado_botao == 1 && j > 7){//esquerda
        mov_esquerda();
        j=0;
    }else if(estado_botao == 2 && j >7){//direita
        mov_direita();
        j=0;
    }else if(estado_botao == 2 || estado_botao == 1){
        j++;
    }
    if(estado_botao == 3){
        //PAUSAR O JOGO
    }

    if(estado_botao != 0){
            estado_anterior = estado_botao;
    }
}

int verificaCHAO(void){
    static int posX_prox_barra = 0;
    if(posX_barra != 0){
        posX_prox_barra = posX_barra - 2;
    }else{
        posX_prox_barra = 8;
    }


    if( (x_doodle+14) >= x_y_barra[posX_prox_barra] && (x_doodle+14) <= (x_y_barra[posX_prox_barra] + 2) ){//se alcancou altura X da proxima barra
        if(x_y_barra[posX_prox_barra+1] == ESQUERDA && y_doodle >= ESQUERDA-6){//verificar posicao Y //6 tolerancia metade do doodle na barra
            return 1;
        }else if(x_y_barra[posX_prox_barra+1] == MEIO && y_doodle >= MEIO-6 && y_doodle <= MEIO+6){//verificar posicao Y
            return 1;
        }else if(x_y_barra[posX_prox_barra+1] == DIREITA && y_doodle <= 6){//verificar posicao Y
            return 1;
        }else{
            //return 0;
        }

    }
    if((x_doodle+14) >= x_y_barra[posX_barra] && (x_doodle+14) <= (x_y_barra[posX_barra] + 2)){
        if(x_y_barra[posX_barra+1] == ESQUERDA && y_doodle >= ESQUERDA-6){//verificar posicao Y
            return 1;
        }else if(x_y_barra[posX_barra+1] == MEIO && y_doodle >= MEIO-6 && y_doodle <= MEIO+6){//verificar posicao Y
            return 1;
        }else if(x_y_barra[posX_barra+1] == DIREITA && y_doodle <= 6){//verificar posicao Y
            return 1;
        }else{
            //return 0;
        }


    }
    return 0;
}


void abaixa(void){
    static int randomico = 0;

    if(x_doodle < 57){//alcancou a proxima barra entao ABAIXA o cenario e o doodle

        SCORE++;
        for(z=0; z<10; z+=2){
            if(x_y_barra[z] != 74){
                x_y_barra[z] += 17;
            }else{
                x_y_barra[z] = 6;
            }
        }
        x_doodle += 17;



        //RANDOMICO DA POSICAO HORIZONTAL (Y)
        srand(SysTickValueGet());
        randomico = rand()%3;
        if(randomico == 0){
            x_y_barra[posX_barra+1] = ESQUERDA;
        }else if(randomico == 1){
            x_y_barra[posX_barra+1] = MEIO;
        }else if(randomico == 2){
            x_y_barra[posX_barra+1] = DIREITA;
        }

    }


   //atualiza posicao da barra
    for(z=0; z<10; z+=2){
        if(x_y_barra[z] == 74){
            posX_barra = z;
        }
    }
}
void morreu(void){
    while(estado_botao != 3){

        bg=0;MORTE=1;
        Nokia5110_ClearBuffer();
        Nokia5110_PrintBMP2(0,0,morreu_Bitmap,24,48);
        Nokia5110_PrintBMP2(68,0,restart_Bitmap,16,48); //restart
        Nokia5110_DisplayBuffer();
        Nokia5110_ClearBuffer();
        estado_botao = start_buttons();
    }

    //restart nas variaveis
    bg=1;MORTE=0;
    tempo_sys = 37000;
    x_doodle = 63 - 21 - 2; y_doodle = 37;SCORE=0;
    x_y_barra[posX_barra+1] =  ESQUERDA;
}

void pula(void){
    //TAXA DE VARIACAO DE 12
    static int a=0,aa=0,b=0,caindo=1;
    a=(int)((b/12)); // taxa


    //cai enquanto nao tiver chao a uma velocidade de 2p por uma taxa de  168/12
    if(!verificaCHAO() && caindo == 1){
        //verifica se morreu
        if((x_doodle+13) > 78){
            morreu();
        }

        if(a > aa){//IF(a > aa)
            x_doodle += 3;
        }

    }else{//Se achar o chao
        //reseta as variaveis UMA UNICA VEZ
        if(caindo == 1){
            //sobe o cenario 17 px
            abaixa();
            caindo = 0;
            b=0;
            a=(int)((b/12));
            aa = a;
        }

        //mantem a velocidade de subida
        if(a > aa){
                x_doodle -= 3;
            }

        if(b >= 84){
            b=0;
            a=(int)((b/12));
            aa = a;
            caindo = 1;
        }

    }


    b++;
    aa = a;
}
void background(void){//SYSTICK PRO CENARIO

    if(bg){
        Nokia5110_PrintBMP2(x_y_barra[0],x_y_barra[1],barra0_Bitmap,2,13);
        Nokia5110_PrintBMP2(x_y_barra[2],x_y_barra[3],barra0_Bitmap,2,13);
        Nokia5110_PrintBMP2(x_y_barra[4],x_y_barra[5],barra0_Bitmap,2,13);
        Nokia5110_PrintBMP2(x_y_barra[6],x_y_barra[7],barra0_Bitmap,2,13);
        Nokia5110_PrintBMP2(x_y_barra[8],x_y_barra[9],barra0_Bitmap,2,13);

        Nokia5110_PrintBMP2(77,0,base_Bitmap,1,48); //barra
        Nokia5110_PrintBMP2(79,22,score_Bitmap,5,19); //SCORE
        Nokia5110_PrintBMP2(79,0,vet_num_Bitmap[(SCORE - (SCORE/10)*10)],5,3); //ultimo digito score
        Nokia5110_PrintBMP2(79,4,vet_num_Bitmap[(SCORE/10 - (SCORE/100)*10)],5,3); //penultimo
        Nokia5110_PrintBMP2(79,8,vet_num_Bitmap[(SCORE/100 - (SCORE/1000)*10)],5,3); //antepenultimo
        Nokia5110_PrintBMP2(79,12,vet_num_Bitmap[SCORE/1000],5,3); //primeiro

    }
    if(MORTE){
        Nokia5110_PrintBMP2(35,26,score_Bitmap,5,19); //SCORE
        Nokia5110_PrintBMP2(35,4,vet_num_Bitmap[(SCORE - (SCORE/10)*10)],5,3); //ultimo digito score
        Nokia5110_PrintBMP2(35,8,vet_num_Bitmap[(SCORE/10 - (SCORE/100)*10)],5,3); //penultimo
        Nokia5110_PrintBMP2(35,12,vet_num_Bitmap[(SCORE/100 - (SCORE/1000)*10)],5,3); //antepenultimo
        Nokia5110_PrintBMP2(35,16,vet_num_Bitmap[SCORE/1000],5,3); //primeiro

    }

}

void start_game(void){
    //botoes
    trataBotoes();
    pula();


    //ativa ou nao systick - CENARIO DE FUNDO
    bg = 1;


    //imprime o doodle
    Nokia5110_PrintBMP2(x_doodle,y_doodle,doodle[ju],13,11);
    Nokia5110_DisplayBuffer();
    Nokia5110_ClearBuffer();

    //acelera o jogo com base no SCORE

    if((SCORE+1)%6 == 0 && tempo_sys <= 40500){
        tempo_sys +=500;
        SysTickPeriodSet (tempo_sys);
    }

}

