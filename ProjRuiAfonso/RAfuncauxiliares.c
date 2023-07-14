#include "ProjRuiAfonso.h"

int testecartavalida(char *cartai){
    //a função não permite que o primeiro caracter de cada uma das srrings de cartas seja diferente de A,2,3,4,5,6,7,8,9,T,J,Q,K
    //a função não permite que o segundo caracter de cada uma das strings de cartas seja diferente de C(Copas),E(Espadas),O(Ouros) e P(Paus)
    if (!((cartai[0]<=57 && cartai[0]>=50)||cartai[0]==65||cartai[0]==84||cartai[0]==75||cartai[0]==74||cartai[0]==81)||(!(cartai[1]==79||cartai[1]==80||cartai[1]==69||cartai[1]==67))){
      return 0;
    }
    return 1;
}

void retiranumerovetor(int *vetor, int posicao, int tamanho){ //remove um elemento do vetor indicado pela sua posicao
    int i,aux;
    vetor[posicao]=0;
    for(i=0;i<tamanho-1;i++){
        if(vetor[i]==0){
            aux=vetor[i+1];
            vetor[i+1]=0;
            vetor[i]=aux;
        }
    }
    return;
}

char** alocarvetor2d(int linhas, int colunas){ //alocacao de memoria para vetor bidimensional de char
    int i;
    char **vetor;
    if((vetor=(char**)calloc(linhas,sizeof(char*)))==NULL){
        erro();
    }
    for(i=0;i<linhas;i++){
        if((vetor[i]=(char*)calloc(colunas,sizeof(char)))==NULL){
            erro();
        }
    }
    return vetor;
}

void free2d(char** vetor, int linhas){ //libertacao de memoria para vetor bidimensional de char
    int i;
    for(i=0;i<linhas;i++){
        free(vetor[i]);
    }
    free(vetor);
    return;
}

char*** alocarvetor3d(int a, int b, int c){ //alocacao de memoria para vetor tridimensional de char
    int i,j;
    char ***vetor;
    if((vetor=(char***)calloc(a,sizeof(char**)))==NULL){
        erro();
    }
    for(i=0;i<a;i++){
        if((vetor[i]=(char**)calloc(b,sizeof(char*)))==NULL){
            erro();
        }
        for(j=0;j<b;j++){
            if((vetor[i][j]=(char*)calloc(c,sizeof(char)))==NULL){
                erro();
            }
        }
    }
    return vetor;
}

void free3d(char***vetor,int a,int b,int c)  //libertacao de memoria para vetor tridimensional de char
{
    int i,j;
    for(i=0;i<1;i++){
        for(j=0;j<b;j++){
            free(vetor[i][j]);
        }
    }
    for(i=1;i<a;i++){
        for(j=0;j<b;j++){
            free(vetor[i][j]);
        }
    }
    for(i=0;i<a;i++){
        free(vetor[i]);
    }
    free(vetor);
}

int* alocarvetorint(int nelementos){ //aloca vetor de inteiros
    int *vetor;
    if((vetor=(int*)calloc(nelementos,sizeof(int)))==NULL){
        erro();
    }
    return vetor;
}

float* alocarvetorfloat(int nelementos){ //aloca vetor de floats
    float *vetor;
    if((vetor=(float*)calloc(nelementos,sizeof(float)))==NULL){
        erro();
    }
    return vetor;
}

double* alocarvetordouble(int nelementos){ //aloca vetor de floats
    double *vetor;
    if((vetor=(double*)calloc(nelementos,sizeof(double)))==NULL){
        erro();
    }
    return vetor;
}

void funcaoatribuicartas(char **x1,char **carta,int a1, int a2, int a3, int a4, int a5, int b1, int b2, int b3, int b4, int b5){ //funçao que coloca uma mão no vetor x1
    x1[a1][0]=carta[b1][0]; //primeira combinação guardada em x1
    x1[a1][1]=carta[b1][1];
    x1[a1][2]=carta[b1][2];
    x1[a2][0]=carta[b2][0];
    x1[a2][1]=carta[b2][1];
    x1[a2][2]=carta[b2][2];
    x1[a3][0]=carta[b3][0];
    x1[a3][1]=carta[b3][1];
    x1[a3][2]=carta[b3][2];
    x1[a4][0]=carta[b4][0];
    x1[a4][1]=carta[b4][1];
    x1[a4][2]=carta[b4][2];
    x1[a5][0]=carta[b5][0];
    x1[a5][1]=carta[b5][1];
    x1[a5][2]=carta[b5][2];
    return;
}

