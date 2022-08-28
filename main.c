//Gabriel Garuthi Goncalves
//11821EAU016



#include <stdio.h> // para o FILE
#include <stdlib.h>
#include <conio.h> // para o getch()
#include <string.h>//para strcmp

//definindo o tamanho maximo das variaveis
#define NOMEMAX 81
#define MAXIMOLOGRADOURO 40
#define MAXIMOCADASTRO 120
#define MAXIMONOMEREMEDIO 120
#define MAXIMOVALORESCOLHA 2
#define MAXIMOVALORCPF 12
#define MAXIMOQUANTIDADEREMEDIO 150

typedef struct Endereco//struct para o endereco do cliente
{
    char Logradouro[40];
    char Bairro[30];
    char  NumCs[20];
    char Cidade[30];
    char Estado[40];
    char Complemento[81];
} Endereco;

typedef struct Dadospessoais//struct para os dados pessoais do cliente
{
    char Nome[NOMEMAX];
    char Cpf[MAXIMOVALORCPF];
    int datadia;
    int datames;
    int dataano;
}Dadospessoais;

typedef struct Remedio//struct para os dados dos remedios cadastrados
{
    char Nome_remedio[MAXIMONOMEREMEDIO];
    int CodigoR;
    int EstoqueR;
}Remedio;

typedef struct Cliente//struct para o cadastro do cliente
{
    Endereco end_cliente;
    Dadospessoais dados_cliente;
    Remedio remedio_cliente;

}Cliente;

Remedio cadastroremedio(int *a,int *acontadorfixo2, Remedio remedio[])//funcao para cadastrar remedios
{
    int j;
    int escolha = 0, aumentaremedio, codigoremedio;
    printf("\t--Cadastro dos remedios.--\n\n");
    printf("Digite o codigo do remedio:\nR:");
    fflush(stdin);
    scanf(" %d", &codigoremedio);
    fflush(stdin);
    for(j = 0; j <= *acontadorfixo2; j++){
        if(remedio[j].CodigoR == codigoremedio){
            printf("\n--Remedio ja cadastrado.--\n");
            printf("\nDeseja aumentar seu estoque?\n");
            printf("Digite '1' para sim.\nR:");
            fflush(stdin);
            scanf(" %d", &escolha);
            fflush(stdin);
            if(escolha == 1){
                printf("Em quantos?\n");
                fflush(stdin);
                scanf(" %d",&aumentaremedio);
                fflush(stdin);
                remedio[j].EstoqueR = remedio[j].EstoqueR + aumentaremedio;
                fflush(stdin);
                return remedio[j];
            }
            else{
                printf("\n\t--Voltando ao menu anterior.--\n\n");
                return remedio[j];
            }
        }
    }
    printf("\n\t--Remedio ainda nao cadastrado.--\n");
    printf("Digite o Nome do remedio: \nR:");
    fflush(stdin);
    gets(remedio[*a].Nome_remedio);
    fflush(stdin);
    printf("Digite o codigo do remedio: \nR:");
    fflush(stdin);
    scanf(" %d", &remedio[*a].CodigoR);
    fflush(stdin);
    remedio[*a].EstoqueR = 1;
    *a = *a + 1;
    *acontadorfixo2 = *a;
    fflush(stdin);
    return remedio[*acontadorfixo2 - 1];
}
//funcao para o cliente fazer a compra de remedios
void compracliente(int contadorfixo, int *contadorfixo2, char aserconsultado[MAXIMOVALORCPF], Cliente cliente[], Remedio remedio[])
{
    int selecioneremedio;
    int m, n;
    int resultado;
    for(m = 0; m <= contadorfixo; m++){
        resultado = strcmp(cliente[m].dados_cliente.Cpf,aserconsultado);
        if(resultado == 0){
            printf("\n\t--O cliente %s esta cadastrado.--\n", cliente[m].dados_cliente.Nome);
            printf("Remedios disponiveis:\n");
            fflush(stdin);
            for(n = 0; n < *contadorfixo2; n++){
                printf("[%d] - %s(%d)\n", remedio[n].EstoqueR, remedio[n].Nome_remedio, remedio[n].CodigoR);//[quantidade no estoque]
            }
            printf("Qual remedio deseja comprar(Digite o codigo):\nR:");
            fflush(stdin);
            scanf(" %d", &selecioneremedio);
            fflush(stdin);
            for(n = 0; n < *contadorfixo2; n++){
                if(remedio[n].CodigoR == selecioneremedio){
                    if(remedio[n].EstoqueR > 0){
                            strcpy(cliente[m].remedio_cliente.Nome_remedio, remedio[n].Nome_remedio);
                            cliente[m].remedio_cliente.CodigoR = remedio[n].CodigoR;
                            remedio[n].EstoqueR --;
                            printf("Venda feita com sucesso.\n");
                            fflush(stdin);
                            break;
                    }
                    else{
                        printf("O remedio nao esta disponivel.\n");
                        fflush(stdin);
                    }
                }
            }
            break;
        }
        else{
            printf("Cliente nao cadastrado.\n\n");
            fflush(stdin);
            break;
        }
    }
    fflush(stdin);


}

