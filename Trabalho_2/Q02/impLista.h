typedef struct _Linhas Linhas;

void InsereNoLinha(Linhas **NoListaLinhas, int NumLinha);
Linhas* CriaNoLinha(int NumLinha);
void RemoveNoLinha(Linhas **NoListaLinhas, int NumLinha);
void LiberaListaLinhas(Linhas **NoListaLinhas);
void ImprimeListaLinhas(Linhas *NoListaLinhas);