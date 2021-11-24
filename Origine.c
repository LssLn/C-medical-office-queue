/*
Progettare ed implementare in ANSI C un programma che permetta di gestire 4 code di attesa in uno studio medico. Ogni singola coda gestisce i pazienti in attesa di uno dei medici, i medici sono identificati dai numeri 0, 1, 2, 3.
Ogni paziente è identificato dai seguenti attributi
- Codice Fiscale
- Cognome (senza spazi bianchi)
- Nome (senza spazi bianchi)
- Urgenza (valore booleano implementato con gli interi)
Progettare la struttura dati adatta a mantenere in memoria centrale le informazioni utilizzando
strutture e puntatori per la coda;
Scrivere un opportuno main in cui sia previsto un menù di scelta delle operazioni richieste.
Tutti i valori necessari al funzionamento devono essere passati utilizzando parametri,
non è permesso l’uso di variabili globali;
Il programma deve prevedere le seguenti funzionionalita:
1) funzione Carica che legga dal file Elenco.txt i dati dei pazienti e li inserisca nelle code appropriate;
2) funzione StampaCada di Attesa, che dato il codice di un medico stampa l'elenco dei clienti in coda
3) funzione che dato il medico tramite il suo codice numerico (0, 1, 2, 3) estrae il primo paziente
in attesa e lo restituisce al main all’interno del quale viene stampato
4) Scrivere una funzione che restituisca in un vettore il numero di pazienti presenti in ogni lista
(l’elemento di indice 0 contiene il numero di pazienti nella coda del medico 0,
l’elemento di indice 1 contiene il numero di pazienti nella coda del medico 1, ecc.)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define strLL 20
#define nMEdici 4
#define NOMEFILE "elenco.txt"

/*definizione tipo paziente*/
typedef struct paz {
    char CF[17];
    char nome[strLL], cognome[strLL];
    int urgenza; //0 non urgente, 1 urgente
}paziente;

void stampaPaziente(paziente p) {
    printf("%s  %s %s  %s\n", p.CF, p.nome, p.cognome, p.urgenza ? "urgente" : "non urgente");
}

/*definizione coda e funzioni coda*/
typedef struct nd {
    paziente info;
    struct nd* successivo;
}nodoCoda;

typedef struct c {
    nodoCoda* primo, * ultimo;
}coda;

coda creaCodaVuota() {
    //coda coda;
    //coda.primo = coda.ultimo = NULL; //valido?
    coda coda = { NULL,NULL };//primo e ultimo null
    return coda;
}

int testCodaVuota(coda c) {
    //verifica se una coda è vuota
    return c.primo == NULL;
}

coda EliminaCoda(coda c) {
    //elimina un elemento dalla coda restituendo la coda senza il primo elemento

    if (testCodaVuota(c)) { //caso codavuota
        return c;
    }

    nodoCoda* aux = c.primo; //prendo il primo elemento
    //devo cancellare il primo elemento non solo spostarlo con succ! per cui aux
    
    if (c.primo == c.ultimo) //caso 1 elemento
        c.primo = c.ultimo = NULL;
    else                     //caso + elementi (aux)
        c.primo = c.primo->successivo;
    free(aux); //libera l'elemento che stiamo scartando, se non lo libero rimane spazio sprecato
    return c;

}

paziente PrimoInCoda(coda c) {
    //restituisce il primo elemento della cosa
    if (!testCodaVuota(c)) 
        return c.primo->info;
}

coda inCoda(coda c, paziente p) {
    //inserisce un elemento in coda;
    //COMPLETARE IL CODICE
    nodoCoda* aux = (nodoCoda*)malloc(sizeof(nodoCoda));
    aux->info = p;
    aux->successivo = NULL;
    if (testCodaVuota(c)) {
        c.primo = c.ultimo = aux;
    }
    else {
        c.ultimo->successivo = aux; 
        c.ultimo = aux;
    }
    return c;
}

int size(coda c) {
    //calcola e restituisce la lunghezza di una coda
    int i = 0;
    nodoCoda* l = c.primo;
    while (l != NULL) {
        l = l->successivo;
        i++;
    }
    return i;
}

