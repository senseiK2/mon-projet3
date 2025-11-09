#ifndef ARBRE_H
#define ARBRE_H

struct noeud{
    uint8_t c;
    uint32_t occurence;
    uint32_t code;
    uint32_t tailleCode;
    struct noeud *gauche, *droite;
};

void creerFeuille(struct noeud* arbre[256], uint32_t tab[256]);

void afficheTabArbreHuffman(struct noeud* arbre[256], uint32_t taille);

void triArbre(struct noeud* arbre[256], uint32_t taille);

struct noeud* CreeNoeud(struct noeud* arbre[256], uint32_t taille);

void parcourirArbre(struct noeud* ptrNoeud);

void creerCode(struct noeud* ptrNoeud,uint32_t code,uint32_t taille);
#endif // ARBRE_H
