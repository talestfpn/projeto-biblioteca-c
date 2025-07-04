#include <stdio.h>      // Funções de entrada/saída (printf, fgets).
#include <stdlib.h>     // Funções utilitárias (system).
#include <string.h>     // Funções para manipulação de strings (strcmp, strcpy, strtok).
#include <ctype.h>      // Função 'isdigit' para verificar se um caractere é um dígito.
#include "biblioteca.h" // Inclui nosso próprio cabeçalho com as definições e protótipos.

// --- Implementação das Funções ---

//Função de limpar buffer do teclado (para resolver bug de pular linha \n)
void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu() {
    system("clear || cls");
    printf("=====================================================\n");
    printf("||         BEM-VINDO AO SISTEMA DE BIBLIOTECA      ||\n");
    printf("====================================================\n");
    printf("||  1. Cadastrar Livro                             ||\n");
    printf("||  2. Cadastrar Usuario                           ||\n");
    printf("||  3. Realizar Emprestimo                         ||\n");
    printf("||  4. Realizar Devolucao                          ||\n");
    printf("||  5. Listar Livros                               ||\n");
    printf("||  6. Listar Usuarios                             ||\n");
    printf("||  7. Buscar Livro por ISBN                       ||\n");
    printf("||  8. Buscar Usuario por CPF                      ||\n");
    printf("||  0. Sair                                        ||\n");
    printf("====================================================\n");
    printf("Escolha uma opcao: ");
}

bool validar_string_somente_numeros(const char *str, int tamanho_exato) {
    if (strlen(str) != tamanho_exato) { // Verifica se o tamanho da string bate com o esperado.
        return false;
    }
    for (int i = 0; i < tamanho_exato; i++) {
        if (!isdigit(str[i])) { // 'isdigit' vem de <ctype.h> e checa se o caractere é um dígito numérico.
            return false;
        }
    }
    return true; // Se passou por todas as verificações, a string é válida.
}

void cadastrar_livro(Biblioteca *db) {
    // 1. Verifica se a biblioteca já atingiu sua capacidade máxima de livros.
    if (db->num_livros >= MAX_LIVROS) {
        printf("\nErro: Limite maximo de livros atingido!\n");
        return;
    }

    // 2. Cria um ponteiro 'novo_livro' que aponta para o próximo espaço livre no array de livros.
    Livro *novo_livro = &db->livros[db->num_livros];
    char buffer[MAX_TAMANHO];

    printf("\n--- Cadastro de Livro ---\n");

    // 3. Loop de validação para o ISBN. O loop só termina quando um ISBN válido e único é inserido.
    while (true) {
        printf("Digite o ISBN (%d digitos, somente numeros): ", TAMANHO_ISBN);
        fgets(buffer, sizeof(buffer), stdin); // 'fgets' para ler strings
        strtok(buffer, "\n"); // 'strtok' remove o caractere '\n' que o 'fgets' captura no final da string.

        // Valida o formato do ISBN.
        if (!validar_string_somente_numeros(buffer, TAMANHO_ISBN)) {
            printf("ISBN invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_ISBN);
            continue; // Volta para o início do loop.
        }

        // Verifica se o ISBN já existe, chamando a função de busca.
        if (buscar_livro_por_isbn(db, buffer) != NULL) {
            printf("Erro: Um livro com este ISBN ja existe no acervo.\n");
            continue; // Volta para o início do loop.
        }

        // 4. Se o ISBN é válido e único, copia para a struct e sai do loop.
        strcpy(novo_livro->isbn, buffer); // 'strcpy' copia o conteúdo do buffer para o campo 'isbn'.
        break;
    }

    // 5. Pede os outros dados do livro.
    printf("Digite o Titulo: ");
    fgets(novo_livro->titulo, MAX_TAMANHO, stdin); //Garante que o usuário escreva uma string com caracteres limitados
    strtok(novo_livro->titulo, "\n"); //Resolver problema do fgets que sempre le a string + \n

    printf("Digite o Autor: ");
    fgets(novo_livro->autor, MAX_TAMANHO, stdin);
    strtok(novo_livro->autor, "\n");

    // 6. Define os valores iniciais para o novo livro.
    novo_livro->disponivel = true;
    novo_livro->emprestado_para_cpf[0] = '\0'; // Define a string como vazia.

    // 7. Incrementa o contador de livros. Este é o passo que efetivamente "salva" o novo livro.
    db->num_livros++;

    printf("\nLivro cadastrado com sucesso!\n");
}

// A função 'cadastrar_usuario' segue exatamente a mesma lógica da 'cadastrar_livro'
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
    for (int i = 0; i < db->num_livros; i++) { // Percorre todos os livros cadastrados.
        if (strcmp(db->livros[i].isbn, isbn) == 0) { //Compara a string digitada com o ISBn que o user digitou
            return &db->livros[i]; // Retorna o endereço de memória do livro encontrado.
        }
    }


    return NULL; // Retorna NULL para indicar que o livro não foi encontrado.
}

