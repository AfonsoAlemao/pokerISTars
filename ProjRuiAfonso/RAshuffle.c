#include "ProjRuiAfonso.h"

typedef struct poker1{
    char cartab[3];
    struct poker1 *next;
    struct poker1 *prev;
}poker1;

poker1 *criacarta(char *strtemp);
poker1 *inserecartanofimdalista(poker1*Listhead, poker1*novacarta );
poker1 *modoinverter(poker1 *Listhead);
poker1 *modointercalar(poker1 *Listhead);
poker1 *modocorte(poker1 *Listhead);

void freelist(poker1*Listhead);

void shuffle(FILE *ponteiroresultados,char *argv[],int argc,int numerocartas,int tamanhostringnomeficheiro){
    FILE *ficheirorecebido;
    poker1 *Listhead=NULL,*novacarta;
    int nbaralhosshuffles=0,i;
    if(argc<3){
        erro();
    }
    tamanhostringnomeficheiro=strlen(argv[2]);
    if(tamanhostringnomeficheiro<9){
        erro();
    }
    if(argv[2][tamanhostringnomeficheiro-8]!= '.' || argv[2][tamanhostringnomeficheiro-7]!='s' || argv[2][tamanhostringnomeficheiro-6]!= 'h' || argv[2][tamanhostringnomeficheiro-5]!='u' || argv[2][tamanhostringnomeficheiro-4]!= 'f'|| argv[2][tamanhostringnomeficheiro-3]!= 'f'|| argv[2][tamanhostringnomeficheiro-2]!= 'l'|| argv[2][tamanhostringnomeficheiro-1]!= 'e'){
        erro();
    }
    if((ficheirorecebido=fopen(argv[2],"r"))==NULL){
        erro();
    }
    char **baralhar123;
    if((baralhar123=(char**)calloc(1,sizeof(char*)))==NULL){
        erro();
    }
    int v=0;
    char strtemp[3];
    numerocartas=0;
    while(fscanf(ficheirorecebido,"%s",strtemp)!=EOF){ //strtemp vai conter  os numeros dos modos do shuffle e as cartas
        if(nbaralhosshuffles==1){
            fprintf(ponteiroresultados,"\n");
        }
        nbaralhosshuffles=0;
        if((!(strcmp(strtemp,"1")))||(!(strcmp(strtemp,"2")))||(!(strcmp(strtemp,"3")))){
            v++;
            if(numerocartas%52==0 && numerocartas!=0){
                numerocartas=0;
                if((baralhar123=(char**)calloc(1,sizeof(char*)))==NULL){
                    erro();
                }
                v=1;
            }
            if((baralhar123=(char**)realloc(baralhar123,v*sizeof(char*)))==NULL){
                erro();
            }
            if((baralhar123[v-1]=(char*)calloc(2,sizeof(char)))==NULL){
                erro();
            }
            strncpy(baralhar123[v-1],strtemp,2); //baralhar123 vai conter  os numeros correspondentes aos modos de baralhar
        }
        else{
            numerocartas++;
            novacarta= criacarta(strtemp);
            Listhead=inserecartanofimdalista(Listhead,novacarta);
            if(numerocartas%52==0 && numerocartas!=0){
                for(i=0;i<v;i++){
                    if(strcmp(baralhar123[i],"1")==0){ //ativa modo 1
                        modointercalar(Listhead);
                    }
                    else if(strcmp(baralhar123[i],"2")==0){ //ativa modo 2
                        modoinverter(Listhead);
                        modointercalar(Listhead);
                    }
                    else if(strcmp(baralhar123[i],"3")==0){ //ativa modo 3
                        modocorte(Listhead);
                    }
                }
                poker1 *Aux1; //apresenta o baralho de cartas final em grupos de 13
                for(i=0,Aux1=Listhead;i<13;i++,Aux1=Aux1->next){
                    fprintf(ponteiroresultados,"%s ",Aux1->cartab);
                }
                fprintf(ponteiroresultados,"\n");
                for(i=0;i<13;i++,Aux1=Aux1->next){
                    fprintf(ponteiroresultados,"%s ",Aux1->cartab);
                }
                fprintf(ponteiroresultados,"\n");
                for(i=0;i<13;i++,Aux1=Aux1->next){
                    fprintf(ponteiroresultados,"%s ",Aux1->cartab);
                }
                fprintf(ponteiroresultados,"\n");
                for(i=0;i<13;i++,Aux1=Aux1->next){
                    fprintf(ponteiroresultados,"%s ",Aux1->cartab);
                }
                fprintf(ponteiroresultados,"\n");
            freelist(Listhead);
            free2d(baralhar123,v);
            nbaralhosshuffles=1;
            Listhead=NULL; //o ponteiro da List Head passa apontar pra NULL para que depois se possa voltar a utilizá-lo no proximo baralho
            }
        }
    }
    fprintf(ponteiroresultados,"\n");
    fclose(ficheirorecebido);
    return;
}

