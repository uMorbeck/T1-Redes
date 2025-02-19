#include "../inc/main.h"

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Argumentos insuficientes, utilize:\n%s <IP do servidor>\n", argv[0]);
        return -1;
    }

    // Criando Variáveis
    int socket_client = -1;
    struct sockaddr_in addr_server;
    socklen_t struct_addrlen = sizeof(addr_server);
    char buffer[MAX_SIZE_BUFFER] = {0};
    struct timeval timeout;
    

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

    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;
    
    if (setsockopt(socket_client, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        printf("Erro ao setar o timeout\n");
        close(socket_client);
        return -1;
    }

    // Stringificando o Pacote
    juntate_sntp_packet(&packet, buffer);

    // Envia para o servidor
    printf("Enviando Requisição para %s\n", argv[1]);
    if (sendto(socket_client, buffer, MAX_SIZE_BUFFER, 0, (struct sockaddr*) &addr_server, struct_addrlen) < 0) {
        printf("Erro ao enviar\n");
        return -1;
    }

    memset(buffer, '\0', sizeof(buffer));

    // Recebe a resposta do servidor
    int bytes_recebidos = recvfrom(socket_client, buffer, sizeof(buffer), 0, (struct sockaddr*) &addr_server, &struct_addrlen);
    if (bytes_recebidos < 0){
        printf("Timeout da Requisição, Tentando Novamente...\n");
        if (sendto(socket_client, buffer, MAX_SIZE_BUFFER, 0, (struct sockaddr*) &addr_server, struct_addrlen) < 0) {
            printf("Erro ao enviar\n");
            return -1;
        }
        bytes_recebidos = recvfrom(socket_client, buffer, sizeof(buffer), 0, (struct sockaddr*) &addr_server, &struct_addrlen);
        if (bytes_recebidos < 0) {
            printf("\nData/hora: não foi possível contactar servidor\n");
            close(socket_client);
            return -1;
        }
    }
    
    printf("Resposta do Servidor:\n");
    for (int i = 0; i < bytes_recebidos; i++) {
        printf("%02X ", (unsigned char) buffer[i]);
    }
    printf("\n\n");

    unjuntate_sntp_packet(&packet, buffer);

    // Exibe a data/hora
    print_ntp_time(&packet);
    
    // Fechar o socket
    close(socket_client);
    return 0;
}