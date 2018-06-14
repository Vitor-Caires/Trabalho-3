//
//  main.c
//  Trabalho 3
//
//  Created by Vitor Caires on 13/06/18.
//  Copyright © 2018 Vitor Caires. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct celula {
    unsigned long posm;
    unsigned long posn;
    float valor;
    struct celula *prox;
};

typedef struct celula cell;

long somaM = 0;
long somaN = 0;
cell *p1;
cell *ptemp;
void addcellREC(cell *point,unsigned long M,unsigned long N, float VALOR);
void addinfo(cell *POINTADD,unsigned long M,unsigned long N, float VALOR);
long consultaValor(cell *POINTCONSULTA,unsigned long M,unsigned long N);
long Soma(cell *POINTCSOMA,unsigned long M,unsigned long N);
void BREAKFREE(cell *POINTFREE);

int main(int argc, const char * argv[]) {
    
    int exist = 0;
    float valore = 0;
    unsigned long m=0, n=0;
    long mMAX = 0;
    long nMAX = 0;
    int FIMFLAG = 0;
    int menuselect = 0;
    void menu(void);
    
    p1 = malloc(sizeof(cell));
    if(p1 == NULL){
        printf("Erro na alocacao de memoria!! \n");
        return 0;
    }else{
        p1 -> prox = NULL;
    }
    while(FIMFLAG == 0){
        menu();
        setbuf(stdin,0);
        scanf("%d",&menuselect);
        switch (menuselect) {
                
            case 1:
                if(exist == 0){
                setbuf(stdin, 0);
                printf("Digite o valor de m da sua matriz: \n");
                scanf("%ld",&mMAX);
                setbuf(stdin, 0);
                printf("Digite o valor de n da sua matriz: \n");
                scanf("%ld",&nMAX);
                nMAX--;
                mMAX--;
                printf("Matriz criada! \n");
                    exist = 1;
                }else{
                    printf("Matriz ja existente! \n");
                }
                break;
                
            case 2:
                if(exist == 1){
                printf("Liberando matriz... \n");
                BREAKFREE(p1);
                if(p1 -> prox == NULL){
                    exist = 0;
                    printf("Matriz deletada! \n");
                }else{
                    printf("Erro ao deletar matriz");
                }
                }else{
                    printf("Sem matriz para deletar.. \n");
                }
                
            case 3:
                setbuf(stdin, 0);
                while(1){
                    printf("Indique m para consulta: \n");
                    scanf("%ld",&m);
                    if(m <= mMAX){break;
                    }else{ printf("m exede o m maximo! Tente novamente \n");}
                }
                setbuf(stdin, 0);
                while(1){
                    printf("Indique n para consulta: \n");
                    scanf("%ld",&n);
                    if(n <= nMAX){break;
                    }else{ printf("n exede o n maximo! Tente novamente \n");}
                }
                printf("Valor em %ld %ld : %ld \n",m,n,consultaValor(p1, m, n));
                break;
                
            case 4:
                somaN = 0;
                somaM = 0;
                while(1){
                    printf("Indique a linha para consulta: \n");
                    scanf("%ld",&m);
                    if(m <= mMAX){break;
                    }else{ printf("m exede o m maximo! Tente novamente \n");}
                }
                printf("Soma de todos os valores em m: %ld \n",Soma(p1,m,0));
                break;
                
            case 5:
                somaN = 0;
                somaM = 0;
                while(1){
                    printf("Indique a coluna para consulta: \n");
                    scanf("%ld",&n);
                    if(n <= nMAX){break;
                    }else{ printf("n exede o n maximo! Tente novamente \n");}
                }
                printf("Soma de todos os valores em n: %ld \n",Soma(p1,0,n));
                break;
                
            case 6:
                setbuf(stdin, 0);
                while(1){
                    printf("Indique a posicao m: \n");
                    scanf("%ld",&m);
                    if(m <= mMAX){break;
                    }else{ printf("m exede o m maximo! Tente novamente \n");}
                }
                setbuf(stdin, 0);
                while(1){
                    printf("Indique a posicao n: \n");
                    scanf("%ld",&n);
                    if(n <= nMAX){break;
                    }else{ printf("n exede o n maximo! Tente novamente \n");}
                }
                setbuf(stdin, 0);
                printf("Indique o numero em %ld %ld: \n",m,n);
                scanf("%f",&valore);
                if(p1 -> prox == NULL){
                    p1 -> prox = malloc(sizeof(cell));
                    p1 -> posm = m;
                    p1 -> posn = n;
                    p1 -> valor = valore;
                    p1 -> prox -> prox = NULL;
                }else{
                    addcellREC(p1,m,n,valore);
                }
                
                break;
            case 0:
                printf("Fim de programa \n");
                BREAKFREE(p1);
                return 0;
                
            default:
                printf("Algo de errado nao esta certo no menu... \n");
                break;
        }
    }
}

void menu(void){
    printf("\n >>> Aperte para uma tecla para continuar <<< \n\n");
    setbuf(stdin,0);
    getchar();
    printf("1) Criar Matriz \n");
    printf("2) Excluir Matriz \n\n");
    printf("3) Consultar posicao \n\n");
    printf("4) Soma Linha \n");
    printf("5) Soma Coluna \n\n");
    printf("6) Adicionar Valor \n\n");
    printf("0) Fim de programa... \n");
}

void addcellREC(cell *point,unsigned long M,unsigned  long N, float VALOR){
    if((point -> posm == M) && (point -> posn == N)){
        point -> valor = VALOR;
        return;
    }
    if(point -> prox == NULL){
        point -> prox = malloc(sizeof(cell));
        addinfo(point -> prox,M,N,VALOR);
        return;
    }
    return addcellREC(point -> prox,M,N,VALOR);
}

void addinfo(cell *POINTADD,unsigned long M,unsigned long N,float VALOR){
    POINTADD -> posm = M;
    POINTADD -> posn = N;
    POINTADD -> valor = VALOR;
    POINTADD -> prox = NULL;
}

long consultaValor(cell *POINTCONSULTA,unsigned long M,unsigned long N){
    if((POINTCONSULTA -> posn == N)&&(POINTCONSULTA -> posm == M)){
        return POINTCONSULTA -> valor;
    }else{
        if(POINTCONSULTA -> prox == NULL){
            return 0;
        }
        return consultaValor(POINTCONSULTA -> prox,M,N);
    }
}

long consultaSoma(cell *POINTSOMA,unsigned long M,unsigned long N){
    if((POINTSOMA -> posn == N)&&(POINTSOMA -> posm == 0)){
        return POINTSOMA -> valor;
    }
    return consultaSoma(POINTSOMA -> prox,M,N);
}

void BREAKFREE(cell *POINTFREE){
    if(POINTFREE -> prox != NULL){
        ptemp = POINTFREE -> prox;
        POINTFREE -> prox = POINTFREE -> prox -> prox;
        free(ptemp);
        ptemp = NULL;
        return BREAKFREE(p1);
    }else{
        POINTFREE -> posn = 0;
        POINTFREE -> posm = 0;
        POINTFREE -> valor = 0;
        return;
    }
}

long Soma(cell *POINTSOMA,unsigned long M,unsigned  long N){
    if(POINTSOMA -> posm == M){
        somaM += POINTSOMA -> valor;
    }
    if(POINTSOMA -> posn == N){
        somaN += POINTSOMA -> valor;
    }
    if((N == 0)&&(POINTSOMA -> prox == NULL)){
        return somaM;
    }
    if((M == 0)&&(POINTSOMA -> prox == NULL)){
        return somaN;
    }
    return Soma(POINTSOMA -> prox,M,N);
}
