#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "FILA.h"
#include <string.h>
/* ============== TODO ============== */
// - função para atender o próximo pet (retirar da fila e adicionar ao histórico)
// - Verificar o motivo de pets selecionados para irem para a fila normal irem para a fila de emergência
// -
// -
// -
// -
// -
/* ============== TODO ============== */

//* ============== DONE ============== */
// -
// -
// -
// -
// -
// -
// -
// -
//* ============== DONE ============== */


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

    bool vetorID[900] = {false}; // inicializa o vetor de ids como todos falsos
    srand(time(NULL)); // semente para o programa inteiro

 // CRIANDO FILAS

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
                // Atender próximo
                atenderPet(filaEmergencia, filaNormal, filaAtendidos, vetorID);
                break;

            case 3:
                // Buscar por nome ou ID
                buscarPetInterface(filaEmergencia, filaNormal, filaAtendidos);
                break;

            case 4:
                // Imprimir relatório das filas
                imprimeRelatorio(filaEmergencia, filaNormal);
                break;

            case 5:
                // Mostrar próximo da fila
                mostrarProximo(filaEmergencia, filaNormal);
                break;

            case 6:
                // Listar pets já atendidos
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

    // Libera memoria e deixa os ponteiros null pois o libera fila retorna null
    filaEmergencia = liberaFila(filaEmergencia);
    filaNormal     = liberaFila(filaNormal);
    filaAtendidos  = liberaFila(filaAtendidos);

    return 0;
}


// --------------------------------------------------------
// Menu
// --------------------------------------------------------
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
    getchar(); // consome o '\n' deixado no buffer
    return escolha;
}
// ----------------------------------------------------------------



//===============================================
//Funções principais
//===============================================





//=================================================================


//TODO verificar se os pets já atendidos sairam da fila de espera de seu respectivo tipo
void atenderPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, bool v[]) {
    Pet petAtendido;

    // Verifica se há pets na fila de emergência primeiro
    if (!VaziaFila(filaEmergencia)) {
        petAtendido = RetiraFila(filaEmergencia, v);
        printf("\n=== ATENDENDO PET DE EMERGENCIA ===\n");
    }
    // Se não há emergência, verifica fila normal
    else if (!VaziaFila(filaNormal)) {
        petAtendido = RetiraFila(filaNormal, v);
        printf("\n=== ATENDENDO PET NORMAL ===\n");
    }
    // Se ambas estão vazias
    else {
        printf("\nNao ha pets aguardando atendimento!\n");
        return;
    }

    // Marca o pet como atendido
    petAtendido.atendido = 1;

    // Adiciona à fila de atendidos
    InsereFila(filaAtendidos, petAtendido);

    // Mostra informações do pet atendido
    printf("Pet atendido com sucesso!\n");
    printf("ID: %d | Nome: %s | Especie: %s\n",
           petAtendido.id, petAtendido.nome, petAtendido.especie);
    printf("Prioridade: %s\n", (petAtendido.prioridade == 0 ? "Emergencial" : "Normal"));
}

//= ================================================
//TODO talvez fazer um switch case para escolher se quer buscar por nome ou id
void buscarPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, char *termo, int buscarPorId) {
    Nos *q;

    if(buscarPorId){    //CHECA SE A BUSCA SERÁ POR ID OU POR NOME
        int id = atoi(termo);
        for (q = filaEmergencia->inicio; (q != NULL && q->info.id != id); q = q->prox){}    //RODA TODA A FILA EMERGENCIAL ATÉ ENCONTRAR O ID, OU ACABAR A FILA

        if(q->info.id == id) {              //SE O PET FOR ENCONTRADO NA FILA EMERGENCIAL, IMPRIMIR INFORMAÇÕES E STATUS DO PET
            printf("\n=== PET ENCONTRADO NA FILA DE EMERGENCIA ===\n");

            printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                    q->info.id, q->info.nome, q->info.especie, q->info.idade);
            printf("Nascimento: %02d/%02d/%04d | Prioridade: Emergencial\n",
                    q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);

        } else{                             //CASO O PET NÃO ESTEJA NA FILA PREFERENCIAL, BUSCAR NA FILA NORMAL
            for (q = filaNormal -> inicio; (q != NULL && q->info.id != id); q = q->prox){}

            if(q->info.id == id) {
            printf("\n=== PET ENCONTRADO NA FILA NORMAL ===\n");

            printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                    q->info.id, q->info.nome, q->info.especie, q->info.idade);
            printf("Nascimento: %02d/%02d/%04d | Prioridade: Normal\n",
                    q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);

            } else{                         //CASO O PET NÃO ESTEJA NA FILA DE ATENDIMENTO, BUSCAR NO HISTÓRICO DE PETS JÁ ATENDIDOS
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
    } else{     //BUSCA REALIZADA POR NOME
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

//= =============================================

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
            fgets(termo, sizeof(termo), stdin); //std
            termo[strcspn(termo, "\n")] = '\0'; //strcsonspn remove o \n do final da string, assim não precisa usar o getchar depois do fgets
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

    // Conta pets na fila de emergência
    for (q = filaEmergencia->inicio; q != NULL; q = q->prox) {
        countEmergencia++;
    }

    // Conta pets na fila normal
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

//-----------------------------------------------
//Gera um novo id que ainda nao foi utilizado
//-----------------------------------------------

int gerarID(bool v[]){

    int id;

    do {
        id = rand() % 900 + 100;  // gera  id entre 100 e 999
    } while (v[id - 100]);    // se a condição for verdadeira significa que ja foi usado, portando gera outro id

    v[id - 100] = true;       //  caso o id nao tenha sido usado ainda, marca como usado

    return id;
}


//Cria um novo pet
Pet criaPet(bool v[]){
    Pet p;

    p.atendido = 0; // Um novo pet ainda nao foi atendido, por padrao = 0
    p.id = gerarID(v);

    printf("Nome: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';


    printf("Especie: ");
    fgets(p.especie, sizeof(p.especie), stdin);
    p.especie[strcspn(p.especie, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &p.idade);
    getchar(); // limpa o \n deixado no buffer

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


//Insere um novo pet na fila
void inserirPet(Fila *filaEmergencia, Fila *filaNormal, bool v[]){

    //cria o pet
    Pet novoPet = criaPet(v);

    //insere o pet na fila
    if (novoPet.prioridade == 0){
        InsereFila(filaEmergencia, novoPet); // Insere na fila emergencial
    } else{
        InsereFila(filaNormal, novoPet); // Insere na fila normal
    }
}

// Mostra o proximo pet a ser antendido
// Deve exibir nome, especie e tipo de atendimento
void mostrarProximo(Fila *filaEmergencia, Fila *filaNormal){

    Pet p;
    printf("\n=== PROXIMO PET A SER ATENDIDO ===\n");
    if (!VaziaFila(filaEmergencia) ) { // Se a fila de emergencia nao estiver vazia, mostra o proximo a ser atendido
        p = filaEmergencia->inicio->info;
        printf("Nome: %s | Especie: %s | Tipo de atendimento: Emergencial (%d)\n", p.nome, p.especie, p.prioridade);
    }
    else if (!VaziaFila(filaNormal)){ //Se a fila normal nao estiver vazia
        p = filaNormal->inicio->info;
        printf("Nome: %s | Especie: %s | Tipo de atendimento: Normal (%d)\n", p.nome, p.especie, p.prioridade);
    }
    else{
        printf("\nNao ha pets aguardando atendimento!\n");
    }

}
