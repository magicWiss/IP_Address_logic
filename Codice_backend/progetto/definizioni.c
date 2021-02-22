#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dichiarazioni.h"
/*INserimento degli 1 relativi al host nel vettore Netmask*/

void convertiNetMask(int mask, int * vet)
{
    for(int i=0;i<32;i++)
    {
        if(mask<=0)
        {
            vet[i]=0;
        }
        else
        {
            vet[i]=1;
        }
        mask--;
    }
}
void stampaNetMask(int * vet)
{
    printf("\n____________VETTORE NETMASK______________________\n");
    for(int i=0;i<32;i++)
    {
        printf("[%d]",vet[i]);
    }
    printf("\n\n");
   
}

/*
 * NON SETTA IL BIT HOST 
 * 
 * */
void convertiIndirizzoInVet(int* Ip, BIT*vet)            //da migliorare--->utilizzo di un array invece di 4 ottetti
                                                                                                        //poichè le operzioni sono uguali-->controllo per vedere il range in cui mi trovo e setto la variabile da convertitre in binario
{
    int i=31;
   int A= Ip[0];            //si necessitano variabili di appoggio poichè la modifica dei valori dell'array risulta essere persistente. 
    int B=Ip[1];            //modificando il valore dell' array dividendo per due, modifico radicalmente il valore del' ip
    int C=Ip[2];
    int D=Ip[3];
    while(i>=0)
    {
        if(i>=24)       //quarto ottetto conversione di D
        {
            vet[i].val=D%2;     //resto
            D=D/2;          //nuovo valore
        }
        if(i>=16 && i<=23)      //terzo ottetto-->conversione di C
        {
             vet[i].val=C%2;     //resto
            C=C/2;          //nuovo valore
           
        }
        if(i>=8 && i<=15)      //terzo ottetto-->conversione di C
        {
             vet[i].val=B%2;     //resto
            B=B/2;          //nuovo valore
           
        }
        if(i>=0 && i<=7)      //terzo ottetto-->conversione di C
        {
             vet[i].val=A%2;     //resto
            A=A/2;          //nuovo valore
        }
        i--;
    }
    
}
/*Stampa del vettore Indirizzi*/
void stampaConversioneIndirizzo(BIT*vet)
{
    printf("\n__________________INDIRIZZO IP IN BINARIO [ X *--->PREFISSO] [ X  ----->HOST_____________________\n");
    for(int i=0; i<=31; i++)            
    {
       if(i==7 || i==15 || i==23)       //bit separatori degli ottetti
       {
           if(vet[i].host==0)
           {
                    printf("  %d * .",vet[i].val);
                    
           }
           else
           {
               printf("  %d  .",vet[i].val);
           }
               
       }
       else
       {
           if(vet[i].host==0)
           {
                    printf(" %d*  ", vet[i].val);
           }
           else
           {
               printf("  %d   ",vet[i].val);
           }
       }
    }
    printf("\n\n\n");
}
int valDecimale(int val,int x, int g, int indice)
{
    return val*pow(2, x+(7*g)-indice);
}
/*Conversione del vettore di bit indirizzo in decimale*/
/*Regola della conversione--->valBit * 2^(x+(7*g) - indice)
 * 1°otetto--->x=0;  g=1
 * 2°ottetto-->x=1; g=2
 * 3°ottetto-->x=2; g=3
 * 4°ottetto--->x=3; g=4
 *  
 * */
int * convertiDecimaleDaBinario(BIT*vet, int *out)
{
    printf("\n_________________CONVERSIONE INDIRIZZO DA BINARIO IN DECIMALE____________________\n");
  
    out[1]=0;   //inizializzazione dei valori di output
    out[0]=0;
    out[2]=0;
    out[3]=0;
    for(int i=0;i<32;i++)
    {
        if(vet[i].val==1)
        {
            if(i<8)         //primo ottetto x=0; g=1
            {
                out[0]+=valDecimale(vet[i].val,0,1,i);
            }
            if(i<=15 && i>=8)       //secondo ottetto x=1, g=2
            {
                out[1]+=valDecimale(vet[i].val,1,2,i);
            }
            if(i<=23 && i>=16)
            {
                out[2]+=valDecimale(vet[i].val,2,3,i);
            }
            if(i<=31 && i>=24)
            {
                out[3]+=valDecimale(vet[i].val,3,4,i);
            }
        }
    }
    
    printf("\n  [   %d  ][   %d   ][   %d   ][   %d   ]\n\n",out[0],out[1],out[2],out[3] );
    return out;
}


void calcoloPrefisso ( BIT* vetInd, int * vet_Net, BIT* out)
{
    
    for(int i=0;i<32; i++)
    {
        out[i].val=vetInd[i].val&&vet_Net[i];
    }
  
}

void settaHOSTeNET(BIT*vet, int num)
{
    for(int i=0;i<32;i++)
    {
        if(num>0)
        {
            vet[i].host=0;
        }
        else
        {
            vet[i].host=1;
        }
        num--;
    }
}

void calcolaBroadcast(BIT* vet, int *out)
{
    
    printf("\n___________________CALCOLO DEL BROADCAST____________________________\n");
    out[1]=0;   //inizializzazione dei valori di output
    out[0]=0;
    out[2]=0;
    out[3]=0;
    for(int i=0;i<32;i++)
    {
        {
            if(i<8)         //primo ottetto x=0; g=1
            {
                if(vet[i].host==0)                                              //se il bit è realtivo al prefisso allora si passa il valore del bit
                {
                    out[0]+=valDecimale(vet[i].val,0,1,i);
                }
                if(vet[i].host==1)
                {
                     out[0]+=valDecimale(1,0,1,i);                          //se il bit è host, ha valore 1
                }
            }
            if(i<=15 && i>=8)       //secondo ottetto x=1, g=2
            {
               if(vet[i].host==0)                                              //se il bit è realtivo al prefisso allora si passa il valore del bit
                {
                    out[1]+=valDecimale(vet[i].val,1,2,i);
                }
                if(vet[i].host==1)
                {
                     out[1]+=valDecimale(1,1,2,i);                          //se il bit è host, ha valore 1
                }
            }
            if(i<=23 && i>=16)
            {
               if(vet[i].host==0)                                              //se il bit è realtivo al prefisso allora si passa il valore del bit
                {
                    out[2]+=valDecimale(vet[i].val,2,3,i);
                }
                if(vet[i].host==1)
                {
                     out[2]+=valDecimale(1,2,3,i);                          //se il bit è host, ha valore 1
                }
            }
            if(i<=31 && i>=24)
            {
                if(vet[i].host==0)                                              //se il bit è realtivo al prefisso allora si passa il valore del bit
                {
                    out[3]+=valDecimale(vet[i].val,3,4,i);
                }
                if(vet[i].host==1)
                {
                     out[3]+=valDecimale(1,3,4,i);                          //se il bit è host, ha valore 1
                }
            }
        }
    }
    
    printf("\n  [   %d  ][   %d   ][   %d   ][   %d   ]\n\n",out[0],out[1],out[2],out[3] );
    
}

int massimoHost(int n)
{
    return pow(2,n)-2;
    
}
