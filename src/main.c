#include "../inc/main.h"
#define PORT 5000
#define MAX_SIZE_BUFFER 100

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Argumentos insuficientes, utilize:\n%s <IP do servidor>\n", argv[0]);
        return -1;
    }

    int socket_client = -1;
    struct sockaddr_in addr_server;
    socklen_t struct_addrlen = sizeof(addr_server);
    char buffer[MAX_SIZE_BUFFER];

    memset(buffer, '\0', sizeof(buffer));

    // Criar o Socket como protocolo UDP
    socket_client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_client < 0) {
        printf("Erro ao criar socket UDP\n");
        return -1;
    }
    printf("Socket criado com sucesso\n");

    // Configuração do endereço do servidor, utiliza IP informado pelo usuário e Porta definida em PORT
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(PORT);
    addr_server.sin_addr.s_addr = inet_addr(argv[1]);

    // Mensagem a ser enviada
    printf("Insira a mensagem: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Envia para o servidor
    if (sendto(socket_client, buffer, strlen(buffer), 0, (struct sockaddr*) &addr_server, struct_addrlen) < 0) {
        printf("Erro ao enviar\n");
        return -1;
    }

    memset(buffer, '\0', sizeof(buffer));

    // Recebe a resposta do servidor
    if (recvfrom(socket_client, buffer, sizeof(buffer), 0, (struct sockaddr*) &addr_server, &struct_addrlen) < 0){
        printf("Erro ao receber resposta do Servidor\n");
        return -1;
    }
    
    printf("Resposta do Servidor: %s\n", buffer);
    
    // Fechar o socket
    close(socket_client);

    // printf("IP = %s\nPort = %d\n", argv[1], PORT);

    return 0;
}