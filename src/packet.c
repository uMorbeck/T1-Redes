#include "../inc/packet.h"

// Converts and show the time, based on the transmitted timestam (txTm_s) in the packet
void print_ntp_time(ntp_packet *packet) {
    // Converts to big-endian
    uint32_t txTm_s = ntohl(packet->txTm_s);  
    //  Adjusts Epoch NTP to UNIX 
    time_t time_val = (time_t)(txTm_s - 2208988800U); 

    // Converts to time structure
    struct tm *time_info = gmtime(&time_val); 
    printf("Data/hora: %s", asctime(time_info));
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
