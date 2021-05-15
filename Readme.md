# Introdução

Esse repositório conta com dois projetos que foram desenvolvidos para Algoritmos e estruturas de dados I e II.

# Trabalho Prático de Algoritmos e estruturas de dados I - Pilha

Este trabalho tem como objetivo aplicar os conhecimentos sobre pilha, desta forma será implementado uma pilha capaz de fazer tais manipulações com os dados

- Inserção
- Remoção
- Verificação

# Trabalho Prático de Algoritmos e estruturas de dados II - Participantes do ENEM

Este trabalho tem como objetivo armazenar dados em um arquivo binário de acordo com uma organização de campos e registros, bem como recuperar os dados armazenados; também é uma de suas funcionalidades realizar operações de inserção, remoção e atualização de dados baseadas na abordagem dinâmica de reaproveitamento de espaços nos registros logicamente removidos.

## Informações básicas sobre o projeto:

- O projeto todo foi desenvolvido com auxílio a linguagem C.
- O projeto consiste em fazer manipulações com dados de participantes do enem, se utilizando de arquivos de dados; trabalhar com conceitos de registros, páginas de disco e campos fixos/variáveis.
- No projeto é utilizado registros de tamanho fixo e campos de tamanho fixos e variáveis.
- As páginas de disco e registros possuem, por padrão, 16000 bytes e 80 bytes, respectivamente.
- Quando não há mais dados para serem escritos, o restante da página de disco é preenchida com lixo (caractere: "@").

## Registro de cabeçalho

O registro de cabeçalho ocupa uma pagina de disco completa (16000 bytes) e contêm os seguintes campos:  

• **status:** indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. Pode assumir os valores 0, para indicar que o arquivo de dados está inconsistente, ou 1, para indicar que o arquivo de dados está consistente. Ao se abrir um arquivo para escrita, seu status deve ser 0 e, ao finalizar o uso desse arquivo, seu status deve ser 1 – tamanho: string de 1 byte.  
• **topoPilha:** armazena o RRN de um registro logicamente removido, ou -1 caso não haja registros logicamente removidos – tamanho: inteiro de 4 bytes.  
• **tagCampo1:** valor resumido da tag para o campo nroInscricao. Deve assumir o valor 1 – tamanho: string de 1 byte.  
• **desCampo1:** descrição completa do campo nroInscricao. Deve assumir o valor ‘numero de inscricao do participante do ENEM’ – tamanho: string de 55 bytes.  
• **tagCampo2:** valor resumido da tag para o campo nota. Deve assumir o valor 2 – tamanho: string de 1 byte.  
• **desCampo2:** descrição completa do campo nota. Deve assumir o valor ‘nota do participante do ENEM na prova de matematica’ – tamanho: string de 55 bytes.  
• **tagCampo3:** valor resumido da tag para o campo data. Deve assumir o valor 3 – tamanho: string de 1 byte.  
• **desCampo3:** descrição completa do campo data. Deve assumir o valor ‘data’ – tamanho: string de 55 bytes.  
• **tagCampo4:** valor resumido da tag para o campo cidade. Deve assumir o valor 4 – tamanho: string de 1 byte.  
• **desCampo4:** descrição completa do campo cidade. Deve assumir o valor ‘cidade na qual o participante do ENEM mora’ – tamanho: string de 55 bytes.  
• **tagCampo5:** valor resumido da tag para o campo nomeEscola. Deve assumir o valor 5 – tamanho: string de 1 byte.  
• **desCampo5:** descrição completa do campo nomeEscola. Deve assumir o valor ‘nome da escola de ensino medio’ – tamanho: string de 55 bytes 

**Representação Gráfica do Registro de Cabeçalho** 
O tamanho do registro de cabeçalho deve ser de 285 bytes, representado da seguinte forma:  
                            **IMAGEM**

## Registros de Dados. 

Cada registro do arquivo de dados contém dados relacionados aos participantes do ENEM. Esses dados foram gerados usando dados reais obtidos do ENEM e também dados sintéticos. Cada registro representa um participante do ENEM e contém os seguintes campos:  

• **Campos de tamanho fixo: 22 bytes**
• nroInscricao – inteiro – tamanho: 4 bytes
• nota – número de dupla precisão – tamanho: 8 bytes
• data – tamanho: 10 bytes, no formato DD/MM/AAAA
• **Campos de tamanho variável:**
• cidade – string de tamanho variável
• nomeEscola – string de tamanho variável

Os dados dos participantes do ENEM são fornecidos juntamente com as pastas deste trabalho prático por meio de um arquivo .csv.

