#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

void exibirDesenho() {
    printf(" /$$$$$$$$                               /$$$$$$$                     /$$      \n");
    printf("| $$_____/                              | $$__  $$                   | $$      \n");
    printf("| $$        /$$$$$$   /$$$$$$$ /$$   /$$| $$  \\ $$ /$$$$$$   /$$$$$$ | $$   /$$\n");
    printf("| $$$$$    |____  $$ /$$_____/| $$  | $$| $$$$$$$/|____  $$ /$$__  $$| $$  /$$/\n");
    printf("| $$__/     /$$$$$$$|  $$$$$$ | $$  | $$| $$____/  /$$$$$$$| $$  \\__/| $$$$$$/ \n");
    printf("| $$       /$$__  $$ \\____  $$| $$  | $$| $$      /$$__  $$| $$      | $$_  $$ \n");
    printf("| $$$$$$$$|  $$$$$$$ /$$$$$$$/|  $$$$$$$| $$     |  $$$$$$$| $$      | $$ \\  $$\n");
    printf("|________/ \\_______/|_______/  \\____  $$|__/      \\_______/|__/      |__/  \\__/\n");
    printf("                               /$$  | $$                                        \n");
    printf("                              | $$$$$$/                                         \n");
    printf("                               \\______/                                          \n");
}

struct reg {
    char nome[20], veiculo[8];
    int dias;
    char status;
};

void imprimirTracos(int n) {
    for (int i = 0; i < n; i++) {
        printf("=");
    }
    printf("\n");
}

int tamanho(FILE *);

void cadastrar(FILE *);

void consultar(FILE *);

void excluir(FILE *);

int main() {
	setlocale(LC_ALL, "Portuguese");
    int escolha;

    FILE *arq;
	
    if ((arq = fopen("F:\\registro\\reg.dat", "rb+")) == NULL) {
        if ((arq = fopen("F:\\registro\\reg.dat", "wb+")) == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1; 
        }
    }
	
    do {
    	exibirDesenho();
		printf("\n\n");
		imprimirTracos(60);
		printf("EasyPark: Sistema Simples de Cadastramento de Veículos\n");
		imprimirTracos(60);
	
        imprimirTracos(30);
        printf("MENU DE OPCOES\n");
        imprimirTracos(30);
        printf("Escolha uma das opcões abaixo:\n");
        printf("1- Cadastrar veiculo\n");
        printf("2- Consultar veiculo\n");
        printf("3- Excluir veiculo\n");
        printf("4- Sair\n");

        printf("Escolha uma opcao (1-4): ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                imprimirTracos(30);
                printf("Opcao escolhida: Cadastrar veiculo\n");
                cadastrar(arq);
                break;
            case 2:
                imprimirTracos(30);
                printf("Opcao escolhida: Consultar veiculo\n");
                consultar(arq);
                break;
            case 3:
                imprimirTracos(30);
                printf("Opcao escolhida: Excluir veiculo\n");
                excluir(arq);
                break;
            case 4:
                imprimirTracos(30);
                printf("Opcao escolhida: Sair\n");
                break;
            default:
                imprimirTracos(30);
                printf("Opcao invalida.\n");
                getchar();
                system("pause");
                system("cls");
                
                //return 0;
                
        }

    } while (escolha != 4);

    printf("Sistema encerrado.\n");

    return 0;
}

void cadastrar(FILE *arq) {
    reg contato;
    char confirma;
    contato.status = ' ';

    printf("Cadastrando novo registro:\n");
    printf("\nNumero do registro:%d\n", tamanho(arq) + 1);
    printf("Nome.......................:");
    getchar(); 
    fgets(contato.nome, sizeof(contato.nome), stdin);
    contato.nome[strcspn(contato.nome, "\n")] = '\0'; 
    printf("Placa do veiculo..........:");
    fgets(contato.veiculo, sizeof(contato.veiculo), stdin);
    contato.veiculo[strcspn(contato.veiculo, "\n")] = '\0';
    printf("Diaria para estacionar:");
    scanf("%d", &contato.dias);
    printf("\nConfirma <s/n>:");
    getchar();
    scanf("%c", &confirma);
    if (toupper(confirma) == 'S') {
        printf("\n gravando...\n");
        fseek(arq, 0, SEEK_END);
        fwrite(&contato, sizeof(reg), 1, arq);
    }
    
   // getchar();
    system("pause");
    system("cls");
}

void consultar(FILE *arq) {
    reg contato;
    char nomeConsulta[20];

    printf("Digite o nome para consultar veículos cadastrados: ");
    getchar(); 
    fgets(nomeConsulta, sizeof(nomeConsulta), stdin);
    nomeConsulta[strcspn(nomeConsulta, "\n")] = '\0';

    fseek(arq, 0, SEEK_SET);

    int encontrado = 0;

    while (fread(&contato, sizeof(reg), 1, arq) == 1) {
        if (strncmp(nomeConsulta, contato.nome, sizeof(nomeConsulta)) == 0 && contato.status == ' ') {
            encontrado = 1;
            printf("\nSituação atual do veículo:\n");
            printf("Nome: %s\n", contato.nome);
            printf("Veículo: %s\n", contato.veiculo);
            printf("Dias estacionado: %d\n", contato.dias);
            printf("Status: %c\n", contato.status);
            break;
        }
    }

    if (!encontrado) {
        printf("\nVeículo não encontrado.\n");
    }
    // getchar();
    system("pause");
	system("cls");
}


int tamanho(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / sizeof(reg);
}

void excluir(FILE *arq) {
    reg contato;
    char nomeExcluir[20];
    char confirma;

    printf("Informe o nome do registro para excluir: ");
    getchar(); 
    fgets(nomeExcluir, sizeof(nomeExcluir), stdin);
    nomeExcluir[strcspn(nomeExcluir, "\n")] = '\0';

    fseek(arq, 0, SEEK_SET);
    int encontrado = 0;
    int posicao = 0;

    while (fread(&contato, sizeof(reg), 1, arq) == 1) {
        posicao++;

        if (strcmp(nomeExcluir, contato.nome) == 0 && contato.status == ' ') {
            encontrado = 1;
            printf("\nRegistro encontrado:\n");
            printf("Nome......:%s\n", contato.nome);
            printf("Veiculo...:%s\n", contato.veiculo);
            printf("Dias estacionado:%d\n", contato.dias);
            printf("Confirma a exclusao: <s/n>\n");
            //getchar();
            scanf(" %c",&confirma);

            if (toupper(confirma)== 'S') {
                printf("\nexcluindo...\n\n");
                fseek(arq, (posicao - 1) * sizeof(reg), SEEK_SET);
                contato.status = '*';
                fwrite(&contato, sizeof(reg), 1, arq);
                printf("Registro excluido com sucesso.\n");
                system("pause");
  				system("cls");;
            } else {
                printf("Exclusao cancelada.\n");
                system("pause");
                system ("cls");
            }

            break;
        }
        
        
    }

    if (!encontrado) {
        printf("\nRegistro nao encontrado ou ja excluido.\n");
    }
    system("pause");
    system("cls");
    
}




