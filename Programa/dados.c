#include "trab.h"
// Definicoes
#define tamPagDisco 16000
#define tamRegistroCab 285
#define tamStringDesc 55
#define tamCamposFixos 27
#define tamRegistro 80

void inicializaCabecalho(Cabecalho *aux) {
    //status atualizado para 1 ao final da escrita de todos registros
    aux->status = '1'; 
    aux->topoPilha = -1;
    char lixo[40];
    char *ptr;

    for(int i = 0; i < 52; i++) lixo[i] = '@';

    aux->tagCampo1 = '1';
    strcpy(aux->desCampo1, "numero de inscricao do participante do ENEM.");
    strncat(aux->desCampo1, lixo, 11);
    ptr = strchr(aux->desCampo1, '.');
    *ptr = '\0';

    aux->tagCampo2 = '2';
    strcpy(aux->desCampo2, "nota do participante do ENEM na prova de matematica.");
    strncat(aux->desCampo1, lixo, 3);
    ptr = strchr(aux->desCampo2, '.');
    *ptr = '\0';

    aux->tagCampo3 = '3';
    strcpy(aux->desCampo3, "data.");
    strncat(aux->desCampo1, lixo, 50);
    ptr = strchr(aux->desCampo3, '.');
    *ptr = '\0';

    aux->tagCampo4 = '4';
    strcpy(aux->desCampo4, "cidade na qual o participante do ENEM mora.");
    strncat(aux->desCampo1, lixo, 12);
    ptr = strchr(aux->desCampo4, '.');
    *ptr = '\0';

    aux->tagCampo5 = '5';
    strcpy(aux->desCampo5, "nome da escola de ensino medio.");
    strncat(aux->desCampo1, lixo, 24);
    ptr = strchr(aux->desCampo5, '.');
    *ptr = '\0';
}
void Escreve_RegCabecalho(Cabecalho *aux, FILE *arq) {  
    char lixo = '@';

    fwrite(&aux->status, sizeof(char), 1, arq);
    fwrite(&aux->topoPilha, sizeof(int), 1, arq);

    fwrite(&aux->tagCampo1, sizeof(char), 1, arq);
    fwrite(&aux->desCampo1, max, 1, arq);

    fwrite(&aux->tagCampo2, sizeof(char), 1, arq);
    fwrite(&aux->desCampo2, max, 1, arq);

    fwrite(&aux->tagCampo3, sizeof(char), 1, arq);
    fwrite(&aux->desCampo3, max, 1, arq);

    fwrite(&aux->tagCampo4, sizeof(char), 1, arq);
    fwrite(&aux->desCampo4, max, 1, arq);

    fwrite(&aux->tagCampo5, sizeof(char), 1, arq);
    fwrite(&aux->desCampo5, max, 1, arq);

    // Escreve lixo ate completar o resto da pagina de disco
    for(int i = 0; i < tamPagDisco - tamRegistroCab; i++) 
        fputc(lixo, arq);
}

void Inicializa_Remove(Registro *removed) { // Serve pra atualizar os removidos
    removed->removido = '-';
    removed->encadeamento = -1;
}
void Le_RegDados_CSV(FILE *arq_read, Registro *leitura, char str[]) {
    char *ptr; // Usado para ler todo o arquivo

    fgets(str, 80, arq_read); // Coloca todo o registro na string

    leitura->nroInscricao = strtol(str, &ptr, 10); // Le o numero de inscricao;
                                                  //strol transforma o int do nroInscricao em string

    ptr++; // Incrementa o ponteiro pra nao ler a ","

    if (*ptr != ',')
        leitura->nota = strtod(ptr, &ptr); // Le a nota e usa o strtof para transformar float em string
    else
        leitura->nota = -1; // Caso a nota esteja vazia

    ptr++; // Incrementa o ponteiro pra nao ler a ","

    if (*ptr != ',') {
        strncpy(leitura->data, ptr, 10); // Le a data e atualiza o ponteiro para +10, pois a data sempre tera 10 caracteres
        ptr += 10;
    }
    else { // Caso a DATA esteja vazia
        leitura->data[leitura->contCity] = '\0';
        while (leitura->contCity < 10) { // Usei a variavel contCity para contar ate o 10 para que nao precisasse criar um contador
            leitura->data[++leitura->contCity] = '@';
        }
    }
    ptr++; // Incrementa o ponteiro pra nao ler a ","
    leitura->contCity = 0; // Atualiza o contCity, pois eu o usei no caso da data estiver vazia

    while (*ptr != ',') {
        leitura->cidade[leitura->contCity++] = *ptr; // Le a cidade ate que o ponteiro chegue na virgula
        ptr++;
    }
    leitura->cidade[leitura->contCity] = '\0'; // Caso tenha passado pelo while, o contCity estara no final da string; caso nao tenha passado, entao o contCity estara na posicao 0
    ptr++;                                   // Incrementa o ponteiro pra nao ler a ","

    if (*ptr != ',') {

        leitura->contSchool = 0;

        while (*ptr != '\n') { // Continua lendo enquanto nao acabar a string
            leitura->nomeEscola[leitura->contSchool++] = *ptr;
            ptr++;
        }
        leitura->nomeEscola[leitura->contSchool] = '\0'; // Le o \0 depois do while
    }
    else
        leitura->nomeEscola[0] = '\0'; // Coloca \0 se o campo nome da escola estiver vazio
}

