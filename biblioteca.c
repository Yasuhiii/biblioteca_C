#include <stdio.h>    
#include <string.h>   
#include <stdlib.h>   
#include "biblioteca.h" 

void limparBuffer(void) {
    int c;
    // Le caractere a caractere ateh encontrar '\n' (Enter) ou EOF
    while ((c = getchar()) != '\n' && c != EOF);
}


int mostrarMenu(void) {
    int opcao;

    printf("\n+======================================+\n");
	printf("|       BIBLIOTECA - UNI MINDELO       |\n");
	printf("+======================================+\n");
	printf("|  1. Adicionar novo livro             |\n");
	printf("|  2. Listar todos os livros           |\n");
	printf("|  3. Procurar livro por codigo        |\n");
	printf("|  4. Mostrar livros disponiveis       |\n");
	printf("|  5. Atualizar quantidade             |\n");
	printf("|  6. Remover livro                    |\n");
	printf("|  7. Total de livros registados       |\n");
	printf("|  8. Sair                             |\n");
	printf("+======================================+\n");
	printf("Escolha uma opcao: ");

    // Se a opção nao estiver entre 1 e 8, pedimos de novo.
    while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 8) {
        limparBuffer(); // Limpa o que ficou no teclado
        printf("Opcao invalida! Escolha entre 1 e 8: ");
    }
    limparBuffer(); // Limpa o Enter que ficou apos o número

    return opcao;
}


int codigoExiste(const Livro biblioteca[], int totalLivros, int codigo) {
    int i;
    // Percorremos todos os livros um a um
    for (i = 0; i < totalLivros; i++) {
        if (biblioteca[i].codigo == codigo) {
            return 1; // Devolve verdadeiro
        }
    }
    return 0; // Devolve o falso
}

int encontrarIndice(const Livro biblioteca[], int totalLivros, int codigo) {
    int i;
    for (i = 0; i < totalLivros; i++) {
        if (biblioteca[i].codigo == codigo) {
            return i; // Devolve a posicao no array
        }
    }
    return -1; // -1 significa "nao encontrei"
}


void imprimirLivro(const Livro *livro) {
    printf("------------------------------------------\n");
    printf("  Codigo    : %d\n",   livro->codigo);
    printf("  Titulo    : %s\n",   livro->titulo);
    printf("  Autor     : %s\n",   livro->autor);
    printf("  Ano       : %d\n",   livro->ano);
    printf("  Qtd.      : %d exemplar(es)\n", livro->quantidade);
    printf("------------------------------------------\n");
    /* Nota: usamos livro->campo porque livro eh um ponteiro.
       Se fosse uma variavel normal, usariamos livro.campo. */
}

