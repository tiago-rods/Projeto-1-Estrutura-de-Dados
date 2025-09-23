#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "FILA.h"

int mostrarMenu();
Pet criaPet(bool v[]);
void inserirPet(Fila *filaEmergencia, Fila *filaNormal, bool v[]);
int gerarID(bool v[]);
void registrarNoHistorico(Fila *historico, Pet p);
void atenderPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, bool v[]);
void mostrarProximo(Fila *filaEmergencia, Fila *filaNormal);
void buscarPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, char *termo, int buscarPorId);
void buscarPetInterface(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos);
void imprimeRelatorio(Fila *filaEmergencia, Fila *filaNormal);


int main() {

    bool vetorID[900] = {false};
    srand(time(NULL));


    Fila *filaEmergencia = CriaFila();
    Fila *filaNormal     = CriaFila();
    Fila *filaAtendidos  = CriaFila();
    int numEscolha;

    do {
        numEscolha = mostrarMenu();

        switch (numEscolha) {
            case 1:

                inserirPet(filaEmergencia, filaNormal, vetorID);
                break;

            case 2:
                atenderPet(filaEmergencia, filaNormal, filaAtendidos, vetorID);
                break;

            case 3:
                buscarPetInterface(filaEmergencia, filaNormal, filaAtendidos);
                break;

            case 4:
                imprimeRelatorio(filaEmergencia, filaNormal);
                break;

            case 5:
                mostrarProximo(filaEmergencia, filaNormal);
                break;

            case 6:
                imprimeFila(filaAtendidos);
                break;

            case 7:
                printf("\nFinalizando o sistema.\n");
                break;

            default:
                printf("\nDigite um numero valido!\n");
                break;
        }

    } while (numEscolha != 7);

    filaEmergencia = liberaFila(filaEmergencia);
    filaNormal     = liberaFila(filaNormal);
    filaAtendidos  = liberaFila(filaAtendidos);

    return 0;
}


int mostrarMenu() {

    int escolha;
    printf("\n==============================================\n");
    printf("   CLINICA VETERINARIA - GERENCIAMENTO DE FILAS\n");
    printf("==============================================\n");
    printf("1) Inserir pet na fila\n");
    printf("2) Atender proximo pet\n");
    printf("3) Buscar pet por Nome/ID\n");
    printf("4) Imprimir relatorio das filas\n");
    printf("5) Mostrar proximo a ser atendido\n");
    printf("6) Listar pets ja atendidos\n");
    printf("7) Finalizar\n");
    printf("----------------------------------------------\n");

    printf("Escolha: ");
    fflush(stdout);
    scanf("%d", &escolha);
    getchar();
    return escolha;
}

void atenderPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, bool v[]) {
    Pet petAtendido;

    if (!VaziaFila(filaEmergencia)) {
        petAtendido = RetiraFila(filaEmergencia, v);
        printf("\n=== ATENDENDO PET DE EMERGENCIA ===\n");
    }
    else if (!VaziaFila(filaNormal)) {
        petAtendido = RetiraFila(filaNormal, v);
        printf("\n=== ATENDENDO PET NORMAL ===\n");
    }
    else {
        printf("\nNao ha pets aguardando atendimento!\n");
        return;
    }

    petAtendido.atendido = 1;

    InsereFila(filaAtendidos, petAtendido);

    printf("Pet atendido com sucesso!\n");
    printf("ID: %d | Nome: %s | Especie: %s\n",
           petAtendido.id, petAtendido.nome, petAtendido.especie);
    printf("Prioridade: %s\n", (petAtendido.prioridade == 0 ? "Emergencial" : "Normal"));
}

void buscarPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, char *termo, int buscarPorId) {
    Nos *q;

    if(buscarPorId){
        int id = atoi(termo);
        for (q = filaEmergencia->inicio; (q != NULL && q->info.id != id); q = q->prox){}

        if(q->info.id == id){
            printf("\n=== PET ENCONTRADO NA FILA DE EMERGENCIA ===\n");

            printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                    q->info.id, q->info.nome, q->info.especie, q->info.idade);
            printf("Nascimento: %02d/%02d/%04d | Prioridade: Emergencial\n",
                    q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);

        } else{
            for (q = filaNormal -> inicio; (q != NULL && q->info.id != id); q = q->prox){}

            if(q->info.id == id) {
            printf("\n=== PET ENCONTRADO NA FILA NORMAL ===\n");

            printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                    q->info.id, q->info.nome, q->info.especie, q->info.idade);
            printf("Nascimento: %02d/%02d/%04d | Prioridade: Normal\n",
                    q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);

            } else{
                for (q = filaAtendidos -> inicio; (q != NULL && q->info.id != id); q = q->prox){}

                if (q->info.id == id) {
                    printf("\n=== PET ENCONTRADO NA FILA DE ATENDIDOS ===\n");

                    printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                           q->info.id, q->info.nome, q->info.especie, q->info.idade);
                    printf("Nascimento: %02d/%02d/%04d | Status: ATENDIDO\n",
                           q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);

                } else{
                    printf("\nPet nao encontrado!\n");
                }
            }
        }
    } else{
        for (q = filaEmergencia -> inicio; (q != NULL); q = q->prox){
            if (strstr(q->info.nome, termo) != NULL) {
                printf("\n=== PET ENCONTRADO NA FILA DE EMERGENCIA ===\n");
                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                        q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Prioridade: Emergencial\n",
                        q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);
                buscarPorId++;
            }
        }
        for (q = filaNormal -> inicio; (q != NULL); q = q->prox){
            if (strstr(q->info.nome, termo) != NULL) {
                printf("\n=== PET ENCONTRADO NA FILA NORMAL ===\n");
                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                        q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Prioridade: Normal\n",
                        q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);
                buscarPorId++;
            }
        }
        for (q = filaAtendidos -> inicio; (q != NULL); q = q->prox){
            if (strstr(q->info.nome, termo) != NULL) {
                printf("\n=== PET ENCONTRADO NA FILA DE ATENDIDOS ===\n");
                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                        q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Status: ATENDIDO\n",
                        q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);
                buscarPorId++;
            }
        }
        if(buscarPorId == 0){
            printf("\nPet nao encontrado!\n");
        }
    }
}


