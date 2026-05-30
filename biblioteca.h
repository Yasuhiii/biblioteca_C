#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#define MAX_LIVROS     100   
#define MAX_TITULO     100   
#define MAX_AUTOR      80    
#define CODIGO_MIN     1     
#define CODIGO_MAX     9999  


typedef struct {
    int  codigo;             
    char titulo[MAX_TITULO]; 
    char autor[MAX_AUTOR];   
    int  ano;                
    int  quantidade;         
} Livro;


int  mostrarMenu(void);

void adicionarLivro(Livro biblioteca[], int *totalLivros);

void listarLivros(const Livro biblioteca[], int totalLivros);

void procurarPorCodigo(const Livro biblioteca[], int totalLivros);

void mostrarDisponiveis(const Livro biblioteca[], int totalLivros);

void atualizarQuantidade(Livro biblioteca[], int totalLivros);

void removerLivro(Livro biblioteca[], int *totalLivros);

void mostrarTotal(int totalLivros);

int  codigoExiste(const Livro biblioteca[], int totalLivros, int codigo);
int  encontrarIndice(const Livro biblioteca[], int totalLivros, int codigo);
void imprimirLivro(const Livro *livro);
void limparBuffer(void);

#endif 
