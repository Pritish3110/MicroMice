#ifndef SIMMCOMM_H
#define SIMMCOMM_H

#ifdef __cplusplus
extern "C" {
#endif

void sendCommand(const char* command);
char* receiveResponse(void);

#ifdef __cplusplus
}
#endif

#endif