void Escreve_RegDados(Registro *aux, FILE *arq_escreve) {
    int size = 0; // Para calcular o quanto foi escrito e o quanto de lixo colocar para completar o registro
    Registro leitura = *aux;
    Cabecalho campo; // Eh so para pegar as tags dos campos 4 e 5
    char lixo = '@';

    // Escreve os campos fixos
    fwrite(&leitura.removido, 1, 1, arq_escreve);

    fwrite(&leitura.encadeamento, 4, 1, arq_escreve);

    fwrite(&leitura.nroInscricao, 4, 1, arq_escreve);

    fwrite(&leitura.nota, 8, 1, arq_escreve);

    fwrite(&leitura.data, 10, 1, arq_escreve);

    size = 27;

    // Escreve os campos variaveis
    if (leitura.cidade[0] != '\0') { // Se for diferente de \0, significa que nao esta vazio, entao escreve, mas se for \0 entao esta vazio e nao escreve nada
        fwrite(&leitura.contCity, 4, 1, arq_escreve); // Indicador de tamanho
        fwrite(&campo.tagCampo4, 1, 1, arq_escreve);
        fwrite(leitura.cidade, 1, leitura.contCity, arq_escreve);
        size += leitura.contCity + 5;
    }

    if (leitura.nomeEscola[0] != '\0') { // Se for diferente de \0, significa que nao esta vazio, entao escreve, mas se for \0 entao esta vazio e nao escreve nada
        fwrite(&leitura.contSchool, 4, 1, arq_escreve); // Indicador de tamanho
        fwrite(&campo.tagCampo5, 1, 1, arq_escreve);
        fwrite(leitura.nomeEscola, 1, leitura.contSchool, arq_escreve);
        size += leitura.contSchool + 5;
    }

    // Coloca lixo no resto do arquivo
    for (int i = 0; i < 80 - size; i++) {
        fputc(lixo, arq_escreve);
    }

}

void Recupera_Dados(FILE *arquivo) {
    Registro leitura;
    int pag_disco = 1; // Comeca em 1 pois ja leu o registro de cabecalho
    int cont = 0;

        fseek(arquivo, tamPagDisco, SEEK_SET);
        while(fread(&leitura.removido, 1, 1, arquivo)) { // Verifica se ainda dar pra ler, se nao der eh pq o arquivo chegou ao fim
            Le_Registro(&leitura, arquivo); //Le e imprime todos os registros
            if(leitura.removido == '-')
                Imprime_Registro(&leitura);
            cont += 80; // Significa que leu um registro
            if(cont >= tamPagDisco) { // Se o numero de registros lidos der 1600, entao aumenta 1 pagina de disco
                pag_disco++;
                cont = tamPagDisco - cont;
            }
        }
        if(cont > 0) // Para caso tenha lido registros mas nao chegou a dar 1600, porem foi usado 1 pagina de disco mesmo assim
            pag_disco++;
        printf("Número de páginas de disco acessadas: %d", pag_disco);

    return;
}

