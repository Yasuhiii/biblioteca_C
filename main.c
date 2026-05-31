#include <stdio.h>      
#include "biblioteca.h" 

int main(void) {
    Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;
    char resp;

    printf("Bem-vindo ao Sistema de Biblioteca da Uni Mindelo!\n");

    do {
        opcao = mostrarMenu(); // Mostra o menu e obtem a escolha

        switch (opcao) {
            case 1:
                adicionarLivro(biblioteca, &totalLivros);
                break;

            case 2:
                listarLivros(biblioteca, totalLivros);
                break;

            case 3:
                procurarPorCodigo(biblioteca, totalLivros);
                break;

            case 4:
                mostrarDisponiveis(biblioteca, totalLivros);
                break;

            case 5:
                atualizarQuantidade(biblioteca, totalLivros);
                break;

            case 6:
                removerLivro(biblioteca, &totalLivros);
                break;

            case 7:
                mostrarTotal(totalLivros);
                break;

            case 8:
                printf("Tem certeza que deseja sair? (S/N): ");
                scanf(" %c", &resp);

                if (resp == 'S' || resp == 's') {
                    printf("Saindo...\n");
                    return 0;
                
                } else {
                    printf("A voltar ao menu...\n");
                    opcao = 0;
                    // Ao mudar para 0, a condicao "while(opcao != 8)" continua verdadeira
                }
            	break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 8); // Repete enquanto nao escolher Sair

    return 0;
}