Cliente cadastrocliente()//funcao para cadastrar o cliente
{
    char completar[81] = {"vazio"};//preenchendo os remedios no cadastro dos clientes
    Cliente cliente;

    printf("\n--Cadastro dos dados pessoais.--\n");
    fflush(stdin);
    printf("\nDigite o Nome do cliente:\nR:");
    gets(cliente.dados_cliente.Nome);
    fflush(stdin);
    printf("\nDigite o Cpf(sem ponto e sem traco):\nR:");
    fflush(stdin);
    gets(cliente.dados_cliente.Cpf);
    fflush(stdin);
    printf("\nDigite a data de nascimento no formato x/x/x:\nR:");
    fflush(stdin);
    scanf("%d/%d/%d", &cliente.dados_cliente.datadia, &cliente.dados_cliente.datames, &cliente.dados_cliente.dataano);
    fflush(stdin);

    printf("\n--Cadastro do endereco.--\n");
    printf("\nDigite o Logradouro do cliente(%s):\nR:", cliente.dados_cliente.Nome);
    gets(cliente.end_cliente.Logradouro);
    fflush(stdin);
    printf("\nDigite o Numero:\nR:");
    fflush(stdin);
    gets(cliente.end_cliente.NumCs);
    fflush(stdin);
    printf("\nDigite o bairro:\nR:");
    gets(cliente.end_cliente.Bairro);
    fflush(stdin);
    printf("\nDigite a cidade:\nR:");
    gets(cliente.end_cliente.Cidade);
    fflush(stdin);
    printf("\nDigite o Estado:\nR:");
    gets(cliente.end_cliente.Estado);
    fflush(stdin);
    strcpy(cliente.remedio_cliente.Nome_remedio, completar);
    fflush(stdin);

    return cliente;
}
//consultandos os dados de 1 cliente
void consultacadastro(int contadorfixo, char aserconsultado[MAXIMOVALORCPF], Cliente cliente[], Remedio remedio[]){

    int m,n;
    int resultado;
    for(m = 0; m < contadorfixo; m++){
        resultado = strcmp(cliente[m].dados_cliente.Cpf,aserconsultado);
        if(resultado == 0){
            printf("\nO cliente '%s' esta cadastrado.\n", cliente[m].dados_cliente.Nome);
            printf("Deseja ver seu cadastro?\n \n1 - Sim\n2 - Nao\nR:");
            fflush(stdin);
            scanf(" %d", &n);
            fflush(stdin);
            if(n == 1){
                printf("\nNome: %s\n", cliente[m].dados_cliente.Nome);
                printf("Cpf: %s\n", cliente[m].dados_cliente.Cpf);
                printf("Data de nascimento: %d/%d/%d\n", cliente[m].dados_cliente.datadia, cliente[m].dados_cliente.datames, cliente[m].dados_cliente.dataano);
                printf("Logradouro: %s\n", cliente[m].end_cliente.Logradouro);
                printf("Bairro: %s\n", cliente[m].end_cliente.Bairro);
                printf("Numero: %s\n", cliente[m].end_cliente.NumCs);
                printf("Cidade: %s\n", cliente[m].end_cliente.Cidade);
                printf("Estado: %s\n", cliente[m].end_cliente.Estado);
                printf("Remedios comprados pelo cliente: %s\n", cliente[m].remedio_cliente.Nome_remedio);
                return;
            }
            if(n != 0){
                printf("Voltando ao menu anterior.\n");
                return;
            }
        }
        if(resultado != 0){
            printf("Cliente nao possui cadastro.");
            return;
        }


    }

}

