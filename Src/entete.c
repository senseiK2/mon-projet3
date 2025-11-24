#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "freq.h"
#include "arbre.h"
#include "code.h"
#include "entete.h"

uint16_t calculerTailleEntete(void){
    uint16_t tailleEntete = 6 + nbrCaractereDifferent * 9;
    return tailleEntete;
}


uint32_t BitTotal(struct noeud* racine) {
    if (racine == NULL) {
        return 0;
    }

    if (racine->gauche == NULL && racine->droite == NULL) {
        return racine->occurence * racine->tailleCode;
    }

    uint32_t tailleGauche = BitTotal(racine->gauche);
    uint32_t tailleDroite = BitTotal(racine->droite);

    return tailleGauche + tailleDroite;
}


uint16_t TailleFichierComp(struct noeud* racine) {
    uint16_t OctetFichier = (BitTotal(racine) + 7) / 8;
    
    uint16_t TailleEntete = calculerTailleEntete();

    return OctetFichier + TailleEntete;
}