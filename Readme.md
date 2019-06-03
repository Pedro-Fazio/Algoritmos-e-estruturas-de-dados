
# Trabalho Prático de Algoritmos e estruturas de dados II

Este trabalho tem como objetivo armazenar dados em um arquivo binário de acordo com uma organização de campos e registros, bem como recuperar os dados armazenados; também é uma de suas funcionalidades realizar operações de inserção, remoção e atualização de dados baseadas na abordagem dinâmica de reaproveitamento de espaços de registros logicamente removidos.

 
***Funcionalidades:***

No projeto foram utilizadas algumas funcionalidades para manipular o arquivo recebido, sendo elas:

Função 1:
* Permite a leitura de vários registros obtidos a partir de um arquivo de entrada
(arquivo no formato CSV).
* Gera como saída um arquivo binário com os registros lidos gravados no mesmo.

*Entrada do programa para a funcionalidade [1]:*
1 arquivo.csv // arquivo de entrada no formato .csv
*Saída caso o programa seja executado com sucesso:*
arquivoTrab1si.bin
*Mensagem de saída caso algum erro seja encontrado:*
Falha no carregamento do arquivo.
*Exemplo de execução:*
./programaTrab1
1 arquivo.csv
arquivoTrab1si.bin


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