typedef struct cursos Cursos;

void InsereCurso(Cursos **raizArvCurso, Cursos *NovoCurso);
int max(int a, int b);
int getHeight(Cursos* raizArvCurso);
int getBalance(Cursos* raizArvCurso);
Cursos* rotateRight(Cursos* y);
Cursos* rotateLeft(Cursos* x);
void balanceTree(Cursos** raizArvCurso);
void EntradaDadosCurso(Cursos **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc);
void InsereDadosCursos(Cursos **raizArvCurso);
int GeraCodCurso(Cursos *raizArvCurso);
Cursos *BuscaCursoCod(Cursos *raizArvCurso, int CodCurso);

void ImprimeArvCursos(Cursos *raizArvCurso);
void ImprimeDisciplinasCurso(Cursos *raizArvCurso, int CodCurso);
void ImprimeCurso(Cursos *raizArvCurso, int CodCurso);
void ImprimeCursosBlocosIguais(Cursos *raizArvCurso, int NumBlocos);
void ImprimeDisciplinaCurso(Cursos *raizArvCurso, int CodCurso, int CodDisc);
void ImprimeDisciplinaBloco(Cursos *raizArvCurso, int bloco);
void ImprimeDisciplinasCargaHoraria(Cursos *raizArvCurso, int cod_curso, int ch);
void RemoveDisciplinas(Cursos *raizArvCurso, int cod_curso, int cod_disc);
int RemoveCurso(Cursos *raizArvCursos, int cod_curso);
void RemoveCursoDaArv(Cursos** raizArvCursos, int cod_curso);
void ImprimirInfosAVLCursos(Cursos *raizArvCursos);
void TesteInsercao(Cursos **raizArvCurso, double *TempoInsercao);
void ArmazenaTemposInsercao(double TempoInsercao);