#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef char Stringa[20];

typedef struct Indirizzo{
    
        int val;            //valore del bit
        int host;           //1 se HOST, 0 se Prefisso
}IND;


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

void convertiIndirizzoInVet(int A, int B, int C, int D, IND *vet)            //da migliorare--->utilizzo di un array invece di 4 ottetti
                                                                                                        //poichè le operzioni sono uguali-->controllo per vedere il range in cui mi trovo e setto la variabile da convertitre in binario
{
    int i=31;
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
void stampaConversioneIndirizzo(IND *vet)
{
    printf("\n__________________INDIRIZZO IP IN BINARIO_____________________\n");
    for(int i=0; i<=31; i++)            
    {
       if(i==7 || i==15 || i==23)       //bit separatori degli ottetti
       {
           printf("  %d  .",vet[i].val);
       }
       else
       {
           printf(" %d  ", vet[i].val);
       }
    }
    printf("\n\n\n");
}
int valDecimale(int x, int g, int indice)
{
    return pow(2, x+(7*g)-indice);
}
/*Conversione del vettore di bit indirizzo in decimale*/
/*Regola della conversione--->valBit * 2^(x+(7*g) - indice)
 * 1°otetto--->x=0;  g=1
 * 2°ottetto-->x=1; g=2
 * 3°ottetto-->x=2; g=3
 * 4°ottetto--->x=3; g=4
 *  
 * */
int * convertiDecimaleDaBinario(IND *vet, int *out)
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
                out[0]+=valDecimale(0,1,i);
            }
            if(i<=15 && i>=8)       //secondo ottetto x=1, g=2
            {
                out[1]+=valDecimale(1,2,i);
            }
            if(i<=23 && i>=16)
            {
                out[2]+=valDecimale(2,3,i);
            }
            if(i<=31 && i>=24)
            {
                out[3]+=valDecimale(3,4,i);
            }
        }
    }
    
    printf("\n  [   %d  ][   %d   ][   %d   ][   %d   ]\n\n",out[0],out[1],out[2],out[3] );
    return out;
}


void calcoloPrefisso ( IND * vetInd, int * vet_Net, IND * out)
{
    
    for(int i=0;i<32; i++)
    {
        out[i].val=vetInd[i].val&&vet_Net[i];
    }
  
}
int main(int n , char *vet[])
{
        int ott1,ott2,ott3,ott4,netMask;        //valore decimale del primo ottetto
        int k=1;
        IND  vet_ind[32];
        for(int i=0;i<32;i++)
        {
            vet_ind[i].val=0;
        }
        int vet_net[32];
 
        printf("\nInserisci il valore del %d Otetto: ", k);
        scanf("%d", &ott1);
        getchar();
        printf("\n");
        k++;
          printf("\nInserisci il valore del %d Otetto: ", k);
        scanf("%d", &ott2);
        printf("\n");
        k++;
          printf("\nInserisci il valore del %d Otetto: ", k);
        scanf("%d", &ott3);
        printf("\n");
        k++;
          printf("\nInserisci il valore del %d Otetto: ", k);
        scanf("%d", &ott4);
        printf("\n");
          printf("\nInserisci il valore della netmask: ");
        scanf("%d", &netMask);
        
        printf("\nIP-->%d . %d . %d . %d / %d\n", ott1,ott2,ott3,ott4, netMask);
        
        convertiNetMask(netMask,vet_net);       //conversione netmask in vettore contiguo di 1 e 0
        
        stampaNetMask(vet_net);                     //stampa vettore netmask
        
        convertiIndirizzoInVet(ott1,ott2,ott3,ott4, vet_ind);   //da decimale a binario
        
        stampaConversioneIndirizzo(vet_ind);        //stampa da decimale a binario
        
        int indirizzo[4];
      convertiDecimaleDaBinario(vet_ind,indirizzo);  //da binario a decimale
        
       
        
        IND prefissoBin [32];
       calcoloPrefisso(vet_ind,vet_net, prefissoBin);
        int prefissoDec[4];
        convertiDecimaleDaBinario(prefissoBin,prefissoDec);
        printf("\n\nNET--->%d  . %d  . %d  . %d  ", prefissoDec[0],prefissoDec[1],prefissoDec[2],prefissoDec[3]);
        
        
        
}
