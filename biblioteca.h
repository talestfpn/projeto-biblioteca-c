
 //Garante que o conte�do deste arquivo seja inclu�do apenas uma vez durante a compila��o, mesmo que v�rios outros arquivos o chamem.
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <stdbool.h> // Necess�rio para usar o tipo 'bool' (true/false) nas structs


 //                               --- Constantes Globais (Defines) ---
 // Usar #define torna o c�digo mais f�cil de manter. Se precisarmos mudar o tamanho m�ximo de livros mudamos em um s� lugar aqui.

#define MAX_LIVROS 50
#define MAX_USUARIOS 50
#define MAX_TAMANHO 100
#define TAMANHO_CPF 11
#define TAMANHO_ISBN 13

// --- Defini��o das Estruturas de Dados ---

// Estrutura para representar as informa��es de um �nico Livro.
typedef struct {
    char isbn[15]; // Identificador �nico do livro.
    char titulo[MAX_TAMANHO];
    char autor[MAX_TAMANHO];
    bool disponivel; // 'flag' que indica se o livro est� dispon�vel ou emprestado. (sinalizar estado)
    char emprestado_para_cpf[15]; // Armazena o CPF do usu�rio que pegou o livro emprestado.
} Livro;

// Estrutura para representar as informa��es de um �nico Usu�rio.
typedef struct {
    char cpf[15]; // Usado como identificador �nico do usu�rio.
    char nome[MAX_TAMANHO];
} Usuario;

// Estrutura principal que representa a Biblioteca como um todo.
typedef struct {
    Livro livros[MAX_LIVROS]; // Um array que armazena todos os objetos do tipo Livro.
    int num_livros; // Contador para saber quantos livros realmente existem no array.
    Usuario usuarios[MAX_USUARIOS]; //Um array para armazenar todos os objetos do tipo Usuario.
    int num_usuarios; // Contador para saber quantos usu�rios existem no array.
} Biblioteca;


 //                                   Fun��es (Interface P�blica do M�dulo)
 // Esta � a "face p�blica" da biblioteca. O arquivo main.c s� precisa conhecer estas assinaturas para poder chamar as fun��es


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
void apresentar_busca_livro(Biblioteca *db);
void apresentar_busca_usuario(Biblioteca *db);

#endif // Fim da guarda de inclus�o BIBLIOTECA_H
