#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Huffman.h"
void huffman(){
    float taxa_compressao = 0;
    float MIN, Segundo_Menor;
    int escolha = 0;
    int total_caracter = 0;
    TipoInt booleano;
    TipoInt num_caracter = 0;
    TipoInt i, j, k, indice, n;
    TipoChar str[128];
    TipoInt MenorTam, Seg_Tam_Maior;
    FILE *arq = fopen("arq.txt","r");
    FILE *arq_saida;
    ArvoreHuffman *arvore_huffman;
    ArvoreHuffman *vet_nos[26], *letras[26];

    if ( arq == NULL ) {
        printf("\nArquivo nao encontrado !!");
        return 0;
    }
    else {
        for(i = 0; i < 26; i++){
            vet_nos[i] = 0;
        }
        num_caracter = 0;
        if(fgets(str, 128, arq) != NULL)
            booleano = 1;
        while(!feof(arq) || booleano) {
            n = strlen(str);
            for (i = 0; i < n ; i ++ ) {
                str[i] = toupper(str[i]);
                if(str[i] >= 'A' && str[i] <= 'Z') {
                    num_caracter ++;
                    indice = str[i] - 'A';
                    if (vet_nos[indice] == NULL) {
                        vet_nos[indice] = (ArvoreHuffman*)malloc(sizeof(ArvoreHuffman));
                        vet_nos[indice]->c = str[i];
                        vet_nos[indice]->frequencia = 1;
                        vet_nos[indice]->esquerda = vet_nos[indice]->direita = NULL;
                    }
                    else{
                        vet_nos[indice]->frequencia += 1;
                    }
                }
            }
            if (booleano) {
                booleano = fgets(str, 128, arq) != NULL;
            }
        }
    }
    fclose(arq);
    total_caracter = num_caracter * 8;

    for ( i = 0, n = 0 ; i < 26 ; i ++ ) {
        letras[i] = vet_nos[i];
        if (vet_nos[i] != NULL) {
            vet_nos[i]->frequencia = vet_nos[i]->frequencia/num_caracter;
            n ++;
        }
    }
    j = 1;
    do {
        BuscaMenores(vet_nos, &MIN, &MenorTam, &Segundo_Menor, &Seg_Tam_Maior);
        if (MenorTam != -1 && Seg_Tam_Maior != -1 && MenorTam != Seg_Tam_Maior) {
            ArvoreHuffman *temp;
            arvore_huffman = (ArvoreHuffman*)malloc(sizeof(ArvoreHuffman));
            arvore_huffman->frequencia = vet_nos[MenorTam]->frequencia + vet_nos[Seg_Tam_Maior]->frequencia;
            arvore_huffman->c = j;
            arvore_huffman->esquerda = vet_nos[MenorTam];
            temp = (ArvoreHuffman*)malloc(sizeof(ArvoreHuffman));
            temp->c = vet_nos[Seg_Tam_Maior]->c;
            temp->frequencia = vet_nos[Seg_Tam_Maior]->frequencia;
            temp->esquerda = vet_nos[Seg_Tam_Maior]->esquerda;
            temp->direita = vet_nos[Seg_Tam_Maior]->direita;
            arvore_huffman->direita = temp;
            vet_nos[MenorTam] = arvore_huffman;
            vet_nos[Seg_Tam_Maior] = NULL;
        }
        j ++;
    } while( j < n );
    printf("\n1)Codificar\n2)Tamanho do arquivo de entrada\n");
    scanf("%d", &escolha);
    switch(escolha){
        case 1:{ /*Codificar*/
                for ( i = 0 ; i < 26 ; i ++ ) {
                    if (vet_nos[i] != NULL)  {
                        char codigo[128];
                        strcpy(codigo, "");
                        Codifica(arvore_huffman = vet_nos[i], letras, 0, 0, codigo);
                        printf("\n\nArvore Codificada com Sucesso\n\n");
                        //ExibeArvore(vet_nos[i]);
                        break;
                    }
                }
                printf("\n1)Decodificar\n2)Mostrar arvore\n");
                scanf("%d", &escolha);
                switch(escolha){
                    case 1:{/*DECODIFICAR*/
                        arq = fopen("arq.txt", "r");
                        arq_saida = fopen("arq_saida.txt", "w");
                        booleano = fgets(str, 128, arq) != NULL;
                        while(!feof(arq) || booleano) {
                            n = strlen(str);
                            for (i = 0; i < n ; i ++ ) {
                                str[i] = toupper(str[i]);
                                if (str[i] >= 'A' && str[i] <= 'Z') {
                                    indice = str[i] - 'A';
                                    fputs(letras[indice]->codigo, arq_saida);
                                }
                            }
                            if (booleano) {
                            booleano = fgets(str, 128, arq) != NULL;
                            }
                        }
                        fclose(arq);
                        fclose(arq_saida);
                        taxa_compressao = num_caracter*8;
                        arq_saida = fopen("arq_saida.txt", "r");
                        booleano = fgets(str, 128, arq_saida) != NULL;
                        num_caracter = 0;
                        while(!feof(arq_saida) || booleano) {
                            num_caracter += strlen(str);
                            if (booleano) {
                                booleano = fgets(str, 128, arq_saida) != NULL;
                            }
                        }
                        fclose(arq_saida);
                        printf("\n");
                        printf("\nArquivo decodificado:\n\n");
                        arq_saida = fopen("arq_saida.txt", "r");
                        booleano = fgets(str, 128, arq_saida) != NULL;
                        while(!feof(arq_saida) || booleano) {
                            n = strlen(str);
                            i = 0 ;
                            while(i < n) {
                                Decodifica(str, &i, arvore_huffman);
                            }
                            if (booleano) {
                                booleano = fgets(str, 128, arq_saida) != NULL;
                            }
                        }
    //}
                        fclose(arq_saida);
                        printf("\n1)Taxa de compressao\n2)Tamanho do arquivo de saida\n");
                        scanf("%d", &escolha);
                        switch(escolha){
                            case 1:{/*Taxa de compressao*/
                                printf("\nTaxa de compressao: %.1f%%", 100*(taxa_compressao - num_caracter)/taxa_compressao);
                                break;
                            }
                            case 2:{/*Tamanho do arquivo de saida*/
                                printf("\nTamanho do arquivo de saida: %d bits", num_caracter);
                                break;
                            }
                        }//FIM DO TERCEIRO SWITCH
                        break;
                    }//FIM DO CASE DECODIFICAR
                    case 2:{/*MOSTRA ARVORE*/
                        for( i = 0; i < 26; i++)
                            ExibeArvore(vet_nos[i]);
                        break;
                    }
                }//FIM DO SEGUNDO SWITCH
            break;
        }//FIM DO CASE DO DECODIFICAR
        case 2:{/*Tamanho do arquivo de entrada*/
            printf("\nTamanho do arquivo de entrada: %d bits", total_caracter);
        }//FIM DO CASE DO TAMANHO DE ENTRADA
    }//FIM DO PRIMEIRO SWITCH
}
