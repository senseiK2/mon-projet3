#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "arbre.h"
#include "freq.h"

int16_t nbrCaractereTotal = 0;
int16_t nbrCaractereDifferent = 0;

void occurence(uint8_t* chaine, uint32_t tab[256]){
    uint8_t i = 0;
    while (chaine[i] != '\0') {
        uint8_t ASCII = chaine[i];
        if (tab[ASCII] == 0){
            nbrCaractereDifferent++;
        }
        tab[ASCII]++;
        i++;
    }
    nbrCaractereTotal = i;
}

void AffTab(uint32_t tab[256]){
    for (uint32_t i = 0; i < 256; i++)
    {
        if(tab[i] != 0){
            printf("lettre %c, ASCII %u, occurence %u\n", i, i, tab[i]);
        }
    }
    
}