poker1 *criacarta(char *strtemp){ //usaram-se listas duplamente ligadas
    poker1 *carta1;
    if((carta1=(poker1*) calloc(1,sizeof(poker1)))==NULL){
        printf("-1\n");
        return 0;
    }
    strncpy(carta1->cartab,strtemp,3);
    carta1->prev=NULL;
    carta1->next=NULL;
    return carta1;
}

poker1 *inserecartanofimdalista(poker1*Listhead, poker1*novacarta ){
    poker1 *Aux;
    if(Listhead == NULL){
        Listhead = novacarta;
    }
    else{
        Aux = Listhead;
        while(Aux->next != NULL){
            Aux = Aux->next;
        }
        Aux->next =novacarta;
        novacarta->prev = Aux;
    }
    return Listhead;
}
poker1 *modocorte(poker1 *Listhead){
    poker1 *Aux1,*Aux2 ;
    char palavra[3];
    int i;
    Aux1=Listhead;
    Aux2=Listhead;
    for(i=0;i<26;i++,Aux1=Aux1->next); //O Aux1 vai ser o ponteiro que aponta pra estrutura que contem a carta 52

    for(i=0;i<26;i++,Aux2=Aux2->next,Aux1=Aux1->next){
        // o valor das cartas estrutura Aux1 trocam pelo valor das cartas da estrutura Aux2
        strncpy(palavra,Aux1->cartab,3);
        strncpy(Aux1->cartab,Aux2->cartab,3);
        strncpy(Aux2->cartab,palavra,3);
    }
    return Listhead;
}

poker1 *modointercalar(poker1 *Listhead){
    poker1 *Aux1,*Aux2,*Aux3,*Aux4;
    int i;
    Aux2=Listhead;
    for(i=0;i<=25;i++,Aux2=Aux2->next);
    Aux1=Listhead;
    for(i=0;i<=25;i++,Aux1=Aux4){
        //insere um dos elementos da segunda metade no meio de dois da primeira
        Aux3=Aux2->next; //guarda o valor de Aux2->next
        Aux4=Aux1->next; //guarda o valor de Aux1->next
        //insere uma nova estrutura entre outras duas
        Aux2->next=Aux1->next;
        Aux2->prev=Aux1;
        (Aux1->next)->prev=Aux2;
        Aux1->next=Aux2;
        if(Aux3!=NULL){
            Aux2=Aux3; //atualiza o valor de Aux2 (este passa a ter o valor de Aux2->next)
        }
    }
    Aux2->next=NULL;
    return Listhead;

}

poker1 *modoinverter(poker1 *Listhead){
    poker1 *Aux1,*Aux2;
    int i;
    char palavra[3];

    for(i=0,Aux1=Listhead;i<26;i++,Aux1=Aux1->next); //Aux1 vai conter o ponteiro que aponta pra estrutura que tem o valor da carta 26
    for(Aux2=Listhead,i=0;i<51;i++,Aux2=Aux2->next);  //Aux2 vai conter o ponteiro que aponta pra estrutura que tem o valor da carta 52

    for(i=0;i<13;Aux1=Aux1->next,Aux2=Aux2->prev,i++){
        strncpy(palavra,Aux1->cartab,3);
        strncpy(Aux1->cartab,Aux2->cartab,3);
        strncpy(Aux2->cartab,palavra,3);
    }
    return Listhead;
}

void freelist(poker1*Listhead){
    poker1 *Aux;
    Aux=Listhead;
    while(Listhead!=NULL){
        Aux= Listhead;
        Listhead=(Listhead->next);
        free(Aux);
    }
    return;
}
