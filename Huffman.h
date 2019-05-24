//Declaração dos Tads
typedef char TipoChar;
typedef char * PTipoChar;
typedef short TipoBoolean;
typedef int TipoInt;
typedef int * PTipoInt;
typedef struct TipoHuffman *TipoApontador;
typedef struct TipoHuffman {
    float frequencia;
    TipoChar c;
    TipoChar codigo[128];
    TipoApontador *esquerda;
    TipoApontador *direita;
} ArvoreHuffman;
//Declaração das funções
void BuscaMenores(ArvoreHuffman *vet_nos[], float *MIN, PTipoInt MenorTam, float *Segundo_Menor, PTipoInt Seg_Tam_Maior);
void ExibeArvore(ArvoreHuffman *no);
void Decodifica(PTipoChar str, PTipoInt indice, ArvoreHuffman *arvore_huffman);
void Codifica(ArvoreHuffman *no, ArvoreHuffman **letras, TipoChar direcao, TipoBoolean level, PTipoChar codigo);
void huffman();
