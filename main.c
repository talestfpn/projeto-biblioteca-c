#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h" // Inclui nosso m�dulo de biblioteca

int main() {
// Bloco novo com dados pr�-carregados
Biblioteca minha_biblioteca = {
    // Inicializando a lista de livros
    .livros = {
        {"9788535914841", "Cem Anos de Solidao", "Gabriel Garcia Marquez", true, ""},
        {"9788579802681", "O Guia do Mochileiro das Galaxias", "Douglas Adams", true, ""},
        {"9788576572886", "A Revolucao dos Bichos", "George Orwell", true, ""}
    },
    .num_livros = 3, // Atualiza o contador de livros

    // Inicializando a lista de usu�rios
    .usuarios = {
        {"11122233344", "Joao da Silva"},
        {"55566677788", "Maria Oliveira"}
    },
    .num_usuarios = 2 // Atualiza o contador de usu�rios
};

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
            // NOVOS CASES
            case 7: apresentar_busca_livro(&minha_biblioteca); break;
            case 8: apresentar_busca_usuario(&minha_biblioteca); break;
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
