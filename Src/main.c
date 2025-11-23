#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "freq.h"
#include "arbre.h"
#include "code.h"

uint8_t texte[] = "aaaabbbccd";
uint8_t texteCompress[TAILLE_MAX_COMPRESS] = {0};
uint32_t tabCaractere[256];
struct noeud* arbreHuffman[256];

int main(void)
{
	FPU_Init();
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();

	printf("\r\n\r\n\r\nStart\r\n");
	occurence(texte, tabCaractere);
	AffTab(tabCaractere);

	creerFeuille(arbreHuffman, tabCaractere);
	afficheTabArbreHuffman(arbreHuffman, nbrCaractereDifferent);

    printf("\n");

	triArbre(arbreHuffman, nbrCaractereDifferent);
	afficheTabArbreHuffman(arbreHuffman, nbrCaractereDifferent);

	struct noeud *racine = CreeNoeud(arbreHuffman,nbrCaractereDifferent);
	parcourirArbre(racine);

	creerCode(racine,0,0);

	compresserTexte(texte,racine,texteCompress);
	while(1);
}
