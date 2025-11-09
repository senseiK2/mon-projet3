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
