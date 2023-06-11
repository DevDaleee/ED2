
typedef struct cursos Cursos;

int alturaCursos(Cursos *raizArvCursos);
// Entrada e inserção de dados
void InsereDadosCursos(Cursos **raizArvCurso);
void EntradaDadosCurso(Cursos **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc);
void InsereCurso(Cursos **raizArvCurso, Cursos *NovoCurso);

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
void RemoveCursoDaArv(Cursos *raizArvCursos, int cod_curso);
int maiorC(int a, int b);
int fatorBalanceamentoCursos(Cursos *raizArvCursos);
Cursos* rEsqC(Cursos **raizArvCursos);
Cursos* rDirC(Cursos **raizArvCursos);
void balancearCurso(Cursos **raizArvCursos);
void ImprimirInfosAVLCursos(Cursos *raizArvCursos);
void ImprimirInfosAVLDisc(Cursos *raizArvCursos);

