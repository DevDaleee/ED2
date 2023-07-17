typedef struct curso Curso;

// Entrada e inserção de dados
void InsereDadosCursos(Curso **raizArvCurso);
void NovoCurso(Curso **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc);
void InsereCurso(Curso **raizArvCurso, Curso *NovoCurso);

int GeraCodCurso(Curso *raizArvCurso);
Curso *BuscaCursoCod(Curso *raizArvCurso, int CodCurso);
int CursoFolha(Curso *raizArvCurso);
int CursoDoisFilhos(Curso *raizArvCurso);

//Impressão de dados
void ImprimeArvCursos(Curso *raizArvCurso, char *situacao);
void ImprimeCursosQuantBlocosIguais(Curso *raizArvCurso, int NumBlocos, char *situacao);
void ImprimeDisciplinasCurso(Curso *raizArvCurso, int CodCurso, char *situacao);
void ImprimeCurso(Curso *raizArvCurso, int CodCurso, char *situacao);
void ImprimeDisciplinaCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao);
void ImprimeDiscMesmoBloco(Curso *raizArvCurso, int CodCurso, int Bloco, char *situacao);
void ImprimeDiscMesmaCH(Curso *raizArvCurso, int CodCurso, int CargaHoraria, char *situacao);

void RemoveDiscCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao);
Curso* MaiorCursoEsq(Curso *raizArvCurso);
Curso* CursoLado(Curso *raizArvCurso);
void RemoveCurso(Curso **raizArvCurso, int CodCurso, char *situacao);