#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define max 55 // Tamanho maximo das strings de descricoes

typedef struct {
    char status;         // Se o valor for 0, esta incosistente. Se for 1, esta tudo certo
    int topoPilha;       // Pilha
    char tagCampo1;      // Tag do numero de inscricao
    char tagCampo2;      // Tag da nota
    char tagCampo3;      // Tag da data
    char tagCampo4;      // Tag da cidade
    char tagCampo5;      // Tag do nome da escola
    char desCampo1[max]; // Numero de inscricao
    char desCampo2[max]; // Nota
    char desCampo3[max]; // Data
    char desCampo4[max]; // Cidade
    char desCampo5[max]; // Nome da escola

} Cabecalho;

typedef struct {
    char removido;    // Recebe "*" caso o registro fora removido e "-" caso nao foi removido
    int encadeamento; // Armazena os RRNs dos registros logicamente removidos
    int nroInscricao;
    double nota;
    char data[10];
    char cidade[max];
    char nomeEscola[max];
    int contCity;
    int contSchool;

} Registro;

void Inicializa_Remove(Registro *removed); // Atualiza o removido e encadeamento
void inicializaCabecalho(Cabecalho *aux); // Seta os valores do cabecalho
void Escreve_RegCabecalho(Cabecalho *aux, FILE *arq); // Escreve o registro de cabecalho na primeira pagina de disco
void Le_RegDados_CSV(FILE *arq_read, Registro *leitura, char str[]); // Le do arquivo .csv
void Escreve_RegDados(Registro *leitura, FILE *arq_escreve); // Escreve em um novo arquivo os dados do registro
void Recupera_Dados(FILE *arquivo); // Recupera e imprime todo o arquivo
void Le_Registro(Registro *leitura, FILE *arquivo); // Le os dados de um registro do arquivo
void Imprime_Registro(Registro *leitura); // Imprimir os dados de um registro do arquivo
void Busca_Registro(char nome_arquivo[], char nome_campo[], char valor[]); // Busca um registro por determinado campo e valor
int Busca_por_Campo(FILE *nome_arquivo, char *nome_campo, char *valor, Registro leitura); // Busca determinado campo no arquivo
int Remove_Registro(FILE *arquivo, int topo); // Remove um registro do arquivo
void RRN(char nome_arquivo[], int rrn); // Busca um registro pelo seu RRN
void Escreve_Registro(Registro leitura, FILE *arq); // Escreve um registro em um arquivo
int Insercao_Registro(Registro leitura, int topo, FILE *arq); // Insere um registro em um espaco disponivel no arquivo
void Atualiza_Campo(FILE *arq, char nome_campo[], char valor[], Registro leitura); // Muda o valor de um campo especifico

// Funcoes usadas dos monitores
void binarioNaTela1(FILE *ponteiroArquivoBinario);
void binarioNaTela2(char *nomeArquivoBinario);
void trim(char *str);
void scan_quote_string(char *str);
