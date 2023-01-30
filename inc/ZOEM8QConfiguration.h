//
// Created by Daniel on 01/12/2022.
//

#ifndef CODAL_ZOEM8QCONFIGURATION_H
#define CODAL_ZOEM8QCONFIGURATION_H

#include "CodalCompat.h"

namespace codal
{

class ZOEM8QConfiguration
{
public:
    uint8_t time_pulse_index = 0;
    uint8_t version = 0;
    uint8_t _reserved1[2] = {0, 0};
    int16_t antenna_cable_delay = 0;
    int16_t rf_group_delay = 0;
    uint32_t pulse_freq_unlocked = 0;
    uint32_t pulse_freq_locked = 0;
    uint32_t pulse_length_unlocked = 0;
    uint32_t pulse_length_locked = 0;
    int32_t user_delay = 0;

    bool active = true;
    bool lock_to_gps_req = true;
    bool lock_to_gnss_freq = true;
    bool locked_other_setting = true;
    bool is_frequency = false;
    bool is_length = false;
    bool align_to_tow = false;
    bool polarity = true;
    bool timegrid = true;

    uint8_t* asMessage();
};

} // namespace codal

#endif // CODAL_ZOEM8QCONFIGURATION_H
