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

uint8_t texte[] = "aaaabbbccd";
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

	//creerCode(arbreHuffman,0,0);

	while(1);
}
