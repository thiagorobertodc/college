//Implementa��o das fun��es
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "huffman.h"
void BuscaMenores(ArvoreHuffman *vet_nos[], float *MIN, PTipoInt MenorTam, float *Segundo_Menor, PTipoInt Seg_Tam_Maior){
    int i, k;
    k = 0;
    *MenorTam = -1;
    while (k < 26 && vet_nos[k] == NULL) k++;
    *MenorTam = k;
    *MIN = vet_nos[k]->frequencia;
    for ( i = k ; i < 26; i ++ ) {
        if ( vet_nos[i] != NULL && vet_nos[i]->frequencia < *MIN ) {
            *MIN = vet_nos[i]->frequencia;
            *MenorTam = i;
        }
    }
    k = 0;
    *Seg_Tam_Maior = -1;
    while ((k < 26 && vet_nos[k] == NULL) || (k == *MenorTam && vet_nos[k] != NULL)) k++;
    *Segundo_Menor = vet_nos[k]->frequencia;
    *Seg_Tam_Maior = k;
    if (k == *MenorTam) k ++;
    for ( i = k ; i < 26; i ++ ) {
        if ( vet_nos[i] != NULL && vet_nos[i]->frequencia < *Segundo_Menor && i != *MenorTam ) {
            *Segundo_Menor = vet_nos[i]->frequencia;
            *Seg_Tam_Maior = i;
        }
    }
}
void ExibeArvore(ArvoreHuffman *no) {
    int n;
    if ( no != NULL ) {
        if (no->c >= 'A' && no->c <= 'Z') {
            printf("%c:{\n  frequencia: %.f%%\n  codigo huffman: %s\n}\n\n", no->c, 100*(no->frequencia), no->codigo);
        }
        ExibeArvore(no->esquerda);
        ExibeArvore(no->direita);
    }
}
void Decodifica(PTipoChar str, PTipoInt indice, ArvoreHuffman *arvore_huffman) {
    int n = strlen(str);
    if (arvore_huffman->c >= 'A' && arvore_huffman->c <= 'Z') {
        printf("%c
               ", arvore_huffman->c);
        return ;
    } else {
        if ( *indice < n ) {
            if (str[*indice] == '0') {
                (*indice) ++;
                Decodifica(str, indice, arvore_huffman->esquerda);
            } else {
                if (str[*indice] == '1') {
                    (*indice) ++;
                    Decodifica(str, indice, arvore_huffman->direita);
                }
            }
        }
    }
}
void Codifica(ArvoreHuffman *no, ArvoreHuffman **letras, TipoChar direcao, TipoBoolean level, PTipoChar codigo) {
    int n;
    if ( no != NULL ) {
        if ((n = strlen(codigo)) < level) {
            if (direcao == 1) {
                strcat(codigo, "1");
            } else {
                if (direcao == 0) {
                    strcat(codigo, "0");
                }
            }
        } else {
            if (n >= level) {
                codigo[n - (n - level) - 1] = 0;
                if (direcao == 1) {
                    strcat(codigo, "1");
                } else {
                    if (direcao == 0) {
                        strcat(codigo, "0");
                    }
                }
            }
        }
        if (no->c >= 'A' && no->c <= 'Z') {
            strcpy(no->codigo, codigo);
            strcpy(letras[no->c - 'A']->codigo, codigo);
        }
        Codifica(no->esquerda, letras, 0, level + 1, codigo);
        Codifica(no->direita, letras, 1, level + 1, codigo);
    }
}
