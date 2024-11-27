#include "../inc/main.h"

int main(int argc, char *argv[]) {
    if (argc < 3){
        printf("Argumentos insuficientes, utilize:\n%s <IP do servidor> <Porta>\n", argv[0]);
        return -1;
    }

    printf("IP = %s\nPort = %s\n", argv[1], argv[2]);

    return 0;
}