/*funzioni di utilita*/
int menu() {
    int x;
    printf("\n 1: Carica file nel vettore di code\n");
    printf("\n 2: Stampa Coda di attesa di un medico\n");
    printf("\n 3: Estrae primo paziente in attesa di un medico e lo stampa\n");
    printf("\n 4: Contolla e stampa le lunghezze delle code\n");
    scanf("%d", &x);
    return x;
}

void stampaVettore(int* vettore, int n) {
    for (int i = 0; i < n; i++)
        printf("\n elemento %d = %d", i, vettore[i]);
}

int leggiCodiceMedico() {
    int codice=-1;
    //leggi un codice del medico da tastiera verificando che sia uno di quelli ammessi
    //COMPLETARE IL CODICE
    printf("\nInserire codice medico : ");
    while (codice < 0 || codice>3) {
        scanf("%d", &codice);
    }
    return codice;
}

/*quesito 1 Carica file nel vettore di code*/
void quesito1(char* nome, coda* archivio) { // coda*=coda[]
    FILE* f;
    paziente p;
    int i;
    f = fopen(nome, "r");
    if (f == NULL)
        return;
    while (fscanf(f, "%s%s%s%d%d", p.CF, p.nome, p.cognome, &p.urgenza, &i) == 5) {
        if (i < 0 || i>3) {
            printf("Codice medico (l'ultimo numero) del cliente %s errato! deve essere tra 0,3.\n",p.CF);
            continue; // continue fa saltare la prossima riga, eseguendo di nuovo while! scarto l'elemento.
        }
        archivio[i]=inCoda(archivio[i], p); 
        //se non assegno è come se non avessi fatto nulla, inCoda lavora per valore non riferimento
    }
}

/*stampa coda di attesa
/*quesito 2*/
void quesito2(coda c) {
    while (c.primo!= NULL) {
        stampaPaziente(c.primo->info);
        c.primo=c.primo->successivo;
    }
}

/*
void visita_coda(nodoCoda* pt) { //xstampa ( quesito 2
    if (pt == NULL)
        return;
    while (pt != NULL) {
        stampaPaziente(pt->info);
        pt = pt->successivo;
    }
}*/ 
//alternativa a quesito 2

/*quesito 3*/
coda quesito3(coda c) {
    //estrae il primo paziente e lo stampa;
    if (!testCodaVuota(c)) {
        stampaPaziente(PrimoInCoda(c));
        return EliminaCoda(c);
    }
}

/*quesito 4*/
int* quesito4(coda* c) {//coda[] contenente le 4 code
    // restituisce il vettore contenente le dimensioni di tutte le code 
    int *vettore=(int*)malloc(sizeof(int) * nMEdici); //alloco un vettore di interi di dimensione n volte int;// int* vettore però così dichiaro subito la dim(4)
    for (int i = 0; i < nMEdici; ++i) { //i++
        
        vettore[i] = size(c[i]);
    }
    return vettore;

    /*
    int vettore[nMEdici];// int* vettore però così dichiaro subito la dim(4)
    for (int i = 0; i < nMEdici; i++) {
        vettore[i] = size(c[i]);
    }
    return vettore[nMEdici];
    */
}




/*main*/

int main() {
    int medico, scelta = 0;
    coda archivio[nMEdici];
    for (int i = 0; i < nMEdici; i++) archivio[i] = creaCodaVuota();
    int* vettoreLunghezzaCode = NULL;
    do {
        scelta = menu();
        switch (scelta) {
        case 1:
            quesito1(NOMEFILE,archivio);
                break;
        case 2:
            medico = leggiCodiceMedico();
            quesito2(archivio[medico]); //questa stampa e basta, non c'è bisogno di assegnare
            break;
        case 3:
            medico = leggiCodiceMedico();
            //COMPLETARE IL CODICE
            archivio[medico] = quesito3(archivio[medico]); //questa invece cancella il primo! quindi assegno (funz per valore)
            break;
        case 4:
            //COMPLETARE IL CODICE
            //vettoreLunghezzaCode = quesito4(&archivio[nMEdici]);  //errore 
            //ho messo la & perchè mi dice coda è incompatibile con coda* <- errore

            vettoreLunghezzaCode = quesito4(archivio); //archivio è vettore di code

            stampaVettore(vettoreLunghezzaCode, nMEdici);
            break;
        }
    } while (scelta != 0);
}
