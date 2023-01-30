#include <CodalDmesg.h>
#include <NMEAParser.h>

#define DEVICE_ID_GPS 55
#define GPS_EVT_DATA_UPDATE 1

namespace codal
{
NMEAParser::NMEAParser() : CodalComponent(), GlobalPosition()
{
    status |= DEVICE_COMPONENT_STATUS_SYSTEM_TICK;
    _buffer = ManagedBuffer(255, BufferInitialize::Zero);
}

void NMEAParser::periodicCallback()
{
    // panic!
}

void NMEAParser::autoDetect()
{

}

void NMEAParser::parse() {
    if (strncmp((char*) _buffer.getBytes(), "$GNGGA", 5) == 0) {
        _parseGNGGA();
    }

    _buffer.fill(0);
    _bufferWritePos = 0;

    Event(DEVICE_ID_GPS, GPS_EVT_DATA_UPDATE);
}

void NMEAParser::_parseGNGGA()
{
    char* message = (char*) _buffer.getBytes();

    strtok(message, ",");

    char* utc = strtok(nullptr, ",");
    char* lat = strtok(nullptr, ",");
    char* lat_dir = strtok(nullptr, ",");
    char* lon = strtok(nullptr, ",");
    char* lon_dir = strtok(nullptr, ",");
    char* quality = strtok(nullptr, ",");
    char* sats = strtok(nullptr, ",");
    char* hdop = strtok(nullptr, ",");
    char* alt = strtok(nullptr, ",");
    char* a_units = strtok(nullptr, ",");
    char* undulation = strtok(nullptr, ",");
    char* u_units = strtok(nullptr, ",");
    char* age = strtok(nullptr, ",");
    char* station = strtok(nullptr, ",");

    // todo: process/discard other fields

    float latRaw = strtof(lat, nullptr);
    latitude = (floor(latRaw / 100) + fmod(latRaw, 100) / 60) * (lat_dir[0] == 'S' ? -1 : 1);

    float lonRaw = strtof(lon, nullptr);
    longitude = (floor(lonRaw / 100) + fmod(lonRaw, 100) / 60) * (lon_dir[0] == 'W' ? -1 : 1);

    altitude = strtof(alt, nullptr);
}
} // namespace codal