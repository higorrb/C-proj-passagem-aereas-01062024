#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NOMES 100

typedef struct{
    int id_voo;
    char origem[MAX_NOMES];
    char destino[MAX_NOMES];
    char data_partida[11];
    char horario_partida[6];
    int assentos_disponiveis;
}Voo;

typedef struct{
    char nome[MAX_NOMES];
    int idade;
    char sexo;
    int qnt_filhos;
    char numero_doc[12];
}Passageiro;


void Adicionar_passageiro(Passageiro *reg_passageiro){

    
    printf("Digite o seu nome: ");
    fgets(reg_passageiro->nome, MAX_NOMES, stdin);
    reg_passageiro->nome[strcspn(reg_passageiro->nome, "\n")] = '\0';
    

    printf("Digite sua Idade: ");
    scanf("%d", &reg_passageiro->idade);
    fflush(stdin);
    

    printf("Digite seu Sexo: ");
    scanf("%c", &reg_passageiro->sexo);
    fflush(stdin);
    

    printf("Digite quantos filhos possui: ");
    scanf("%d", &reg_passageiro->qnt_filhos);
    fflush(stdin);
    

    printf("Digite o numero do seu documento[apenas numeros]: ");
    fgets(reg_passageiro->numero_doc, 12, stdin);
    reg_passageiro->numero_doc[strcspn(reg_passageiro->numero_doc, "\n")] = '\0';
    fflush(stdin);

    printf("Passageiro Adicionado com sucesso!");
}


void Mostrar_passageiro(Passageiro *reg_passageiro){
    printf("~~~~~~DADOS DO PASSAGEIRO~~~~~~\n");
    printf("\nNome: %s\n", reg_passageiro->nome);
    printf("Idade: %d\n", reg_passageiro->idade);
    printf("Sexo: %c\n", reg_passageiro->sexo);
    printf("Filhos: %d\n", reg_passageiro->qnt_filhos);
    printf("Documento: %s\n", reg_passageiro->numero_doc);
}

void Alterar_dados(Passageiro *reg_passageiro){
      printf("Digite o seu nome: ");
    fgets(reg_passageiro->nome, MAX_NOMES, stdin);
    reg_passageiro->nome[strcspn(reg_passageiro->nome, "\n")] = '\0';
    

    printf("Digite sua Idade: ");
    scanf("%d", &reg_passageiro->idade);
    fflush(stdin);
    

    printf("Digite seu Sexo: ");
    scanf("%c", &reg_passageiro->sexo);
    fflush(stdin);
    

    printf("Digite quantos filhos possui: ");
    scanf("%d", &reg_passageiro->qnt_filhos);
    fflush(stdin);
    

    printf("Digite o numero do seu documento[apenas numeros]: ");
    fgets(reg_passageiro->numero_doc, 12, stdin);
    reg_passageiro->numero_doc[strcspn(reg_passageiro->numero_doc, "\n")] = '\0';
    fflush(stdin);

    printf("Dados alterados com sucesso!");
}