void funcaoatribuicartasint(int *x1,int *carta,int a1, int a2, int a3, int a4, int a5, int a6, int a7,int a8, int b1, int b2, int b3, int b4, int b5, int b6, int b7,int b8){ //funçao que coloca uma mão no vetor x1
    x1[a1]=carta[b1];
    x1[a2]=carta[b2];
    x1[a3]=carta[b3];
    x1[a4]=carta[b4];
    x1[a5]=carta[b5];
    x1[a6]=carta[b6];
    x1[a7]=carta[b7];
    x1[a8]=carta[b8];
    return;
}

int valordascartas1(char **carta,int i){   //função tendo em vista a atribuição de um valor a uma carta=valorcarta
    int valorcarta=0,resultado;
    if(carta[i][0]=='A'){
        valorcarta=14;
    }
    else if(carta[i][0]=='K'){
        valorcarta=13;
    }
    else if(carta[i][0]=='Q'){
        valorcarta=12;
    }
    else if(carta[i][0]=='J'){
        valorcarta=11;
    }
    else if(carta[i][0]=='T'){
        valorcarta=10;
    }
    else if(carta[i][0]=='9'){
        valorcarta=9;
    }
    else if(carta[i][0]=='8'){
        valorcarta=8;
    }
    else if(carta[i][0]=='7'){
        valorcarta=7;
    }
    else if(carta[i][0]=='6'){
        valorcarta=6;
    }
    else if(carta[i][0]=='5'){
        valorcarta=5;
    }
    else if(carta[i][0]=='4'){
        valorcarta=4;
    }
    else if(carta[i][0]=='3'){
        valorcarta=3;
    }
    else if(carta[i][0]=='2'){
        valorcarta=2;
    }
    resultado=valorcarta;
    return resultado;
}

int funcaoanalisenype(int valornype1[10],int valornype2[10],int a1, int a2, int a3, int a4, int a5, int b1, int b2, int b3, int b4, int b5){
    int nypewin=0;
    if(valornype1[a1]>valornype2[b1]){  //análise de qual das mãos possui um valor nype da carta mais relevante mais alto, e se este for o mesmo, esta verificaçao carta a carta
        nypewin=1;                         //visando que no final da função 10 fique no vetor carta, no caso de empate, a mao com os nypes como pedido no enunciado
    }
    else if(valornype1[a1]<valornype2[b1]){
        nypewin=2;
    }
    else{
        if(valornype1[a2]>valornype2[b2]){
            nypewin=1;
        }
        else if(valornype1[a2]<valornype2[b2]){
            nypewin=2;
        }
        else{
            if(valornype1[a3]>valornype2[b3]){
                nypewin=1;
            }
            else if(valornype1[a3]<valornype2[b3]){
                nypewin=2;
            }
            else{
                if(valornype1[a4]>valornype2[b4]){
                    nypewin=1;
                }
                else if(valornype1[a4]<valornype2[b4]){
                    nypewin=2;
                }
                else{
                    if(valornype1[a5]>=valornype2[b5]){
                        nypewin=1;
                    }
                    else if(valornype1[a5]<valornype2[b5]){
                        nypewin=2;
                    }
                }
            }
        }
    }
    return nypewin;
}

int valornype(char **carta,int i){  //função tendo em vista a atribuição de um valor a uma carta relativamente ao seu nype=valornype
    int valornyp=0,resultado;
    if(carta[i][1]=='C'){
        valornyp=4;
    }
    else if(carta[i][1]=='E'){
        valornyp=3;
    }
    else if(carta[i][1]=='O'){
        valornyp=2;
    }
    else if(carta[i][1]=='P'){
        valornyp=1;
    }
    resultado=valornyp;
    return resultado;
}

int verificacartasiguais(char **carta,int inicio,int fim){
    int i,j;
    for (j=inicio;j<fim;j++){
        for (i=inicio;i<fim;i++){
            if (!(i==j)){
                if ((carta[j][0]== carta[i][0])&&(carta[j][1]==carta[i][1])&&(carta[j][2]== carta[i][2])){
                    return 1;
                }
            }
        }
    }
    return 0;
}
void erro(){
    fprintf(stdout,"-1\n");
    exit (0);
}

int determinanumerocartas(FILE *ficheirorecebido){
    int n=0;
    char strtemp[3];
    while(fscanf(ficheirorecebido,"%s",strtemp)!=EOF){
        n++;
    }
    fseek(ficheirorecebido,0,SEEK_SET);
    return n;
}