// A função 'buscar_usuario_por_cpf' segue a mesma lógica de buscada função acima.
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
    fgets(isbn, sizeof(isbn), stdin); // 'fgets' para ler strings com valor máximo
    strtok(isbn, "\n");

    // 1. Busca o livro.
    Livro *livro = buscar_livro_por_isbn(db, isbn); //Cria ponteiro e chama função para procurar isbn digitado

    // 2. Valida o livro.
    if (livro == NULL) {
        printf("Erro: Livro com este ISBN nao encontrado.\n");
        return;
    }
    if (!livro->disponivel) {
        printf("Erro: Livro ja esta emprestado para o CPF %s.\n", livro->emprestado_para_cpf);
        return;
    }

    // 3. Busca o usuário.
    printf("Digite o CPF do usuario: ");
    fgets(cpf, sizeof(cpf), stdin);
    strtok(cpf, "\n");
    Usuario *usuario = buscar_usuario_por_cpf(db, cpf);

    // 4. Valida o usuário.
    if (usuario == NULL) {
        printf("Erro: Usuario com este CPF nao encontrado.\n");
        return;
    }

    // 5. Se tudo estiver correto, altera o estado do livro para "emprestado".
    livro->disponivel = false;
    strcpy(livro->emprestado_para_cpf, cpf); // 'strcpy' copia o conteúdo do cpf para o campo 'emprestado_para_cpf'.

    printf("\nEmprestimo do livro '%s' para o usuario '%s' (CPF: %s) realizado com sucesso!\n", livro->titulo, usuario->nome, usuario->cpf);
}

void realizar_devolucao(Biblioteca *db) {
    char isbn[15];

    printf("\n--- Realizar Devolucao ---\n");
    printf("Digite o ISBN do livro a ser devolvido: ");
    fgets(isbn, sizeof(isbn), stdin);
    strtok(isbn, "\n");

    // 1. Busca o livro.
    Livro *livro = buscar_livro_por_isbn(db, isbn);

    // 2. Valida o estado do livro.
    if (livro == NULL) {
        printf("Erro: Livro com este ISBN nao encontrado.\n");
        return;
    }
    if (livro->disponivel) {
        printf("Erro: Este livro ja esta disponivel no acervo.\n");
        return;
    }

    // 3. Se o livro estava emprestado, altera seu estado para "disponível".
    printf("\nLivro '%s' que estava com o CPF %s foi devolvido com sucesso!\n", livro->titulo, livro->emprestado_para_cpf);
    livro->disponivel = true;
    livro->emprestado_para_cpf[0] = '\0'; // Limpa o CPF de quem o emprestou.
}

void listar_livros(Biblioteca *db) {
    printf("\n--- Lista de Livros (%d) ---\n", db->num_livros);
    if (db->num_livros == 0) { // Primeiro, uma verificação para o caso de a biblioteca estar vazia
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (int i = 0; i < db->num_livros; i++) { // Se existem livros, um loop 'for' itera sobre o array de livros, do índice 0 até o último livro cadastrado
        printf("ISBN: %s | Titulo: %s | Autor: %s | Status: ",
               db->livros[i].isbn,
               db->livros[i].titulo,
               db->livros[i].autor);
        if (db->livros[i].disponivel) {
            printf("Disponivel\n"); //Muda status p disponível
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


void apresentar_busca_livro(Biblioteca *db) {
    char isbn[15];
    printf("\n--- Buscar Livro por ISBN ---\n");

    // Valida o formato do ISBN antes de fazer a busca.
    while(true) {
        printf("Digite o ISBN do livro a ser buscado (%d digitos): ", TAMANHO_ISBN);
        fgets(isbn, sizeof(isbn), stdin);
        strtok(isbn, "\n");

        if(validar_string_somente_numeros(isbn, TAMANHO_ISBN)) {
            break; // Sai do loop se o ISBN for válido.
        } else {
            printf("ISBN invalido! Deve conter exatamente %d digitos numericos.\n", TAMANHO_ISBN);
        }
    }

    // Chama a função de busca real.
    Livro *livro = buscar_livro_por_isbn(db, isbn);

    // Apresenta o resultado
    if (livro == NULL) {
        printf("\nNenhum livro encontrado com o ISBN: %s\n", isbn);
    } else {
        printf("\n--- Livro Encontrado ---\n");
        printf("ISBN: %s\n", livro->isbn);
        printf("Titulo: %s\n", livro->titulo);
        printf("Autor: %s\n", livro->autor);
        printf("Status: %s\n", livro->disponivel ? "Disponivel" : "Emprestado"); // Usando operador ternário de novo.
        if (!livro->disponivel) {
            printf("Emprestado para o CPF: %s\n", livro->emprestado_para_cpf);
        }
    }
}

// Segue a mesma lógica da função anterior, mas para usuários.
void apresentar_busca_usuario(Biblioteca *db) {
    char cpf[15];
    printf("\n--- Buscar Usuario por CPF ---\n");

    while(true) {
        printf("Digite o CPF do usuario a ser buscado (%d digitos): ", TAMANHO_CPF);
        fgets(cpf, sizeof(cpf), stdin);
        strtok(cpf, "\n");

        if(validar_string_somente_numeros(cpf, TAMANHO_CPF)) {
            break;
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
