#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// Structure of NTP Packet
typedef struct {
    uint8_t li_vn_mode;     // Leap indicator, version, mode. Three bits. Client will pick mode 3 for client.
    uint8_t stratum;        // Stratum level
    uint8_t poll;           // Polling interval
    uint8_t precision;      // Precision of clock
    uint32_t rootDelay;     // Root delay
    uint32_t rootDispersion;// Root dispersion
    uint32_t refId;         // Reference ID
    uint32_t refTm_s;       // Reference timestamp (seconds)
    uint32_t refTm_f;       // Reference timestamp (fraction)
    uint32_t origTm_s;      // Originate timestamp (seconds)
    uint32_t origTm_f;      // Originate timestamp (fraction)
    uint32_t rxTm_s;        // Receive timestamp (seconds)
    uint32_t rxTm_f;        // Receive timestamp (fraction)
    uint32_t txTm_s;        // Transmit timestamp (seconds)
    uint32_t txTm_f;        // Transmit timestamp (fraction)
} ntp_packet;

void print_ntp_time(ntp_packet *packet);
// void serialize_ntp_packet(ntp_packet *packet, uint8_t *buffer);
void juntate_sntp_packet(ntp_packet *packet, char *buffer);

#endif
