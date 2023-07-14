#include "ProjRuiAfonso.h"

void modosdiandx(FILE *ponteiroresultados,char *argv[],int argc,int numerocartas,int tamanhostringnomeficheiro){
    if(argv[1][2]!='1' && argv[1][2]!= '2' && argv[1][2]!='3' && argv[1][2]!='4' && argv[1][2]!='x'){ //sai se nao for um dos modos esperados
        erro();
    }
    if(argc<3){
        erro();
    }
    tamanhostringnomeficheiro=strlen(argv[2]);
    if(tamanhostringnomeficheiro<6){
        erro();
    }
    if(argv[2][tamanhostringnomeficheiro-5]!= '.' || argv[2][tamanhostringnomeficheiro-4]!='d' || argv[2][tamanhostringnomeficheiro-3]!= 'e' || argv[2][tamanhostringnomeficheiro-2]!='c' || argv[2][tamanhostringnomeficheiro-1]!= 'k'){
        erro();
    } //sai se o ficheiro recebido nao for .deck
    FILE *ficheirorecebido;

    if((ficheirorecebido=fopen(argv[2],"r"))==NULL){ //abre ficheiro .deck
        erro();
    }



    if(argc>3){
        if(strlen(argv[3])!=2){
            erro();;
        }
        if(argv[3][0]=='-' && argv[3][1]=='o'){
            if(argc!=5 ){
                erro();
            }
        }
    }

    if(argv[1][2]=='1'){ //modo d1
        processargruposcincocartas(numerocartas,argv,argc,ponteiroresultados,ficheirorecebido);
    }
    else if(argv[1][2]=='2'){ //modo d2
        processargrupossetecartas(numerocartas,argv,argc,ponteiroresultados,ficheirorecebido);
    }
    else if(argv[1][2]=='3'){ //modo d3
        processargruposnovecartas(numerocartas,argv,argc,ponteiroresultados,ficheirorecebido);
    }
    else if(argv[1][2]=='4'){ //modo d4
        processargruposdezcartas(numerocartas,argv,argc,ponteiroresultados,ficheirorecebido);
    }
    else if(argv[1][2]=='x'){ //modo dx
        torneiodepoker(numerocartas,argv,argc,ponteiroresultados,ficheirorecebido);
    }
    fclose(ficheirorecebido);
    return;
}

void processargruposcincocartas(int numerocartas, char *argv[],int argc, FILE *ponteiroresultados,FILE *ficheirorecebido){ //processa os baralhos lidos, cada um deles em grupos de 5 cartas
    int ncartas=determinanumerocartas(ficheirorecebido);
    int nmaos=(ncartas/52)*(52/5);
    int *resultados;
    resultados=alocarvetorint(nmaos);
    int i=0,j=0,k=0,testefimbaralho, resultadobaralho1[(ncartas/52)*10],numerobaralho=1;
    testefimbaralho=ncartas;
    char **x;
    x=alocarvetor2d(5,3); //vetor para armazenas 5 cartas, que irá armazenas 5 a 5 as cartas dos baralhos e ser utilizado para verificar qual o tipo de mao
    i=0;
    char **cartab;

    do{
        cartab=alocarvetor2d(52,3);
        k=0;
        while(fscanf(ficheirorecebido,"%s",cartab[k])!=EOF && k<51){//memory alocation para as cartas dos baralhos com recutso a string auxiliar para ser possivel ao mesmo tempo saber o numero total de cartas
            k++;
        }

        for(i=i,j=j,k=0;i<(50+52*(numerobaralho-1));i+=5,k=k+5,j++){
            funcaoatribuicartas(x,cartab,0,1,2,3,4,k,k+1,k+2,k+3,k+4); //colocação das cartas do baralho, 5 em 5 no vetor x
            resultadobaralho1[j]=tipodemao(x);
            fprintf(ponteiroresultados,"%d\n",resultadobaralho1[j]);
        }
        testefimbaralho-=52;  //variável de controlo de quantas cartas faltam ler
        i=i+2;
        numerobaralho+=1;
        if(testefimbaralho>51){
            fprintf(ponteiroresultados,"\n");
        }
        free2d(cartab,52);
        cartab=NULL;
    }while(testefimbaralho>51); //verificacao se ainda há baralhos a processar
    free2d(x,5);
    fprintf(ponteiroresultados,"\n");
    estatisticatipodemao(argv,argc,ncartas,5,ponteiroresultados,resultadobaralho1,ficheirorecebido,nmaos,resultados);
    return;
}

