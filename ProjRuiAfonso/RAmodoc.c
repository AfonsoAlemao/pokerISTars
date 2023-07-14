#include "ProjRuiAfonso.h"

int modoc(FILE *ponteiroresultados,char *argv[],int argc,int numerocartas,int tamanhostringnomeficheiro){
    int testecartaval,i,cartasiguais=0,testecartaval0=1,testecartaval1=1,testecartaval2=1,testecartaval3=1,testecartaval4=1,testecartaval5=1,testecartaval6=1,testecartaval7=1,testecartaval8=1,testecartaval9=1;
    int resultado=0;
    numerocartas=argc-2;
    if (!(numerocartas==5||numerocartas==7||numerocartas==9||numerocartas==10)){ //o numero de cartas não pode ser diferente de 5, 7 ,9 e 10
        fprintf(ponteiroresultados,"-1\n");
        exit (0);
    }
    char **carta;
    carta=alocarvetor2d(numerocartas,3);
    for(i=0;i<numerocartas;i++){
        if(strlen(argv[i+2])!=2){
            fprintf(ponteiroresultados,"-1\n");
            exit (0);
        }
    }
    for(i=0;i<numerocartas;i++){
        carta[i][0]=argv[i+2][0];
        carta[i][1]=argv[i+2][1];
        carta[i][2]=argv[i+2][2];
    }
    if(numerocartas==7){
        testecartaval5=testecartavalida(carta[5]);  // Chama a função testecartavalida() para detetar se a carta não está fora da gama dos valores pretendidos
        testecartaval6=testecartavalida(carta[6]);
    }
    else if(numerocartas==9){
        testecartaval5=testecartavalida(carta[5]);
        testecartaval6=testecartavalida(carta[6]);
        testecartaval7=testecartavalida(carta[7]);
        testecartaval8=testecartavalida(carta[8]);
    }
    else if(numerocartas==10){
        testecartaval5=testecartavalida(carta[5]);
        testecartaval6=testecartavalida(carta[6]);
        testecartaval7=testecartavalida(carta[7]);
        testecartaval8=testecartavalida(carta[8]);
        testecartaval9=testecartavalida(carta[9]);
    }
    testecartaval0=testecartavalida(carta[0]);
    testecartaval1=testecartavalida(carta[1]);
    testecartaval2=testecartavalida(carta[2]);
    testecartaval3=testecartavalida(carta[3]);
    testecartaval4=testecartavalida(carta[4]);
    testecartaval=testecartaval0*testecartaval1*testecartaval2*testecartaval3*testecartaval4*testecartaval5*testecartaval6*testecartaval7*testecartaval8*testecartaval9; //Se alguma das cartas não for valida, testecartaval=0
    if(testecartaval==0){  //caso em que uma das cartas não é válida, pois um de um dos testes retorna 0, tornando testecartaval=0
        fprintf(ponteiroresultados,"-1\n");
        exit (0);
    }

    if (numerocartas==5){
        cartasiguais=verificacartasiguais(carta,0,5); //não permite que haja cartas repetidas
        if(cartasiguais==1){
            fprintf(ponteiroresultados,"-1\n");
            exit (0);
        }
        resultado=tipodemao(carta); //o resultado indica o valor da mão(1-10)
    }
    if (numerocartas==7){ //não permite que haja cartas repetidas
        cartasiguais=verificacartasiguais(carta,0,7);
        if(cartasiguais==1){
            fprintf(ponteiroresultados,"-1\n");
            exit (0);
        }
        resultado=chamarcartas(carta,argv,argc,ponteiroresultados,1); //a função chamarcartas indica as 5 melhores cartas(dentro das 7) e o seu respetivo valor dessa mão(1-10) fica em resultado
    }
    if (numerocartas==9){  //não permite que haja cartas repetidas
        cartasiguais=verificacartasiguais(carta,0,9);
        if(cartasiguais==1){
            printf("-1\n");
            exit (0);
        }
        resultado=funcaonovecartas(carta,argv,argc,ponteiroresultados,1); //a função funçãonovecartas devolve a melhor mão possivel do jogador 1 (e o seu valor respetivo)
    }
                                         //e a melhor mão possivel do jogador2(e o seu valor respetivo), guardando o resultado do confronto entre estes jogadores,0-empate,1-vence jogador 1, 2-vence jogador 2
    if (numerocartas==10){
        //mão de 5 cartas do jogador 1 não poderá ter cartas repetidas
        cartasiguais=verificacartasiguais(carta,0,5);
        if(cartasiguais==1){
            fprintf(ponteiroresultados,"-1\n");
            exit (0);
        }
        //mão de 5 cartas do jogador 1 não poderá ter cartas repetidas
        cartasiguais=verificacartasiguais(carta,5,10);
        if(cartasiguais==1){
            fprintf(ponteiroresultados,"-1\n");
            exit (0);
        }
        resultado=funcaodezcartas(carta); //a função funcaodezcartas retorna um valor inteiro que simboliza 0-empate, 1-vence primeira mão, 2-vence segunda mão
    }
    free2d(carta,numerocartas);
    return resultado;
}

