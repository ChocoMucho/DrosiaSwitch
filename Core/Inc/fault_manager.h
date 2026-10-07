#ifndef FAULT_MANAGER_H_
#define FAULT_MANAGER_H_

#include <stdbool.h>

typedef enum
{
    FIRST_CHECK,
    NORMAL,
    RECHECK,
    FAULT
} FaultState;

void FaultManagerInit(void);
void FaultReport(bool readSucceeded);
FaultState GetFaultState(void);

#endif
