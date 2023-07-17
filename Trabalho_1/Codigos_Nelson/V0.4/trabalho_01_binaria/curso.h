typedef struct curso Curso;

// Entrada e inserção de dados
void InsereDadosCursos(Curso **raizArvCurso);
Curso* NovoCurso(Curso *raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc, int CodCurso);
void InsereCurso(Curso **raizArvCurso, Curso *NovoCurso);

// Auxiliares
int GeraCodCurso(Curso *raizArvCurso);
Curso *BuscaCursoCod(Curso *raizArvCurso, int CodCurso);
int VerificaCursoFolha(Curso *NoCurso);
int VerificaCursoDoisFilhos(Curso *NoCurso);
Curso* MaiorFilhoCursoEsq(Curso *raizArvCurso);
Curso* FilhoCursoLado(Curso *raizArvCurso);
//int BuscaValorNoMaisProf(Curso* raizArvCurso);

//Impressão de dados
void ImprimeArvCursos(Curso *raizArvCurso, char *situacao);
void ImprimeCursosQuantBlocosIguais(Curso *raizArvCurso, int NumBlocos, char *situacao);
void ImprimeDisciplinasCurso(Curso *raizArvCurso, int CodCurso, char *situacao);
void ImprimeCurso(Curso *raizArvCurso, int CodCurso, char *situacao);
void ImprimeDisciplinaCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao);
void ImprimeDiscMesmoBloco(Curso *raizArvCurso, int CodCurso, int Bloco, char *situacao);
void ImprimeDiscMesmaCH(Curso *raizArvCurso, int CodCurso, int CargaHoraria, char *situacao);

// Remoção
void RemoveDiscCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao);
void RemoveCurso(Curso **raizArvCurso, int CodCurso, char *situacao);
