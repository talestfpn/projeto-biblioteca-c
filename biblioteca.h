
 //Garante que o conteúdo deste arquivo seja incluído apenas uma vez durante a compilação, mesmo que vários outros arquivos o chamem.
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <stdbool.h> // Necessário para usar o tipo 'bool' (true/false) nas structs


 //                               --- Constantes Globais (Defines) ---
 // Usar #define torna o código mais fácil de manter. Se precisarmos mudar o tamanho máximo de livros mudamos em um só lugar aqui.

#define MAX_LIVROS 50
#define MAX_USUARIOS 50
#define MAX_TAMANHO 100
#define TAMANHO_CPF 11
#define TAMANHO_ISBN 13

// --- Definição das Estruturas de Dados ---

// Estrutura para representar as informações de um único Livro.
typedef struct {
    char isbn[15]; // Identificador único do livro.
    char titulo[MAX_TAMANHO];
    char autor[MAX_TAMANHO];
    bool disponivel; // 'flag' que indica se o livro está disponível ou emprestado. (sinalizar estado)
    char emprestado_para_cpf[15]; // Armazena o CPF do usuário que pegou o livro emprestado.
} Livro;

// Estrutura para representar as informações de um único Usuário.
typedef struct {
    char cpf[15]; // Usado como identificador único do usuário.
    char nome[MAX_TAMANHO];
} Usuario;

// Estrutura principal que representa a Biblioteca como um todo.
typedef struct {
    Livro livros[MAX_LIVROS]; // Um array que armazena todos os objetos do tipo Livro.
    int num_livros; // Contador para saber quantos livros realmente existem no array.
    Usuario usuarios[MAX_USUARIOS]; //Um array para armazenar todos os objetos do tipo Usuario.
    int num_usuarios; // Contador para saber quantos usuários existem no array.
} Biblioteca;


 //                                   Funções (Interface Pública do Módulo)
 // Esta é a "face pública" da biblioteca. O arquivo main.c só precisa conhecer estas assinaturas para poder chamar as funções


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

#endif // Fim da guarda de inclusão BIBLIOTECA_H