void processargrupossetecartas(int numerocartas, char *argv[],int argc,FILE *ponteiroresultados,FILE *ficheirorecebido){ //processa os baralhos lidos, cada um deles em grupos de 7 cartas
    int ncartas=determinanumerocartas(ficheirorecebido);
    int nmaos=(ncartas/52)*(52/7);
    int *resultados;
    resultados=alocarvetorint(nmaos);
    int i=0,j=0,k=0,testefimbaralho, resultadobaralho1[(ncartas/52)*7],numerobaralho=1,cartasiguais=0;
    testefimbaralho=ncartas;
    char **x,**cartab;
    x=alocarvetor2d(7,3); //vetor para armazenas 7 cartas, que irá armazenas 7 a 7 as cartas dos baralhos e ser utilizado para verificar qual o tipo de mao do melhor conjunto de 5 cartas nas 7
    i=0;
    do{
        cartab=alocarvetor2d(52,3);
        k=0;
        while(fscanf(ficheirorecebido,"%s",cartab[k])!=EOF && k<51){//memory alocation para as cartas dos baralhos com recutso a string auxiliar para ser possivel ao mesmo tempo saber o numero total de cartas
            k++;
        }
        for(i=i,k=0,j=j;i<(49+52*(numerobaralho-1));i+=7,k=k+7,j++){
            funcaoatribuicartas(x,cartab,0,1,2,3,4,k,k+1,k+2,k+3,k+4); //colocação das cartas do baralho, 5 em 5 no vetor x
            x[5][0]= cartab[k+5][0];
            x[5][1]= cartab[k+5][1];
            x[5][2]= cartab[k+5][2];
            x[6][0]= cartab[k+6][0];
            x[6][1]= cartab[k+6][1];
            x[6][2]= cartab[k+6][2];
            cartasiguais=verificacartasiguais(cartab,k,k+7);
            if(cartasiguais==1){
                fprintf(ponteiroresultados,"-1\n");
                resultadobaralho1[j]=-1;
            }
            else{
                resultadobaralho1[j]=chamarcartas(x,argv,argc,ponteiroresultados,1);
                fprintf(ponteiroresultados,"%d\n",resultadobaralho1[j]);
            }

        }
        testefimbaralho-=52; //variável de controlo de quantas cartas faltam ler
        i=i+3;
        numerobaralho+=1;
        if(testefimbaralho>51){
        fprintf(ponteiroresultados,"\n");
        }
        free2d(cartab,52);
        cartab=NULL;
    }while(testefimbaralho>51); //verificacao se ainda há baralhos a processar
    free2d(x,7);
    fprintf(ponteiroresultados,"\n");
    estatisticatipodemao(argv,argc,ncartas,7,ponteiroresultados,resultadobaralho1,ficheirorecebido,nmaos,resultados);
    return;
}

