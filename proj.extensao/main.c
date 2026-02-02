#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

//número máximo de cadastros permitidos
#define NUM_MAX_CAD 1024
#define ARQUIVO_DADOS "barbearia.dat"  // Novo define para o arquivo de dados

typedef struct Cadastro {
    char nomeCliente [256];
    int codigoAtendente;
    char horario[6];
    int hora, minuto;
    int servico;
    char cpf[13];
    char *atendente;
    float preco;
    int ocupado;
} Cadastro;


//função com passagem e retorno de valor
float calculoServico(int servico){
    switch(servico){
    case 1:
        return 35.00;
        break;
    case 2:
        return 45.00;
        break;
    case 3:
        return 60.00;
        break;
    case 4:
        return 70.00;
        break;
    default:
        return -1.0;
    }
}

void salvarClientes(Cadastro *clientes, int total) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");
    if (arquivo == NULL) {
        printf("\nErro ao abrir arquivo para salvar dados!\n");
        system("pause");
        return;
    }

    // Primeiro escreve o total de clientes
    fwrite(&total, sizeof(int), 1, arquivo);

    // Escreve cada cliente ocupado
    for (int i = 0; i < total; i++) {
        if (clientes[i].ocupado == 1) {
            fwrite(&clientes[i], sizeof(Cadastro), 1, arquivo);
        }
    }

    fclose(arquivo);
}

int carregarClientes(Cadastro *clientes) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "rb");
    int total = 0;

    if (arquivo == NULL) {
        return 0; // Retorna 0 se o arquivo não existir (primeira execução)
    }

    // Lê primeiro o total de clientes
    fread(&total, sizeof(int), 1, arquivo);

    // Lê cada cliente do arquivo
    for (int i = 0; i < total; i++) {
        if (fread(&clientes[i], sizeof(Cadastro), 1, arquivo) != 1) {
            printf("\nErro ao ler cliente do arquivo!\n");
            break;
        }
        clientes[i].ocupado = 1; // Marca como ocupado ao carregar
    }

    fclose(arquivo);
    return total;
}


