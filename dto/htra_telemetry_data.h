#ifndef HTRA_TELEMETRY_DATA_H
#define HTRA_TELEMETRY_DATA_H

#include <stdint.h>

struct HtraTelemetryData {
    bool isOnline;
    double centerFreq;
    double level;
    double span;
    double rbw;
    double vbw;
    uint8_t pickSearchType;
    double pickSearchCenter;
    double pickSearchWidth;
    double pick;
};

#endif // HTRA_TELEMETRY_DATA_H