int tipodemao (char **carta){
    int valorcarta[10],valornype[10],i,j,testecartaval0=1, cartasiguais=0;
    int valtroca;
    char vetortroca[3];
    int nypeigual=0, sequenciaigual=0,cincocartasmaisaltas=0;
    //atribuir valor às cartas associado ao primeiro caracter=valor
    for(i=0;i<5;i++){
        testecartaval0=testecartavalida(carta[i]);  //validaçao para cartas iguais no mesmo baralho??
        if (testecartaval0==0){
            return -1;
        }
    }
    cartasiguais=verificacartasiguais(carta,0,5);
    if(cartasiguais==1){
        return -1;
    }

    for(i=0;i<=4;i++){
        valorcarta[i]=valordascartas1(carta,i);
    }
    for(i=0;i<=4;i++){
        if(carta[i][1]=='C'){  //atribuir valor às cartas associado ao seu nype=valornype
            valornype[i]=4;
        }
        else if(carta[i][1]=='E'){
            valornype[i]=3;
        }
        else if(carta[i][1]=='O'){
            valornype[i]=2;
        }
        else if(carta[i][1]=='P'){
            valornype[i]=1;
        }
    }
    for (j=0;j<=6;j++){  //ordenar cartas pelo seu valor
        for (i=0;i<=3;i++){
            while(valorcarta[i]<valorcarta[i+1]){
                vetortroca[0]=carta[i][0]; //vetortroca guarda o valor da carta[i]
                vetortroca[1]=carta[i][1];
                carta[i][0]=carta[i+1][0]; //a carta[i] passa a ter o valor da carta[i+1]
                carta[i][1]=carta[i+1][1];
                carta[i+1][0]=vetortroca[0]; //a carta[i+1] passa a ter o valor da carta[i]
                carta[i+1][1]=vetortroca[1];
                valtroca=valorcarta[i];  //guarda o valorcarta[i]
                valorcarta[i]=valorcarta[i+1];  //o valor da carta[i] passa a ter o valor da carta[i+1]
                valorcarta[i+1]=valtroca;  //o valor da carta[i+1] passa a ter o valor da carta[i]
                valtroca=valornype[i];
                valornype[i]=valornype[i+1]; //o valor do nype carta[i] passa a ter o valor do nype da carta[i+1]
                valornype[i+1]=valtroca;  //o valor do nype da carta[i+1] passa a ter o valor do nype da carta[i]
            }
        }
    }
    //ordenar as cartas do mesmo valor pelo seu nype
    for (j=0;j<=7;j++){
        for (i=0;i<=3;i++){
            if(valorcarta[i]==valorcarta[i+1] && valornype[i]<valornype[i+1]){
                vetortroca[0]=carta[i][0];
                vetortroca[1]=carta[i][1];
                carta[i][0]=carta[i+1][0];
                carta[i][1]=carta[i+1][1];
                carta[i+1][0]=vetortroca[0];
                carta[i+1][1]=vetortroca[1];
                valtroca=valorcarta[i];
                valorcarta[i]=valorcarta[i+1];
                valorcarta[i+1]=valtroca;
                valtroca=valornype[i];
                valornype[i]=valornype[i+1];
                valornype[i+1]=valtroca;
            }
        }
    }

    if((carta[0][1]==carta[1][1]) && (carta[1][1]==carta[2][1]) && (carta[2][1]==carta[3][1]) && (carta[3][1]==carta[4][1])){  //nype igual
        nypeigual=1;
    }
    if (((valorcarta[0]==(valorcarta[1]+1)) && (valorcarta[0]==(valorcarta[2]+2)) && (valorcarta[0]==(valorcarta[3]+3)) && (valorcarta[0]==(valorcarta[4]+4)))||
       ((valorcarta[0]==14) && (valorcarta[1]==5) && (valorcarta[1]==(valorcarta[2]+1)) && (valorcarta[1]==(valorcarta[3]+2)) && (valorcarta[1]==(valorcarta[4]+3)))){
            sequenciaigual=1;  //é verificado se as cartas estão em sequência sem esquecer o caso 5,4,3,2,A
            if(valorcarta[0]==14 && valorcarta[1]==13){
                cincocartasmaisaltas=1; //sequência das cartas mais altas
            }
    }
    if(sequenciaigual==1){
        if(nypeigual==1){
            if(cincocartasmaisaltas==1){
                return 10; //10-Royal flush
            }
            else if(cincocartasmaisaltas==0){
                return 9; //9-Straight flush
            }
        }
        else if (nypeigual==0){
            return 5;  //5-Straight
        }
    }
    if (sequenciaigual==0){
        if(nypeigual==1){
            return 6; //6-Flush
        }
    }

    if(((carta[0][0]==carta[1][0]) && (carta[1][0]==carta[2][0]) && (carta[2][0]==carta[3][0]) )|| //ver se é peixinho(4 cartas de igual valor dos 4 naipes)
       ((carta[0][0]==carta[1][0]) && (carta[1][0]==carta[2][0]) && (carta[2][0]==carta[4][0]) )||
       ((carta[0][0]==carta[1][0]) && (carta[1][0]==carta[3][0]) && (carta[3][0]==carta[4][0]) )||
       ((carta[0][0]==carta[4][0]) && (carta[4][0]==carta[2][0]) && (carta[2][0]==carta[3][0]) )||
       ((carta[4][0]==carta[1][0]) && (carta[1][0]==carta[2][0]) && (carta[2][0]==carta[3][0]) )){
            return 8; //8-Four of a kind
    }

    //bloco de código para detetar  three of a kind, two pair, one pair e full house,  definido várias vezes as combinações possíveis dos valores das cartas para cada um dos tipos de mão
    if((((valorcarta[0]==valorcarta[1])&&(valorcarta[1]==valorcarta[2])&&(valorcarta[0]!=valorcarta[3])&&(valorcarta[0]!=valorcarta[4])&&(valorcarta[3]!=valorcarta[4])))||
    (((valorcarta[1]==valorcarta[2])&&(valorcarta[2]==valorcarta[3])&&(valorcarta[1]!=valorcarta[0])&&(valorcarta[1]!=valorcarta[4])&&(valorcarta[0]!=valorcarta[4])))||
    (((valorcarta[2]==valorcarta[3])&&(valorcarta[3]==valorcarta[4])&&(valorcarta[2]!=valorcarta[0])&&(valorcarta[2]!=valorcarta[1])&&(valorcarta[0]!=valorcarta[1])))){
        return 4; //4-Three of a kind       aaabc ou baaac ou bcaaa
    }

    if (((valorcarta[0]==valorcarta[1])&&(valorcarta[2]==valorcarta[3])&&(valorcarta[2]!=valorcarta[0])&&(valorcarta[2]!=valorcarta[4])&&(valorcarta[0]!=valorcarta[4])) ||
    ((valorcarta[0]==valorcarta[1])&&(valorcarta[3]==valorcarta[4])&&(valorcarta[3]!=valorcarta[0])&&(valorcarta[3]!=valorcarta[2])&&(valorcarta[0]!=valorcarta[2])) ||
    ((valorcarta[1]==valorcarta[2])&&(valorcarta[3]==valorcarta[4])&&(valorcarta[1]!=valorcarta[3])&&(valorcarta[0]!=valorcarta[1])&&(valorcarta[0]!=valorcarta[3]))){
        return 3; //3-Two pair  xx-yy ou xxyy- ou -xxyy
    }

    if (((valorcarta[0]==valorcarta[1])&&(valorcarta[1]!=valorcarta[2])&&(valorcarta[2]!=valorcarta[3])&&(valorcarta[3]!=valorcarta[4]))||
    ((valorcarta[0]!=valorcarta[1])&&(valorcarta[1]==valorcarta[2])&&(valorcarta[2]!=valorcarta[3])&&(valorcarta[3]!=valorcarta[4]))||
    ((valorcarta[0]!=valorcarta[1])&&(valorcarta[1]!=valorcarta[2])&&(valorcarta[2]==valorcarta[3])&&(valorcarta[3]!=valorcarta[4]))||
    ((valorcarta[0]!=valorcarta[1])&&(valorcarta[1]!=valorcarta[2])&&(valorcarta[2]!=valorcarta[3])&&(valorcarta[3]==valorcarta[4]))){
        return 2; //2-One pair  xx---  -xx--  --xx-  ---xx
    }

    if(((valorcarta[0]==valorcarta[1])&&(valorcarta[1]==valorcarta[2])&&(valorcarta[2]!=valorcarta[3])&&(valorcarta[3]==valorcarta[4]))|| //3 cartas de um valor e 2 de outro
    ((valorcarta[0]==valorcarta[1])&&(valorcarta[1]!=valorcarta[2])&&(valorcarta[2]==valorcarta[3])&&(valorcarta[3]==valorcarta[4]))) {
        return 7; //7-Full House    aaabb ou bbaaa
    }

    return 1; //1-High card, no caso de não verificarmos a ocorrência dos outros tipos de mão
}