int main()
{
    Cliente cliente[MAXIMOCADASTRO];//criando a variavel cliente do tipo cliente
    Remedio remedio[MAXIMOCADASTRO];//criando a variavel remedio do tipo remedio
    FILE  *farmacia;//criando o arquivo
    farmacia = fopen("projeto_farmacia.bin", "wb");//abrindo o arquivo

    if(farmacia == NULL){//testantdo se tem falha fisica
        printf("O arquivo nao pode ser executado");
        exit(1);
    }
//Começo do sistema.
    printf("----------\tSeja Bem vindo ao sistema de farmacia.\t\t----------\n");

    char cpfconsulta[MAXIMOVALORCPF];
    int senha;
    int y, m=0, n = 0, h, o = 0;
    int x;
    int contadorfixo = 0;
    int contadorfixo2 = 0;

    do
    {//menu para opcoes
        printf("\nDigite a opcao desejada:\n");
        printf("[1] - Faca sua compra.\n");
        printf("[2] - Area do funcionario.\n");
        printf("[3] - Para sair.\n");
        scanf(" %d", &x);;

        if(x == 1){
                printf("Digite seu cpf(sem ponto e sem espaco): \n");
                fflush(stdin);
                gets(cpfconsulta);
                fflush(stdin);
                compracliente(contadorfixo, &contadorfixo2, cpfconsulta, cliente, remedio);
        }


        if(x == 2){
            printf("Digite a senha:\n");
            fflush(stdin);
            scanf("%d", &senha);
            if(senha == 141312){//menu para opcoes para funcionarios
                printf("Digite uma opcao desejada:\n");
                printf("1 - Cadastro do cliente.\n");
                printf("2 - Cadastro de remedio.\n");
                printf("3 - Consultar cliente.\n");
                printf("4 - Mostrar cadastro completo.\n");
                fflush(stdin);
                scanf(" %d", &y);
                fflush(stdin);
                if(y == 1){
                    h=1;
                    while(h != 0)
                    {
                        cliente[m] = cadastrocliente();

                        if(fwrite(&cliente[m], sizeof(Cliente), 1, farmacia) != 1){
                            printf("Erro na escrita.");
                            break;
                        }
                            m++;
                            contadorfixo = m;
                            printf("\nDeseja cadastrar mais clientes?\n");
                            printf("-Digite '0', caso nao queira.-\n");
                            fflush(stdin);
                            scanf(" %d", &h);
                            fflush(stdin);
                            system("cls");
                    }
                }
                if(y == 2){
                    h=1;
                    do{
                        remedio[n] = cadastroremedio(&n, &contadorfixo2, remedio);
                        if(fwrite(&remedio[n], sizeof(Remedio), 1, farmacia) != 1){
                            printf("Erro na escrita.");
                            break;
                        }
                        printf("Deseja cadastrar mais remedios?\n");
                        printf("Digite 0, caso nao queira.\n");
                        fflush(stdin);
                        scanf(" %d", &h);
                        fflush(stdin);
                        system("cls");

                    }while(h != 0);
                }
               if(y == 3){
                    printf("Digite o cpf do cliente: \n");
                    fflush(stdin);
                    gets(cpfconsulta);
                    fflush(stdin);
                    consultacadastro(contadorfixo, cpfconsulta, cliente, remedio);

               }
               if(y == 4){
                printf("Digite:\n1- para listar todos os clientes\n2- para listar todos os remedios disponiveis.\nR:");
                scanf(" %d", &o);
                fflush(stdin);
                if(o == 1){
                    printf("\n--Todos os clientes cadastrados sao:\n\n");
                    for(m = 0; m < contadorfixo; m++){
                        printf("\nNome: %s\n", cliente[m].dados_cliente.Nome);
                        printf("Cpf: %s\n", cliente[m].dados_cliente.Cpf);
                        printf("Data de nascimento: %d/%d/%d\n", cliente[m].dados_cliente.datadia, cliente[m].dados_cliente.datames, cliente[m].dados_cliente.dataano);
                        printf("Logradouro: %s\n", cliente[m].end_cliente.Logradouro);
                        printf("Bairro: %s\n", cliente[m].end_cliente.Bairro);
                        printf("Numero: %s\n", cliente[m].end_cliente.NumCs);
                        printf("Cidade: %s\n", cliente[m].end_cliente.Cidade);
                        printf("Estado: %s\n", cliente[m].end_cliente.Estado);
                        printf("Remedio comprado pelo cliente: %s\n", cliente[m].remedio_cliente.Nome_remedio);
                    }
                if(m == 0){
                    printf("Nao possui clientes cadastrados.\n");
                    }
                }
                if(o == 2){
                    printf("\nTodos os remedios cadastrados sao:\n\n");
                    for(n = 0; n < contadorfixo2; n++){
                        printf("[%d] - %s(%d)\n", remedio[n].EstoqueR, remedio[n].Nome_remedio, remedio[n].CodigoR);
                    }
                    if(n == 0){
                    printf("Nao possui remedios cadastrados.\n");
                    }
                }

               }

            }
            else{
                printf("\nSenha incorreta.\n");
            }
        }

    }while(x != 3);

    fclose(farmacia);//fechando o arquivo
    system("PAUSE");//fechando o programa
    return 0;
}