void processargruposnovecartas(int numerocartas, char *argv[],int argc,FILE *ponteiroresultados,FILE *ficheirorecebido){ //processa os baralhos lidos, cada um deles em grupos de 9 cartas
    int ncartas=determinanumerocartas(ficheirorecebido);
    int nmaos=2*(ncartas/52)*(52/9);
    int *resultados,k=0;
    resultados=alocarvetorint(nmaos);
    int i=0,j=0,l=0,testefimbaralho, resultadobaralho1[(ncartas/52)*5],numerobaralho=1,cartasiguais=0;
    char **vetorcartas,**vetorcartas1;
    vetorcartas=alocarvetor2d(7,3);
    vetorcartas1=alocarvetor2d(7,3);
    testefimbaralho=ncartas;
    char **x,**cartab;
    x=alocarvetor2d(9,3);  //vetor para armazenas 9 cartas, que irá armazenas 5 a 5 as cartas dos baralhos e ser utilizado para verificar qual o jogador com a melhor mão sas 7 cartas de cada um
    do{
        cartab=alocarvetor2d(52,3);
        k=0;
        while(fscanf(ficheirorecebido,"%s",cartab[k])!=EOF && k<51){//memory alocation para as cartas dos baralhos com recutso a string auxiliar para ser possivel ao mesmo tempo saber o numero total de cartas
            k++;
        }
        for(i=i,k=0,l=l,j=j;i<(45+52*(numerobaralho-1));i+=9,j++,k=k+9,l=l+2){
            funcaoatribuicartas(x,cartab,0,1,2,3,4,k,k+1,k+2,k+3,k+4); //colocação das cartas do baralho, 9 em 9 no vetor x
            funcaoatribuicartas(x,cartab,5,6,7,8,8,k+5,k+6,k+7,k+8,k+8);
            cartasiguais=verificacartasiguais(cartab,k,k+9);
            funcaoatribuicartas(vetorcartas,cartab,0,1,2,3,4,k,k+1,k+4,k+5,k+6); //colocação das cartas do baralho dividindo cada 9 cartas por 7 para cada jogador e vendo o tipo de mao
            funcaoatribuicartas(vetorcartas,cartab,5,6,6,6,6,k+7,k+8,k+8,k+8,k+8);
            funcaoatribuicartas(vetorcartas1,cartab,0,1,2,3,4,k+2,k+3,k+4,k+5,k+6);
            funcaoatribuicartas(vetorcartas1,cartab,5,6,6,6,6,k+7,k+8,k+8,k+8,k+8);
            if(cartasiguais==1){
                fprintf(ponteiroresultados,"-1\n");
                resultadobaralho1[j]=-1;
            }
            else{
                resultadobaralho1[j]=funcaonovecartas(x,argv,argc,ponteiroresultados,1);
                fprintf(ponteiroresultados,"%d\n",resultadobaralho1[j]);
            }

            if(cartasiguais==1){
                resultados[l]=-1;
                resultados[l+1]=-1;
            }
            else{
                resultados[l]=chamarcartas(vetorcartas,argv,argc,ponteiroresultados,0);
                resultados[l+1]=chamarcartas(vetorcartas1,argv,argc,ponteiroresultados,0);
            }
        }
        testefimbaralho-=52; //variável de controlo de quantas cartas faltam ler
        i=i+7;
        numerobaralho+=1;
        if(testefimbaralho>51){
            fprintf(ponteiroresultados,"\n");
        }
        free2d(cartab,52);
        cartab=NULL;
    }while(testefimbaralho>51); //verificacao se ainda há baralhos a processar
    free2d(x,9);
    fprintf(ponteiroresultados,"\n");
    estatisticatipodemao(argv,argc,ncartas,9,ponteiroresultados,resultadobaralho1,ficheirorecebido,nmaos,resultados);
    fprintf(ponteiroresultados,"\n");
    produzdadosintese(argv,ncartas,9,ponteiroresultados,resultadobaralho1,ficheirorecebido);
    free2d(vetorcartas,7);
    free2d(vetorcartas1,7);
    return;
}

