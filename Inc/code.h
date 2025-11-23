#ifndef CODE_H
#define CODE_H


void creerCode(struct noeud* ptrNoeud,uint32_t code,uint32_t taille);

struct noeud* getAddress(struct noeud* ptrNoeud, uint8_t caractere);

void compresserTexte(uint8_t* texte, struct noeud* racine, uint8_t texteCompress[]);

void afficherBits(uint8_t* texteCompress, uint32_t byteCount, uint8_t bitRestants);

#endif // CODE_H
