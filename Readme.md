
# Trabalho Prático de Algoritmos e estruturas de dados II

Este trabalho tem como objetivo armazenar dados em um arquivo binário de acordo com uma organização de campos e registros, bem como recuperar os dados armazenados; também é uma de suas funcionalidades realizar operações de inserção, remoção e atualização de dados baseadas na abordagem dinâmica de reaproveitamento de espaços nos registros logicamente removidos.

 
## ***Funcionalidades:***

No projeto foram utilizadas algumas funcionalidades para manipular o arquivo de dados, sendo elas:

**Função 1:**
* Permite a leitura de vários registros obtidos a partir de um arquivo de entrada
(arquivo no formato CSV).
* Gera como saída um arquivo binário com os registros lidos gravados no mesmo.

***Entrada do programa para a funcionalidade [1]:***  
1 arquivo.csv // arquivo de entrada no formato .csv  
***Saída caso o programa seja executado com sucesso:***   
arquivoTrab1si.bin  
***Mensagem de saída caso algum erro seja encontrado:***    
Falha no carregamento do arquivo.  
***Exemplo de execução:***    
./programaTrab1  
1 arquivo.csv  
arquivoTrab1si.bin  

**Função 2:**
* Permite a recuperação de dados de todos os registros armazenados no arquivo de dados, mostrando os dados de forma organizada na saída.
* O tratamento de "lixo" é realizado para que tenha uma saída padrão e permita a distinção dos campos e registros.
* Exibe a quantidade de página de disco acessadas.

***Entrada do programa para a funcionalidade [2]:***    
2 arquivo.bin //arquivo binário gerado na funcionalidade [1]  
***Saída caso o programa seja executado com sucesso:***  
Cada registro deve ser mostrado em uma única linha e os seus campos devem ser mostrados de forma sequencial separado por espaço. Campos de tamanho fixo que tiverem o valor nulo não devem mostrados. Para os campos com tamanho variável, mostre também sua quantidade de caracteres (tamanhos em bytes sem o caractere '\0'). Para os campos de tamanho variável com valores nulos, não deve ser exibido nada. Ao final, deve ser exibido o número de páginas de disco acessadas.  
***Mensagem de saída caso não existam registros:***    
Registro inexistente.  
***Mensagem de saída caso algum erro seja encontrado:***    
Falha no processamento do arquivo.  
***Exemplo de execução (são mostrados apenas 2 registros):***   
./programaTrab1  
2 arquivo.bin  
439 607.5 01/01/2004 6 Maceio 8 PEDRO II  
387 9 Sao Paulo 10 JOAO KOPKE  
Número de páginas de disco acessadas: 25  

**Função 3:**
* Permite a recuperação de todos os registros que satisfaçam um critério de busca determinado pelo usuário.
* O critério de busca é determinado pelo nome do campo, como por exemplo: *número de inscrição; data; nota; nome da escola ou cidade.*
* Exibe os registros com o critério escolhido pelo usuário.
* Mostra o número de página de disco acessadas.

***Sintaxe do comando para a funcionalidade [3]:***  
3 arquivo.bin NomeDoCampo valor  
***Saída caso o programa seja executado com sucesso:***  
Podem ser encontrados vários registros que satisfaçam à condição de busca. Cada registro deve ser mostrado em uma única linha e os seus campos devem ser mostrados de forma sequencial separado por espaço. Campos de tamanho fixo que tiverem o valor nulo não devem mostrados. Para os campos com tamanho variável, mostre também seu mostre também sua quantidade de caracteres (tamanhos em bytes sem o caractere '\0'). Para os campos de tamanho variável com valores nulos, não deve ser exibido nada. Ao final, deve ser exibido o número de páginas de disco acessadas.  
***Mensagem de saída caso não seja encontrado o registro que contém o valor do campo ou o campo pertence a um registro que esteja removido:***  
Registro inexistente.  
***Mensagem de saída caso algum erro seja encontrado:***  
Falha no processamento do arquivo.  
Exemplo de execução (é mostrado apenas o primeiro registro que satisfez à busca, embora a funcionalidade provida pelo programa deva exibir mais do que um registro quando for o caso):  
./programaTrab1  
3 nroInscricao 332  
332 400.8 03/01/2004 8 Brasilia 29 REINALDO RIBEIRO DA SILVA DOU  
Número de páginas de disco acessadas: 1  

**Função 4:**
* Permite a recuperação de dados de um registro a partir da identificação do RRN (número relativo do registro).
* Exibe o registro solicitado pelo usuário através RRN solicitado.
* Mostra o número de páginas de disco acessadas.

***Sintaxe do comando para a funcionalidade [4]:***  
4 arquivo.bin RRN  
***Saída caso o programa seja executado com sucesso:***  
Será recuperado, no máximo, 1 registro. O registro deve ser mostrado em uma única linha e os seus campos devem ser mostrados de forma sequencial separado por espaço. Campos de tamanho fixo que tiverem o valor nulo não devem mostrados. Para os campos com tamanho variável, mostre também seu mostre também sua quantidade de caracteres (tamanhos em bytes sem o caractere '\0'). Para os campos de tamanho variável com valores nulos, não deve ser exibido nada. Ao final, deve ser exibido o número de páginas de disco acessadas.  
***Mensagem de saída caso não seja encontrado o registro ou o registro esteja removido:***  
Registro inexistente.  
***Mensagem de saída caso algum erro seja encontrado:***  
Falha no processamento do arquivo.  
***Exemplo de execução:***  
./programaTrab1  
4 arquivo.bin 1  
387 9 Sao Paulo 10 JOAO KOPKE  
Número de páginas de disco acessadas: 1  

