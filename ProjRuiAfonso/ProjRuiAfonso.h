#ifndef ProjRuiAfonso_H_INCLUDED
#define ProjRuiAfonso_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int testecartavalida (char* );
int verificacartasiguais(char **carta,int inicio,int fim);
int tipodemao (char **carta);
int valordamao (char **carta);
int chamarcartas(char **carta,char *argv[],int argc,FILE *ponteiroresultados,int escreveresultados);
int funcaonovecartas(char **carta,char *argv[],int argc,FILE *ponteiroresultados,int enableescrita);
int funcaodezcartas(char **carta);
int valordascartas1(char **carta,int i);
int funcaoanalisenype(int valornype1[10],int valornype2[10],int a1, int a2, int a3, int a4, int a5, int b1, int b2, int b3, int b4, int b5);
void funcaoatribuicartasint(int *x1,int *carta,int a1, int a2, int a3, int a4, int a5, int a6, int a7,int a8, int b1, int b2, int b3, int b4, int b5, int b6, int b7,int b8);
void funcaoatribuicartas(char **x1,char **carta,int a1, int a2, int a3, int a4, int a5, int b1, int b2, int b3, int b4, int b5);
void processargruposcincocartas(int numerocartas, char *argv[],int argc,FILE *ponteiroresultados,FILE *ficheirorecebido);
void processargrupossetecartas(int numerocartas, char *argv[],int argc,FILE *ponteiroresultados,FILE *ficheirorecebido);
void processargruposnovecartas(int numerocartas,char *argv[],int argc,FILE *ponteiroresultados,FILE *ficheirorecebido);
void processargruposdezcartas(int numerocartas, char *argv[],int argc,FILE *ponteiroresultados,FILE *ficheirorecebido);
void estatisticatipodemao(char *argv[],int argc,int numerocartas, int tipodemaoanalizada, FILE *ponteiroresultados, int *resultadobaralho,FILE *ficheirorecebido,int nmaos, int *resultados);
void produzdadosintese(char *argv[],int numerocartas, int tipodemaoanalizada,FILE *ponteiroresultados,int *resultadobaralho,FILE *ficheirorecebido);
void torneiodepoker (int numerodecartas,char *argv[],int argc, FILE *ponteiroresultados, FILE *ficheirorecebido);
void retiranumerovetor(int *vetor, int posicao, int tamanho);
int playerstofinalconfront(int *valormaojog,int *vencedores);
void estatisticamaoganhadora(int *maosganhadoras,int numeromaosganhadoras,int numeromaosganhadorasparacalculo,FILE *ponteiroresultados);
void quadroclassificativo(double *pontuacoes,FILE *ponteiroresultados);
char **alocarvetor2d(int linhas, int colunas);
int* alocarvetorint(int nelementos);
float* alocarvetorfloat(int nelementos);
char*** alocarvetor3d(int a, int b, int c);
void free2d(char** vetor, int linhas);
void free3d(char*** vetor, int a, int b, int c);
void confronto(int bitsailoop,int *vetoraux,char ***cartajogador,int argc,char *argv[],FILE *ponteiroresultados,int result,char **vetorparaalteracoes,int numerovencedores);
double* alocarvetordouble(int nelementos);
void shuffle(FILE *ponteiroresultados,char *argv[],int argc,int numerocartas,int tamanhostringnomeficheiro);
void modosdiandx(FILE *ponteiroresultados,char *argv[],int argc,int numerocartas,int tamanhostringnomeficheiro);
int modoc(FILE *ponteiroresultados,char *argv[],int argc,int numerocartas,int tamanhostringnomeficheiro);
int valornype(char **carta,int i);
void erro();
int determinanumerocartas(FILE *ficheirorecebido);

#endif // ProjRuiAfonso_H_INCLUDED