void Le_Registro(Registro *leitura, FILE *arquivo) {
    char tagCampo;
    leitura->nomeEscola[0] = '\0';
    leitura->cidade[0] = '\0';

    // Le os campos fixos
    fread(&leitura->removido, sizeof(char), 1, arquivo);
    fread(&leitura->encadeamento, sizeof(int), 1, arquivo);
    fread(&leitura->nroInscricao, sizeof(int), 1, arquivo);
    fread(&leitura->nota, sizeof(double), 1, arquivo);
    fread(leitura->data, 10 * sizeof(char), 1, arquivo);

    leitura->data[10] = '\0'; // Atribui o \0 no final da string

    if (fgetc(arquivo) == 64) { // Os 2 campos sao nulos
        fseek(arquivo, 52, SEEK_CUR);
    }
    else { // Le os registros para as verificacoes
        fseek(arquivo, -1, SEEK_CUR);
        fread(&leitura->contCity, sizeof(int), 1, arquivo);
        fread(&tagCampo, sizeof(char), 1, arquivo);

        if(tagCampo == '4') { // Cidade nao eh nulo
            fread(leitura->cidade, --leitura->contCity, 1, arquivo);
        }else if(tagCampo == '5') { // Cidade eh nulo e nomeEscola nao eh nulo
            leitura->contSchool = --leitura->contCity;
            leitura->contCity = 0;
            fread(leitura->nomeEscola, leitura->contSchool, 1, arquivo);
            fseek(arquivo, 80 - (32 + leitura->contSchool), SEEK_CUR);
            return;
        }
        if(fgetc(arquivo) == 64) { // Cidade e nomeEscola sao nulos
            leitura->contSchool = 0;
            fseek(arquivo, 47 - leitura->contCity, SEEK_CUR);
        }
        else { // Cidade eh nulo e nomeEScola nao eh nulo
            fseek(arquivo, -1, SEEK_CUR);
            fread(&leitura->contSchool, sizeof(int), 1, arquivo);
            fgetc(arquivo);
            fread(leitura->nomeEscola, sizeof(char), --leitura->contSchool, arquivo);
            fseek(arquivo, 43 - (leitura->contCity + leitura->contSchool), SEEK_CUR);
        }
    }
    return;
}

void Imprime_Registro(Registro *leitura) {

    printf("%d", leitura->nroInscricao);

    if (leitura->nota != -1) // Se nota nao for nulo, imprime
        printf(" %.1f", leitura->nota);

    if (!leitura->data[0] == '\0')  { // Se a data nao for nula
        printf(" "); // Espaco para comecar a escrever a data
        for (int i = 0; i < 10; i++) {
        printf("%c", leitura->data[i]);
        }
    }
    if (leitura->cidade[0] != '\0') // Se o indicador de tamanho da cidade for maior que zero, imprime cidade
        printf(" %d %s", --leitura->contCity, leitura->cidade);

    if (leitura->nomeEscola[0] != '\0') // Se o indicador de tamanho de nomeEscola for maior que zero, imprime nomeEscola
        printf(" %d %s", --leitura->contSchool, leitura->nomeEscola);

    printf("\n");

    return;
}

