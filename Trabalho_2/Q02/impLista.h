typedef struct Palavras LPalavras;

void InsereNoLinha(LPalavras **NoListaLinhas, int NumLinha);
LPalavras* CriaNoLinha(int NumLinha);
void RemoveNoLinha(LPalavras **NoListaLinhas, int NumLinha);
void LiberaListaLinhas(LPalavras **NoListaLinhas);
void ImprimeListaLinhas(LPalavras *NoListaLinhas);