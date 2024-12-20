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

void juntate_sntp_packet(ntp_packet *packet, char *buffer) {
    char temp[50]; // Buffer temporário para conversão

    // Concatenar `li_vn_mode`
    sprintf(temp, "%02X ", packet->li_vn_mode); // Converte para string hexadecimal
    strcat(buffer, temp);

    // Concatenar `stratum`
    sprintf(temp, "%02X ", packet->stratum);
    strcat(buffer, temp);

    // Concatenar `poll`
    sprintf(temp, "%02X ", packet->poll);
    strcat(buffer, temp);

    // Concatenar `precision`
    sprintf(temp, "%02X ", packet->precision);
    strcat(buffer, temp);

    // Concatenar `rootDelay`
    sprintf(temp, "%08X ", packet->rootDelay); // Converte `uint32_t` para string hexadecimal
    strcat(buffer, temp);

    // Concatenar `rootDispersion`
    sprintf(temp, "%08X ", packet->rootDispersion);
    strcat(buffer, temp);

    // Concatenar `refId`
    sprintf(temp, "%08X ", packet->refId);
    strcat(buffer, temp);

    // Concatenar `refTm_s`
    sprintf(temp, "%08X ", packet->refTm_s);
    strcat(buffer, temp);

    // Concatenar `refTm_f`
    sprintf(temp, "%08X ", packet->refTm_f);
    strcat(buffer, temp);

    // Concatenar `origTm_s`
    sprintf(temp, "%08X ", packet->origTm_s);
    strcat(buffer, temp);

    // Concatenar `origTm_f`
    sprintf(temp, "%08X ", packet->origTm_f);
    strcat(buffer, temp);

    // Concatenar `rxTm_s`
    sprintf(temp, "%08X ", packet->rxTm_s);
    strcat(buffer, temp);

    // Concatenar `rxTm_f`
    sprintf(temp, "%08X ", packet->rxTm_f);
    strcat(buffer, temp);

    // Concatenar `txTm_s`
    sprintf(temp, "%08X ", packet->txTm_s);
    strcat(buffer, temp);

    // Concatenar `txTm_f`
    sprintf(temp, "%08X ", packet->txTm_f);
    strcat(buffer, temp);
}
