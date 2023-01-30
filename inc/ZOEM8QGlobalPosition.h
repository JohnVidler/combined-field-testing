#pragma once

#include <I2C.h>
#include "NMEAParser.h"
#include "ZOEM8QConfiguration.h"

#define ZOEM8Q_I2C_REGISTER 0x42

namespace codal
{

/**
 * Global positioning driver for the U-BLOX ZOE-M8Q sensor
 */
class ZOEM8QGlobalPosition : public NMEAParser
{
public:
    /**
     * Constructor for the driver
     * @param _i2c the I2C instance to read data from
     */
    ZOEM8QGlobalPosition(I2C &_i2c, ZOEM8QConfiguration &config);

    void autoDetect() override;

private:
    I2C *_i2c;
    ZOEM8QConfiguration *_config;

    void periodicCallback() override;
};

} // namespace codal