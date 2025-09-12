#include <stdio.h>
#include <conio.h> // Para _getch() e _kbhit()
#include <stdlib.h>
#include <windows.h> // Para Sleep()


// Função para obter a largura do console no Windows
int get_console_width_win() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return -1; // Erro ao obter o handle do console
    }
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return -1; // Erro ao obter informações do buffer
    }
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int main(){
    int width = get_console_width_win();
    if (width == -1) {
        printf("Erro ao obter a largura do console.\n");
        return 1;
    }

    const char *message = "Bem-vindo à Clínica Veterinária!";
    int msg_len = strlen(message);
    int pos = 0;
    int direction = 1; // 1 para direita, -1 para esquerda

    while (1) {
        // Limpa a linha
        printf("\r%*s", width, ""); // Preenche com espaços em branco

        // Calcula a posição atual da mensagem
        int start_pos = pos % (width + msg_len);
        if (start_pos < width) {
            printf("\r%*s%s", start_pos, "", message);
        } else if (start_pos < width + msg_len) {
            printf("\r%s%*s", message + (start_pos - width), width - (start_pos - width), "");
        }

        fflush(stdout);
        Sleep(100); // Ajuste a velocidade aqui

        // Atualiza a posição
        pos += direction;
        if (pos > width || pos < -msg_len) {
            direction *= -1; // Inverte a direção
        }

        // Verifica se uma tecla foi pressionada
        if (_kbhit()) {
            _getch(); // Lê o caractere pressionado (sem exibir)
            break; // Sai do loop
        }
    }

    printf("\nPrograma encerrado.\n");
    return 0;
}