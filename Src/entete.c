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

void creerEntete(uint8_t texteCompress[], struct noeud* table[], struct noeud* racine) {
    
    uint16_t tailleEntete      = calculerTailleEntete();      
    uint32_t nbBits            = BitTotal(racine);            
    uint16_t tailleCompressee  = (nbBits + 7) / 8;            


    for (int32_t i = (int32_t)tailleCompressee - 1; i >= 0; i--) {
        texteCompress[i + tailleEntete] = texteCompress[i];
    }

    uint16_t pos = 0;

    texteCompress[pos++] = (tailleEntete >> 8) & 0xFF;
    texteCompress[pos++] =  tailleEntete       & 0xFF;

    texteCompress[pos++] = (tailleCompressee >> 8) & 0xFF;
    texteCompress[pos++] =  tailleCompressee       & 0xFF;

    texteCompress[pos++] = (nbrCaractereTotal >> 8) & 0xFF;
    texteCompress[pos++] =  nbrCaractereTotal       & 0xFF;

    for (uint32_t i = 0; i < nbrCaractereDifferent; i++) {

        struct noeud* n = table[i];

        texteCompress[pos++] = n->c;

        texteCompress[pos++] = (n->code >> 24) & 0xFF;
        texteCompress[pos++] = (n->code >> 16) & 0xFF;
        texteCompress[pos++] = (n->code >>  8) & 0xFF;
        texteCompress[pos++] =  n->code        & 0xFF;

        texteCompress[pos++] = (n->tailleCode >> 24) & 0xFF;
        texteCompress[pos++] = (n->tailleCode >> 16) & 0xFF;
        texteCompress[pos++] = (n->tailleCode >>  8) & 0xFF;
        texteCompress[pos++] =  n->tailleCode        & 0xFF;
    }
}
