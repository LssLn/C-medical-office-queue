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