void processargruposdezcartas(int numerocartas, char *argv[],int argc,FILE *ponteiroresultados,FILE *ficheirorecebido){ //processa os baralhos lidos, cada um deles em grupos de 10 cartas
    int ncartas=determinanumerocartas(ficheirorecebido);
    int nmaos=2*(ncartas/52)*(52/10);
    int i=0,j=0,k=0,l=0,testefimbaralho, resultadobaralho1[(ncartas/52)*5],numerobaralho=1,cartasiguais1=0,cartasiguais=0;
    testefimbaralho=ncartas;
    int *resultados;
    resultados=alocarvetorint(nmaos);
    char **x,**cartab;
    x=alocarvetor2d(10,3); //vetor para armazenas 10 cartas, que irá armazenas 10 a 10 as cartas dos baralhos e ser utilizado para verificar qual o jogador com a melhor mão
    char **vetorcartas;
    vetorcartas=alocarvetor2d(7,3);

    do{
        cartab=alocarvetor2d(52,3);
        k=0;
        while(fscanf(ficheirorecebido,"%s",cartab[k])!=EOF && k<51){//memory alocation para as cartas dos baralhos com recutso a string auxiliar para ser possivel ao mesmo tempo saber o numero total de cartas
            k++;
        }
        for(i=i,j=j,l=l,k=0;i<(50+52*(numerobaralho-1));k=k+10,i+=10,j++,l=l+2){
            funcaoatribuicartas(x,cartab,0,1,2,3,4,k,k+1,k+2,k+3,k+4); //colocação das cartas do baralho, 10 em 10 no vetor x
            funcaoatribuicartas(x,cartab,5,6,7,8,9,k+5,k+6,k+7,k+8,k+9);
            cartasiguais1=verificacartasiguais(cartab,k,k+5);
            cartasiguais=verificacartasiguais(cartab,k+5,k+10);
            cartasiguais=cartasiguais1||cartasiguais;
            funcaoatribuicartas(vetorcartas,cartab,0,1,2,3,4,k,k+1,k+2,k+3,k+4);
            resultados[l]=tipodemao(vetorcartas);
            funcaoatribuicartas(vetorcartas,cartab,0,1,2,3,4,k+5,k+6,k+7,k+8,k+9);
            resultados[l+1]=tipodemao(vetorcartas);
            if(cartasiguais==1){
                fprintf(ponteiroresultados,"-1\n");
                resultadobaralho1[j]=-1;
            }
            else{
                resultadobaralho1[j]=funcaodezcartas(x);
                fprintf(ponteiroresultados,"%d\n",resultadobaralho1[j]);
            }
        }
        testefimbaralho-=52; //variável de controlo de quantas cartas faltam ler
        i=i+2;
        numerobaralho+=1;
        if(testefimbaralho>51){
            fprintf(ponteiroresultados,"\n");
        }
        free2d(cartab,52);
        cartab=NULL;
    }while(testefimbaralho>51); //verificacao se ainda há baralhos a processar
    free2d(x,10);
    for(i=0;i<nmaos;i++){
        if(resultados[i]==-1){
            if(i%2==1){
                resultados[i-1]=-1;
            }
            else{
                resultados[i+1]=-1;
            }
        }
    }
    fprintf(ponteiroresultados,"\n");
    estatisticatipodemao(argv,argc,ncartas,10,ponteiroresultados,resultadobaralho1,ficheirorecebido,nmaos,resultados);
    fprintf(ponteiroresultados,"\n");
    produzdadosintese(argv,ncartas,10,ponteiroresultados,resultadobaralho1,ficheirorecebido);
    free2d(vetorcartas,7);
}

