typedef struct _Arv23 Arv23;
typedef struct _InfoPalavra InfoPalavra;

void LeituraDadosArq(Arv23** RaizArv23, InfoPalavra** PalavraSobe);
Arv23* InsereArv23(Arv23** RaizArv23, Arv23* Pai, InfoPalavra** PalavraSobe, char* PalavraInfo, int LinhaPalavra);
void AdicionaInfoNo(Arv23 **RaizArv23, InfoPalavra* PalavraInfo, Arv23* Filho);
Arv23* CriaNo23(InfoPalavra* PalavraInfo, Arv23* Esq, Arv23* Centro, Arv23* Dir);
Arv23* QuebraNo(Arv23** No, InfoPalavra** Palavra, InfoPalavra* PalavraInfo, Arv23* Filho);
InfoPalavra* CriaInfoPalavra(char* Palavra);
int VerificaFolha(Arv23* NoArv23);
InfoPalavra* BuscaInfo23(Arv23* RaizArv23, char* Palavra);
void ImprimeInfo(InfoPalavra* InfoNo);
void ImprimeNo23(Arv23* No);
void ImprimeArv23(Arv23 *RaizArv23, int nivel);
void removeQuebrasDeLinha(char *str);
void RemovePalavra23(Arv23** RaizArv23, Arv23** Pai, char* Palavra, int LinhaPalavra);
void RemoveMaiorInfoEsq(Arv23** RaizArv23, Arv23** PaiMaior, Arv23** MaiorInfoRemove, int LocalInfo);
void RedistribuiArv23(Arv23** RaizArv23, Arv23** Pai);