void buscarPetInterface(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos) {
    char termo[50];
    int opcao;

    printf("\nBuscar por:\n");
    printf("1) ID\n");
    printf("2) Nome\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("Digite o ID: ");
            fgets(termo, sizeof(termo), stdin);
            termo[strcspn(termo, "\n")] = '\0';
            buscarPet(filaEmergencia, filaNormal, filaAtendidos, termo, 1);
            break;
        case 2:
            printf("Digite o nome (ou parte do nome): ");
            fgets(termo, sizeof(termo), stdin);
            termo[strcspn(termo, "\n")] = '\0';
            buscarPet(filaEmergencia, filaNormal, filaAtendidos, termo, 0);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
    }
}



void imprimeRelatorio(Fila *filaEmergencia, Fila *filaNormal) {
    int countEmergencia = 0, countNormal = 0;
    Nos *q;

    for (q = filaEmergencia->inicio; q != NULL; q = q->prox) {
        countEmergencia++;
    }

    for (q = filaNormal->inicio; q != NULL; q = q->prox) {
        countNormal++;
    }

    printf("\n==============================================\n");
    printf("           RELATORIO DAS FILAS\n");
    printf("==============================================\n");
    printf("Pets na fila de EMERGENCIA: %d\n", countEmergencia);
    printf("Pets na fila NORMAL: %d\n", countNormal);
    printf("Total de pets aguardando: %d\n", countEmergencia + countNormal);
    printf("==============================================\n");

    if (countEmergencia > 0) {
        printf("\n--- FILA DE EMERGENCIA ---\n");
        imprimeFila(filaEmergencia);
    }

    if (countNormal > 0) {
        printf("\n--- FILA NORMAL ---\n");
        imprimeFila(filaNormal);
    }

    if (countEmergencia == 0 && countNormal == 0) {
        printf("\nNenhum pet aguardando atendimento.\n");
    }
}


int gerarID(bool v[]){

    int id;

    do {
        id = rand() % 900 + 100;
    } while (v[id - 100]);

    v[id - 100] = true;

    return id;
}


Pet criaPet(bool v[]){
    Pet p;

    p.atendido = 0;
    p.id = gerarID(v);

    printf("Nome: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';


    printf("Especie: ");
    fgets(p.especie, sizeof(p.especie), stdin);
    p.especie[strcspn(p.especie, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &p.idade);
    getchar();

    printf("Ano de nascimento: ");
    scanf("%d", &p.nascimento.ano);
    getchar();

    printf("Mes de nascimento: ");
    scanf("%d", &p.nascimento.mes);
    getchar();

    printf("Dia de nascimento: ");
    scanf("%d", &p.nascimento.dia);
    getchar();

    printf("Tipo de prioridade (0 = Emergencia | 1 = Normal ): ");
    scanf("%d", &p.prioridade);
    getchar();

    return p;
}


void inserirPet(Fila *filaEmergencia, Fila *filaNormal, bool v[]){

    Pet novoPet = criaPet(v);

    if (novoPet.prioridade == 0){
        InsereFila(filaEmergencia, novoPet);
    } else{
        InsereFila(filaNormal, novoPet);
    }
}

void mostrarProximo(Fila *filaEmergencia, Fila *filaNormal){

    Pet p;
    printf("\n=== PROXIMO PET A SER ATENDIDO ===\n");
    if (!VaziaFila(filaEmergencia) ) {
        p = filaEmergencia->inicio->info;
        printf("Nome: %s | Especie: %s | Tipo de atendimento: Emergencial (%d)\n", p.nome, p.especie, p.prioridade);
    }
    else if (!VaziaFila(filaNormal)){
        p = filaNormal->inicio->info;
        printf("Nome: %s | Especie: %s | Tipo de atendimento: Normal (%d)\n", p.nome, p.especie, p.prioridade);
    }
    else{
        printf("\nNao ha pets aguardando atendimento!\n");
    }

}