void estatisticatipodemao(char *argv[],int argc,int numerocartas, int tipodemaoanalizada, FILE *ponteiroresultados, int *resultadobaralho,FILE *ficheirorecebido,int nmaos, int *resultados){ //produz as estatisticas de um dos modos -d1,d2,d3,d4, relativas a freq relativa de cada uma das maos
    int i=0,j=0;
    int *freqabsoluta;
    double *freqrelativa;


    if((freqrelativa=(double*) calloc(11,sizeof(double)))==NULL){
        erro();
    }
    freqabsoluta=alocarvetorint(11);

    if(resultados==NULL || freqabsoluta==NULL || freqrelativa==NULL){
        erro();
    }
    if(tipodemaoanalizada==5){ //várias leituras diferentes para tipos diferentes, por ex no d1, o ficheiro já apresenta os tipos de maos, no d3,d4, apresenta os tipos de maos entre strings de cartas e no tipo 10 temos mesmo de ir descobrir qual o tipo de mao novamente pq nao temos essa informaçao no ficheiro
        for(i=0;i<nmaos;i++){
            resultados[i]=resultadobaralho[i];
        }
    }
    if(tipodemaoanalizada==7){
        for(i=0;i<nmaos;i++){
            resultados[i]=resultadobaralho[i];
        }
    }

    for(i=0;i<nmaos;i++){  //através da comparacao com o vetor resultados, atribuicao da freq absoluta para os diferentes tipos de mao
        for(j=1;j<=10;j++){
            if(resultados[i]==j){
                freqabsoluta[j]++;
            }
        }
        if(resultados[i]==-1){
            freqabsoluta[0]++;
        }
    }
    for(i=0;i<=10;i++){
        freqrelativa[i]=(double) freqabsoluta[i]/nmaos; //calculo freq relativa
    }

    fprintf(ponteiroresultados,"-1 %.2E\n",freqrelativa[0]);    //producao de output
    for(i=1;i<=10;i++){
        fprintf(ponteiroresultados,"%d %.2E\n",i,freqrelativa[i]);
    }
    free(freqrelativa);
    free(freqabsoluta);
    free(resultados);

    return;
}

void produzdadosintese(char *argv[],int numerocartas, int tipodemaoanalizada,FILE *ponteiroresultados,int *resultadobaralho,FILE *ficheirorecebido){ //funcao que para os modos d3 e d4 produz a estatistica de vitórias e empates
    int nmaos,i,j=0;
    nmaos=(numerocartas/52)*(52/tipodemaoanalizada);
    int *resultados,*freqabsoluta;
    resultados=alocarvetorint(nmaos);
    freqabsoluta=alocarvetorint(3);
    if(resultados==NULL || freqabsoluta==NULL){
        erro();
    }
    i=0;
    if(tipodemaoanalizada==9){
        for(i=0;i<nmaos;i++){
            resultados[i]=resultadobaralho[i];
        }
    }
    else if(tipodemaoanalizada==10){ //leitura dos resultados dos confrontos
        for(i=0;i<nmaos;i++){
            resultados[i]=resultadobaralho[i];
        }
    }

    for(i=0;i<nmaos;i++){ //estatistica dos resultados, -1 é empate (0)
        for(j=0;j<=2;j++){
            if(resultados[i]==j){
                freqabsoluta[j]++;
            }
        }
        if(resultados[i]==-1){
            freqabsoluta[0]++;
        }
    }

    for(i=0;i<=2;i++){ //output da estatistica de quem ganhou
        fprintf(ponteiroresultados,"%d %d\n",i,freqabsoluta[i]);
    }
    free(resultados);
    free(freqabsoluta);
    return;
}

