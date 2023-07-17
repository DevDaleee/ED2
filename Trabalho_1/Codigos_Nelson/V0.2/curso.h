
typedef struct curso Curso;

// Entrada e inserção de dados
void InsereDadosCursos(Curso **raizArvCurso);
void EntradaDadosCurso(Curso **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc);
void InsereCurso(Curso **raizArvCurso, Curso *NovoCurso);

int GeraCodCurso(Curso *raizArvCurso);

Curso *BuscaCursoCod(Curso *raizArvCurso, int CodCurso);

//Impressão de dados
void ImprimeArvCursos(Curso *raizArvCurso);
void ImprimeDisciplinasCurso(Curso *raizArvCurso, int CodCurso);
void ImprimeCurso(Curso *raizArvCurso, int CodCurso);
void ImprimeCursosBlocosIguais(Curso *raizArvCurso, int NumBlocos);
void ImprimeDisciplinaCurso(Curso *raizArvCurso, int CodCurso, int CodDisc);