#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

typedef struct {
    unsigned int sensor;
    unsigned int mode;
    unsigned int alarm;
    unsigned int channel;
} Telemetry;

int read_telemetry(Telemetry *data);
uint16_t pack_telemetry(Telemetry data);
Telemetry unpack_telemetry(uint16_t packet);
int same_telemetry(Telemetry a, Telemetry b);

int main(void)
{
    Telemetry input;
    printf("Enter sensor(0..255) mode(0..15) alarm(0..1) channel(0..7): ");
    if (!read_telemetry(&input)) {
        fputs("Error: expected four integers in ranges 0..255 0..15 0..1 0..7.\n",
              stderr);
        return 1;
    }
    printf("Original: sensor=%u mode=%u alarm=%u channel=%u\n",
           input.sensor, input.mode, input.alarm, input.channel);
    uint16_t packet = pack_telemetry(input);
    printf("Packet HEX: 0x%04" PRIX16 "\n", packet);
    Telemetry restored = unpack_telemetry(packet);
    printf("Restored: sensor=%u mode=%u alarm=%u channel=%u\n",
           restored.sensor, restored.mode, restored.alarm, restored.channel);
    int ok = same_telemetry(input, restored);
    printf("Round-trip: %s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}

int read_telemetry(Telemetry *data)
{
    char line[128];
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    if (strchr(line, '\n') == NULL && !feof(stdin)) return 0;
    const long limits[4] = {255, 15, 1, 7};
    unsigned int values[4];
    char *cursor = line;
    for (int i = 0; i < 4; ++i) {
        char *end;
        errno = 0;
        long value = strtol(cursor, &end, 10);
        if (end == cursor || errno == ERANGE || value < 0 || value > limits[i]) {
            return 0;
        }
        if (*end != '\0' && !isspace((unsigned char)*end)) return 0;
        values[i] = (unsigned int)value;
        cursor = end;
    }
    while (isspace((unsigned char)*cursor)) ++cursor;
    if (*cursor != '\0') return 0;  // Зайвих значень чи символів бути не повинно.
    data->sensor = values[0];
    data->mode = values[1];
    data->alarm = values[2];
    data->channel = values[3];
    return 1;
}

uint16_t pack_telemetry(Telemetry data)
{
    // Приймаємо перевірені значення. Маски задають ширину кожного поля.
    // Зсуви виконуємо у uint32_t; готове 16-бітне слово повертаємо як uint16_t.
    uint32_t packet = ((uint32_t)data.sensor & UINT32_C(0xFF))
        | (((uint32_t)data.mode & UINT32_C(0x0F)) << 8)
        | (((uint32_t)data.alarm & UINT32_C(0x01)) << 12)
        | (((uint32_t)data.channel & UINT32_C(0x07)) << 13);
    return (uint16_t)packet;
}

Telemetry unpack_telemetry(uint16_t packet)
{
    Telemetry data;
    // Переносимо потрібне поле вправо та відкидаємо решту бітів маскою.
    data.sensor = (unsigned int)((uint32_t)packet & UINT32_C(0xFF));
    data.mode = (unsigned int)(((uint32_t)packet >> 8) & UINT32_C(0x0F));
    data.alarm = (unsigned int)(((uint32_t)packet >> 12) & UINT32_C(0x01));
    data.channel = (unsigned int)(((uint32_t)packet >> 13) & UINT32_C(0x07));
    return data;
}

int same_telemetry(Telemetry a, Telemetry b)
{
    // Порівнюємо значення полів, а не байти структури з можливими відступами.
    return a.sensor == b.sensor && a.mode == b.mode
        && a.alarm == b.alarm && a.channel == b.channel;
}