void Busca_Registro(char nome_arquivo[], char nome_campo[], char valor[]) {
    Registro leitura;
    int op;
    int pag_disco = 1; // Comeca em 1 pois ja leu o registro de cabecalho
    int cont = 0;
    int flag = 0; // Para verificar se o valor solicitado existe

    FILE *arquivo = fopen(nome_arquivo, "rb");

    if(arquivo == NULL)
        printf("Falha no processamento do arquivo.");

    // Verifica qual eh o campo desejado
    if(strcmp(nome_campo, "nroInscricao") == 0)
        op = 1;

    if(strcmp(nome_campo, "nota") == 0)
        op = 2;

    if(strcmp(nome_campo, "data") == 0)
        op = 3;

    if(strcmp(nome_campo, "cidade") == 0)
        op = 4;

    if(strcmp(nome_campo, "nomeEscola") == 0)
        op = 5;

    fseek(arquivo, tamPagDisco, SEEK_SET);

    switch(op){
        case 1:
            while(fread(&leitura.removido, 1, 1, arquivo)) { // Verifica se ainda dar pra ler, se nao der eh pq o arquivo chegou ao fim
                Le_Registro(&leitura, arquivo); //Le e imprime todos os registros
                    if(leitura.nroInscricao == atoi(valor)) {
                        Imprime_Registro(&leitura);
                        flag++;
                        pag_disco++;
                        break;
                    }
                cont += 80; // Significa que leu um registro
                    if(cont >= tamPagDisco) { // Se o numero de registros lidos der 1600, entao aumenta 1 pagina de disco
                    pag_disco++;
                    cont = tamPagDisco - cont;
                    }
            }
        break;

        case 2:
            while(fread(&leitura.removido, 1, 1, arquivo)) { // Verifica se ainda dar pra ler, se nao der eh pq o arquivo chegou ao fim
                Le_Registro(&leitura, arquivo); //Le e imprime todos os registros
                    if(leitura.nota == atof(valor)) {
                        Imprime_Registro(&leitura);
                        flag++;
                    }
                cont += 80; // Significa que leu um registro
                    if(cont >= tamPagDisco) { // Se o numero de registros lidos der 1600, entao aumenta 1 pagina de disco
                    pag_disco++;
                    cont = tamPagDisco - cont;
                    }
            }
        break;

        case 3:
            while(fread(&leitura.removido, 1, 1, arquivo)) { // Verifica se ainda dar pra ler, se nao der eh pq o arquivo chegou ao fim
                Le_Registro(&leitura, arquivo); //Le e imprime todos os registros
                    if(strncmp(leitura.data,valor,strlen(valor)) == 0) {
                        Imprime_Registro(&leitura);
                        flag++;
                    }
                cont += 80; // Significa que leu um registro
                    if(cont >= tamPagDisco) { // Se o numero de registros lidos der 1600, entao aumenta 1 pagina de disco
                    pag_disco++;
                    cont = tamPagDisco - cont;
                    }
            }
        break;

        case 4:
            while(fread(&leitura.removido, 1, 1, arquivo)) { // Verifica se ainda dar pra ler, se nao der eh pq o arquivo chegou ao fim
                Le_Registro(&leitura, arquivo); //Le e imprime todos os registros
                    if(leitura.contCity != 0 && strcmp(leitura.cidade, valor) == 0) {
                        Imprime_Registro(&leitura);
                        flag++;
                    }
                cont += 80; // Significa que leu um registro
                    if(cont >= tamPagDisco) { // Se o numero de registros lidos der 1600, entao aumenta 1 pagina de disco
                    pag_disco++;
                    cont = tamPagDisco - cont;
                    }
            }
        break;

        case 5:
            while(fread(&leitura.removido, 1, 1, arquivo)) { // Verifica se ainda dar pra ler, se nao der eh pq o arquivo chegou ao fim
                Le_Registro(&leitura, arquivo); //Le e imprime todos os registros
                    if(leitura.contSchool != 0 && strcmp(leitura.nomeEscola, valor) == 0) {
                        Imprime_Registro(&leitura);
                        flag++;
                    }
                cont += 80; // Significa que leu um registro
                    if(cont >= tamPagDisco) { // Se o numero de registros lidos der 1600, entao aumenta 1 pagina de disco
                    pag_disco++;
                    cont = tamPagDisco - cont;
                    }
            }
        break;

    }

    if(flag > 0) {
        if(cont > 0) // Para caso tenha lido registros mas nao chegou a dar 1600, porem foi usado 1 pagina de disco mesmo assim
            pag_disco++;
            printf("Número de páginas de disco acessadas: %d", pag_disco);
    }
    else
        printf("Registro inexistente.");

    return;
}

void RRN(char nome_arquivo[], int rrn) {
    int size; // Usado para saber o tamanho do arquivo
    FILE *arq = fopen(nome_arquivo, "rb");
    Registro leitura;

    if(arq != NULL) { // Se o arquivo nao for nulo, ele prossegue
        fseek(arq, 0, SEEK_END); // Vai para o fim do arquivo
        size = ftell(arq); //Calcula o numero de bytes do arquivo

        if(tamRegistro * (rrn + 200) > size) { // Se o RRN dado for maior que o tamanho do arquivo
            printf("Registro inexistente.");
            return;
        } else { // Caso seja um RRN valido, ele printa o registro
            fseek(arq, tamRegistro * (rrn + 200), SEEK_SET); // Pula para o registro apontado pelo RRN
            if(!fread(&leitura.removido, 1, 1, arq))
                printf("Registro inexistente.");

            Le_Registro(&leitura, arq);
            Imprime_Registro(&leitura);
            printf("Número de páginas de disco acessadas: 2"); // Numero de paginas de disco sempre vai ser 2, pois acessa o Registro de Cabecalho
            return;                                           // e a pagina de disco que o registro desejado se encontra
        }
    }
    printf("Falha no processamento do arquivo."); // Caso o arquivo seja nulo
    return;
}

