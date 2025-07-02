#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdbool.h>

// --- Definição de Constantes ---
#define MAX_LIVROS 50
#define MAX_USUARIOS 50
#define MAX_TAMANHO 100
#define TAMANHO_CPF 11
#define TAMANHO_ISBN 13

// --- Definição das Estruturas de Dados ---

typedef struct {
    char isbn[15];
    char titulo[MAX_TAMANHO];
    char autor[MAX_TAMANHO];
    bool disponivel;
    char emprestado_para_cpf[15];
} Livro;

typedef struct {
    char cpf[15];
    char nome[MAX_TAMANHO];
} Usuario;

typedef struct {
    Livro livros[MAX_LIVROS];
    int num_livros;
    Usuario usuarios[MAX_USUARIOS];
    int num_usuarios;
} Biblioteca;

// --- Protótipos das Funções ---

void limpar_buffer_entrada();
void exibir_menu();
bool validar_string_somente_numeros(const char *str, int tamanho_exato);
void cadastrar_livro(Biblioteca *db);
void cadastrar_usuario(Biblioteca *db);
Livro* buscar_livro_por_isbn(Biblioteca *db, const char *isbn);
Usuario* buscar_usuario_por_cpf(Biblioteca *db, const char *cpf);
void realizar_emprestimo(Biblioteca *db);
void realizar_devolucao(Biblioteca *db);
void listar_livros(Biblioteca *db);
void listar_usuarios(Biblioteca *db);

// Novas funções para a interface de busca
void apresentar_busca_livro(Biblioteca *db);
void apresentar_busca_usuario(Biblioteca *db);

#endif // BIBLIOTECA_H