int chamarcartas(char **carta,char *argv[],int argc,FILE *ponteiroresultados,int escreveresultados){   //Função para quando avaliamos 7 cartas, saber destas qual a melhor mão de 5 cartas possível
    int *valorx1;
    valorx1=alocarvetorint(5);                    //estratégia: usar confrontos entre as mãos possíveis e eliminando a mão perdedora até obter apenas uma mão vencedora, a melhor mão possível
    int resultado,i;
    char **x1;                   //criação de todas as combinações possíveis entre as 7 cartas, para gerar todas as mãos possíveis
    x1=alocarvetor2d(10,3);
    funcaoatribuicartas(x1,carta,0,1,2,3,4,0,1,2,3,4); //primeira combinação guardada em x1

    int aux=7,a,b,c,d,e;
    for(a=2; a<=aux-3;++a){
        for(b=a+1; b<=aux-2;++b){
            for(c=b+1; c<=aux-1;++c){
                for(d=c+1; d<=aux;++d){
                    for(e=d+1; e<=aux+1;++e){
                        funcaoatribuicartas(x1,carta,5,6,7,8,9,a-2,b-2,c-2,d-2,e-2);    //uma das 21 combinações, concatenar em x1 e executar funçaodezcartas
                        resultado=funcaodezcartas(x1);  //em carta [0-4] ficaram guardadas as melhores 5 cartas, vencedoras do confronto entre estas 2 combinações anteriores
                    }   //colocação da próxima combinação na parte final do vetor x1, de modo a confrontar esta combinação com a mão que se mantém invencivel até ao momento
                }
            }
        }
    }

    resultado=tipodemao(x1);

    funcaoatribuicartas(carta,x1,0,1,2,3,4,0,1,2,3,4); //colocação das 5 melhores cartas no vetor carta

    for(i=0;i<=4;i++){
        valorx1[i]=valordascartas1(x1,i);
    }
    if (valorx1[0]==14 && valorx1[1]==5 && valorx1[2]==4 && valorx1[3]==3 && valorx1[4]==2){ //Sequência especial, pior sequência possível: 5,4,3,2,A
        funcaoatribuicartas(carta,x1,0,1,2,3,4,1,2,3,4,0);  //troca da ordem das cartas passando de A,5,4,3,2 para 5,4,3,2,A
        if(escreveresultados){
            fprintf(ponteiroresultados,"%s %s %s %s %s ",x1[1],x1[2],x1[3],x1[4],x1[0]);
        }
        free(valorx1);
        free2d(x1,10);
        return resultado;
    }
    if(escreveresultados){
        fprintf(ponteiroresultados,"%s %s %s %s %s ",x1[0],x1[1],x1[2],x1[3],x1[4]);
    }
    free(valorx1);
    free2d(x1,10);
    return resultado;  //retorna um número que caracteriza o tipo de mão de 0 a 10
}

int funcaonovecartas(char **carta,char *argv[],int argc,FILE *ponteiroresultados,int enableescrita){  //função que recebe 9 cartas de main, e irá retornar um resultado 0-empate, 1-primeiro jogador vence, 2-segundo jogador vence, tal como as melhores mãos e o seu tipo de cada um destes
    int resultadoconfronto,resultado1,resultado2,i,j,testecartaval0;
    char **jog1,**jog2,**tencards;
    jog1=alocarvetor2d(7,3);
    jog2=alocarvetor2d(7,3);
    tencards=alocarvetor2d(10,3);

    for(i=0;i<9;i++){
        testecartaval0=testecartavalida(carta[i]);  //validaçao para cartas iguais no mesmo baralho??
        if (testecartaval0==0){
            free2d(tencards,10);
            free2d(jog1,7);
            free2d(jog2,7);
            return -1;
        }
    }
    funcaoatribuicartas(jog1,carta,0,1,2,3,4,0,1,4,5,6);  //primeiro jogador fica com as cartas 0,1,4,5,6,7,8
    jog1[5][0]=carta[7][0];
    jog1[5][1]=carta[7][1];
    jog1[5][2]=carta[7][2];
    jog1[6][0]=carta[8][0];
    jog1[6][1]=carta[8][1];
    jog1[6][2]=carta[8][2];

    for(i=0;i<=6;i++){
        for(j=0;j<=2;j++){
            jog2[i][j]=carta[i+2][j];
        }
    } //segundo jogador fica com as cartas 2,3,4,5,6,7,8

    resultado1=chamarcartas(jog1,argv,argc,ponteiroresultados,enableescrita);  //funçao chamar cartas retorna vetor jog1 com as 5 melhores catas do primeiro jogador e imprime essas cinco cartas
    if(enableescrita==1){
        fprintf(ponteiroresultados,"%d ",resultado1);       //imprime valor dessa melhor mão do jogador 1
    }
    funcaoatribuicartas(tencards,jog1,0,1,2,3,4,0,1,2,3,4); //coloca nas primeiras 5 posições do vetor as 5 cartas da melhor mão possível para o jogador 1

    resultado2=chamarcartas(jog2,argv,argc,ponteiroresultados,enableescrita);  //funçao chamar cartas retorna vetor jog2 com as 5 melhores catas do segundo jogador e imprime essas cinco cartas
    if(enableescrita==1){
        fprintf(ponteiroresultados,"%d ",resultado2);
    }
    funcaoatribuicartas(tencards,jog2,5,6,7,8,9,0,1,2,3,4);     //coloca nas últimas 5 posições do vetor as 5 cartas da melhor mão possível para o jogador 2

    resultadoconfronto=funcaodezcartas(tencards);   //compara a mão das primeiras 5 cartas (jogador 1) com as últimas 5 cartas (jogador 2), e retorna 0-empate, 1-vence jogador 1, 2-vence jogador 2
    free2d(tencards,10);
    free2d(jog1,7);
    free2d(jog2,7);
    return resultadoconfronto;
}

