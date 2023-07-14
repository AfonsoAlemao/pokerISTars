/*============================================================================*/
/* Programa: Pokeristars                                                      */
/*                                                                            */
/* Descrição do programa: Este programa foi realizado no âmbito da UC de      */
/*                        Programação tendo em vista a utilização da matéri   */
/*                        lecionada para simular um jogo de poker.            */
/*                                                                            */
/* Ficheiros:                                                                 */
/*  (1) ProjRuiAfonso.c                                                       */
/*  (2) RAfuncauxiliares.c                                                    */
/*  (3) RAmodoc.c                                                             */
/*  (4) RAmododianddx.c                                                       */
/*  (5) RAshuffle.c                                                           */
/*                                                                            */
/* Autoria: Afonso Alemão 96135 MEEC IST                                      */
/*          Rui Daniel 96317 MEEC IST                                         */
/*          Grupo 28                                   Data: 2019/2020        */
/*============================================================================*/

#include "ProjRuiAfonso.h"

int main(int argc, char *argv[]){
    int numerocartas=0,resultado=0,tamanhostringnomeficheiro=0;
    FILE *ponteiroresultados;
    ponteiroresultados=stdout;

    if(argc<2){
        erro();
    }
    if((argv[1][0]!= '-' || argv[1][1]!='c' || strlen(argv[1])!=2) && (argv[1][0]!= '-' || argv[1][1]!='d' || strlen(argv[1])!=3)&& (argv[1][0]!= '-' || argv[1][1]!='s'|| argv[1][2]!='1' || strlen(argv[1])!=3)){  //apenas é aceitável o modo linha de comando, com opcão -c
        erro();
    }
    if(argc>4){
        if(argc==5 && argv[3][0]=='-' && argv[3][1]=='o'){
            ponteiroresultados= fopen(argv[4], "w+");
            if(ponteiroresultados==NULL){
                erro();
            }
        }
    }
    else{
        ponteiroresultados= stdout;
    }
    if(argv[1][0]== '-' && argv[1][1]=='s' && argv[1][2]=='1' && strlen(argv[1])==3){
        shuffle(ponteiroresultados,argv,argc,numerocartas,tamanhostringnomeficheiro); //entrada no modo shuffle
        fclose(ponteiroresultados);
        return 0;
    }
    if((argv[1][0]== '-' && argv[1][1]=='d' && strlen(argv[1])==3)){  //modo ficheiro de baralho di e dx
        modosdiandx(ponteiroresultados,argv,argc,numerocartas,tamanhostringnomeficheiro);
        fclose(ponteiroresultados);
        return 0;
    }
    ponteiroresultados=stdout;
    if((argv[1][0]== '-' && argv[1][1]=='c' && strlen(argv[1])==2)){ //modolinha de comando -c
        resultado=modoc(ponteiroresultados,argv,argc,numerocartas,tamanhostringnomeficheiro);
    }
    fprintf(ponteiroresultados,"%d\n",resultado);
    fclose(ponteiroresultados);
    return 0;
}
