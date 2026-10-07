#include "fault_manager.h"
#include <stdint.h>

#define RECOVERY_SUCCESS_COUNT 2U

// Main writes the state; TIM3 reads it for the FND.
static volatile FaultState m_sensorState = FIRST_CHECK;
static uint8_t m_recoveryCount = 0U;

void FaultManagerInit(void)
{
    m_recoveryCount = 0U;
    m_sensorState = FIRST_CHECK;
}

void FaultReport(bool readSucceeded)
{
    if (!readSucceeded)
    {
        m_recoveryCount = 0U;

        if (m_sensorState == NORMAL)
        {
            m_sensorState = RECHECK;
        }
        else
        {
            // FIRST_CHECK or RECHECK fails; FAULT stays FAULT.
            m_sensorState = FAULT;
        }

        return;
    }

    if (m_sensorState == FAULT)
    {
        ++m_recoveryCount;

        if (m_recoveryCount < RECOVERY_SUCCESS_COUNT)
        {
            return;
        }
    }

    m_recoveryCount = 0U;
    m_sensorState = NORMAL;
}

FaultState GetFaultState(void)
{
    return m_sensorState;
}
