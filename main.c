#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h" // Inclui nosso módulo de biblioteca

int main() {
    Biblioteca minha_biblioteca;
    minha_biblioteca.num_livros = 0;
    minha_biblioteca.num_usuarios = 0;

    int opcao;

    while (true) {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Por favor, digite um numero.\n");
            limpar_buffer_entrada();
            printf("\nPressione Enter para continuar...");
            getchar();
            continue;
        }
        limpar_buffer_entrada();

        switch (opcao) {
            case 1: cadastrar_livro(&minha_biblioteca); break;
            case 2: cadastrar_usuario(&minha_biblioteca); break;
            case 3: realizar_emprestimo(&minha_biblioteca); break;
            case 4: realizar_devolucao(&minha_biblioteca); break;
            case 5: listar_livros(&minha_biblioteca); break;
            case 6: listar_usuarios(&minha_biblioteca); break;
            case 0:
                printf("\nObrigado por utilizar o sistema! Saindo...\n");
                exit(0);
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar();
    }

    return 0;
}
