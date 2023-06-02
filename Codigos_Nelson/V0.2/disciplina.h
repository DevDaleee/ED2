typedef struct disciplina Disciplina;

void InsereDadosDisc(Disciplina **raizArvDisc);
void EntradaDadosDisc(Disciplina **raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria);
void InsereDisc(Disciplina **raizArvDisc, Disciplina *NovaDisc);

int GeraCodDisc(Disciplina *raizArvDisc);
Disciplina* BuscaDiscCod(Disciplina *raizArvDisc, int CodDisc);

//Impressão de dados
void ImprimeArvDisc(Disciplina *raizArvDisc);
void ImprimeDisc(Disciplina *DisciplinaCurso);