// funcao para adicionar livros (nem sei pq comentei isso pq o nome diz tudo)
void adicionarLivro(Livro biblioteca[], int *totalLivros) {
    Livro novoLivro; // Criamos uma variável temporária para o novo livro
    int codigo;

    // Verificar se ainda ha espaço no array
    if (*totalLivros >= MAX_LIVROS) {
        printf("\nErro: sistema cheio! Maximo de %d livros atingido.\n", MAX_LIVROS);
        return; /* Saímos da função sem fazer nada */
    }

    printf("\n=== ADICIONAR NOVO LIVRO ===\n");

    // --- Ler o CODIGO ---
    printf("Codigo do livro (%d a %d): ", CODIGO_MIN, CODIGO_MAX);
    while (scanf("%d", &codigo) != 1
           || codigo < CODIGO_MIN
           || codigo > CODIGO_MAX) {
        limparBuffer();
        printf("Codigo invalido! Insira um numero entre %d e %d: ",
               CODIGO_MIN, CODIGO_MAX);
    }
    limparBuffer();

    // Verificar se o codigo ja existe
    if (codigoExiste(biblioteca, *totalLivros, codigo)) {
        printf("\nErro: ja existe um livro com o codigo %d!\n", codigo);
        return;
    }
    novoLivro.codigo = codigo;

    // --- Ler o TITULO ---
    printf("Titulo do livro: ");
    fgets(novoLivro.titulo, MAX_TITULO, stdin);

    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';

    // Verificar se o titulo nao ficou vazio
    if (novoLivro.titulo[0] == '\0') {
        printf("Erro: o titulo nao pode estar vazio!\n");
        return;
    }

    // --- Ler o AUTOR ---
    printf("Nome do autor: ");
    fgets(novoLivro.autor, MAX_AUTOR, stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';

    if (novoLivro.autor[0] == '\0') {
        printf("Erro: o autor nao pode estar vazio!\n");
        return;
    }

    /* --- Ler o ANO --- */
    printf("Ano de publicacao: ");
    while (scanf("%d", &novoLivro.ano) != 1
           || novoLivro.ano < 1 || novoLivro.ano > 2025) {
        limparBuffer();
        printf("Ano invalido! Insira um ano entre 1 e 2025: ");
    }
    limparBuffer();

    /* --- Ler a QUANTIDADE --- */
    printf("Quantidade disponivel: ");
    while (scanf("%d", &novoLivro.quantidade) != 1 || novoLivro.quantidade < 0) {
        limparBuffer();
        printf("Quantidade invalida! Insira um numero positivo: ");
    }
    limparBuffer();

    biblioteca[*totalLivros] = novoLivro;
    (*totalLivros)++;
    printf("\nLivro adicionado com sucesso!\n");
}

// funcao para listar os livros
void listarLivros(const Livro biblioteca[], int totalLivros) {
    int i;

    printf("\n=== LISTA DE TODOS OS LIVROS ===\n");

    // Se nao ha livros sai
    if (totalLivros == 0) {
        printf("Nenhum livro registado ainda.\n");
        return;
    }

    printf("Total: %d livro(s)\n", totalLivros);

    // Percorremos todos os livros e imprimimos cada um 
    for (i = 0; i < totalLivros; i++) {
        // Passamos o endereco (&) do livro — criamos um ponteiro
        imprimirLivro(&biblioteca[i]);
    }
}


void procurarPorCodigo(const Livro biblioteca[], int totalLivros) {
    int codigo, indice;

    printf("\n=== PROCURAR LIVRO POR CODIGO ===\n");

    if (totalLivros == 0) {
        printf("Nenhum livro registado ainda.\n");
        return;
    }

    printf("Insira o código do livro: ");
    while (scanf("%d", &codigo) != 1) {
        limparBuffer();
        printf("Codigo invalido! Tente novamente: ");
    }
    limparBuffer();

    // Procuramos o índice do livro com esse codigo
    indice = encontrarIndice(biblioteca, totalLivros, codigo);

    if (indice == -1) {
        // -1 significa que nao foi encontrado
        printf("Livro com codigo %d nao encontrado.\n", codigo);
    } else {
        printf("Livro encontrado:\n");
        imprimirLivro(&biblioteca[indice]);
    }
}


void mostrarDisponiveis(const Livro biblioteca[], int totalLivros) {
    int i;
    int encontrados = 0; // Conta quantos livros tem disponivel

    printf("\n=== LIVROS DISPONIVEIS ===\n");

    if (totalLivros == 0) {
        printf("Nenhum livro registado ainda.\n");
        return;
    }

    for (i = 0; i < totalLivros; i++) {
        // So mostramos se a quantidade for maior que 0
        if (biblioteca[i].quantidade > 0) {
            imprimirLivro(&biblioteca[i]);
            encontrados++;
        }
    }

    // Se o contador ficou em 0, nao ha nenhum disponivel
    if (encontrados == 0) {
        printf("Nenhum livro disponivel no momento.\n");
    } else {
        printf("Total de livros disponiveis: %d\n", encontrados);
    }
}

// funcao para atualizar a quantidade de livros
void atualizarQuantidade(Livro biblioteca[], int totalLivros) {
    int codigo, indice, novaQtd;

    printf("\n=== ATUALIZAR QUANTIDADE ===\n");

    if (totalLivros == 0) {
        printf("Nenhum livro registado ainda.\n");
        return;
    }

    printf("Codigo do livro a atualizar: ");
    while (scanf("%d", &codigo) != 1) {
        limparBuffer();
        printf("Código inválido! Tente novamente: ");
    }
    limparBuffer();

    indice = encontrarIndice(biblioteca, totalLivros, codigo);

    if (indice == -1) {
        printf("Livro com codigo %d nao encontrado.\n", codigo);
        return;
    }

    // Mostramos o livro atual antes de alterar
    printf("Livro encontrado:\n");
    imprimirLivro(&biblioteca[indice]);

    printf("Nova quantidade: ");
    while (scanf("%d", &novaQtd) != 1 || novaQtd < 0) {
        limparBuffer();
        printf("Quantidade invalida! Insira um numero positivo: ");
    }
    limparBuffer();

    // Atualizamos o campo quantidade dentro do array
    biblioteca[indice].quantidade = novaQtd;
    printf("Quantidade atualizada com sucesso!\n");
}


void removerLivro(Livro biblioteca[], int *totalLivros) {
    int codigo, indice, i;
    char confirmacao;

    printf("\n=== REMOVER LIVRO ===\n");

    if (*totalLivros == 0) {
        printf("Nenhum livro registado ainda.\n");
        return;
    }

    printf("Codigo do livro a remover: ");
    while (scanf("%d", &codigo) != 1) {
        limparBuffer();
        printf("Codigo invalido! Tente novamente: ");
    }
    limparBuffer();

    indice = encontrarIndice(biblioteca, *totalLivros, codigo);

    if (indice == -1) {
        printf("Livro com codigo %d nao encontrado.\n", codigo);
        return;
    }

    // Mostramos o livro e pedimos confirmação antes de apagar
    printf("Livro a remover:\n");
    imprimirLivro(&biblioteca[indice]);
    printf("Tem a certeza? (s/n): ");
    scanf(" %c", &confirmacao); /* O espaço antes de %c ignora espaços/enters */
    limparBuffer();

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Remocao cancelada.\n");
        return;
    }

    /*
      Deslocamos todos os livros apos o removido uma posicao
      para tras, sobrescrevendo o livro apagado.
    */
    
    for (i = indice; i < *totalLivros - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
    }

    // Reduz-se o contador — o ultimo elemento fica inacessivel
    (*totalLivros)--;
    printf("Livro removido com sucesso!\n");
}

// funcao que mostra o total de livros registados
void mostrarTotal(int totalLivros) {
    printf("\n=== TOTAL DE LIVROS ===\n");
    printf("Livros registados no sistema: %d / %d\n", totalLivros, MAX_LIVROS);
}