void torneiodepoker (int numerodecartas,char *argv[],int argc, FILE *ponteiroresultados, FILE *ficheirorecebido){ //simulacao de um jogo de poker
    int i=0,j=0,k=0,l=0,testecartasfimbaralho,numerovencedores=0,numeromelhores,result=0,numerodemaosganhadoras,controlo=0,numerodemaosganhadorasparacalculo,numerocartasdistribuidas;
    double *pontuacoes;
    pontuacoes=alocarvetordouble(8);
    char ***cartajogador,***iniciocartajogador; //vetor para armazenar as cartas de cada jogador
    cartajogador=alocarvetor3d(8,7,3);
    iniciocartajogador=cartajogador;
    char ***melhorescincocartas;  //vetor para armazenas as 5 melhores cartas de cada jogador
    melhorescincocartas=alocarvetor3d(8,5,3);
    int ncartas=determinanumerocartas(ficheirorecebido);
    numerodecartas=ncartas;

    testecartasfimbaralho=numerodecartas;

    int *vencedores,*valormaojog,*fold,*maosganhadoras,*fazfold, *acumuladorfolds, *acumuladoridasajogo;
    fazfold=alocarvetorint(8);  //sinal que obriga jogador a fazer fold nesta ronda
    vencedores=alocarvetorint(8); //vetor que guarda os vencedores da ronda
    valormaojog=alocarvetorint(8); //vetor que guarda os valores das maos de cada jogador na ronda
    fold=alocarvetorint(8); //sinal se o jogador faz ou nao fold esta ronda
    acumuladorfolds=alocarvetorint(8);
    acumuladoridasajogo=alocarvetorint(8);
    numerodemaosganhadoras=numerodecartas/52;
    numerodemaosganhadorasparacalculo=numerodemaosganhadoras;
    maosganhadoras=alocarvetorint(numerodemaosganhadoras);

    char **vetorparaalteracoes,**cartab;
    vetorparaalteracoes=alocarvetor2d(10,3);
    do{
        l=0;
        cartab=alocarvetor2d(52,3);
        k=0;
        while(fscanf(ficheirorecebido,"%s",cartab[k])!=EOF && k<51){//memory alocation para as cartas dos baralhos com recutso a string auxiliar para ser possivel ao mesmo tempo saber o numero total de cartas
            k++;
        }
        i=numerodecartas-testecartasfimbaralho;
        if(i!=0 && controlo==0){ //espaço entre baralhos diferentes
            fprintf(ponteiroresultados,"\n");
        }
        for(j=0;j<8;j++){ //limpar fold da jogada anterior mas não acumuladores de folds que vão ditar se o jogador recebe ou não as faltas
            fold[j]=0;
            fazfold[j]=0;
            vencedores[j]=0;
        }

        for(j=0;j<8;j++){ //caso jogador tenha feito fold nas ultimas 4 jogadas, tem de ir a jogo
            valormaojog[j]=0;
            if(acumuladorfolds[j]==4){
                fold[j]=0;
                acumuladorfolds[j]=0;
                fazfold[j]=1;
            }
            else if(acumuladoridasajogo[j]==2){ //caso jogador tenha ido a jogo nas ultimas 2 jogadas, tem de fazer fold e nao recebe cartas
                fold[j]=1;
                acumuladoridasajogo[j]=0;

            }
        }
        for(j=0;j<8;j++){ //se nao tiver com fold=0, jogador vai a jogo e recebe 2 cartas do baralho
            if(fold[j]==1){
                l=l-2;
            }
            else{
                funcaoatribuicartas(cartajogador[j],cartab,0,1,1,1,1,l,l+1,l+1,l+1,l+1);
            }
            l=l+2;
        } //atribuir cartas a cada jogador
        numerocartasdistribuidas=l;

        for(j=0;j<8;j++){ //5 cartas seguintes, são as cartas da mesa, para todos os jogadores
           if(fold[j]==0){
                funcaoatribuicartas(cartajogador[j],cartab,2,3,4,5,6,numerocartasdistribuidas,numerocartasdistribuidas+1,numerocartasdistribuidas+2,numerocartasdistribuidas+3,numerocartasdistribuidas+4);
            }
        }

        for(j=0;j<8;j++){
            funcaoatribuicartas(vetorparaalteracoes,cartajogador[j],0,1,2,3,4,0,1,2,3,4);
            funcaoatribuicartas(vetorparaalteracoes,cartajogador[j],5,6,2,3,4,5,6,2,3,4);
            valormaojog[j]=chamarcartas(vetorparaalteracoes,argv,argc,ponteiroresultados,0); //calculo do tipo de mao de cada jogador
            funcaoatribuicartas(melhorescincocartas[j],vetorparaalteracoes,0,1,2,3,4,0,1,2,3,4);
            if(valormaojog[j]<(j+1) && fazfold[j]!=1){ //caso tipo de mao seja menor que o indice do jogador este sai da jogada
                fold[j]=1;
                acumuladorfolds[j]++;
                acumuladoridasajogo[j]=0;
            }
            if(fold[j]==0){ //há aqui uma regulacao com acumuladores dos folds/idas a jogo dos jogadores
                acumuladoridasajogo[j]++;
                acumuladorfolds[j]=0;
                fprintf(ponteiroresultados,"%d ",j+1);
                fprintf(ponteiroresultados,"%s %s %s %s %s ",vetorparaalteracoes[0],vetorparaalteracoes[1],vetorparaalteracoes[2],vetorparaalteracoes[3],vetorparaalteracoes[4]);
                fprintf(ponteiroresultados,"%d\n",valormaojog[j]); //output das maos dos jogadores que foram a jogo neste ronda
            }
            else if(fold[j]==1){
                valormaojog[j]=0;
            }
        }
        numeromelhores=playerstofinalconfront(valormaojog,vencedores); //verificacao de quais os jogadores com o tipo de carta max, para depois os confrontar entre si
        numerovencedores=numeromelhores;
        int bitsailoop=0;
        if(numerovencedores>0){
            if(numerovencedores>1){ //os jogadores com a mão de maior valor serão confrontados, vencedores fica apenas com os vencedores finais da ronda
                confronto(bitsailoop,vencedores,cartajogador,argc,argv,ponteiroresultados,result,vetorparaalteracoes,numerovencedores);
                for(i=0;vencedores[i]!=0;i++);
                numerovencedores=i;
            }
            fprintf(ponteiroresultados,"W %s %s %s %s %s",melhorescincocartas[vencedores[0]-1][0],melhorescincocartas[vencedores[0]-1][1],melhorescincocartas[vencedores[0]-1][2],melhorescincocartas[vencedores[0]-1][3],melhorescincocartas[vencedores[0]-1][4]);
            fprintf(ponteiroresultados," %d %d",valormaojog[vencedores[0]-1],vencedores[0]); //output vencedor, em caso de empate do jogador vencedor com menor indice
            maosganhadoras[(numerodecartas-testecartasfimbaralho)/52]=valormaojog[vencedores[0]-1];
            if(numerovencedores>1){
                for(i=1;i<numerovencedores;i++){ //print do indice dos outros vencedores
                     fprintf(ponteiroresultados," %d",vencedores[i]);
                }
            }
            fprintf(ponteiroresultados,"\n");
            for(i=0;i<numerovencedores;i++){
                pontuacoes[vencedores[i]-1]+=(double)1/numerovencedores;
            } //atribuicao de pontuacao a cada jogador tendo em conta a atual ronda

        }
        numerovencedores=0;
        controlo= fold[0]&&fold[1]&&fold[2]&&fold[3]&&fold[4]&&fold[5]&&fold[6]&&fold[7];  //controla se nesta ronda houve vencedores
        if(controlo==1){
            numerodemaosganhadorasparacalculo--;
        }
        testecartasfimbaralho-=52; //variavel que deteta se ha mais baralhos a ler, ou seja, se ha mais rondas a serem jogadas
        free2d(cartab,52);
        cartab=NULL;
    }while(testecartasfimbaralho>51);
    if(controlo==0){
        fprintf(ponteiroresultados,"\n");
    }
    estatisticamaoganhadora(maosganhadoras,numerodemaosganhadoras,numerodemaosganhadorasparacalculo,ponteiroresultados); //estatistica ao longo das rondas da mao que mais venceu
    quadroclassificativo(pontuacoes,ponteiroresultados); //tabela classificativa dos jogadores
    free(vencedores);
    free(valormaojog);
    free(fold);
    free(pontuacoes);
    free(maosganhadoras);
    free(fazfold);
    free(acumuladoridasajogo);
    free(acumuladorfolds);
    free3d(iniciocartajogador,8,7,3);
    free3d(melhorescincocartas,8,5,3);
    free2d(vetorparaalteracoes,10);
}

