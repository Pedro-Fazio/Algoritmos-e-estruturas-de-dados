// Nome: Pedro Afonso Fazio Michalichem
// N USP: 10734196
#include "dados.h"

int main() {
    char nome_arquivo[100], nome_campo[100], valor[100], status;
    char str[200]; // Eh onde guardo os registros lidos para depois passar para o arquivo
    int rrn, op, topo, n, size;
    Registro leitura;
    Cabecalho aux;
    FILE *arq = NULL, *arq_read = NULL, *arq_escreve = NULL;

    scanf("%d %s", &op, nome_arquivo);

    arq = fopen(nome_arquivo, "rb");
    if (arq == NULL) {
        printf("Falha no processamento do arquivo.");
        return 0;
    }

    Inicializa_Remove(&leitura);
    inicializaCabecalho(&aux);
    Escreve_RegCabecalho(&aux, arq);


    switch(op) {
        case 1:
            arq_read = fopen(nome_arquivo, "r"); // Ponteiro usado para ler o arquivo

            if (arq_read == NULL) {
                printf("Falha no carregamento do arquivo.");
                break;
            }

            FILE *arq_escreve = fopen("arquivoTrab1si.bin", "wb");
            if (arq_escreve == NULL) {
                printf("Falha no carregamento do arquivo.");
                break;
            }

            // fgets retorna erro quando nao conseguir ler, entao ele continua com o while ate que nao seja mais possivel ler
            while (fgets(str, 100, arq_read)) {
                Le_RegDados_CSV(arq_read, &leitura, str);
                Escreve_RegDados(&leitura, arq_escreve);
            }
            fclose(arq_read);
            fclose(arq_escreve);
            break;
        case 2:
            Recupera_Dados(arq);
            break;
        case 3:
            scanf("%s %[^\n]s", nome_campo, valor);
            Busca_Registro(nome_arquivo, nome_campo, valor);
            break;
        case 4:
            scanf("%d", &rrn);
            if (rrn >= 0) {
                RRN(nome_arquivo, rrn);
            }
            else
                printf("Falha no processamento do arquivo.");

            return 0;
        case 5:
            scanf("%d", &n);
            // Status '0' para inconsistencia do arquivo
            fread(&status, 1, 1, arq);
            if(status == '0') {
                printf("Falha no processamento do arquivo.");
                break;
            }
            // Seta arquivo para inconsistente
            fseek(arq, -1, SEEK_CUR);
            fputc('0', arq);
            // Le topo da pilha de removidos
            fseek(arq, 0, SEEK_CUR);
            fread(&topo, 4, 1, arq);

            scanf(" %d", &n);
            while(n--) {
                fseek(arq, 16000, SEEK_SET);
                scanf(" %s", nome_campo);
                scan_quote_string(valor);
                // Le todos os registros no arquivo
                while(fread(&leitura.removido, 1, 1, arq)) {
                    // Se registro não estiver removido compara seu valor com o buscado
                    if(leitura.removido == '-') {
                        Le_Registro(&leitura, arq);
                        if(Busca_por_Campo(arq, nome_campo, valor, leitura)) {
                            topo = Remove_Registro(arq, topo);
                            if(strcmp(nome_campo, "nroInscricao") == 0) break;
                        }
                        fseek(arq, 0, SEEK_CUR);
                    } else {
                        fseek(arq, 79, SEEK_CUR);
                    }
                }
            }
            if(!arq || fgetc(arq) == '0') {
                printf("Falha no processamento do arquivo.");
                break;
            }

            fseek(arq, 0, SEEK_SET);
            fputc('1', arq);
            fwrite(&topo, 4, 1, arq);
            binarioNaTela1(arq);
            break;

        case 6:
            scanf("%d", &n);
            fseek(arq, 0, SEEK_SET);
            fread(&status, sizeof(char), 1, arq);

            // Verifica se o arquivo esta corrompido
            if (status != '1') {
                printf("Falha no processamento do arquivo.");
                break;
            }

            fread(&topo, 4, 1, arq);    //  Le o encadeamento e coloca no topo
            fseek(arq, 16000, SEEK_SET); // Pula o registro de cabecalho

            // Faz um laco com as n remocoes que o usuario solicitou
            for (int i = 0; i < n; i++) {
                char nota[10];
                scanf(" %d", &leitura.nroInscricao); // Le o numero de inscricao
                scan_quote_string(nota);   // Le a nota com a funcao dos monitores
                leitura.nota = atof(nota); // Faz a string da nota virar float
                if (leitura.nota == 0)     // Seta -1 para nota nula
                    leitura.nota = -1;

                scan_quote_string(leitura.data); // Le a data com a funcao dos monitores

                // Completa com lixo data vazia
                if(leitura.data[0] == '\0') {
                    for (int i = 1; i < 10; i++)
                        leitura.data[i] = '@';
                }

                scan_quote_string(leitura.cidade); // Le a cidade sem as apas
                scan_quote_string(leitura.nomeEscola); // Le o nome da escola sem as aspas

                Inicializa_Remove(&leitura); // Atualiza o encadeamento e os removidos
                topo = Insercao_Registro(leitura, topo, arq);
            }
            status = '1'; // Ja foi mexido com o arquivo, entao o status volta para "nao corrompido"

            // Atualiza o status e o encadeamento
            fseek(arq, 0, SEEK_SET);
            fwrite(&status, 1, 1, arq);
            fwrite(&topo, 4, 1, arq);
            binarioNaTela1(arq);
            break;
        case 7:
            scanf("%d", &n);
            fseek(arq, 0, SEEK_SET);
            fread(&status, sizeof(char), 1, arq);

            // Verifica se o arquivo esta corrompido
            if (status != '1') {
                printf("Falha no processamento do arquivo.");
                break;
            }

            for(int i = 0; i < n; i++) {
                scanf("%d", &rrn);
                scanf(" %s", nome_campo);
                scan_quote_string(valor);

                if(strlen(valor) == 0) {
                    continue;
                }

                fseek(arq, 0, SEEK_END); // Vai para o fim do arquivo
                size = ftell(arq); //Calcula o numero de bytes do arquivo

                // Se o RRN dado for maior que o tamanho do arquivo, entao o RRN eh invalido
                if(16000 + (rrn * 80) > size) {
                    //printf("Morreu");
                    continue;
                } else { // Caso seja um RRN valido
                    fseek(arq, 16000 + (rrn * 80), SEEK_SET); // Pula para o registro apontado pelo RRN
                    /*Le_Registro(&leitura, arq);*/
                    //fseek(arq, -80, SEEK_CUR); // Volta o ponteiro para o comeco do registro

                    // Verifica se o registro esta removido
                    fread(&leitura.removido, sizeof(char), 1, arq);
                    fseek(arq, -1, SEEK_CUR);
                    if(leitura.removido == '*') {
                        continue;
                    }
                    Atualiza_Campo(arq, nome_campo, valor, leitura);
                }
            }
            status = '1'; // Ja foi mexido com o arquivo, entao o status volta para "nao corrompido"
            // Atualiza o status e o encadeamento
            fseek(arq, 0, SEEK_SET);
            fwrite(&status, 1, 1, arq);
            binarioNaTela1(arq);
            break;
    }
    fclose(arq);
    return 0;
}
