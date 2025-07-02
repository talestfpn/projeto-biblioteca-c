#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdbool.h> // Necessário para usar o tipo 'bool' nas structs

// --- Definição de Constantes Globais (Defines) ---
#define MAX_LIVROS 50
#define MAX_USUARIOS 50
#define MAX_TAMANHO 100
#define TAMANHO_CPF 11
#define TAMANHO_ISBN 13

// --- Definição das Estruturas de Dados ---


// Estrutura para representar um Livro e seus atributos.
typedef struct {
    char isbn[15];
    char titulo[MAX_TAMANHO];
    char autor[MAX_TAMANHO];
    bool disponivel;
    char emprestado_para_cpf[15];
} Livro;

// Estrutura para representar um Usuário da biblioteca.
typedef struct {
    char cpf[15];
    char nome[MAX_TAMANHO];
} Usuario;

typedef struct {
    Livro livros[MAX_LIVROS];
    int num_livros; // Contador para saber quantos livros realmente existem no array.
    Usuario usuarios[MAX_USUARIOS];
    int num_usuarios; // Contador para saber quantos usuarios realmente existem no array.
} Biblioteca;

// --- Funções(Interface Pública do Módulo)---

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

#endif // BIBLIOTECA_H