void confronto(int bitsailoop,int *vetoraux,char ***cartajogador,int argc,char *argv[],FILE *ponteiroresultados,int result,char **vetorparaalteracoes,int numerovencedores){
    int i,jaretirados=0;
    for(i=0;vetoraux[1]!=0 && bitsailoop==0 && vetoraux[i+1]!=0;i++){
        funcaoatribuicartas(vetorparaalteracoes,cartajogador[vetoraux[0]-1],0,1,4,5,6,0,1,2,3,4);
        funcaoatribuicartas(vetorparaalteracoes,cartajogador[vetoraux[i+1]-1],2,3,7,8,8,0,1,5,6,6);
        result=funcaonovecartas(vetorparaalteracoes,argv,argc,ponteiroresultados,0); //confronto entre 2 jogadores
        if (result==1){
            retiranumerovetor(vetoraux,i+1,8);
            i=-1;
            jaretirados++;
        }
        else if (result==2){
            retiranumerovetor(vetoraux,0,8);
            i=-1;
            jaretirados++;
        }
        if(result==0 && i+2>=numerovencedores){
            bitsailoop=1;
        }
    }

}

int playerstofinalconfront(int *valormaojog,int *vencedores){ //confronta os tipos de mao de todos os jogadores, coloca em vetor os indices dos vencedores e define quantos jogadores possuem o tipo de mao maximo
    int i,j,indicevencedores=0,winner=0, numerovencedores=0;
    for(i=0;i<8;i++){
        if(valormaojog[i]>winner){
            winner=valormaojog[i];
            indicevencedores=0;
            for(j=0;j<8;j++){
                vencedores[j]=0;
            }
            numerovencedores=1;
            vencedores[indicevencedores]=i+1;
            indicevencedores++;
        }
        else if(valormaojog[i]==winner && valormaojog[i]!=0){
            numerovencedores++;
            vencedores[indicevencedores]=i+1;
            indicevencedores++;
        }
    }
    return numerovencedores;
}

