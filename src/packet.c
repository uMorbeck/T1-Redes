#include "../inc/packet.h"

// Converts and show the time, based on the transmitted timestam (txTm_s) in the packet
void print_ntp_time(ntp_packet *packet) {
    // Converts to big-endian
    uint32_t txTm_s = packet->txTm_s;  
    //  Adjusts Epoch NTP to UNIX 
    time_t time_val = (time_t)(txTm_s - 2208988800UL); 

    // Converts to time structure
    struct tm *time_info = localtime(&time_val); 
    char *tempo = asctime(time_info);
    int day;
 
    if (tempo[0] == 'S' && tempo[1] == 'u') {
        day = 1;
    } else if (tempo[0] == 'M') {
        day = 2;
    } else if (tempo[0] == 'T' && tempo[1] == 'u') {
        day = 3;
    } else if (tempo[0] == 'W') {
        day = 4;
    } else if (tempo[0] == 'T' && tempo[1] == 'h') {
        day = 5;
    } else if (tempo[0] == 'F') {
        day = 6;
    } else if (tempo[0] == 'S' && tempo[1] == 'a') {
        day = 7;
    }

    switch (day) {
        case 1:
            tempo[0] = 'D';
            tempo[1] = 'o';
            tempo[2] = 'm';
            break;
        case 2: 
            tempo[0] = 'S';
            tempo[1] = 'e';
            tempo[2] = 'g';
            break;
        case 3:
            tempo[0] = 'T';
            tempo[1] = 'e';
            tempo[2] = 'r';
            break;
        case 4:
            tempo[0] = 'Q';
            tempo[1] = 'u';
            tempo[2] = 'a';
            break;
        case 5:
            tempo[0] = 'Q';
            tempo[1] = 'u';
            tempo[2] = 'i';
            break;
        case 6:
            tempo[0] = 'S';
            tempo[1] = 'e';
            tempo[2] = 'x';
            break;
        case 7:
            tempo[0] = 'S';
            tempo[1] = 'a';
            tempo[2] = 'b';
            break;
        default:
            break;
    }

    int mes;

    if (tempo[4] == 'F') {
        mes = 2;
    } else if (tempo[4] == 'A' && tempo[5] == 'p') {
        mes = 4;
    } else if (tempo[4] == 'M') {
        mes = 5;
    } else if (tempo[4] == 'A' && tempo[5] == 'u') {
        mes = 8;
    } else if (tempo[4] == 'S') {
        mes = 9;
    } else if (tempo[4] == 'O') {
        mes = 10;
    } else if (tempo[4] == 'D') {
        mes = 12;
    }


    switch (mes) {
        case 2:
            tempo[0] = 'F';
            tempo[1] = 'e';
            tempo[2] = 'v';
            break;
        case 4: 
            tempo[0] = 'A';
            tempo[1] = 'b';
            tempo[2] = 'r';
            break;
        case 5:
            tempo[0] = 'M';
            tempo[1] = 'a';
            tempo[2] = 'i';
            break;
        case 8:
            tempo[0] = 'A';
            tempo[1] = 'g';
            tempo[2] = 'o';
            break;
        case 9:
            tempo[0] = 'S';
            tempo[1] = 'e';
            tempo[2] = 't';
            break;
        case 10:
            tempo[0] = 'O';
            tempo[1] = 'u';
            tempo[2] = 't';
            break;
        case 12:
            tempo[0] = 'D';
            tempo[1] = 'e';
            tempo[2] = 'z';
            break;
        default:
            break;
    }

    printf("Data/hora: %s", tempo);
}

void juntate_sntp_packet(ntp_packet *packet, char *buffer) {
    // Escrevendo as variáveis de 1 byte
    buffer[0] = packet->li_vn_mode;
    buffer[1] = packet->stratum; 
    buffer[2] = packet->poll; 
    buffer[3] = packet->precision;

    // Campos do pacote
    uint32_t *campos[] = {
        &packet->rootDelay, &packet->rootDispersion, &packet->refId,
        &packet->refTm_s, &packet->refTm_f, &packet->origTm_s,
        &packet->origTm_f, &packet->rxTm_s, &packet->rxTm_f,
        &packet->txTm_s, &packet->txTm_f
    };

    // Offset para as variáveis de 1 byte
    int offset = 4;

    // Escrevendo as variáveis de 4 bytes
    for (int i = 0; i < 11; i++) {
        buffer[offset++] = (*campos[i] >> 24) & 0xff;
        buffer[offset++] = (*campos[i] >> 16) & 0xff;
        buffer[offset++] = (*campos[i] >> 8) & 0xff;
        buffer[offset++] = *campos[i] & 0xff;
    }

}

void unjuntate_sntp_packet(ntp_packet *packet, char *buffer) {
    // Escrevendo as variáveis de 1 byte
    packet->li_vn_mode = (unsigned char) buffer[0];
    packet->stratum = (unsigned char) buffer[1]; 
    packet->poll = (unsigned char) buffer[2]; 
    packet->precision = (unsigned char) buffer[3];

    // Campos do pacote
    uint32_t *campos[] = {
        &packet->rootDelay, &packet->rootDispersion, &packet->refId,
        &packet->refTm_s, &packet->refTm_f, &packet->origTm_s,
        &packet->origTm_f, &packet->rxTm_s, &packet->rxTm_f,
        &packet->txTm_s, &packet->txTm_f
    };

    // Offset para as variáveis de 1 byte
    int offset = 4;

    // Escrevendo as variáveis de 4 bytes
    for (int i = 0; i < 11; i++) {
        *campos[i] = ((u_int32_t)(unsigned char) buffer[offset] << 24) | 
                    ((u_int32_t)(unsigned char) buffer[offset + 1] << 16) |
                    ((u_int32_t)(unsigned char) buffer[offset + 2] << 8) |
                    ((u_int32_t)(unsigned char) buffer[offset + 3]);
        offset += 4;
    }
}
