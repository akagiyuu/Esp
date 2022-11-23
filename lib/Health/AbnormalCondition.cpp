#include "AbnormalCondition.h"

uint32 AbnormalCondition::detect(int32_t heart_rate, int32_t spo2)
{
    uint32 conditions = 0;
    if(heart_rate < 20 || heart_rate > 100)
        conditions |= UnsualHeartRate;
    if(spo2 < 20 || spo2 > 100)
        conditions |= UnsualSPO2;

    return conditions;
}