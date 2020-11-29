#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define azul "\033[1;34m"
#define branco "\033[0m"
#define laranja "\033[1;33m"
#define roxo "\033[1;35m"
#define vermelho "\033[1;31m"
#define verde "\033[1;32m"
#define color_reset "\033[0m"

// Estrutura de informações de cada jogador.
typedef struct nomes{
    char nome[20];              // Nome de jogador i
    int points;                 // Pontuação do jogador i
    int pecas[6];               // pecas do jogador i
    int times_played;           // vezes que o jogador i jogou na sua vez
    int choice;                 // escolha de linha ou coluna segundo as regras
    int ja_trocou;              // vezes que o jogador ja trocou essa jogada
    int jogadas_da_vez[12];      // coordenadas da primeira e ultima jogada
} user;

// char *printTab(int valor);

// Symbols.c
char Symbols(char *comando , char *peca, char *color);
char *printTab(int valor, char *pecaTab);

// Paineis.c
int PainelPecas();
void PainelInicial();
void PainelJogadores(int *njogadores, user **jogador);
void JogadoresPainel(int *njogadores, user **jogador);
int PainelPrincipale(user *jogador, int vez_do_jogador, char *pecaTab);
int JogadaInvalida(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, user *jogador, int vez_do_jogador, char *pecaTab);
void PainelPontuacao(user *jogador, int njogadores);
void PainelJogadaInvalida(int valor);
void PainelVencedor(user *jogador, int njogadores);

// matrix_print.c
void matrix_print(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, char *pecaTab);
void index_print(int index);
void ReallocMatrix(int ***mat, int *matrix_rows, int *matrix_cols, int *matrix_origin, int add_row, int add_col);
void ShiftMatrix(int **mat, int* matrix_rows, int* matrix_cols, int add_row, int add_col);


//jogada.c
int jogada(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, int *linha, int  *coluna, int *valor_da_peca, user **jogador, int vez_do_jogador, char *game_mode, int (*garbage_array)[], int array_pecas[], int contador_geral, int *temp_linha, int *temp_coluna);
int WasMoveValid(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, int *linha, int *coluna);
int PecaPlacer(int ***matrix, int *matrix_origin, int linha, int coluna, int valor_da_peca, user **jogador, int vez_do_jogador);
int LastMoveNeedsRealloc(int ***matrix, int *matrix_rows, int *matrix_cols, int *matrix_origin, int linha, int coluna);
int SwitchRealloc(int ***matrix, int *matrix_rows, int *matrix_cols, int *matrix_origin, int flag_realloc);
int DoesPlayerHasPiece(user **jogador, int vez_do_jogador, int *valor_da_peca);


//distribuicao.c
int NewPieces(int array_pecas[], int (*garbage_array)[], user **jogador, int vez_do_jogador);
int TrocaPeca(int (*garbage_array)[], int array_pecas[], user **jogador, int vez_do_jogador, int *value);
int RefreshPecas (user **jogador, int vez_do_jogador, int array_pecas[], int (*garbage_array)[]);


//rules.c
int color_form(int **matrix, int *matrix_origin, int matrix_rows, int matrix_cols, int *linha, int *coluna, int *peca);
int game_way(int **matrix, int *matrix_origin, int matrix_rows, int matrix_cols, int *linha, int *coluna, int *peca);
int same_seq(int flag, int *linha, int *coluna, int *temp_linha, int *temp_coluna, user **jogador, int vez_do_jogador, int **matrix, int *matrix_origin);
int away(int **matrix, int *matrix_origin, int *linha, int *coluna, int matrix_cols, int matrix_row);
int AllTheRules(int **matrix, int *matrix_origin, int matrix_cols, int matrix_rows, int contador_geral, int *linha, int *coluna, int *temp_linha, int *temp_coluna, user **jogador, int vez_do_jogador, int *valor_da_peca);
int isNull(int escolha, int linha_origem, int coluna_origem, int nova_linha, int nova_coluna, int **matrix);

//pontuacao.c
int pontos(int **matrix, int *matrix_origin, int linha, int coluna, user **jogador, int vez_do_jogador, int matrix_cols, int matrix_rows);