**Função 5:**
* Permite a remoção lógica de registros baseado na abordagem dinâmica de reaproveitamento de espaços.
* Implementação fora realizada utilizando o conceito de **pilha**
* A **remoção** é realizada seguindo o critério de busca determinado pelo usuário, utilizando-se dos campos como forma de busca, como por exemplo: *número de inscrição; data; nota; nome da escola ou cidade.*
* Todos os registros logicamente removidos serão preenchidos com **lixo**.
* Essa funcionalidade será executada **n** vezes, que será um número determinado pelo próprio usuário.
* Escreve na tela todo o arquivo de dados utilizando-se do **sistema numérico hexadecimal**.

***Entrada do programa para a funcionalidade [5]:***  
5 arquivo.bin n  
nomeCampo1 valorCampo1  
nomeCampo2 valorCampo2  
...  
nomeCampon valorCampon  
***Onde:***  
- arquivo.bin é um arquivo binário de entrada que segue as mesmas especificações definidas no primeiro trabalho prático. As remoções a serem realizadas nessa funcionalidade devem ser feitas nesse arquivo. - n é o número de remoções a serem realizadas. Para cada remoção, deve ser informado o nome do campo a ser considerado e seu critério de busca representado pelo valor do campo. Cada uma das n remoções deve ser especificada em uma linha diferente. Deve ser deixado um espaço em branco entre o nome do campo e o valor do campo. Os valores dos campos do tipo string devem ser especificados entre aspas
duplas (").  
***Saída caso o programa seja executado com sucesso:***  
Listar o arquivo binário arquivo.bin.  
***Mensagem de saída caso algum erro seja encontrado:***  
Falha no processamento do arquivo.  
***Exemplo de execução:***  
./programaTrab2  
5 arquivo.bin 2  
nroInscricao 546  
data "14/01/2004"  

**Função 6:**
* Permite a **inserção** de registros adicionais baseado na abordagem dinâmica de reaproveito de espaços.
* Implementação fora realizada utilizando o conceito de **pilha**.
* Caso haja reaproveitamento de um registro marcado logicamente como removido, esse registro será sobrescrito completamente.
* Essa funcionalidade será executada **n** vezes, que será um número determinado pelo próprio usuário.
* Escreve na tela todo o arquivo de dados utilizando-se do **sistema numérico hexadecimal**.

***Entrada do programa para a funcionalidade [6]:***  
6 arquivo.bin n  
valorNroInscricao1 valorNota1 valorData1 valorCidade1 valorNomeEscola1  
valorNroInscricao2 valorNota2 valorData2 valorCidade2 valorNomeEscola2  
...  
valorNroInscricaon valorNotan valorDatan valorCidaden valorNomeEscolan  
***Onde:***  
- arquivo.bin é um arquivo binário de entrada que segue as mesmas especificações definidas no primeiro trabalho prático. As inserções a serem realizadas nessa funcionalidade devem ser feitas nesse arquivo. - n é o número de inserções a serem realizadas. Para cada inserção, deve ser informado os valores a serem inseridos no arquivo, para os campos especificados na mesma ordem que a definida no primeiro trabalho prático, a saber: nroInscrição, nota, data,cidade, nomeEscola. Não existe truncamento de dados. Valores nulos devem ser identificados, na entrada da funcionalidade, por NULO. Cada uma das n inserções deve ser especificada em uma linha diferente. Deve ser deixado um espaço em branco entre os valores dos campos. Os valores dos campos do tipo string devem ser especificados entre aspas duplas (").  
***Saída caso o programa seja executado com sucesso:***  
Listar o arquivo binário arquivo.bin.  
***Mensagem de saída caso algum erro seja encontrado:***  
Falha no processamento do arquivo.  
***Exemplo de execução:***  
./programaTrab2  
6 arquivo.bin 2  
1234 109.98 NULO NULO "ESCOLA DE ESTUDO PRIMÁRIO"  
2132 408.02 "01/08/2016" "CAMPINAS" NULO  

**Função 7**
* Permite a atualização de um campo específico de um registro identificado por seu RRN.
* O que sobrou do registro após a atualização será preenchido com **lixo**.
* Essa funcionalidade será executada **n** vezes, que será um número determinado pelo próprio usuário.
* Escreve na tela todo o arquivo de dados utilizando-se do **sistema número hexadecimal**.

***Entrada do programa para a funcionalidade [7]:***  
7 arquivo.bin n  
RRN nomeCampo1 valorCampo1  
RRN nomeCampo2 valorCampo2  
...  
RRN nomeCampon valorCampon  
***Onde:***  
- arquivo.bin é um arquivo binário de entrada que segue as mesmas especificações definidas no primeiro trabalho prático. As atualizações a serem realizadas nessa funcionalidade devem ser feitas nesse arquivo. - n é o número de atualizações a serem realizadas. Para cada atualização, deve ser
informado o valor do RRN do registro, o campo do registro a ser alterado e o novo valor desse campo. Não existe truncamento de dados. Valores nulos devem ser identificados, na entrada da funcionalidade, por NULO. Cada uma das n atualizações deve ser especificada em uma linha diferente. Deve ser deixado um espaço em branco entre o RRN e o nome do campo, e entre o nome do campo e o valor do campo. Os valores dos campos do tipo string devem ser especificados entre aspas duplas (").  
***Saída caso o programa seja executado com sucesso:***  
Listar o arquivo binário arquivo.bin.  
***Mensagem de saída caso algum erro seja encontrado:***  
Falha no processamento do arquivo.  
***Exemplo de execução:***  
./programaTrab2  
7 arquivo.bin 2  
1 nomeEscola "ESCOLA DE ENSINO"  
5 data "07/07/2007"  

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
