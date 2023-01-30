//
// Created by Daniel on 01/12/2022.
//

#include <ManagedBuffer.h>
#include "ZOEM8QConfiguration.h"

namespace codal
{
uint8_t *ZOEM8QConfiguration::asMessage()
{
    ManagedBuffer *buffer = new ManagedBuffer(38);

    buffer->setByte(0, 0xb5);
    buffer->setByte(1, 0x62);
    buffer->setByte(2, 0x06);
    buffer->setByte(3, 0x31);
    buffer->setByte(4, 0x32);

    buffer->writeBytes(5 + 0, &time_pulse_index, 1);
    buffer->writeBytes(5 + 1, &version, 1);
    buffer->writeBytes(5 + 2, _reserved1, 2);
    buffer->writeBytes(5 + 4, (uint8_t *)&antenna_cable_delay, 2);
    buffer->writeBytes(5 + 6, (uint8_t *)&rf_group_delay, 4);
    buffer->writeBytes(5 + 8, (uint8_t *)&pulse_freq_unlocked, 4);
    buffer->writeBytes(5 + 12, (uint8_t *)&pulse_freq_locked, 4);
    buffer->writeBytes(5 + 16, (uint8_t *)&pulse_length_unlocked, 4);
    buffer->writeBytes(5 + 20, (uint8_t *)&pulse_length_locked, 4);
    buffer->writeBytes(5 + 24, (uint8_t *)&user_delay, 4);

    uint32_t userConfig = 0;

    userConfig |= active;
    userConfig |= lock_to_gps_req << 1;
    userConfig |= locked_other_setting << 2;
    userConfig |= is_frequency << 3;
    userConfig |= is_length << 4;
    userConfig |= align_to_tow << 5;
    userConfig |= polarity << 6;
    userConfig |= timegrid << 7;

    buffer->writeBytes(5 + 28, (uint8_t *)&userConfig, 4);

    uint8_t ck_a = 0;
    uint8_t ck_b = 0;

    for (uint8_t i = 2; i < 37; i++) {
        ck_a += buffer->getByte(i);
        ck_b += ck_a;
    }

    buffer->setByte(5 + 32, ck_a);
    buffer->setByte(5 + 33, ck_b);
}
} // namespace codal