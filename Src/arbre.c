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



void creerFeuille(struct noeud* arbre[256], uint32_t tab[256]){
    uint32_t compt = 0;
    for (uint32_t i = 0; i < 256; i++)
    {
        if(tab[i] != 0){
            struct noeud *n = malloc(sizeof(struct noeud));
            n->c = (uint8_t)i;
            n->occurence = tab[i];
            n->code = 0;
            n->tailleCode = 0;
            n->gauche = NULL;
            n->droite = NULL;
            arbre[compt++] = n;
        }
    }
}

void afficheTabArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
    for (uint32_t i = 0; i < taille; i++) {
        printf("Caractère '%c' : %u occurrences\n", arbre[i]->c, arbre[i]->occurence);
    }
}


void triArbre(struct noeud* arbre[256], uint32_t taille){
    struct noeud *temp;
    for (uint32_t i = 0; i < taille - 1; i++){
        for(uint32_t j = 0; j < taille - i; j++){
            if ((arbre[j]->occurence) > (arbre[j + 1]->occurence)){
                temp = arbre[j];
                arbre[j] = arbre[j + 1];
                arbre[j + 1] = temp;
            }
        }
    }
}


void CreeNoeud(struct noeud* arbre[256], uint32_t taille){
     while(taille > 1){
        triArbre(arbre,taille);

        struct noeud *g = arbre[0];
        struct noeud *d = arbre[1];

        struct noeud *racine = malloc(sizeof(struct noeud));
        racine->c = 33;
        racine->occurence = g->occurence + d->occurence;
        racine->code = 0;
        racine->tailleCode = 0;
        racine->gauche = g;
        racine->droite = d;

        arbre[0] = racine;
        taille --;
     }
}