Além de armazenar os dados relacionados aos participantes do ENEM, cada registro de dados conterá campos adicionais relacionados à remoção de registros logicamente removidos. Esses campos são:  
• **removido:** indica se o registro se encontra removido ou não. Pode assumir os valores ‘*’, para indicar que o registro é um registro removido, ou ‘-’, para indicar que o registro não é um registro removido – tamanho: string de 1 byte.
• **encadeamento:** armazena os RRNs dos registros logicamente removidos – tamanho: inteiro de 4 bytes.
Representação Gráfica do Registro de Dados. O tamanho de cada registro de dados deve ser de 80 bytes, representado da seguinte forma:
                            **IMAGEM**


## Funcionalidades:

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
Cada registro será mostrado em uma única linha e os seus campos serão mostrados de forma sequencial separado por espaço. Campos de tamanho fixo que tiverem o valor nulo não serão mostrados. Para os campos com tamanho variável, será revelado também sua quantidade de caracteres (tamanhos em bytes sem o caractere '\0'). Para os campos de tamanho variável com valores nulos, não será exibido nada. Ao final, será apresentado o número de páginas de disco acessadas.  
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
Podem ser encontrados vários registros que satisfaçam à condição de busca. Portanto, cada registro será exibido em uma única linha e os seus campos de forma sequencial separado por espaço. Campos de tamanho fixo que tiverem o valor nulo serão mostrados. Para os campos com tamanho variável, aparecerá também sua quantidade de caracteres (tamanhos em bytes sem o caractere '\0'). Para os campos de tamanho variável com valores nulos, será exibido nada. Ao final, será apresentado o número de páginas de disco acessadas.  
***Mensagem de saída caso não seja encontrado o registro que contém o valor do campo ou o campo pertence a um registro que esteja removido:***  
Registro inexistente.  
***Mensagem de saída caso algum erro seja encontrado:***  
Falha no processamento do arquivo.  
**Exemplo de execução (é mostrado apenas o primeiro registro que satisfez à busca, embora a funcionalidade provida pelo programa exibe mais do que um registro quando for o caso):**    
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
Será recuperado, no máximo, 1 registro. O registro será mostrado em uma única linha e os seus campos de forma sequencial separado por espaço. Campos de tamanho fixo que tiverem o valor nulo não serão mostrados. Para os campos com tamanho variável, é revelado também sua quantidade de caracteres (tamanhos em bytes sem o caractere '\0'). Para os campos de tamanho variável com valores nulos, não será exibido nada. Ao final, é apresentado o número de páginas de disco acessadas.  
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
arquivo.bin é um arquivo binário de entrada que segue as mesmas especificações definidas no trabalho prático. As remoções a serem realizadas nessa funcionalidade serão feitas no mesmo arquivo. - *n* é o número de remoções a serem realizadas. Para cada remoção é informado o nome do campo a ser considerado e, também, o seu critério de busca representado pelo valor do campo. Cada uma das *n* remoções é especificada em uma linha diferente. Será deixado um espaço em branco entre o nome do campo e o valor do campo.
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
arquivo.bin é um arquivo binário de entrada que segue as mesmas especificações definidas no trabalho prático. As inserções a serem realizadas nessa funcionalidade serão feitas no mesmo arquivo. - *n* é o número de inserções a serem realizadas. Para cada inserção é informado os valores a serem inseridos no arquivo, para os campos especificados na mesma ordem que a definida no trabalho prático, a saber: nroInscrição, nota, data,cidade, nomeEscola. Não existe truncamento de dados. Valores nulos serão identificados na entrada da funcionalidade por NULO. Cada uma das *n* inserções é especificada em uma linha diferente. Será deixado um espaço em branco entre os valores dos campos.
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
arquivo.bin é um arquivo binário de entrada que segue as mesmas especificações definidas no trabalho prático. As atualizações a serem realizadas nessa funcionalidade serão feitas no mesmo arquivo. - *n* é o número de atualizações a serem realizadas. Para cada atualização, é informado o valor do RRN do registro, o campo do registro a ser alterado e o novo valor desse campo. Não existe truncamento de dados. Valores nulos são identificados na entrada da funcionalidade por NULO. Cada uma das *n* atualizações é especificada em uma linha diferente. Será deixado um espaço em branco entre o RRN e o nome do campo, e entre o nome do campo e o valor do campo. 
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

# Conclusão

Com esse projeto foi possível aprender diversas técnicas muito importantes para o desenvolvimento de códigos em C se utilizando das principais estruturas de dados.