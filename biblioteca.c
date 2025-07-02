#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "biblioteca.h" // Inclui nosso próprio header

// --- Implementação das Funções ---

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu() {
    system("clear || cls");
    printf("====================================================\n");
    printf("||                                                ||\n");
    printf("||    BEM-VINDO AO SISTEMA DE BIBLIOTECA V1.0     ||\n");
    printf("||                                                ||\n");
    printf("====================================================\n");
    printf("||  1. Cadastrar Livro                            ||\n");
    printf("||  2. Cadastrar Usuario                          ||\n");
    printf("||  3. Realizar Emprestimo                        ||\n");
    printf("||  4. Realizar Devolucao                         ||\n");
    printf("||  5. Listar Livros                              ||\n");
    printf("||  6. Listar Usuarios                            ||\n");
    printf("||  7. Buscar Livro por ISBN                      ||\n");
    printf("||  8. Buscar Usuario por CPF                     ||\n");
    printf("||  0. Sair                                       ||\n");
    printf("====================================================\n");
    printf("Escolha uma opcao: ");
}

bool validar_string_somente_numeros(const char *str, int tamanho_exato) {
    if (strlen(str) != tamanho_exato) {
        return false;
    }
    for (int i = 0; i < tamanho_exato; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void cadastrar_livro(Biblioteca *db) {
    if (db->num_livros >= MAX_LIVROS) {
        printf("\nErro: Limite maximo de livros atingido!\n");
        return;
    }

    Livro *novo_livro = &db->livros[db->num_livros];
    char buffer[MAX_TAMANHO];

    printf("\n--- Cadastro de Livro ---\n");

    while (true) {
        printf("Digite o ISBN (%d digitos, somente numeros): ", TAMANHO_ISBN);
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");

        if (!validar_string_somente_numeros(buffer, TAMANHO_ISBN)) {
            printf("ISBN invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_ISBN);
            continue;
        }

        if (buscar_livro_por_isbn(db, buffer) != NULL) {
            printf("Erro: Um livro com este ISBN ja existe no acervo.\n");
            continue;
        }

        strcpy(novo_livro->isbn, buffer);
        break;
    }

    printf("Digite o Titulo: ");
    fgets(novo_livro->titulo, MAX_TAMANHO, stdin);
    strtok(novo_livro->titulo, "\n");

    printf("Digite o Autor: ");
    fgets(novo_livro->autor, MAX_TAMANHO, stdin);
    strtok(novo_livro->autor, "\n");

    novo_livro->disponivel = true;
    novo_livro->emprestado_para_cpf[0] = '\0';
    db->num_livros++;

    printf("\nLivro cadastrado com sucesso!\n");
}

void cadastrar_usuario(Biblioteca *db) {
    if (db->num_usuarios >= MAX_USUARIOS) {
        printf("\nErro: Limite maximo de usuarios atingido!\n");
        return;
    }

    Usuario *novo_usuario = &db->usuarios[db->num_usuarios];
    char buffer[MAX_TAMANHO];

    printf("\n--- Cadastro de Usuario ---\n");

    while (true) {
        printf("Digite o CPF (%d digitos, somente numeros): ", TAMANHO_CPF);
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");

        if (!validar_string_somente_numeros(buffer, TAMANHO_CPF)) {
            printf("CPF invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_CPF);
            continue;
        }

        if (buscar_usuario_por_cpf(db, buffer) != NULL) {
            printf("Erro: Um usuario com este CPF ja esta cadastrado.\n");
            continue;
        }

        strcpy(novo_usuario->cpf, buffer);
        break;
    }

    printf("Digite o Nome do usuario: ");
    fgets(novo_usuario->nome, MAX_TAMANHO, stdin);
    strtok(novo_usuario->nome, "\n");

    db->num_usuarios++;

    printf("\nUsuario cadastrado com sucesso!\n");
}

Livro* buscar_livro_por_isbn(Biblioteca *db, const char *isbn) {
    for (int i = 0; i < db->num_livros; i++) {
        if (strcmp(db->livros[i].isbn, isbn) == 0) {
            return &db->livros[i];
        }
    }
    return NULL;
}

Usuario* buscar_usuario_por_cpf(Biblioteca *db, const char *cpf) {
    for (int i = 0; i < db->num_usuarios; i++) {
        if (strcmp(db->usuarios[i].cpf, cpf) == 0) {
            return &db->usuarios[i];
        }
    }
    return NULL;
}

void realizar_emprestimo(Biblioteca *db) {
    char isbn[15];
    char cpf[15];

    printf("\n--- Realizar Emprestimo ---\n");
    printf("Digite o ISBN do livro: ");
    fgets(isbn, sizeof(isbn), stdin);
    strtok(isbn, "\n");

    Livro *livro = buscar_livro_por_isbn(db, isbn);

    if (livro == NULL) {
        printf("Erro: Livro com este ISBN nao encontrado.\n");
        return;
    }
    if (!livro->disponivel) {
        printf("Erro: Livro ja esta emprestado para o CPF %s.\n", livro->emprestado_para_cpf);
        return;
    }

    printf("Digite o CPF do usuario: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");

    Usuario *usuario = buscar_usuario_por_cpf(db, cpf);
    if (usuario == NULL) {
        printf("Erro: Usuario com este CPF nao encontrado.\n");
        return;
    }

    livro->disponivel = false;
    strcpy(livro->emprestado_para_cpf, cpf);

    printf("\nEmprestimo do livro '%s' para o usuario '%s' (CPF: %s) realizado com sucesso!\n", livro->titulo, usuario->nome, usuario->cpf);
}

void realizar_devolucao(Biblioteca *db) {
    char isbn[15];

    printf("\n--- Realizar Devolucao ---\n");
    printf("Digite o ISBN do livro a ser devolvido: ");
    fgets(isbn, sizeof(isbn), stdin);
    strtok(isbn, "\n");

    Livro *livro = buscar_livro_por_isbn(db, isbn);

    if (livro == NULL) {
        printf("Erro: Livro com este ISBN nao encontrado.\n");
        return;
    }
    if (livro->disponivel) {
        printf("Erro: Este livro ja esta disponivel no acervo.\n");
        return;
    }

    printf("\nLivro '%s' que estava com o CPF %s foi devolvido com sucesso!\n", livro->titulo, livro->emprestado_para_cpf);
    livro->disponivel = true;
    livro->emprestado_para_cpf[0] = '\0';
}

void listar_livros(Biblioteca *db) {
    printf("\n--- Lista de Livros (%d) ---\n", db->num_livros);
    if (db->num_livros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (int i = 0; i < db->num_livros; i++) {
        printf("ISBN: %s | Titulo: %s | Autor: %s | Status: ",
               db->livros[i].isbn,
               db->livros[i].titulo,
               db->livros[i].autor);
        if (db->livros[i].disponivel) {
            printf("Disponivel\n");
        } else {
            printf("Emprestado para o CPF: %s\n", db->livros[i].emprestado_para_cpf);
        }
    }
}

void listar_usuarios(Biblioteca *db) {
    printf("\n--- Lista de Usuarios (%d) ---\n", db->num_usuarios);
     if (db->num_usuarios == 0) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    for (int i = 0; i < db->num_usuarios; i++) {
        printf("CPF: %s | Nome: %s\n",
               db->usuarios[i].cpf,
               db->usuarios[i].nome);
    }
}

// --- ALTERAÇÃO AQUI ---
void apresentar_busca_livro(Biblioteca *db) {
    char isbn[15];
    printf("\n--- Buscar Livro por ISBN ---\n");

    while(true) {
        printf("Digite o ISBN do livro a ser buscado (%d digitos): ", TAMANHO_ISBN);
        fgets(isbn, sizeof(isbn), stdin);
        strtok(isbn, "\n");

        if(validar_string_somente_numeros(isbn, TAMANHO_ISBN)) {
            break; // Se for válido, sai do loop
        } else {
            printf("ISBN invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_ISBN);
        }
    }

    Livro *livro = buscar_livro_por_isbn(db, isbn);

    if (livro == NULL) {
        printf("\nNenhum livro encontrado com o ISBN: %s\n", isbn);
    } else {
        printf("\n--- Livro Encontrado ---\n");
        printf("ISBN: %s\n", livro->isbn);
        printf("Titulo: %s\n", livro->titulo);
        printf("Autor: %s\n", livro->autor);
        printf("Status: %s\n", livro->disponivel ? "Disponivel" : "Emprestado");
        if (!livro->disponivel) {
            printf("Emprestado para o CPF: %s\n", livro->emprestado_para_cpf);
        }
    }
}

// --- ALTERAÇÃO AQUI ---
void apresentar_busca_usuario(Biblioteca *db) {
    char cpf[15];
    printf("\n--- Buscar Usuario por CPF ---\n");

    while(true) {
        printf("Digite o CPF do usuario a ser buscado (%d digitos): ", TAMANHO_CPF);
        fgets(cpf, sizeof(cpf), stdin);
        strtok(cpf, "\n");

        if(validar_string_somente_numeros(cpf, TAMANHO_CPF)) {
            break; // Se for válido, sai do loop
        } else {
            printf("CPF invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_CPF);
        }
    }

    Usuario *usuario = buscar_usuario_por_cpf(db, cpf);

    if (usuario == NULL) {
        printf("\nNenhum usuario encontrado com o CPF: %s\n", cpf);
    } else {
        printf("\n--- Usuario Encontrado ---\n");
        printf("CPF: %s\n", usuario->cpf);
        printf("Nome: %s\n", usuario->nome);
    }
}