int funcaodezcartas(char **carta){  //função que visa receber 2 mãos e retornar qual destas a melhor
    int i;
    char **x1,**x2;
    x1=alocarvetor2d(10,3);
    x2=alocarvetor2d(10,3);
    int *valornype1,*valornype2,testecartaval0;
    valornype1=alocarvetorint(10);
    valornype2=alocarvetorint(10);
    int valor1,valor2,valorpar1=0,valorpar11=0,valorpar2=0,valorpar22=0,maxvalorpar1=0,maxvalorpar2=0,minvalorpar1=0,minvalorpar2=0;
    int valortrio1=0,valortrio2=0,valorpeixinho1=0,valorpeixinho2=0,valorcartasozinha1=0,valorcartasozinha2=0;
    int *valorx1,*valorx2,result,nypewin=0;
    valorx1=alocarvetorint(5);
    valorx2=alocarvetorint(5);
    for(i=0;i<10;i++){
        testecartaval0=testecartavalida(carta[i]);  //validaçao para cartas iguais no mesmo baralho??
        if (testecartaval0==0){
            return -1;
        }
    }
    funcaoatribuicartas(x1,carta,0,1,2,3,4,0,1,2,3,4);//colocação cartas primeiro jogador em x1
    valor1= tipodemao(x1); //ordena as cartas do primeiro jogador e guarda em valor1 o seu tipo de mão
    valornype1[0]=valornype(x1,0); //obter valor do nype das cartas do jogador 1
    valornype1[1]=valornype(x1,1);
    valornype1[2]=valornype(x1,2);
    valornype1[3]=valornype(x1,3);
    valornype1[4]=valornype(x1,4);
    funcaoatribuicartas(x2,carta,0,1,2,3,4,5,6,7,8,9); //colocação cartas segundo jogador em x2
    valor2= tipodemao(x2); //ordena as cartas do segundo jogador e guarda em valor2 o seu tipo de mão
    valornype2[0]=valornype(x2,0); //obter valor do nype das cartas do jogador 2
    valornype2[1]=valornype(x2,1);
    valornype2[2]=valornype(x2,2);
    valornype2[3]=valornype(x2,3);
    valornype2[4]=valornype(x2,4);

    for(i=0;i<=4;i++){
        valorx1[i]=valordascartas1(x1,i);
    }
    for(i=0;i<=4;i++){
        valorx2[i]=valordascartas1(x2,i);
    }
    //obteve-se os valores das cartas de x1 e de x2 para podermos desempatar no caso em que ambas as mãos são do mesmo tipo
    if(valor1>valor2){ //jogador com maior valor da sua mão ganha
        result=1; //vitória jogador 1
    }
    else if (valor1<valor2){
        result=2; //vitória jogador 2
    }
    else if (valor1==valor2){
        if (valor1==10){ // Cartas todas com valores iguais A,K,Q,J,T (ambas Royal Flush), logo empate
            result=0;
            nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
        }
        else if(valor1==1 || valor1==6){ //quando ambas as mãos são ou 1-high card ou 6-flush, estratégia é analisar o valor das cartas carta a carta, pois estas se encontram ordenadas por valor
            if(valorx1[0]>valorx2[0]){
                result=1;
            }
            else if (valorx1[0]<valorx2[0]){
                result=2;
            }
            else if(valorx1[0]==valorx2[0]){
                if(valorx1[1]>valorx2[1]){
                    result=1;
                }
                else if (valorx1[1]<valorx2[1]){
                    result=2;
                }
                else if(valorx1[1]==valorx2[1]){
                    if(valorx1[2]>valorx2[2]){
                        result=1;
                    }
                    else if (valorx1[2]<valorx2[2]){
                        result=2;
                    }
                    else if(valorx1[2]==valorx2[2]){
                        if(valorx1[3]>valorx2[3]){
                            result=1;
                        }
                        else if (valorx1[3]<valorx2[3]){
                            result=2;
                        }
                        else if(valorx1[3]==valorx2[3]){
                            if(valorx1[4]>valorx2[4]){
                                result=1;
                            }
                            else if (valorx1[4]<valorx2[4]){
                                result=2;
                            }
                            else if(valorx1[4]==valorx2[4]){
                                result=0; //no caso de um empate analisar carta a carta pelo valornype, para colocar no vetor que guardará a melhor carta, a mao de cartas cujo valornype da carta por ordem de relevância a ser analisada seja maior
                                nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
                            }
                        }
                    }
                }
            }
        }
        else if(valor1==5 || valor1==9){ //Quando ambas as mãos são 5-Straight ou 9-Straight Flush, sequências
            if (valorx1[0]==14 && valorx1[1]==5 && valorx2[0]==14 && valorx2[1]==5){ //Sequência especial, pior sequência possível: 5,4,3,2,A
                nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,4,0,1,2,3,4,0);
                if(nypewin==1){
                    funcaoatribuicartas(carta,x1,0,1,2,3,4,1,2,3,4,0);  //troca da ordem das cartas passando de A,5,4,3,2 para 5,4,3,2,A
                }
                else{
                    funcaoatribuicartas(carta,x2,0,1,2,3,4,1,2,3,4,0); //troca da ordem das cartas passando de A,5,4,3,2 para 5,4,3,2,A
                }
                free(valorx1);
                free(valorx2);
                free(valornype1);
                free(valornype2);
                free2d(x1,10);
                free2d(x2,10);
                return 0;//caso ambos os jogadores possuam esta mão especial-empate
            }
            else if (valorx1[0]==14 && valorx1[1]==5 && !(valorx2[0]==14 && valorx2[1]==5)){ //jogador com sequencia especial perde contra uma sequencia normal
                result=2;
            }
            else if (!(valorx1[0]==14 && valorx1[1]==5) && valorx2[0]==14 && valorx2[1]==5){
                result=1;
            }
            else if (!(valorx1[0]==14 && valorx1[1]==5) && !(valorx2[0]==14 && valorx2[1]==5)){ //confronto entre 2 sequencias normais
                if(valorx1[0]>valorx2[0]){  //como estão em sequência verificar por valor
                    result=1;
                }
                else if (valorx1[0]<valorx2[0]){
                    result=2;
                }
                else if(valorx1[0]==valorx2[0]){
                    if(valorx1[1]>valorx2[1]){
                        result=1;
                    }
                    else if (valorx1[1]<valorx2[1]){
                        result=2;
                    }
                    else if(valorx1[1]==valorx2[1]){
                        if(valorx1[2]>valorx2[2]){
                            result=1;
                        }
                        else if (valorx1[2]<valorx2[2]){
                            result=2;
                        }
                        else if(valorx1[2]==valorx2[2]){
                            if(valorx1[3]>valorx2[3]){
                                result=1;
                            }
                            else if (valorx1[3]<valorx2[3]){
                                result=2;
                            }
                            else if(valorx1[3]==valorx2[3]){
                                if(valorx1[4]>valorx2[4]){
                                    result=1;
                                }
                                else if (valorx1[4]<valorx2[4]){
                                    result=2;
                                }
                                else if(valorx1[4]==valorx2[4]){
                                    result=0; //quando há empate, verificar carta a carta qual o duelo de cartas, das mais para as menos relevantes, em que uma mao apresenta maior valor de nype que a outra
                                    nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(valor1==2){ //Quando ambas as mãos são 2-Pair, 2 cartas de igual valor, 3 diferentes e entre si
            if(x1[0][0]==x1[1][0]){  //verificação de onde se encontra o par e atribuição de um valor a este
                valorpar1=valorx1[0];
            }
            if(x1[1][0]==x1[2][0]){
                valorpar1=valorx1[1];
            }
            if(x1[2][0]==x1[3][0]){
                valorpar1=valorx1[2];
            }
            if(x1[3][0]==x1[4][0]){
                valorpar1=valorx1[3];
            }
            if(x2[0][0]==x2[1][0]){
                valorpar2=valorx2[0];
            }
            if(x2[1][0]==x2[2][0]){
                valorpar2=valorx2[1];
            }
            if(x2[2][0]==x2[3][0]){
                valorpar2=valorx2[2];
            }
            if(x2[3][0]==x2[4][0]){
                valorpar2=valorx2[3];
            }
            if(valorpar1>valorpar2){ //caso o valor das cartas do par de um jogador seja maior que a do outro, este vence
                result=1;
            }
            else if (valorpar1<valorpar2){
                result=2;
            }
            else if (valorpar1==valorpar2){  //caso este valor seja igual, análise carta a carta, verificando os valores como as cartas estão ordenadas, para ver qual a mao vencedora
                if(valorx1[0]>valorx2[0]){
                    result=1;
                }
                else if (valorx1[0]<valorx2[0]){
                    result=2;
                }
                else if(valorx1[0]==valorx2[0]){
                    if(valorx1[1]>valorx2[1]){
                        result=1;
                    }
                    else if (valorx1[1]<valorx2[1]){
                        result=2;
                    }
                    else if(valorx1[1]==valorx2[1]){
                        if(valorx1[2]>valorx2[2]){
                            result=1;
                        }
                        else if (valorx1[2]<valorx2[2]){
                            result=2;
                        }
                        else if(valorx1[2]==valorx2[2]){
                            if(valorx1[3]>valorx2[3]){
                                result=1;
                            }
                            else if (valorx1[3]<valorx2[3]){
                                result=2;
                            }
                            else if(valorx1[3]==valorx2[3]){
                                if(valorx1[4]>valorx2[4]){
                                    result=1;
                                }
                                else if (valorx1[4]<valorx2[4]){
                                    result=2;
                                }
                                else if(valorx1[4]==valorx2[4]){ //caso todos estes valores sejam iguais-empate
                                    result=0;
                //verificação do valor do nype das cartas tendo em conta que as cartas se encontram ordenadas por valor e quando o valor é o mesmo, por nype
                //4 tipos de aparecimento das cartas na mao xxabc=tipo1, axxbc=tipo2, abxxc=tipo3, abcxx=tipo4, logo podemos ter
                //tipo1 vs tipo1, tipo1 vs tipo2, tipo1 vs tipo3, tipo1 vs tipo4, tipo2 vs tipo 1, tipo2 vs tipo2, tipo2 vs tipo 3, tipo2 vs tipo4
                //tipo3 vs tipo1, tipo3 vs tipo2, tipo3 vs tipo3, tipo3 vs tipo4, tipo4 vs tipo 1, tipo4 vs tipo2, tipo4 vs tipo 3, tipo4 vs tipo4
                //ordem de análise de nype=o  o tipo1=0,1,2,3,4   o tipo2= 1,2,0,3,4    o tipo3= 2,3,0,1,4     o tipo4=3,4,0,1,2

                                    if((x1[0][0]==x1[1][0]) && (x2[1][0]==x2[2][0])){ //xxabc vs axxbc (tipo1 vs tipo2)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,1,2,0,3,4);
                                    }
                                    else if((x1[0][0]==x1[1][0]) && (x2[2][0]==x2[3][0])){ //xxabc vs abxxc (tipo1 vs tipo3)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,2,3,0,1,4);
                                    }
                                    else if((x1[0][0]==x1[1][0]) && (x2[3][0]==x2[4][0])){ //xxabc vs abcxx (tipo1 vs tipo4)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,3,4,0,1,2);
                                    }
                                    else if((x1[1][0]==x1[2][0]) && (x2[2][0]==x2[3][0])){ //axxbc vs abxxc (tipo2 vs tipo3)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,0,3,4,2,3,0,1,4);
                                    }
                                    else if((x1[1][0]==x1[2][0]) && (x2[3][0]==x2[4][0])){ //axxbc abcxx (tipo2 vs tipo4)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,0,3,4,3,4,0,1,2);
                                    }
                                    else if((x1[2][0]==x1[3][0]) && (x2[3][0]==x2[4][0])){ //abxxc vs abcxx (tipo3 vs tipo4)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,0,1,4,3,4,0,1,2);
                                    }
                                    else if((x1[0][0]==x1[1][0]) && (x2[0][0]==x2[1][0])){ //xxabc vs xxabc (tipo1 vs tipo1)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
                                    }
                                    else if((x1[1][0]==x1[2][0]) && (x2[1][0]==x2[0][0])){ //axxbc vs xxabc (tipo2 vs tipo1)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,0,3,4,0,1,2,3,4);
                                    }
                                    else if((x1[1][0]==x1[2][0]) && (x2[1][0]==x2[2][0])){ //axxbc vs axxbc (tipo2 vs tipo2)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,0,3,4,1,2,0,3,4);
                                    }
                                    else if((x1[2][0]==x1[3][0]) && (x2[1][0]==x2[2][0])){ //abxxc vs axxbc (tipo3 vs tipo2)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,0,1,4,1,2,0,3,4);
                                    }
                                    else if((x1[2][0]==x1[3][0]) && (x2[1][0]==x2[0][0])){ //abxxc vs xxabc (tipo3 vs tipo1)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,0,1,4,0,1,2,3,4);
                                    }
                                    else if((x1[2][0]==x1[3][0]) && (x2[2][0]==x2[3][0])){ //abxxc vs abxxc (tipo3 vs tipo3)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,0,1,4,2,3,0,1,4);
                                    }
                                    else if((x1[3][0]==x1[4][0]) && (x2[1][0]==x2[0][0])){ //abcxx vs xxabc (tipo4 vs tipo1)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,3,4,0,1,2,0,1,2,3,4);
                                    }
                                    else if((x1[3][0]==x1[4][0]) && (x2[1][0]==x2[2][0])){ //abcxx vs axxbc (tipo4 vs tipo2)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,3,4,0,1,2,1,2,0,3,4);
                                    }
                                    else if((x1[3][0]==x1[4][0]) && (x2[2][0]==x2[3][0])){ //abcxx vs abxxc (tipo4 vs tipo3)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,3,4,0,1,2,2,3,0,1,4);
                                    }
                                    else if((x1[3][0]==x1[4][0]) && (x2[3][0]==x2[4][0])){ //abcxx vs abcxx (tipo4 vs tipo4)
                                        nypewin= funcaoanalisenype(valornype1,valornype2,3,4,0,1,2,3,4,0,1,2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (valor1==3){ //análise quando ambos os tipos de carta são do tipo 3-two pair, 2 conjuntos de 2 cartas de igual valor e 1 carta diferente
            if(x1[0][0]==x1[1][0]){  //casos aabbc a aacbb
                valorpar1=valorx1[0];
                valorpar11=valorx1[3];
            }
            else if(x1[1][0]==x1[2][0]){  //caso caabb
                valorpar1=valorx1[1];
                valorpar11=valorx1[3];
            }
            if(x2[0][0]==x2[1][0]){  //aplicação do mesmo processo à segunda mão
                valorpar2=valorx2[0];
                valorpar22=valorx2[3];
            }
            else if(x2[1][0]==x2[2][0]){
                valorpar2=valorx2[1];
                valorpar22=valorx2[3];
                }
            if(valorpar1>valorpar11){  //definição do maior e menor par de cada mao
                maxvalorpar1=valorpar1;
                minvalorpar1=valorpar11;
            }
            else{
                maxvalorpar1=valorpar11;
                minvalorpar1=valorpar1;
            }
            if(valorpar2>valorpar22){
                maxvalorpar2=valorpar2;
                minvalorpar2=valorpar22;
            }
            else{
                maxvalorpar2=valorpar22;
                minvalorpar2=valorpar2;
            }
            if(maxvalorpar1>maxvalorpar2){ //caso o valor das cartas do maior par de um jogador seja maior que o do outro, este vence
                 result=1;
            }
            else if(maxvalorpar1<maxvalorpar2){
                result=2;
            }
            else{  //quando os pares de maior valor de cada jogador sao iguais sao iguais
                if(minvalorpar1>minvalorpar2){ //caso o valor das cartas do menor par de um jogador seja maior que o do outro, este vence
                    result=1;
                }
                else if(minvalorpar1<minvalorpar2){
                    result=2;
                }
                else{  //quando também os pares de menor valor de cada jogador sao iguais sao iguais
                    if(valorx1[0]>valorx2[0]){  //análise pelo valor das cartas uma a uma, da melhor mão, pois estas já se encontram ordenadas por valor
                        result=1;
                    }
                    else if (valorx1[0]<valorx2[0]){
                        result=2;
                    }
                    else if(valorx1[0]==valorx2[0]){
                        if(valorx1[1]>valorx2[1]){
                            result=1;
                        }
                        else if (valorx1[1]<valorx2[1]){
                            result=2;
                        }
                        else if(valorx1[1]==valorx2[1]){
                            if(valorx1[2]>valorx2[2]){
                                result=1;
                            }
                            else if (valorx1[2]<valorx2[2]){
                                result=2;
                            }
                            else if(valorx1[2]==valorx2[2]){
                                if(valorx1[3]>valorx2[3]){
                                    result=1;
                                }
                                else if (valorx1[3]<valorx2[3]){
                                    result=2;
                                }
                                else if(valorx1[3]==valorx2[3]){
                                    if(valorx1[4]>valorx2[4]){
                                        result=1;
                                    }
                                    else if (valorx1[4]<valorx2[4]){
                                        result=2;
                                    }
                                    else if(valorx1[4]==valorx2[4]){
                                        result=0;
                    //verificação do valor do nype das cartas tendo em conta que as cartas se encontram ordenadas por valor e quando o valor é o mesmo, por nype
                    //3 tipos de aparecimento das cartas na mao aabbc=tipo1, caabb=tipo2, aacbb=tipo3 logo podemos ter
                    //tipo1 vs tipo1, tipo1 vs tipo 2, tipo1 vs tipo 3, tipo2 vs tipo 1, tipo 2 vs tipo 2, tipo2 vs tipo3, tipo3 vs tipo1, tipo3 vs tipo2, tipo3 vs tipo3
                    //ordem de análise de nype=o   o tipo1=0,1,2,3,4   o tipo2= 1,2,3,4,0   o tipo3= 0,1,3,4,2
                                        if(((x1[0][0]==x1[1][0]) && (x1[2][0]==x1[3][0]))  ||  ((x2[0][0]==x2[1][0]) && (x2[2][0]==x2[3][0]))){ //tipo1 vs tipo1
                                            nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
                                        }
                                        else if(((x1[0][0]==x1[1][0]) && (x1[2][0]==x1[3][0]))  ||  ((x2[1][0]==x2[2][0]) && (x2[3][0]==x2[4][0]))){ //tipo1 vs tipo2
                                            nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,1,2,3,4,0);
                                        }
                                        else if(((x1[0][0]==x1[1][0]) && (x1[2][0]==x1[3][0]))  ||  ((x2[0][0]==x2[1][0]) && (x2[3][0]==x2[4][0]))){ //tipo1 vs tipo3
                                            nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,3,4,2);
                                        }
                                        else if(((x1[1][0]==x1[2][0]) && (x1[3][0]==x1[4][0]))  ||  ((x2[0][0]==x2[1][0]) && (x2[2][0]==x2[3][0]))){ //tipo2 vs tipo1
                                            nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,4,0,0,1,2,3,4);
                                        }
                                        else if(((x1[1][0]==x1[2][0]) && (x1[3][0]==x1[4][0]))  ||  ((x2[1][0]==x2[2][0]) && (x2[3][0]==x2[4][0]))){ //tipo2 vs tipo2
                                            nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,4,0,1,2,3,4,0);
                                        }
                                        else if(((x1[1][0]==x1[2][0]) && (x1[3][0]==x1[4][0]))  ||  ((x2[0][0]==x2[1][0]) && (x2[3][0]==x2[4][0]))){ //tipo2 vs tipo3
                                            nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,4,0,0,1,3,4,2);
                                        }
                                        else if(((x1[0][0]==x1[1][0]) && (x1[3][0]==x1[4][0]))  ||  ((x2[0][0]==x2[1][0]) && (x2[2][0]==x2[3][0]))){ //tipo3 vs tipo1
                                            nypewin= funcaoanalisenype(valornype1,valornype2,0,1,3,4,2,0,1,2,3,4);
                                        }
                                        else if(((x1[0][0]==x1[1][0]) && (x1[3][0]==x1[4][0]))  ||  ((x2[1][0]==x2[2][0]) && (x2[3][0]==x2[4][0]))){ //tipo3 vs tipo2
                                            nypewin= funcaoanalisenype(valornype1,valornype2,0,1,3,4,2,1,2,3,4,0);
                                        }
                                        else if(((x1[0][0]==x1[1][0]) && (x1[3][0]==x1[4][0]))  ||  ((x2[0][0]==x2[1][0]) && (x2[3][0]==x2[4][0]))){ //tipo3 vs tipo3
                                            nypewin= funcaoanalisenype(valornype1,valornype2,0,1,3,4,2,0,1,3,4,2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (valor1==4){ //análise quando ambos os tipos de carta são do tipo 4-three of a kind, 3 cartas iguais em valor, e as outras 2 diferentes entre si e diferentes destas
            if((x1[0][0]==x1[1][0]) && (x1[1][0]==x1[2][0])){ //POSSIBILIDADES DE TRIO XXXab
                valortrio1=valorx1[0];
            }
            else if((x1[1][0]==x1[2][0]) && (x1[2][0]==x1[3][0])){  //aXXXb
                valortrio1=valorx1[1];
            }
            else if((x1[2][0]==x1[3][0]) && (x1[3][0]==x1[4][0])){  //abXXX
                valortrio1=valorx1[2];
            }
            if((x2[0][0]==x2[1][0]) && (x2[1][0]==x2[2][0])){  //o mesmo procedimento para segunda mão
                valortrio2=valorx2[0];
            }
            else if((x2[1][0]==x2[2][0]) && (x2[2][0]==x2[3][0])){
                valortrio2=valorx2[1];
            }
            else if((x2[2][0]==x2[3][0]) && (x2[3][0]==x2[4][0])){
                valortrio2=valorx2[2];
            }
            if(valortrio1>valortrio2){  //caso o valor das cartas do trio de um jogador seja maior que a do outro, este vence
                result=1;
            }
            else if(valortrio1<valortrio2){
                result=2;
            }
            else if(valortrio1==valortrio2){ //quando valor das cartas dos trios de ambas as mãos forem iguais
                if(valorx1[0]>valorx2[0]){  //análise das restantes cartas por ordem de valor da carta, para decidir a mao vencedora
                    result=1;
                }
                else if (valorx1[0]<valorx2[0]){
                    result=2;
                }
                else if(valorx1[0]==valorx2[0]){
                    if(valorx1[1]>valorx2[1]){
                        result=1;
                    }
                    else if (valorx1[1]<valorx2[1]){
                        result=2;
                    }
                    else if(valorx1[1]==valorx2[1]){
                        if(valorx1[2]>valorx2[2]){
                            result=1;
                        }
                        else if (valorx1[2]<valorx2[2]){
                            result=2;
                        }
                        else if(valorx1[2]==valorx2[2]){
                            if(valorx1[3]>valorx2[3]){
                                result=1;
                            }
                            else if (valorx1[3]<valorx2[3]){
                                result=2;
                            }
                            else if(valorx1[3]==valorx2[3]){
                                if(valorx1[4]>valorx2[4]){
                                    result=1;
                                }
                                else if (valorx1[4]<valorx2[4]){
                                    result=2;
                                }
                                else if(valorx1[4]==valorx2[4]){ //quando estes valores sao iguais nas 2 maos-empate
                                    result=0;
                //verificação do valor do nype das cartas tendo em conta que as cartas se encontram ordenadas por valor e quando o valor é o mesmo, por nype
                //3 tipos de aparecimento das cartas na mao xxxab=tipo1, axxxb=tipo2, abxxx=tipo3 logo podemos ter
                //tipo1 vs tipo1, tipo1 vs tipo 2, tipo1 vs tipo 3, tipo2 vs tipo 1, tipo 2 vs tipo 2, tipo2 vs tipo3, tipo3 vs tipo1, tipo3 vs tipo2, tipo3 vs tipo3
                //ordem de análise de nype=o o tipo1=0,1,2,3,4   o tipo 2= 1,2,3,0,4    o tipo 3= 2,3,4,0,1
                                    if((x1[0][0]==x1[1][0]) && (x1[1][0]==x1[2][0]) && (x2[0][0]==x2[1][0]) && (x2[1][0]==x2[2][0])){   //tipo1 vs tipo1
                                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
                                    }
                                    else if((x1[1][0]==x1[2][0]) && (x1[2][0]==x1[3][0]) && (x2[1][0]==x2[2][0]) && (x2[2][0]==x2[3][0])){   //tipo2 vs tipo2
                                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,0,4,1,2,3,0,4);
                                    }
                                    else if((x1[1][0]==x1[2][0]) && (x1[2][0]==x1[3][0]) && (x2[0][0]==x2[1][0]) && (x2[1][0]==x2[2][0])){   //tipo2 vs tipo1
                                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,0,4,0,1,2,3,4);
                                    }
                                    else if((x1[0][0]==x1[1][0]) && (x1[1][0]==x1[2][0]) && (x2[1][0]==x2[2][0]) && (x2[2][0]==x2[3][0])){   //tipo1 vs tipo2
                                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,1,2,3,0,4);
                                    }
                                    else if((x1[1][0]==x1[2][0]) && (x1[2][0]==x1[3][0]) && (x2[2][0]==x2[3][0]) && (x2[3][0]==x2[4][0])){   //tipo2 vs tipo3
                                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,0,4,2,3,4,0,1);
                                    }
                                    else if((x1[2][0]==x1[3][0]) && (x1[3][0]==x1[4][0]) && (x2[1][0]==x2[2][0]) && (x2[2][0]==x2[3][0])){   //tipo3 vs tipo2
                                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,4,0,1,1,2,3,0,4);
                                    }
                                    else if ((x1[2][0]==x1[3][0]) && (x1[3][0]==x1[4][0]) && (x2[2][0]==x2[3][0]) && (x2[3][0]==x2[4][0])){  //tipo3 contra tipo3
                                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,4,0,1,2,3,4,0,1);
                                    }
                                    else if ((x1[2][0]==x1[3][0]) && (x1[3][0]==x1[4][0]) && (x2[0][0]==x2[1][0]) && (x2[1][0]==x2[2][0])){  //tipo3 contra tipo1
                                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,4,0,1,0,1,2,3,4);
                                    }
                                    else if ((x1[0][0]==x1[1][0]) && (x1[1][0]==x1[2][0]) && (x2[2][0]==x2[3][0]) && (x2[3][0]==x2[4][0])){  //tipo1 contra tipo3
                                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,2,3,4,0,1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (valor1==7){ //análise quando ambos os tipos de carta são do tipo 7-full house, 3 cartas iguais em valor, e as outras 2 iguais entre si e diferentes destas
            if((x1[0][0]==x1[1][0]) && (x1[1][0]==x1[2][0])){ //caso xxxyy, em que o trio está nas primeiras 3 cartas e par nas últimas 2
                valortrio1=valorx1[0];
                valorpar1=valorx1[3];
            }
            else {  //caso xxxyy, em que o par está nas primeiras 2 cartas, e o tri onas últimas 3
                valortrio1=valorx1[3];
                valorpar1=valorx1[0];
            }
            if((x2[0][0]==x2[1][0]) && (x2[1][0]==x2[2][0])){ //o mesmo procedimento para a segunda mão
                valortrio2=valorx2[0];
                valorpar2=valorx2[3];
            }
            else {
                valortrio2=valorx2[3];
                valorpar2=valorx2[0];
            }

            if(valortrio1>valortrio2){ //caso o valor das cartas do trio de um jogador seja maior que a do outro, este vence
                result=1;
            }
            else if(valortrio1<valortrio2){
                result=2;
            }
            else{ //quando valor das cartas dos trios de ambas as mãos forem iguais
                if(valorpar1>valorpar2){ //caso o valor das cartas do par de um jogador seja maior que a do outro, este vence
                    result=1;
                }
                else if(valorpar1<valorpar2){
                    result=2;
                }
                else{ //quando também o valor das cartas dos pares de ambas as mãos forem iguais
                    result=0;
                    //verificação do valor do nype das cartas tendo em conta que as cartas se encontram  ordenadas por valor e quando o valor é o mesmo, por nype
                    //2 tipos de aparecimento das cartas na mao xxxyy=tipo1, yyxxx=tipo2, logo podemos ter
                    //tipo1 vs tipo1, tipo1 vs tipo 2, tipo2 vs tipo 1, tipo 2 vs tipo 2
                    //ordem de análise de nype=o        o tipo1=0,1,2,3,4    o tipo 2= 2,3,4,0,1
                    if((x1[0][0]==x1[1][0]) && (x1[1][0]==x1[2][0]) && (x2[0][0]==x2[1][0]) && (x2[1][0]==x2[2][0])){   //xxxyy contra xxxyy (tipo1 vs tipo1)
                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
                    }
                    else if ((x1[0][0]==x1[1][0]) && (x1[1][0]!=x1[2][0]) && (x2[0][0]==x2[1][0]) && (x2[1][0]!=x2[2][0])){  //yyxxx contra yyxxx (tipo2 vs tipo2)
                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,4,0,1,2,3,4,0,1);
                    }
                    else if ((x1[0][0]==x1[1][0]) && (x1[1][0]!=x1[2][0]) && (x2[0][0]==x2[1][0]) && (x2[1][0]==x2[2][0])){  //yyxxx contra xxxyy (tipo2 vs tipo1)
                        nypewin= funcaoanalisenype(valornype1,valornype2,2,3,4,0,1,0,1,2,3,4);
                    }
                    else if ((x1[0][0]==x1[1][0]) && (x1[1][0]==x1[2][0]) && (x2[0][0]==x2[1][0]) && (x2[1][0]!=x2[2][0])){  //xxxyy contra yyxxx (tipo1 vs tipo2)
                       nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,2,3,4,0,1);
                    }
                }
            }
        }
        else if (valor1==8){ //análise quando ambos os tipos de carta são do tipo 8-four of a kind, 4 cartas iguais em valor dos 4 nypes(peixinho), e uma diferente
            if(x1[0][0]==x1[1][0]){ //caso xxxxy, em que o peixinho está nas primeiras 4 cartas e a carta diferente na última carta
                valorpeixinho1=valorx1[0];
                valorcartasozinha1=valorx1[4];
            }
            else {  //caso yxxxx, em que o peixinho está nas últimas 4 cartas e a carta diferente está na última carta
                valorpeixinho1=valorx1[3];
                valorcartasozinha1=valorx1[0];
            }
            if(x2[0][0]==x2[1][0]){  //o mesmo procedimento para a segunda mão
                valorpeixinho2=valorx2[0];
                valorcartasozinha2=valorx2[4];
            }
            else {
                valorpeixinho2=valorx2[3];
                valorcartasozinha2=valorx2[0];
            }
            if(valorpeixinho1>valorpeixinho2){  //caso o valor das cartas do peixinho de um jogador seja maior que a do outro, este vence
                result=1;
            }
            else if(valorpeixinho1<valorpeixinho2){
                result=2;
            }
            else{   //quando ambos os peixinhos são do mesmo valor
                if(valorcartasozinha1>valorcartasozinha2){  //neste caso, vence a mão cujo valor da carta diferente seja maior
                    result=1;
                }
                else if(valorcartasozinha1<valorcartasozinha2){
                    result=2;
                }
                else{   //irei agora verificar no caso de também o valor das cartas diferentes ser o mesmo, após a atribuição de empate-0, qual a mão preferencial, devido à ordenação de nype
                    result=0;
                    if(((x1[0][0]==x1[1][0]) && (x2[0][0]==x2[1][0]))){  //caso aaaab contra aaaab (tipo 1 vs tipo 1)
                    //verificação do valor do nype das cartas tendo em conta que as cartas se encontram ordenadas por valor
                    //e quando o valor é o mesmo, por nype
                    //2 tipos de aparecimento das cartas na mao aaaab=tipo1, baaaa=tipo2, logo podemos ter
                    //tipo1 vs tipo1, tipo1 vs tipo 2, tipo2 vs tipo 1, tipo 2 vs tipo 2 ordem de análise de nype=o
                    //o tipo1=0,1,2,3,4   o tipo 2= 1,2,3,4,0
                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,0,1,2,3,4);
                    }
                    else if((x1[0][0]!=x1[1][0]) && (x2[0][0]==x2[1][0])){ //caso abbbb contra bbbba (tipo2 vs tipo1)
                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,4,0,0,1,2,3,4);
                    }
                    else if((x1[0][0]==x1[1][0]) && (x2[0][0]!=x2[1][0])){ //bbbba contra abbbb (tipo1 vs tipo 2)
                        nypewin= funcaoanalisenype(valornype1,valornype2,0,1,2,3,4,1,2,3,4,0);
                    }
                    else if((x1[0][0]!=x1[1][0]) && (x2[0][0]!=x2[1][0])){ ////baaaa contra baaaa  (tipo2 vs tipo 2)
                        nypewin= funcaoanalisenype(valornype1,valornype2,1,2,3,4,0,1,2,3,4,0);
                    }
                }
            }
        }
    }
    if (result==1 || nypewin==1){                           //caso vença o jogador 1, ou haja um empate e o tipo de nype das cartas da primeira mão seja alfabeticamente preferenciável ao da segunda mão
        funcaoatribuicartas(carta,x1,0,1,2,3,4,0,1,2,3,4);  //serão colocadas as cartas do jogador 1 no vetor carta, que por passagem por referência será posteriormente utilizado pelo programa
    }
    else if (result==2 || nypewin==2){
        funcaoatribuicartas(carta,x2,0,1,2,3,4,0,1,2,3,4);       //caso vença o jogador 2, ou haja um empate e o tipo de nype das cartas da segunda mão seja alfabeticamente preferenciável ao da primeira mão
    }
    free(valorx1);
    free(valorx2);
    free(valornype1);
    free(valornype2);                                                    //serão colocadas as cartas do jogador 2 no vetor carta, que por passagem por referência será posteriormente utilizado pelo programa
    free2d(x1,10);
    free2d(x2,10);
    return result;  //será retornado um valor inteiro que simboliza 0-empate, 1-vence primeira mão, 2-vence segunda mão
}

