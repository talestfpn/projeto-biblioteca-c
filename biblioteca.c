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

// Função de interface, responsável apenas por exibir as opções ao usuário.
void exibir_menu() {
    system("clear || cls");
    printf("====================================================\n");
    printf("||                                                ||\n");
    printf("||    BEM-VINDO AO SISTEMA DE BIBLIOTECA V1.0     ||\n");
    printf("||                                                ||\n");
    printf("====================================================\n");
    printf("||                                                ||\n");
    printf("||  1. Cadastrar Livro                            ||\n");
    printf("||  2. Cadastrar Usuario                          ||\n");
    printf("||  3. Realizar Emprestimo                        ||\n");
    printf("||  4. Realizar Devolucao                         ||\n");
    printf("||  5. Listar Livros                              ||\n");
    printf("||  6. Listar Usuarios                            ||\n");
    printf("||  0. Sair                                       ||\n");
    printf("||                                                ||\n");
    printf("====================================================\n");
    printf("Escolha uma opcao: ");
}

//Função de validação reutilizável garantindo que ambos os campos só aceitem números e tenham o tamanho exato.
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

// mesmo isbn não pode funcionar

// Função para o cadastro de livros, com validação de entrada.
void cadastrar_livro(Biblioteca *db) {
    if (db->num_livros >= MAX_LIVROS) {
        printf("\nErro: Limite maximo de livros atingido!\n");
        return;
    }

    Livro *novo_livro = &db->livros[db->num_livros];
    char buffer[MAX_TAMANHO];

    printf("\n--- Cadastro de Livro ---\n");

// Loop de validação para garantir que o ISBN seja inserido corretamente.
    while (true) {
        printf("Digite o ISBN (%d digitos, somente numeros): ", TAMANHO_ISBN);
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");
        if (validar_string_somente_numeros(buffer, TAMANHO_ISBN)) {
            strcpy(novo_livro->isbn, buffer);
            break;
        } else {
            printf("ISBN invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_ISBN);
        }
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

// Lógica similar à de cadastrar_livro, com loop para validar o CPF)
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
        if (validar_string_somente_numeros(buffer, TAMANHO_CPF)) {
            strcpy(novo_usuario->cpf, buffer);
            break;
        } else {
            printf("CPF invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_CPF);
        }
    }

    printf("Digite o Nome do usuario: ");
    fgets(novo_usuario->nome, MAX_TAMANHO, stdin);
    strtok(novo_usuario->nome, "\n");

    db->num_usuarios++;

    printf("\nUsuario cadastrado com sucesso!\n");
}

//Função de busca que retorna um ponteiro.
Livro* buscar_livro_por_isbn(Biblioteca *db, const char *isbn) {
    for (int i = 0; i < db->num_livros; i++) {
        if (strcmp(db->livros[i].isbn, isbn) == 0) {
            return &db->livros[i];
        }
    }
    return NULL;
}

// Lógica idêntica à busca por ISBN, mas para usuários)
Usuario* buscar_usuario_por_cpf(Biblioteca *db, const char *cpf) {
    for (int i = 0; i < db->num_usuarios; i++) {
        if (strcmp(db->usuarios[i].cpf, cpf) == 0) {
            return &db->usuarios[i];
        }
    }
    return NULL;
}

// Função que combina várias lógicas: busca, validação de status e alteração de estado.
void realizar_emprestimo(Biblioteca *db) {
    char isbn[15];
    char cpf[15];

    printf("\n--- Realizar Emprestimo ---\n");
    printf("Digite o ISBN do livro: ");
    fgets(isbn, sizeof(isbn), stdin);
    strtok(isbn, "\n");

// Passo 1: Encontrar o livro e validar se ele existe.
    Livro *livro = buscar_livro_por_isbn(db, isbn);

// Passo 2: Validar o estado do livro (se está disponível).
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

// Passo 3: Encontrar o usuário e validar se ele existe.
    Usuario *usuario = buscar_usuario_por_cpf(db, cpf);
    if (usuario == NULL) {
        printf("Erro: Usuario com este CPF nao encontrado.\n");
        return;
    }

// Passo 4: Alterar o estado do sistema (o efeito colateral da função).
    livro->disponivel = false;
    strcpy(livro->emprestado_para_cpf, cpf);

    printf("\nEmprestimo do livro '%s' para o usuario '%s' (CPF: %s) realizado com sucesso!\n", livro->titulo, usuario->nome, usuario->cpf);
}

// Ação principal da devolução: reverter o estado do livro.
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

//Funções de listagem, usamos um operador ternário para formatar a saída.
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
