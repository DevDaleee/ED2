typedef struct disciplina Disciplina;

// Entrada e Inserção de dados
void InsereDadosDisc(Disciplina **raizArvDisc, int QuantBlocosCurso, int QntSemDisc);
Disciplina* NovaDisc(Disciplina *raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria, int QuantBlocosCurso, int QntSemDisc);
void InsereDisc(Disciplina **raizArvDisc, Disciplina *NovaDisc);

//Auxiliaries
int GeraCodDisc(Disciplina *raizArvDisc);
Disciplina* BuscaDiscCod(Disciplina *raizArvDisc, int CodDisc);
int VerificaDiscFolha(Disciplina *raizArvDisc);
int VerificaDiscDoisFilhos(Disciplina *raizArvDisc);
int VerificaBlocoDisc(int QuantBlocosCurso, int BlocoDisc);
int VerificaCH(int NumSemDisc, int CHDisc);
Disciplina* MaiorFilhoDiscEsq(Disciplina *raizArvDisc);
Disciplina* FilhoDiscLado(Disciplina *raizArvDisc);

//Balanceamento
void BalanceiaArvDisc(Disciplina **raizArvDisc);
void RotEsqArvDisc(Disciplina **raizArvDisc);
void RotDirArvDisc(Disciplina **raizArvDisc);
int AltDoNoDisc(Disciplina *Disc);
int FBDisc(Disciplina *Disc);
void AtualizaAlturaDisc(Disciplina **raizArvDisc);
int CalcAltDisc(Disciplina *raizArvDisc);

//Impressão de dados
void ImprimeArvDisc(Disciplina *raizArvDisc, char *situacao);
void ImprimeDisc(Disciplina *DisciplinaCurso);
void ImprimeDiscBlocosIguais(Disciplina *raizArvDisc, int Bloco, char *situcao);
void ImprimeDiscCHIguais(Disciplina *raizArvDisc, int CargaHoraria, char *situacao);

//Remoção
int RemoveDisc(Disciplina **raizArvDisc, int CodDisc, char *situacao);
