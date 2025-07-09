#include "SimulatorComms.h"
#include <stdio.h>
#include <string.h>

void sendCommand(const char* command) {
    printf("%s\n", command);
    fflush(stdout);
}

char* receiveResponse(void) {
    static char response[64];
    fgets(response, sizeof(response), stdin);
    size_t len = strlen(response);
    if (len > 0 && response[len - 1] == '\n') {
        response[len - 1] = '\0';
    }
    return response;
}
