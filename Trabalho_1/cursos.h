
typedef struct curso Curso;

void InsereDadosCursos(Curso **raizArvCurso);
void EntradaDadosCurso(Curso **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc);
void InsereCurso(Curso **raizArvCurso, Curso *NovoCurso);

int GeraCodUnico(Curso *raizArvCurso);

int BuscaCursoCod(Curso *raizArvCurso, int CodCurso);

void ImprimeArvCursos(Curso *raizArvCurso);