void estatisticamaoganhadora(int *maosganhadoras,int numeromaosganhadoras,int numeromaosganhadorasparacalculo,FILE *ponteiroresultados){ //produz uma estatistica para a mao que mais venceu, tendo em conta o n de maos que ganharam e quais foram
    int i,j;
    double *freqabs;
    freqabs=alocarvetordouble(10);
    for(j=1;j<=10;j++){
        for(i=0;i<numeromaosganhadoras;i++){
            if(maosganhadoras[i]==j){
                freqabs[j-1]++;
            }
        }
    }
    for(i=0;i<10;i++){
        fprintf(ponteiroresultados,"%d %.2E\n",i+1,freqabs[i]/numeromaosganhadorasparacalculo);
    }
    free(freqabs);
}

void quadroclassificativo(double *pontuacoes,FILE *ponteiroresultados){ //gera um quadro classificativo ordenado com as pontuacoes de todos os jogadores
    fprintf(ponteiroresultados,"\n");
    int i;
    double aux; //ordenar descrescente
    int *jogadores;
    jogadores=alocarvetorint(8);
    for(i=0;i<8;i++){
        jogadores[i]=i+1;
    }
    for(i=0;i<7;i++){
        if(pontuacoes[i]<pontuacoes[i+1]){
            aux=pontuacoes[i+1];
            pontuacoes[i+1]=pontuacoes[i];
            pontuacoes[i]=aux;
            aux=jogadores[i+1];
            jogadores[i+1]=jogadores[i];
            jogadores[i]=aux;
            i=-1;
        }
    }
    for(i=0;i<8;i++){
        fprintf(ponteiroresultados,"%d %.2lf\n",jogadores[i],pontuacoes[i]);
    }
    free(jogadores);
}