int main()
{
    Cadastro vetorClientes[NUM_MAX_CAD];
    int totalClientes = 0;

    //MODIFICAÇÃO: Carrega os dados do arquivo ao iniciar
    totalClientes = carregarClientes(vetorClientes);

    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");

    //cadastro---
    char nomeCliente [256];
    int codigoAtendente;
    char horario[6];
    int hora, minuto;
    int servico;
    char *atendente;
    float preco;
    char cpf [13];
    //------

    int sair = 0; //opção de sair
    int opcao;
    char ch;
    int erro;
    int executando; //adiconar mais cadastros/remoções/pesquisas

    int idxPesquisa = -1;


    for(int i=totalClientes; i < NUM_MAX_CAD; i++)
    {
        vetorClientes[i].ocupado = 0;
    }

    printf("BARBEARIA DE CAMPINAS!\n");
    system("pause");

    do
    {
        system("cls");
        printf("Menu de Opções \n");
        printf("1 - Cadastrar \n");
        printf("2 - Pesquisar \n");
        printf("3 - Remover \n");
        printf("4 - Relatório (todos cadastros registrados) \n");
        printf("5 - Sair \n\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            //-------------------------------------------------------------------
            //- TELA DE CADASTRO ------------------------------------------------
            //-------------------------------------------------------------------
            case 1:

                do{
                    system("cls");
                    printf("1 - Cadastro \n");

                    executando = 0;

                        if(totalClientes >= NUM_MAX_CAD)
                    {
                        printf("\nERRO! O cadastro já atingiu sua capacidade máxima!\n");
                        system("pause");
                        break;
                    }

                        //nome do cliente--------
                    do{
                        system("cls");
                        printf("\nDigite o nome do cliente: ");
                        fflush(stdin);
                        scanf(" %255[^\n]", nomeCliente);

                        erro = 0;

                         if(strlen(nomeCliente) > 254)
                        {
                            erro = 1;
                            printf("ERRO! O nome pode possuir no máximo 254 carracteres!\n");
                            system("pause");
                        }
                        if(strlen(nomeCliente) < 3){
                            erro = 1;
                            printf("ERRO! O nome deve possuir pelo menos 3 (três) carracteres!\n");
                            system("pause");
                        }


                    }while (erro == 1);

                        //cpf-------
                    do
                    {
                        erro = 0;
                        printf("\nDigite o CPF: ");
                        scanf(" %12[^\n]", cpf);
                        fflush(stdin);

                        if(strlen(cpf) != 11)
                        {
                            erro = 1;
                            printf("ERRO! O CPF deve possuir 11 (onze) dígitos!\n");
                        }

                    }while(erro == 1);

                        //horaário de chegada----------
                    do{
                        printf("\nDigite a hora do horário de chegada (formato HHhMM (ex: 11h30)): ");
                        scanf("%s", &horario);

                        if (sscanf(horario, "%dh%d", &hora, &minuto) == 2){
                            if (hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59){
                               erro = 0;
                            }else {
                             printf("Horário inválido.\n");
                             system("pause");
                             erro = 1;
                           }
                        } else {
                            printf("Formato de horário inválido, use o formato HHhMM (ex: 11h30).\n");
                            system("pause");
                            erro = 1;
                            }
                        }while (erro == 1);

                        //escolha do serviço ----------

                    do{
                        printf("\nEscolha o serviço a ser prestado\n");
                        printf("1- Corte:......................(R$35,00)\n");
                        printf("2- Corte + sobrancelha:........(R$45,00)\n");
                        printf("3- Corte e barba:..............(R$60,00)\n");
                        printf("4- Corte, barba e sobracelha:..(R$70,00)\n");
                        printf("Utilize o código: ");
                        erro = scanf("%d", &servico);
                        erro = 0;

                        preco = calculoServico(servico);

                        if (preco == -1.0) {
                            printf("\nOpção Inválida!!! Escolha uma opção de 1 a 4!\n");
                            system("pause");
                            erro = 1;
                        }

                        if (servico < 1 || servico > 4){

                            erro = 1;
                        }
                    }while (erro == 1);

                        //escolha do profissional----------

                    do{
                        printf("\nEscolha com quem será realizado o atendimento\n");
                        printf("1-Tavin \n");
                        printf("2-Theo \n");
                        printf("3-Maillon \n");
                        printf("4-Maycon \n");
                        printf("5-Vinicios \n");
                        printf("Utilize o código: ");
                        erro = scanf("%d", &codigoAtendente);

                        erro = 0;

                        switch(codigoAtendente){
                            case 1:
                                atendente = "Tavin";
                                break;
                            case 2:
                                atendente = "Theo";
                                 break;
                            case 3:
                                atendente = "Maillon";
                                 break;
                            case 4:
                                atendente = "Maycon";
                                 break;
                            case 5:
                                atendente = "Vinicios";
                                 break;

                            default:
                            printf("\nOpção Inválida!!! Escolha uma opção de 1 a 5!\n");
                            system("pause");
                        }

                        if (codigoAtendente < 1 || codigoAtendente > 5){

                            erro = 1;
                        }

                    } while (erro == 1);

                    //armazenar cadastro------

                        idxPesquisa = -1;

                        for(int i=0; i < NUM_MAX_CAD; i++)
                        {
                            if(vetorClientes[i].ocupado == 1) {
                                if( strcmp(vetorClientes[i].cpf, cpf) == 0) {
                                    idxPesquisa = i;
                                    break;
                                }
                            }
                        }
                        if(idxPesquisa != -1) {

                            printf("\nErro! Não foi possível inserir os dados pois já existe um cliente com o mesmo CPF no cadastro:\v");

                            printf("\nCliente com o mesmo cpf: \n");
                            printf("CPF:        %s\n", vetorClientes[idxPesquisa].cpf);
                            printf("Nome:       %s\n", vetorClientes[idxPesquisa].nomeCliente);
                            printf("Horário:    %s\n", vetorClientes[idxPesquisa].horario);
                            printf("Atendente:  %s\n", vetorClientes[idxPesquisa].atendente);
                            printf("A pagar:    R$%.2f\n", vetorClientes[idxPesquisa].preco);
                            printf("Serviço:    %d\n", vetorClientes[idxPesquisa].servico);;
                        }
                        else {

                            for(int i=0; i < NUM_MAX_CAD; i++)
                            {
                                if(vetorClientes[i].ocupado == 0) {

                                    vetorClientes[i].ocupado = 1;

                                    strcpy(vetorClientes[i].cpf, cpf);
                                    strcpy(vetorClientes[i].nomeCliente, nomeCliente);
                                    strcpy(vetorClientes[i].horario, horario);
                                    vetorClientes[i].atendente = atendente;
                                    vetorClientes[i].preco = preco;
                                    vetorClientes[i].servico = servico;


                                    totalClientes = totalClientes + 1;

                                    printf("\nDados cadastrados com sucesso! \n");
                                    break;
                                }
                            }
                        }

                    salvarClientes(vetorClientes, totalClientes);

                    //resultado dos dados cadastrados-------

                            printf("\n CPF: %s\n Cliente: %s\n Horário: %02dh%02d\n Serviço: %d\n A pagar: R$%.2f\n Atendente: %s\n", cpf, nomeCliente, hora, minuto, servico, preco, atendente);

                    do{
                            printf("\nGostaria de cadastrar outro cliente? (s/n): ");
                            scanf(" %c", &ch);
                            fflush(stdin);

                            ch = toupper(ch);

                    }while(!(ch == 'S' || ch == 'N'));

                    if(ch == 'S') {
                        executando = 1;
                    }else {
                        executando = 0;
                    }

                } while(executando == 1);


            break;


            //-------------------------------------------------------------------
            //- TELA DE PESQUISA ------------------------------------------------
            //-------------------------------------------------------------------


            case 2:

                 do{

                    system("cls");
                    printf("2 - Pesquisar \n");

                    do
                    {
                        erro = 0;

                        printf("\nDigite o CPF: ");
                        scanf(" %12[^\n]", cpf);

                        fflush(stdin);

                        if(strlen(cpf) != 11){
                            erro = 1;
                            printf("ERRO! O CPF deve possuir 11 (onze) dígitos!\n");
                        }

                    }while(erro == 1);

                    idxPesquisa = -1;

                    for(int i=0; i<NUM_MAX_CAD; i++) {

                        if(vetorClientes[i].ocupado == 1) {
                            if(strcmp(vetorClientes[i].cpf, cpf) == 0){

                                idxPesquisa = i;

                                break;
                            }
                        }
                    }

                    if(idxPesquisa != -1) {
                        printf("\nCliente Encontrado: \n");
                        printf("CPF:        %s\n", vetorClientes[idxPesquisa].cpf);
                        printf("Nome:       %s\n", vetorClientes[idxPesquisa].nomeCliente);
                        printf("Horário:    %s\n", vetorClientes[idxPesquisa].horario);
                        printf("Atendente:  %s\n", vetorClientes[idxPesquisa].atendente);
                        printf("A pagar:    R$%.2f\n", vetorClientes[idxPesquisa].preco);
                        printf("Serviço:    %d\n", vetorClientes[idxPesquisa].servico);

                    }else {
                        printf("\nNão foi encontrada um cliente com o cpf informado!\n\n");
                    }

                    system("pause");


                    do{

                        printf("\nGostaria de pesquisar outro cliente?  (s/n): ");
                        scanf(" %c", &ch);

                        fflush(stdin);

                        ch = toupper(ch);

                    }while(!(ch == 'S' || ch == 'N'));

                    if(ch == 'S'){
                       executando= 1;
                    }else{
                       executando= 0;
                    }

                } while( executando == 1);

            break;


            //-------------------------------------------------------------------
            //- TELA DE REMOÇÃO -------------------------------------------------
            //-------------------------------------------------------------------


            case 3:

                do
                {
                    system("cls");
                    printf("3 - Remover Cliente\n");

                    do
                    {
                        erro = 0;

                        printf("\nDigite o CPF que será removido: ");
                        scanf(" %12[^\n]", cpf);

                        fflush(stdin);

                        if(strlen(cpf) != 11){
                            erro = 1;
                            printf("ERRO! O CPF deve possuir 11 (onze) dígitos!\n");
                        }

                    }while(erro == 1);

                    // FIM ENTRADA DO CPF

                    idxPesquisa = -1;

                    for(int i = 0; i < NUM_MAX_CAD; i++) {

                        if(vetorClientes[i].ocupado == 1){
                            if(strcmp(vetorClientes[i].cpf, cpf) == 0){

                                totalClientes = totalClientes - 1;
                                vetorClientes[i].ocupado = 0;

                                idxPesquisa = i;

                                break;
                            }
                        }
                    }

                    if(idxPesquisa != -1){
                        printf("\nCliente removido com sucesso!\n");
                    }
                    else {
                        printf("\nNão foi possível remover o cliente do cadastro!\n");
                    }

                    salvarClientes(vetorClientes, totalClientes);

                    system("pause");

                    do{

                        printf("\nGostaria de remover outro cliente?  (s/n): ");
                        scanf(" %c", &ch);

                        fflush(stdin);

                        ch = toupper(ch);

                    }while(!(ch == 'S' || ch == 'N'));

                    if(ch == 'S'){

                        executando = 1;

                    }else{

                        executando = 0;

                    }

                }while(executando);

            break;



            //-------------------------------------------------------------------
            //- TELA DE RELATÓRIO -----------------------------------------------
            //-------------------------------------------------------------------


            case 4:

                system("cls");
                printf("4 - Relatório \n");

                printf("Total de Clientes Cadastrados: %d\n\n", totalClientes);

                float totalDia = 0.0;

                for(int i=0; i<NUM_MAX_CAD; i++){

                    if(vetorClientes[i].ocupado == 1)
                    {
                        printf("\nClientes Encontrados: \n");
                        printf("CPF:        %s\n", vetorClientes[i].cpf);
                        printf("Nome:       %s\n", vetorClientes[i].nomeCliente);
                        printf("Horário:    %s\n", vetorClientes[i].horario);
                        printf("Atendente:  %s\n", vetorClientes[i].atendente);
                        printf("A pagar:    R$%.2f\n", vetorClientes[i].preco);
                        printf("Serviço:    %d\n", vetorClientes[i].servico);

                        totalDia += vetorClientes[i].preco; // Acumula o total
                    }
                }

                printf("\n====================================\n");
                printf("TOTAL DO DIA: R$%.2f\n", totalDia);
                printf("====================================\n");

                system("pause");

            break;



            //-------------------------------------------------------------------
            //- TELA ENCERRAR APLICAÇÃO -----------------------------------------
            //-------------------------------------------------------------------

            case 5:

                system("cls");
                printf("5 - Sair \n\n");

                printf("\nDeseja mesmo sair?  (s/n): ");
                scanf(" %c", &ch);

                ch = toupper(ch);

                if(ch == 'S')
                {
                    salvarClientes(vetorClientes, totalClientes);
                    sair = 1;
                }

            break;


            //-------------------------------------------------------------------
            //- TRATAMENTO DE OPÇÃO INVÁLIDA ------------------------------------
            //-------------------------------------------------------------------


            default:

                printf("\nOpção Inválida !!! \n");
                system("pause");
        }

    }while(sair == 0);

    system("cls");
    printf("\nFim da execução do programa!\n");

    return 0;
}