int Remove_Registro(FILE *arquivo, int topo) {
    fseek(arquivo, -80, SEEK_CUR);
    int RRN = (ftell(arquivo) - 16000) / 80; // Calcula o RRN para o encadeamento;
    char lixo = '@';
    char removido = '*';

    fwrite(&removido, 1, 1, arquivo);
    fwrite(&topo, 4, 1, arquivo);
    for(int i = 0; i < 75; i++) fwrite(&lixo, 1, 1, arquivo);
    topo = RRN;
    return topo;
}

int Busca_por_Campo(FILE *arquivo, char nome_campo[], char valor[], Registro leitura) {
    int op;

    // Verifica qual eh o campo desejado
    if (strcmp(nome_campo, "nroInscricao") == 0)
        op = 1;

    if (strcmp(nome_campo, "nota") == 0)
        op = 2;

    if (strcmp(nome_campo, "data") == 0)
        op = 3;

    if (strcmp(nome_campo, "cidade") == 0)
        op = 4;

    if (strcmp(nome_campo, "nomeEscola") == 0)
        op = 5;

    switch (op) {
    case 1:
        if(leitura.nroInscricao == atoi(valor))
            return 1;
    case 2:
        if(leitura.nota == atof(valor))
            return 1;
    case 3:
        if(strncmp(leitura.data, valor, 10) == 0)
            return 1;
    case 4:
        if(leitura.contCity != 0 && strcmp(leitura.cidade, valor) == 0)
            return 1;
    case 5:
        if(leitura.contSchool != 0 && strcmp(leitura.nomeEscola, valor) == 0)
            return 1;
    }
    return 0;
}

int Insercao_Registro(Registro leitura, int topo, FILE *arq) {
    int flag = 1;

    if(topo != -1) { // Se o topo nao for -1, entao existem registros removidos
        fseek(arq, topo * tamRegistro + tamPagDisco + 1, SEEK_SET); // Pula o registro de cabecalho + o char de removidos
        fread(&topo, 4, 1, arq); // Le o encadeamento
        fseek(arq, -5, SEEK_CUR); // Volta o ponteiro para o campo de removidos
    }
    else { // Caso nao tenha registros removidos
        fseek(arq, 0, SEEK_END);
    }
    Escreve_Registro(leitura, arq); // Escreve o registro no espaco removido
    return topo;
}

void Escreve_Registro(Registro leitura, FILE *arq) {
    char arroba = '@';
    char tag1 = '4'; // Tag da cidade
    char tag2 = '5'; // Tag do nome da escola

    // Escreve as variaveis de tamanho fixo no arquivo
    fwrite(&leitura.removido, sizeof(char), 1, arq);
    fwrite(&leitura.encadeamento, sizeof(int), 1, arq);
    fwrite(&leitura.nroInscricao, sizeof(int), 1, arq);
    fwrite(&leitura.nota, sizeof(double), 1, arq);
    fwrite(leitura.data, 10, 1, arq);

    // Escreve a cidade no arquivo
    if(strlen(leitura.cidade) != 0) {
        int tmp = strlen(leitura.cidade) + 2;
        fwrite(&tmp, sizeof(int), 1, arq);
        fwrite(&tag1, sizeof(char), 1, arq);
        fwrite(leitura.cidade, strlen(leitura.cidade) + 1, 1, arq);
    }

    // Escreve o nome da escola no arquivo
    if(strlen(leitura.nomeEscola) != 0) {
        int tmp = strlen(leitura.nomeEscola) + 2;
        fwrite(&tmp, sizeof(int), 1, arq);
        fwrite(&tag2, sizeof(char), 1, arq);
        fwrite(leitura.nomeEscola, strlen(leitura.nomeEscola) + 1, 1, arq);
    }

    int i = ftell(arq) % 80; // Calcula quanto resta de espaco no registro

    // Caso o tamanho seja nulo
    if(i == 0)
        return;

    for(i; i < 80; i++) { // Preenche o resto do registro de lixo
        fwrite(&arroba, 1, 1, arq);
    }
}

