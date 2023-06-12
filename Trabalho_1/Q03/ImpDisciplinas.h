typedef struct disciplinas Disciplinas;

int getHeightDisciplinas(Disciplinas *raizArvDisc);
void InsereDadosDisc(Disciplinas **raizArvDisc);
void EntradaDadosDisc(Disciplinas **raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria);
void InsereDisc(Disciplinas **raizArvDisc, Disciplinas *NovaDisc);
void ImprimeDiscMsmBloco(Disciplinas *raizArvDisc, int Bloco);
int GeraCodDisc(Disciplinas *raizArvDisc);
Disciplinas* BuscaDiscCod(Disciplinas *raizArvDisc, int CodDisc);
void ImprimeArvDisc(Disciplinas *raizArvDisc);
void ImprimeDisc(Disciplinas *DisciplinasCurso);
void ImprimeDiscCargaHoraria(Disciplinas *raizArvDisc, int ch);
void RemoveDisc(Disciplinas** raizArvDisc, int cod_disciplina);
int maxDisc(int a, int b);
int getBalanceDisciplinas(Disciplinas *raizArvDisc);
Disciplinas* REDisc(Disciplinas *y);
Disciplinas* RDDisc(Disciplinas *x);
void balanceTreeDisciplinas(Disciplinas **raizArvDisc);