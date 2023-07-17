typedef struct curso Curso;

// Entrada e inserção de dados
void InsereDadosCursos(Curso **raizArvCurso);
void NovoCurso(Curso **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc);
void InsereCurso(Curso **raizArvCurso, Curso *NovoCurso);

//Auxiliaries
int GeraCodCurso(Curso *raizArvCurso);
Curso *BuscaCursoCod(Curso *raizArvCurso, int CodCurso);
int VerificaCursoFolha(Curso *raizArvCurso);
int VerificaCursoDoisFilhos(Curso *raizArvCurso);
Curso* MaiorCursoEsq(Curso *raizArvCurso);
Curso* FilhoCursoLado(Curso *raizArvCurso);

//Balanceamento
void BalanceiaArvCursos(Curso **raizArvCurso);
void RotEsqArvCursos(Curso **raizArvCurso);
void RotDirArvCursos(Curso **raizArvCurso);
int AltDoNoCurso(Curso *curso);
int FBCurso(Curso *curso);
void AtualizaAlturaCurso(Curso **raizArvCurso);
int CalcAltCurso(Curso *raizArvCurso);


//Impressão de dados
void ImprimeArvCursos(Curso *raizArvCurso, char *situacao);
void ImprimeCursosQuantBlocosIguais(Curso *raizArvCurso, int NumBlocos, char *situacao);
void ImprimeDisciplinasCurso(Curso *raizArvCurso, int CodCurso, char *situacao);
void ImprimeCurso(Curso *raizArvCurso, int CodCurso, char *situacao);
void ImprimeDisciplinaCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao);
void ImprimeDiscMesmoBloco(Curso *raizArvCurso, int CodCurso, int Bloco, char *situacao);
void ImprimeDiscMesmaCH(Curso *raizArvCurso, int CodCurso, int CargaHoraria, char *situacao);

//Remoção
void RemoveDiscCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao);
int RemoveCurso(Curso **raizArvCurso, int CodCurso, char *situacao);