void Atualiza_Campo(FILE *arq, char nome_campo[], char valor[], Registro leitura) {
    int op, contCity, contSchool, tam;
    char arroba = '@';
    char tagCidade, tagEscola;
    char cidade[20], escola[20];
    int marca_posicao, flag;


    // Verifica qual eh o campo desejado
    if (strcmp(nome_campo, "nroInscricao") == 0)
        op = 1;

    if (strcmp(nome_campo, "nota") == 0)
        op = 2;

    if (strcmp(nome_campo, "data") == 0)
        op = 3;

    if (strcmp(nome_campo, "cidade") == 0)
        op = 4;

    if (strcmp(nome_campo, "nomeEscola") == 0)
        op = 5;

    switch(op) {
        case 1:
            fseek(arq, 5, SEEK_CUR); // Vai para o comeco do campo nroInscricao
            leitura.nroInscricao = atoi(valor);
            fwrite(&leitura.nroInscricao, sizeof(int), 1, arq);
            break;

        case 2:
            fseek(arq, 9, SEEK_CUR); // Vai para o comeco do campo nota
            leitura.nota = atof(valor);
            fwrite(&leitura.nota, sizeof(double), 1, arq);
            break;

        case 3:
            fseek(arq, 17, SEEK_CUR); // Vai para o comeco do campo data
            for(int i = 0; i < 10; i++) {
                fwrite(&valor[i], 1, 1, arq);
            }
            break;

        case 4:
            tam = strlen(valor);
            fseek(arq, 27, SEEK_CUR);
            marca_posicao = ftell(arq);
            fread(&contCity, 4, 1, arq);
            fread(&tagCidade, 1, 1, arq);
            if(tagCidade == '4') { // Se existe cidade, guarda ela em variaveis
                //printf("\n %d %c", contCity, tagCidade);
                for(int i = 0; i < contCity - 1; i++) {
                    fread(&cidade[i], 1, 1, arq);
                    //printf("%c", cidade[i]);
                }
                fread(&contSchool, 4, 1, arq);
                fread(&tagEscola, 1, 1, arq);
                if(tagEscola == '5') { // Se existir cidade e escola, guarda os dois em variaveis
                    //printf("\n %d %c", contSchool, tagEscola);
                    for(int i = 0; i < contSchool - 1; i++) {
                        fread(&escola[i], 1, 1, arq);
                        //printf("%c", escola[i]);
                    }
                    fseek(arq, marca_posicao, SEEK_SET);
                    fwrite(&tam, 4, 1, arq);
                    fwrite(&tagCidade, 4, 1, arq);
                    for(int i = 0; i < tam - 1; i++) {
                        fwrite(&valor[i], 1, 1, arq);
                    }
                    fwrite(&contSchool, 4, 1, arq);
                    fwrite(&tagEscola, 1, 1, arq);
                    for(int i = 0; i < contSchool - 1; i++) {
                        fwrite(&escola[i], 1, 1, arq);
                    }
                    tam += 2;
                    fseek(arq, marca_posicao, SEEK_SET);
                    fseek(arq, tam + contSchool, SEEK_CUR);
                    fwrite(&arroba, 1, 53 - tam - contSchool, arq);
                } else { // Existe cidade e nao escola
                    tam += 2;
                    fseek(arq, marca_posicao, SEEK_SET);
                    fwrite(&tam, 4, 1, arq);
                    fwrite(&tagCidade, 1, 1, arq);
                    for(int i = 0; i < contCity; i++) {
                        fwrite(&valor[i], 1, 1, arq);
                    }
                    fseek(arq, marca_posicao, SEEK_SET);
                    fseek(arq, tam, SEEK_CUR);
                    fwrite(&arroba, 1, 53 - tam, arq);
                }
            } else if(tagCidade == '5') { // Nao existe cidade e existe escola
                for(int i = 0; i < contCity - 1; i++) {
                    fread(&escola[i], 1, 1, arq);
                }
                contSchool = contCity;
                tagEscola = tagCidade;
                tagCidade = '4';
                tam += 2;

                fseek(arq, marca_posicao, SEEK_SET);
                fwrite(&tam, 4, 1, arq);
                fwrite(&tagCidade, 1, 1, arq);
                for(int i = 0; i < tam - 1; i++) {
                    fwrite(&valor[i], 1, 1, arq);
                }
                fwrite(&contSchool, 4, 1, arq);
                fwrite(&tagEscola, 1, 1, arq);
                for(int i = 0; i < contSchool - 1; i++) {
                    fwrite(&escola[i], 1, 1, arq);
                }
                // Vai para depois da parte escrita e enche de arroba
                fseek(arq, marca_posicao, SEEK_SET);
                fseek(arq, tam + contSchool, SEEK_CUR);
                fwrite(&arroba, 1, 53 - tam - contSchool, arq);
            } else { // Nem cidade nem escola existem
                tagCidade = '4';
                tam += 2;
                fseek(arq, marca_posicao, SEEK_SET);
                fwrite(&tam, 4, 1, arq);
                fwrite(&tagCidade, 1, 1, arq);
                for(int i = 0; i < tam - 1; i++) {
                    fwrite(&valor[i], 1, 1, arq);
                }
                fseek(arq, marca_posicao, SEEK_SET);
                fseek(arq, tam, SEEK_CUR);
                fwrite(&arroba, 1, 53 - tam, arq);
            }
            break;

        case 5:
            tam = strlen(valor);
            fseek(arq, 27, SEEK_CUR);
            marca_posicao = ftell(arq);
            fread(&contCity, 4, 1, arq);
            fread(&tagCidade, 1, 1, arq);
            if(tagCidade == '4') {
                for(int i = 0; i < contCity - 1; i++) {
                    fread(&cidade, 1, 1, arq);
                }
                tagEscola = '5';
                fwrite(&tam, 4, 1, arq);
                fwrite(&tagEscola, 1, 1, arq);
                for(int i = 0; i < tam - 1; i++) {
                    fwrite(&valor, 1, 1, arq);
                }
                fseek(arq, marca_posicao, SEEK_SET);
                fseek(arq, tam + contCity, SEEK_CUR);
                fwrite(&arroba, 1, 53 - tam, arq);
            } else {
                tagEscola = '5';
                fseek(arq, marca_posicao, SEEK_SET);
                fwrite(&tam, 4, 1, arq);
                fwrite(&tagEscola, 1, 1, arq);
                for(int i = 0; i < tam - 1; i++) {
                    fwrite(&valor, 1, 1, arq);
                }
                fseek(arq, marca_posicao, SEEK_SET);
                fseek(arq, tam, SEEK_CUR);
                fwrite(&arroba, 1, 53 - tam, arq);
            }
            break;
    return;
    }
}

