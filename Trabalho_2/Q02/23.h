typedef struct _Arv23 Arv23;
typedef struct _InfoPalavra InfoPalavra;

// Funções para inserção
void LeituraDadosArq(Arv23** RaizArv23, InfoPalavra** PalavraSobe);
Arv23* InsereArv23(Arv23** RaizArv23, Arv23* Pai, InfoPalavra** PalavraSobe, char* PalavraInfo, int LinhaPalavra);
void AdicionaInfoNo(Arv23 **RaizArv23, InfoPalavra* PalavraInfo, Arv23* Filho);
Arv23* CriaNo23(InfoPalavra* PalavraInfo, Arv23* Esq, Arv23* Centro, Arv23* Dir);
Arv23* QuebraNo(Arv23** No, InfoPalavra** Palavra, InfoPalavra* PalavraInfo, Arv23* Filho);
void InserePalavraLinhaArq23(Arv23** RaizArv23, char* Palavra, int LinhaPalavra, int* Situacao);
InfoPalavra* CriaInfoPalavra(char* Palavra);

// Funções auxiliares
//InfoPalavra* BuscaArv23Teste(Arv23* RaizArv23, char* PalavraBusca, int* NosPercorridos);
int VerificaFolha(Arv23* NoArv23);
InfoPalavra* BuscaInfo23(Arv23* RaizArv23, char* Palavra);

// Funções para impressão
void ImprimeInfo(InfoPalavra* InfoNo);
void ImprimeNo23(Arv23* No);
void ImprimeArv23(Arv23 *RaizArv23, int nivel);

// Funções para remoção
void removeQuebrasDeLinha(char *str);
void RemoverPalavraLinhaArq23(Arv23** RaizArv23, char* Palavra, int LinhaPalavra, int* Situacao);
void RemovePalavra23(Arv23** RaizArv23, Arv23** Pai, char* Palavra, int LinhaPalavra);
void RemoveMaiorInfoEsq(Arv23** RaizArv23, Arv23** PaiMaior, Arv23** MaiorInfoRemove, int LocalInfo);
void RedistribuiArv23(Arv23** RaizArv23, Arv23** Pai);