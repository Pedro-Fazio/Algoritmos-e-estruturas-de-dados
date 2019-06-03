
**Trabalho Prático de Algoritmos e estruturas de dados II**


    Este trabalho tem como objetivo armazenar dados em um arquivo binário de acordo com uma organização de campos e registros, bem como recuperar os dados armazenados; também é uma de suas funcionalidades realizar operações de inserção, remoção e atualização de dados baseadas na abordagem dinâmica de reaproveitamento de espaços de registros logicamente removidos.

 
***Descrição das funcionalidades:***

#1: ds


'''
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
'''