// Funcoes utilizada dos monitores
void binarioNaTela1(FILE *ponteiroArquivoBinario) {

	/* Escolha essa função se você ainda tem o ponteiro de arquivo 'FILE *' aberto.
	*  Lembrando que você tem que ter aberto ele no fopen para leitura também pra funcionar (exemplo: rb, rb+, wb+, ...) */

	unsigned char *mb;
	unsigned long i;
	size_t fl;
	fseek(ponteiroArquivoBinario, 0, SEEK_END);
	fl = ftell(ponteiroArquivoBinario);
	fseek(ponteiroArquivoBinario, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, ponteiroArquivoBinario);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
}

void binarioNaTela2(char *nomeArquivoBinario) {

	/* Escolha essa função se você já fechou o ponteiro de arquivo 'FILE *'.
	*  Ela vai abrir de novo para leitura e depois fechar. */

	unsigned char *mb;
	unsigned long i;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela2): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar? Se você não fechou ele, pode usar a outra função, binarioNaTela1, ou pode fechar ele antes de chamar essa função!\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
	fclose(fs);
}

void trim(char *str) {

	/*
	*	Essa função arruma uma string de entrada "str".
	*	Manda pra ela uma string que tem '\r' e ela retorna sem.
	*	Ela remove do início e do fim da string todo tipo de espaçamento (\r, \n, \t, espaço, ...).
	*	Por exemplo:
	*
	*	char minhaString[] = "    \t TESTE  DE STRING COM BARRA R     \t  \r\n ";
	*	trim(minhaString);
	*	printf("[%s]", minhaString); // vai imprimir "[TESTE  DE STRING COM BARRA R]"
	*
	*/

	size_t len;
	char *p;

	for(len = strlen(str); len > 0 && isspace(str[len - 1]); len--); // remove espaçamentos do fim
	str[len] = '\0';
	for(p = str; *p != '\0' && isspace(*p); p++); // remove espaçamentos do começo
	len = strlen(p);
	memmove(str, p, sizeof(char) * (len + 1));
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}