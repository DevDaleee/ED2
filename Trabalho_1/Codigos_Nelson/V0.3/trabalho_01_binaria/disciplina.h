typedef struct disciplina Disciplina;

void InsereDadosDisc(Disciplina **raizArvDisc, int QuantBlocosCurso, int QntSemDisc);
void NovaDisc(Disciplina **raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria, int QuantBlocosCurso, int QntSemDisc);
void InsereDisc(Disciplina **raizArvDisc, Disciplina *NovaDisc);

int GeraCodDisc(Disciplina *raizArvDisc);
Disciplina* BuscaDiscCod(Disciplina *raizArvDisc, int CodDisc);
int DiscFolha(Disciplina *raizArvDisc);
int DiscDoisFilhos(Disciplina *raizArvDisc);
int VerificaBlocoDisc(int QuantBlocosCurso, int BlocoDisc);
int VerificaCH(int NumSemDisc, int CHDisc);

//Impressão de dados
void ImprimeArvDisc(Disciplina *raizArvDisc, char *situacao);
void ImprimeDisc(Disciplina *DisciplinaCurso);
void ImprimeDiscBlocosIguais(Disciplina *raizArvDisc, int Bloco, char *situcao);
void ImprimeDiscCHIguais(Disciplina *raizArvDisc, int CargaHoraria, char *situacao);

Disciplina* MaiorDiscEsq(Disciplina *raizArvDisc);
Disciplina* FilhoDiscLado(Disciplina *raizArvDisc);
void RemoveDisc(Disciplina **raizArvDisc, int CodDisc, char *situacao);
