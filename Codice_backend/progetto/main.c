#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dichiarazioni.h"

int main(int n , char *vet[])
{
        IND address;
        
        //inizializzo il vettore BIT della net a 0
        for(int i=0;i<32;i++)
        {
            address.netBit[i].val=0;
        }
       
        
        //acquisizione IP
        for(int i=0;i<=3;i++)
        {
            printf("\nInserisci il %d ottetto: ", i+1);
            scanf("%d", &address.ipDex[i]);
        }
            //acquisizione NETMASK
          printf("\nInserisci il valore della netmask: ");
        scanf("%d", &address.net);
        address.host=32-address.net;
        
       
        
        convertiNetMask(address.net,address.netmaskBit);       //conversione netmask in vettore di 32 bit contigui di 1 e 0
        
        stampaNetMask(address.netmaskBit);                     //stampa vettore netmask
        
        convertiIndirizzoInVet(address.ipDex, address.netBit);   //conversione dell'indirizzo IP in vettore di bit INDIRIZZO
        
         settaHOSTeNET(address.netBit, address.net);            //settaggio dei bit host e net
        
        stampaConversioneIndirizzo(address.netBit);        //stampa da decimale a binario
        
        int indiri[4];
        convertiDecimaleDaBinario(address.netBit,indiri);  //codifica dei valori del vettore di bit INDIRIZZO in decimale
        
       
        
        BIT prefissoBin [32];           //vettore del PREFISSO
       calcoloPrefisso(address.netBit,address.netmaskBit, prefissoBin);       //calcolod del prefisso
        int prefissoDec[4];
        int broadcast[4];
        convertiDecimaleDaBinario(prefissoBin,prefissoDec);     //conversione del prefisso in decimale

        calcolaBroadcast(address.netBit, broadcast);
         printf("\nIP-->%d . %d . %d . %d / %d", address.ipDex[0],address.ipDex[1],address.ipDex[2],address.ipDex[3], address.net);
        printf("\n\nNET--->%d  . %d  . %d  . %d  ", prefissoDec[0],prefissoDec[1],prefissoDec[2],prefissoDec[3]);
         printf("\n\nBROADCAST--->%d  . %d  . %d  . %d  ", broadcast[0],broadcast[1],broadcast[2],broadcast[3]);
         printf("\nMAX HOST [no broadcast and net]--->%d",massimoHost(address.host));
            
        
        
       
}
