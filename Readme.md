
# Trabalho Prático de Algoritmos e estruturas de dados II

Este trabalho tem como objetivo armazenar dados em um arquivo binário de acordo com uma organização de campos e registros, bem como recuperar os dados armazenados; também é uma de suas funcionalidades realizar operações de inserção, remoção e atualização de dados baseadas na abordagem dinâmica de reaproveitamento de espaços de registros logicamente removidos.

 
## ***Funcionalidades:***

No projeto foram utilizadas algumas funcionalidades para manipular o arquivo recebido, sendo elas:

**Função 1:**
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

**Função 2:**
* Permite a recuperação de dados de todos os registros armazenados no arquivo de dados, mostrando os dados de forma organizada na saída.
* O tratamento de "lixo" é realizado para que tenha uma saída padrão e permita a distinção dos campos e registros.
* Exibe a quantidade de página de disco acessadas.

*Entrada do programa para a funcionalidade [2]:*  
2 arquivo.bin //arquivo binário gerado na funcionalidade [1]  
*Saída caso o programa seja executado com sucesso:*  
Cada registro deve ser mostrado em uma única linha e os seus campos devem ser mostrados de forma sequencial separado por espaço. Campos de tamanho fixo que tiverem o valor nulo não devem mostrados. Para os campos com tamanho variável, mostre também sua quantidade de caracteres (tamanhos em bytes sem o caractere '\0'). Para os campos de tamanho variável com valores nulos, não deve ser exibido nada. Ao final, deve ser exibido o número de páginas de disco acessadas. 
*Mensagem de saída caso não existam registros:*  
Registro inexistente.  
*Mensagem de saída caso algum erro seja encontrado:*    
Falha no processamento do arquivo.  
*Exemplo de execução (são mostrados apenas 2 registros):*  
./programaTrab1  
2 arquivo.bin  
439 607.5 01/01/2004 6 Maceio 8 PEDRO II  
387 9 Sao Paulo 10 JOAO KOPKE  
Número de páginas de disco acessadas: 25  

## Structs

**Struct do Cabeçalho:**

Essa struct possue valores constantes, pois os valores serão utilizados apenas para preencher o registro de cabecalho, que por sua vez, será a primeira página de disco; sendo assim, não há necessidade de altera-los.

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

**Struct do Registro**

Essa struct apresenta diversas funcionalidades para o algoritmo, porém sua principal função é guardar, temporariamente, o registro que for lido do arquivo, para que ele possa ser editado e reescrito no mesmo ou em outro arquivo de dados.

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
