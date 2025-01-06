#include "../inc/packet.h"
#include <stdio.h>
#include <time.h>


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

void juntate_sntp_packet(ntp_packet *packet, char *buffer, size_t buffer_size) {    
    char temp[50]; // Buffer temporário para conversão

    // Concatenar `li_vn_mode` sem espaços
    snprintf(temp, sizeof(temp), "%02X", packet->li_vn_mode);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `stratum` sem espaços
    snprintf(temp, sizeof(temp), "%02X", packet->stratum);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `poll` sem espaços
    snprintf(temp, sizeof(temp), "%02X", packet->poll);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `precision` sem espaços
    snprintf(temp, sizeof(temp), "%02X", packet->precision);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `rootDelay` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->rootDelay);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `rootDispersion` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->rootDispersion);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `refId` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->refId);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `refTm_s` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->refTm_s);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `refTm_f` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->refTm_f);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `origTm_s` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->origTm_s);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `origTm_f` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->origTm_f);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `rxTm_s` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->rxTm_s);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `rxTm_f` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->rxTm_f);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `txTm_s` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->txTm_s);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);

    // Concatenar `txTm_f` sem espaços
    snprintf(temp, sizeof(temp), "%08X", packet->txTm_f);
    strncat(buffer, temp, buffer_size - strlen(buffer) - 1);
}
