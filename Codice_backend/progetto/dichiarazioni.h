#ifndef DICHIARAZIONE_H
#define DICHIARAZIONE_H

typedef char Stringa[30];

/*STRUTTURA DATI PER IL VETTORE INDIRIZZO IP*/
/*
 * 
 * val-->valore del bit
 * host-->1 se bit è host
 *              0 se bit è net
 */
typedef struct bit
{
    int val;
    int host;
}BIT;

typedef struct  indirizzo
{
    BIT netBit[32];         //vettore bit dell' address
    int netmaskBit[32];     //vettore in bit della netmask
    int ipDex[4];               //vettore in decimale dell'address (ES. 123.11.222.121)
    int netMaskDex[4];      //vettore in decimale della netmask  (Es. 255.255.0.0)
    int host;                 //numero bit per host
    int net;                  //numero di bit per net  
}IND;

/*
 * CREAZIONE DEL VETTORE NETMASK
 * ->Crea un vettore di 32 inserendo un numero di 1 contigui pari a mask, i restanti 32-mask=0 [HOST]
 */
void convertiNetMask(int mask, int * vet);

/*
 * STAMPA DEL VETTORE NETMASK
 */
void stampaNetMask(int * vet);

/*CREAZIONE DEL VETTORE INDIRIZZO IP__________________[versione base, non setta il bit ad essere host o net]
 * Prende in input il vettore degli indirizzi inserito da tastiera e in modo iterativo inveso (da 31 a 0) ne effettua la conversione in binario
 * inserendo i bit nelle porzioni definite per ogni singolo otetto.
 * ----------------------------------------------
 * ARRAY INDIRIZZO IP
 * |0 1 2 3 4 5 6 7|| 8 9 10 11 12 13 14 15 || 16 17 18 19 20 21 22 23 || 24 25 26 27 28 29 30 31| 
 * primo ottetto        secondo ottetto             terzo ottetto                       quarto ottetto
 * ----------------------------------------------------------
 */
 void convertiIndirizzoInVet(int* Ip, BIT *vet) ;
 
 /*
  * STAMPA DEL VETTORE INIDIRIZZO IP
  * Segna i bit net con *
  */
 void stampaConversioneIndirizzo(BIT *vet);

/*FUNZIONE AUSILIARE PER CONVERSIONE DI BIT IN DECIMALE
 * Segue la regola out=2^(x+(7*g)-indice
 */
int valDecimale(int val,int x, int g, int indice);

/*CONVERSIONE VETTORE INDIRIZZI IN DECIMALE */
/*Regola della conversione--->valBit * 2^(x+(7*g) - indice)
 * 1°otetto--->x=0;  g=1
 * 2°ottetto-->x=1; g=2
 * 3°ottetto-->x=2; g=3
 * 4°ottetto--->x=3; g=4
 *  
 * */
int * convertiDecimaleDaBinario(BIT *vet, int *out);

/*
 * CALCOLO DEL PREFISSO ASSOCIATO AD UN INDIRIZZO IP
 * Genera un vettore di tipo IND* i cui valori sono dati dall'operazione AND bit a bit del vettore NETMASK e il vettore INDIRIZZI
 * Su questo si calcolca il prefisso invocando la funzione "convertiDecimaleDaBinario"
 */
 void calcoloPrefisso ( BIT * vetInd, int * vet_Net, BIT * out);
 
 
 /*
  * SETTAGGIO DEI BIT HOST e NET relativo al vettore INDIRIZZI
  */
void settaHOSTeNET(BIT *vet, int num);

/*CALCOLO DEL BROADCAST
 * itero su tutto il vettore indirizzo.
 * Se il bit è net allora exp(valoreBit, x, g, indice)
 * se il bit è host allora exp(1,x,g, indice)
 */
 void calcolaBroadcast(BIT * vetInd, int  *out);
 
 /*
  * CALCOLO MAX HOST PER RETE
  * FORMULA---->2^n -2
  * n-->è il numero di bit per host
  * -2-->prefisso e boradcast
  */
  int massimoHost(int n);


#endif