int Consultar_voo() {
    char linha[1000];
    Voo reg_voo;

    FILE* arquivo = fopen("Voos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    char passageiro_origem[MAX_NOMES];
    char passageiro_destino[MAX_NOMES];
    char passageiro_data[11];

    printf("Digite a origem da sua viagem[sem espaco]: ");
    fgets(passageiro_origem, MAX_NOMES, stdin);
    passageiro_origem[strcspn(passageiro_origem, "\n")] = '\0';

    printf("Digite o destino da sua viagem[sem espaco]: ");
    fgets(passageiro_destino, MAX_NOMES, stdin);
    passageiro_destino[strcspn(passageiro_destino, "\n")] = '\0';

    printf("Digite a data de partida da sua viagem[DD/MM/AAAA]: ");
    fgets(passageiro_data, sizeof(passageiro_data), stdin);
    passageiro_data[strcspn(passageiro_data, "\n")] = '\0';

    int encontrado = 0;
    printf("--------VIAGENS DISPONIVEIS--------\n");

    
    Voo* voos_disponiveis = malloc(MAX_NOMES * sizeof(Voo));
    if (voos_disponiveis == NULL) {
        printf("Erro de alocação de memória.");
        return 1;
    }
    int num_voos = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%d %s %s %s %s %d", &reg_voo.id_voo, reg_voo.origem, reg_voo.destino, reg_voo.data_partida, reg_voo.horario_partida, &reg_voo.assentos_disponiveis);

        if (stricmp(passageiro_origem, reg_voo.origem) == 0 && stricmp(passageiro_destino, reg_voo.destino) == 0 && stricmp(passageiro_data, reg_voo.data_partida) == 0) {
            
            voos_disponiveis[num_voos++] = reg_voo;

            printf("\nID..........................%d\n", reg_voo.id_voo);
            printf("Origem......................%s\n", reg_voo.origem);
            printf("Destino.....................%s\n", reg_voo.destino);
            printf("Data........................%s\n", reg_voo.data_partida);
            printf("Horario.....................%s\n", reg_voo.horario_partida);
            printf("Assentos[disponiveis].......%d\n", reg_voo.assentos_disponiveis);
            encontrado = 1;
        }
    }
    if (encontrado == 0) {
        printf("Nenhum voo encontrado para os dados fornecidos.\n");
    }

    
    free(voos_disponiveis);
    fclose(arquivo);
    return 0;
}


int Reservar_voo(Voo *reserva_passageiro){
    int id;
    char resposta;
    char linha[1000];
    Voo reg_voo;


     FILE* arquivo = fopen("Voos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    FILE* arquivo_temp = fopen("temporario.txt", "w");
    if (arquivo_temp == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }
    

    printf("Digite o ID da viagem para reservar: ");
    scanf("%d", &id);
    fflush(stdin);

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%d %s %s %s %s %d", &reg_voo.id_voo, reg_voo.origem, reg_voo.destino, reg_voo.data_partida, reg_voo.horario_partida, &reg_voo.assentos_disponiveis);
        if (reg_voo.id_voo == id)
        {
            printf("\nID..........................%d\n", reg_voo.id_voo);
            printf("Origem......................%s\n", reg_voo.origem);
            printf("Destino.....................%s\n", reg_voo.destino);
            printf("Data........................%s\n", reg_voo.data_partida);
            printf("Horario.....................%s\n", reg_voo.horario_partida);
            printf("Assentos[disponiveis].......%d\n", reg_voo.assentos_disponiveis);

            printf("Deseja Reservar essa viagem[S/N]? ");
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S')
            {
                *reserva_passageiro = reg_voo;
                printf("Viagem reservada com sucesso!\n");

                reg_voo.assentos_disponiveis--;

                
            }

        }
        fprintf(arquivo_temp, "%d %s %s %s %s %d\n", reg_voo.id_voo, reg_voo.origem, reg_voo.destino, reg_voo.data_partida, reg_voo.horario_partida, reg_voo.assentos_disponiveis);

        
    }
    fclose(arquivo_temp);
    fclose(arquivo);
    remove("Voos.txt");
    rename("temporario.txt", "Voos.txt");
    return 0;

}

void Consultar_reserva(Voo reserva_passageiro, Passageiro *reg_passageiro){
        printf("\n~~~~~~DADOS DO PASSAGEIRO~~~~~~\n");
        printf("Nome: %s\n", reg_passageiro->nome);
        printf("Idade: %d\n", reg_passageiro->idade);
        printf("Sexo: %c\n", reg_passageiro->sexo);
        printf("Filhos: %d\n", reg_passageiro->qnt_filhos);
        printf("Documento: %s\n", reg_passageiro->numero_doc);
        printf("\n~~~~~~DADOS DA VIAGEM~~~~~~\n");
        printf("ID..........................%d\n", reserva_passageiro.id_voo);
        printf("Origem......................%s\n", reserva_passageiro.origem);
        printf("Destino.....................%s\n", reserva_passageiro.destino);
        printf("Data........................%s\n", reserva_passageiro.data_partida);
        printf("Horario.....................%s\n", reserva_passageiro.horario_partida);
}

