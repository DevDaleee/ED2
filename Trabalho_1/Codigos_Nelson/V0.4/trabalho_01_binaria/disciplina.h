typedef struct disciplina Disciplina;

// Entrada e inserção de dados
void InsereDadosDisc(Disciplina **raizArvDisc, int QuantBlocosCurso, int QntSemDisc);
Disciplina* NovaDisc(Disciplina *raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria, int QuantBlocosCurso, int QntSemDisc);
void InsereDisc(Disciplina **raizArvDisc, Disciplina *NovaDisc);

// Auxiliares
int GeraCodDisc(Disciplina *raizArvDisc);
Disciplina* BuscaDiscCod(Disciplina *raizArvDisc, int CodDisc);
int VerificaDiscFolha(Disciplina *raizArvDisc);
int VerificaDiscDoisFilhos(Disciplina *raizArvDisc);
int VerificaBlocoDisc(int QuantBlocosCurso, int BlocoDisc);
int VerificaCH(int NumSemDisc, int CHDisc);
Disciplina* MaiorFilhoDiscEsq(Disciplina *raizArvDisc);
Disciplina* FilhoDiscLado(Disciplina *raizArvDisc);

//Impressão de dados
void ImprimeArvDisc(Disciplina *raizArvDisc, char *situacao);
void ImprimeDisc(Disciplina *DisciplinaCurso);
void ImprimeDiscBlocosIguais(Disciplina *raizArvDisc, int Bloco, char *situcao);
void ImprimeDiscCHIguais(Disciplina *raizArvDisc, int CargaHoraria, char *situacao);

//Remoção
void RemoveDisc(Disciplina **raizArvDisc, int CodDisc, char *situacao);
