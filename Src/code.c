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


void creerCode(struct noeud* ptrNoeud,uint32_t code,uint32_t taille){
    if(ptrNoeud ->droite==NULL && ptrNoeud ->gauche==NULL){
    ptrNoeud ->tailleCode=taille;
    ptrNoeud ->code=code;
    printf("%c \t code : %d \t taille :%d \r\n", ptrNoeud ->c, ptrNoeud->code, ptrNoeud->tailleCode);
    }
    else{
        //On va a droite (on injecte un 0 à droite dans le code)
        creerCode(ptrNoeud ->droite,code<<1,taille+1);
        // On va a gauche (On injecte un 1 à droite)
        creerCode(ptrNoeud ->gauche,(code<<1)+1,taille+1);
    }
}


struct noeud* getAddress(struct noeud* ptrNoeud, uint8_t caractere){
    if (ptrNoeud == NULL){
        return NULL;
    }

    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        if (ptrNoeud->c == caractere){
            return ptrNoeud;
        }
        else{
            return NULL; 
        }
    }

        struct noeud* gauche = getAddress(ptrNoeud->gauche, caractere);
        if (gauche != NULL){
            return gauche; 
        }

        struct noeud* droite = getAddress(ptrNoeud->droite, caractere);
        if (droite != NULL){
            return droite;
        }
}


 void compresserTexte(uint8_t* texte, struct noeud* racine, uint8_t texteCompress[]){ 
    uint8_t BitPos = 0; 
    uint8_t bytePos = 0; 
    for(uint8_t i = 0; i < nbrCaractereTotal; i++){ 
        struct noeud* feuille = getAddress(racine, texte[i]); 
        uint32_t code = feuille -> code; 
        uint32_t TailleCode = feuille -> tailleCode; 
        while(TailleCode > 0){ 
            if(BitPos == 8){
                BitPos = 0;
                bytePos ++;
            }
             uint8_t bit = (code >> (TailleCode - 1)) & 0x1
            texteCompress[bytePos] |= (bit << (7 - BitPos));
            TailleCode --; 
            BitPos ++;
        } 
    } 
}

