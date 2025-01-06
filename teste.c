#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <arpa/inet.h> // Para htonl e ntohl

typedef struct
{
    uint8_t li_vn_mode;     // Leap Indicator, Version, Mode
    uint8_t stratum;        // Stratum
    uint8_t poll;           // Poll Interval
    uint8_t precision;      // Precision
    uint32_t rootDelay;     // Total round-trip delay time
    uint32_t rootDispersion;// Max error allowed
    uint32_t refId;         // Reference clock identifier
    uint32_t refTm_s;       // Reference timestamp seconds
    uint32_t refTm_f;       // Reference timestamp fraction
    uint32_t origTm_s;      // Originate timestamp seconds
    uint32_t origTm_f;      // Originate timestamp fraction
    uint32_t rxTm_s;        // Received timestamp seconds
    uint32_t rxTm_f;        // Received timestamp fraction
    uint32_t txTm_s;        // Transmit timestamp seconds
    uint32_t txTm_f;        // Transmit timestamp fraction
} ntp_packet;

int main() {
    ntp_packet packet;

    // Obter o timestamp Unix atual
    time_t unix_time = time(NULL);

    // Converter para formato NTP
    uint32_t ntp_time = unix_time + 2208988800U;

    // Atribuir o valor ao campo txTm_s (em formato big-endian)
    packet.txTm_s = htonl(ntp_time);

    // Simular o parsing da resposta
    uint32_t txTm_s_host = ntohl(packet.txTm_s); // Converter de big-endian para host-endian
    time_t parsed_time = txTm_s_host - 2208988800U; // Converter para Unix Time

    // Exibir a data/hora formatada
    printf("Simulação de parsing:\n");
    printf("Timestamp NTP (big-endian): %u\n", packet.txTm_s);
    printf("Timestamp Unix: %ld\n", parsed_time);
    printf("Data/hora: %s", ctime(&parsed_time));

    return 0;
}
