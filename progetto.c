#include "library.h"


int main()
{
    //leggo stringa per stringa

    //init variabili
    init();
    setVar();
    
    free_var();

    return 0;
}

void init(){
    init_autostrada();
}

void free_var(){
    free_autostrada();
}



void setVar() {
    int i = 0;
    char *command;
    // Leggi il contenuto del file riga per riga
    while (fgets(buffer_in, sizeof(buffer_in), stdin) != NULL)
    {
        // riga completa
        printf("\n %s", buffer_in);
        i=0;
        //split string
        command = strtok(buffer_in, " ");
        controller(command);
    }

    //.DEBUG
    printHighway();
}

void controller(char *command){

    if (strcmp(command, "aggiungi-stazione") == 0)
    {
        addStation();
    }
    else if (strcmp(command, "demolisci-stazione") == 0)
    {
        demolisciStazione();
    }
    else if (strcmp(command, "aggiungi-auto") == 0)
    {
        addAuto();
    }
    else if (strcmp(command, "rottama-auto") == 0)
    {
        rottamaAuto();
    }
    else if (strcmp(command, "pianifica-percorso") == 0)
    {
        plan();
    }
    
}

void addStation(){
    int distance, num_auto;
    int index;
    veicolo v;
    argument = strtok(NULL, " ");
    distance = atoi(argument);

    argument = strtok(NULL, " ");
    num_auto = atoi(argument);

    stazione s;
    s.distanza_da_inizio_autostada = distance;
    index = add_station(s, num_auto);
    if (index == -1)
    {
        ErrorAdd();//stazione gia presente
        return;
    }

    while (argument != NULL)//adesso qui sono tutte auto
    {
        argument = strtok(NULL, " ");
        //.DEBUG
        //printf("\nargument: %s", argument);
        if (argument == NULL || strcmp(argument, newline) == 0)
        {
            break;
        }
        v.autonomia = atoi(argument);
        if (add_auto(&highway.stazioni[index].parco, v)==-1){
            //errore aggiunta auto
            ErrorAdd();
            return;
        }
    }
    SuccessAdd();

}

void demolisciStazione(){
    int distance;
    argument = strtok(NULL, " ");
    distance = atoi(argument);
    // in questo particolare caso la stampa la faccio all interno di demolisci_stazione perche piu ottimizzata
    if (demolisci_stazione(distance) == 0)
    {
        SuccessDemolisci();
    }else{
        ErrorDemolisci();
    }
}

void addAuto(){
    int distance, autonomia;
    veicolo v;
    parco_veicoli *p;
    argument = strtok(NULL, " ");
    distance = atoi(argument);

    argument = strtok(NULL, " ");
    autonomia = atoi(argument);

    v.autonomia = autonomia;
    p = get_parco(distance);
    if(p== NULL){
        ErrorAdd();
        return;
    }
    if(add_auto(p, v) == 0)
        SuccessAdd();
    else
        ErrorAdd();

}

void rottamaAuto(){
    int distance, autonomia;
    veicolo v;
    parco_veicoli *p;
    argument = strtok(NULL, " ");
    distance = atoi(argument);

    argument = strtok(NULL, " ");
    autonomia = atoi(argument);

    v.autonomia = autonomia;
    p = get_parco(distance);
    if(p== NULL){
        ErrorRottama();
        return;
    }

    if(rottama_auto(p, v) == 0)
        SuccessRottama();
    else
        ErrorRottama();

}

void plan(){//TODO
    printf("nessun percorso");

}