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

	printf("\r\n\r\n========================================\r\n");
	printf("     DEMO COMPRESSION HUFFMAN STM32     \r\n");
	printf("========================================\r\n\r\n");

	printf("[INIT] Texte source : \"%s\"\r\n", texte);

	// 1) Calcul des occurrences
	printf("\r\n[1] Calcul des occurrences des caractères...\r\n");
	occurence(texte, tabCaractere);
	printf("    > Nombre total de caractères   : %lu\r\n", (unsigned long)nbrCaractereTotal);
	printf("    > Nombre de caractères distincts : %lu\r\n", (unsigned long)nbrCaractereDifferent);
	printf("    > Détail des occurrences :\r\n");
	AffTab(tabCaractere);

	// 2) Création des feuilles de l'arbre Huffman
	printf("\r\n[2] Création des feuilles de l'arbre Huffman...\r\n");
	creerFeuille(arbreHuffman, tabCaractere);
	printf("    > Feuilles initiales (non triées) :\r\n");
	afficheTabArbreHuffman(arbreHuffman, nbrCaractereDifferent);

	// 3) Tri du tableau de feuilles
	printf("\r\n[3] Tri des feuilles (ordre croissant d'occurrences)...\r\n");
	triArbre(arbreHuffman, nbrCaractereDifferent);
	printf("    > Feuilles après tri :\r\n");
	afficheTabArbreHuffman(arbreHuffman, nbrCaractereDifferent);

	// 4) Construction de l'arbre Huffman
	printf("\r\n[4] Construction de l'arbre Huffman complet...\r\n");
	struct noeud *racine = CreeNoeud(arbreHuffman, nbrCaractereDifferent);
	printf("    > Parcours de l'arbre (debug) :\r\n");
	parcourirArbre(racine);

	// 5) Génération des codes de Huffman
	printf("\r\n[5] Génération des codes pour chaque caractère...\r\n");
	printf("    > Format : <caractère> | code (binaire stocké en entier) | taille du code\r\n");
	creerCode(racine, 0, 0);

	// 6) Compression du texte
	printf("\r\n[6] Compression du texte en flux de bits...\r\n");
	printf("    > Bits compressés (avant ajout de l'entête) :\r\n");
	compresserTexte(texte, racine, texteCompress);

	// 7) Création de l'entête du fichier compressé
	printf("\r\n[7] Ajout de l'entête au buffer compressé...\r\n");
	printf("    > Buffer final (entête + données compressées) en bits :\r\n");
	creerEntete(texteCompress, racine);

	printf("\r\n[END] Compression Huffman terminée. Boucle infinie...\r\n");

	while(1);
}