int Cancelar_reserva(Voo *reserva_passageiro){
    Voo reg_voo;
    char resposta;
    char linha[1000];

     FILE* arquivo = fopen("Voos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    FILE* arquivo_temp = fopen("temporario.txt", "w");
    if (arquivo_temp == NULL) {
        printf("Erro ao abrir arquivo");
        return 1;
    }

    printf("Deseja Cancelar essa Reserva[S/N]? ");
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S')
            {
                while (fgets(linha, sizeof(linha), arquivo) != NULL)
            {
            sscanf(linha, "%d %s %s %s %s %d", &reg_voo.id_voo, reg_voo.origem, reg_voo.destino, reg_voo.data_partida, reg_voo.horario_partida, &reg_voo.assentos_disponiveis);
                if (reserva_passageiro->id_voo == reg_voo.id_voo)
                {
                    reg_voo.assentos_disponiveis++;
                }   
            fprintf(arquivo_temp, "%d %s %s %s %s %d\n", reg_voo.id_voo, reg_voo.origem, reg_voo.destino, reg_voo.data_partida, reg_voo.horario_partida, reg_voo.assentos_disponiveis);
            }
            
            reserva_passageiro->id_voo = 0;
            reserva_passageiro->origem[0] = '\0';
            reserva_passageiro->destino[0] = '\0';
            reserva_passageiro->data_partida[0] = '\0';
            reserva_passageiro->horario_partida[0] = '\0';
            reserva_passageiro->assentos_disponiveis = 0;


        }
    else{
        printf("Cancelamento negado...\n");
        fclose(arquivo_temp);
        fclose(arquivo);
        return 0;
    }
    fclose(arquivo_temp);
    fclose(arquivo);
    remove("Voos.txt");
    rename("temporario.txt", "Voos.txt");
    return 0;
}



int main(){
    Voo reserva_passageiro;
    Passageiro reg_passageiro;
    reg_passageiro.idade = 0;
    reserva_passageiro.id_voo = 0;

    int op;

    do
    {
        printf("\n=-=-=-=-=-=-=MENU=-=-=-=-=-=-=\n=====PASSAGEIRO=====\n[1]-Inserir dados passageiro\n[2]-Mostrar dados passageiro\n[3]-Alterar dados passageiro\n======VOOS======\n[4]-Consultar voos disponiveis\n[5]-Reservar Passagem\n[6]-Consultar Reserva\n[7]-Cancelar Reserva\n=====ENCERRAR=====\n[0]-Sair do Programa\nDigite um opcao: ");
        scanf("%d", &op);
        fflush(stdin);
        switch (op)
        {
        case 1:
            Adicionar_passageiro(&reg_passageiro);
            break;

        case 2:
            if(reg_passageiro.idade != 0){
                Mostrar_passageiro(&reg_passageiro);
            }
            else{
                printf("Primeiramente Insira os dados do Passageiro...");
            }
            break;

        case 3:
            if(reg_passageiro.idade != 0){
                Alterar_dados(&reg_passageiro);
            }
            else{
                printf("Primeiramente Insira os dados do Passageiro...");
            }
            break;

        case 4:
            Consultar_voo();
            break;

        case 5:
            if(reg_passageiro.idade != 0){
                Reservar_voo(&reserva_passageiro);
            }
            else{
                printf("Primeiramente Insira os dados do Passageiro...");
            }
            break;

        case 6:
            if(reg_passageiro.idade != 0 && reserva_passageiro.id_voo != 0){
                Consultar_reserva(reserva_passageiro, &reg_passageiro);
            }
            else{
                printf("Primeiramente Insira os dados do Passageiro e faca uma reserva....");
            }
            break;

        case 7:
            if(reg_passageiro.idade != 0 && reserva_passageiro.id_voo != 0){
                Cancelar_reserva(&reserva_passageiro);
            }
            else{
                printf("Primeiramente Insira os dados do Passageiro e faca uma reserva....");
            }
            break;
        case 0:
            printf("Programa Encerrado.");
            break;
        default:
            printf("DIgite novamente...");
            break;
        }
    } while (op != 0);
    


    return 0;
}