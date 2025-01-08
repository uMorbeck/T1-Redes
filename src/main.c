#include "../inc/main.h"
#define PORT 123
#define MAX_SIZE_BUFFER 48
#define TIMEOUT 20

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Argumentos insuficientes, utilize:\n%s <IP do servidor>\n", argv[0]);
        return -1;
    }

    int socket_client = -1;
    struct sockaddr_in addr_server;
    socklen_t struct_addrlen = sizeof(addr_server);
    char buffer[MAX_SIZE_BUFFER] = {0};

    // Inicializa o pacote NTP
    ntp_packet packet = {0};
    packet.li_vn_mode = 0x1B;
    
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

    // Stringificando o Pacote
    juntate_sntp_packet(&packet, buffer);

    // Envia para o servidor
    if (sendto(socket_client, buffer, MAX_SIZE_BUFFER, 0, (struct sockaddr*) &addr_server, struct_addrlen) < 0) {
        printf("Erro ao enviar\n");
        return -1;
    }

    memset(buffer, '\0', sizeof(buffer));

    // Recebe a resposta do servidor
    int bytes_recebidos = recvfrom(socket_client, buffer, sizeof(buffer), 0, (struct sockaddr*) &addr_server, &struct_addrlen);
    if (bytes_recebidos < 0){
        printf("Erro ao receber resposta do Servidor\n");
        return -1;
    }
    
    printf("Resposta do Servidor:\n");
    for (int i = 0; i < bytes_recebidos; i++) {
        printf("%02X ", (unsigned char) buffer[i]);
    }
    printf("\n");

    // Exibe a data/hora
    // print_ntp_time(&packet);
    
    // Fechar o socket
    close(socket_client);
    return 0;
}