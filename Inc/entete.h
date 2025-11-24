#ifndef ENTETE_H
#define ENTETE_H

uint16_t calculerTailleEntete(void);

uint32_t BitTotal(struct noeud* racine);

uint16_t TailleFichierComp(struct noeud* racine);

void creerEntete(uint8_t texteCompress[], struct noeud* table[], struct noeud* racine);
#endif // ENTETE_H