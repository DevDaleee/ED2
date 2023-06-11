typedef struct disciplinas Disciplinas;

int alturaD(Disciplinas *raizArvDisc);
void InsereDadosDisc(Disciplinas **raizArvDisc);
void EntradaDadosDisc(Disciplinas **raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria);
void InsereDisc(Disciplinas **raizArvDisc, Disciplinas *NovaDisc);
void ImprimeDiscMsmBloco(Disciplinas *raizArvDisc, int Bloco);
int GeraCodDisc(Disciplinas *raizArvDisc);
Disciplinas* BuscaDiscCod(Disciplinas *raizArvDisc, int CodDisc);
void ImprimeArvDisc(Disciplinas *raizArvDisc);
void ImprimeDisc(Disciplinas *DisciplinasCurso);
void ImprimeDiscCargaHoraria(Disciplinas *raizArvDisc, int ch);
Disciplinas* RemoveDisc(Disciplinas* raizArvDisc, int cod_disciplina);
int maiorD(int a, int b);
int fatorBalanceamentoDisc(Disciplinas *raizArvDisc);
Disciplinas* rEsqD(Disciplinas **raizArvDisc);
Disciplinas* rDirD(Disciplinas **raizArvDisc);
void balancearDisc(Disciplinas **raizArvDisc);