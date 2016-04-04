#include <Balloonduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

Balloonduino module;
TinyGPSPlus gps;
SoftwareSerial ss(4, 5);

double releaseWindow[] = { 0, 90, 0, 180, 36575, 1000 };    // [ min latitude, max latitude, min longitude, max longitude, drop altitude, parachute altitude ] in meters
bool released = false;

void setup()
{
    module.begin();
    ss.begin(9600);
}

void loop()
{
    // update GPS data
    while (ss.available() > 0)
    {
        gps.encode(ss.read());
    }

    if (!released)
    {
        // read GPS data
        if (gps.location.lat() > releaseWindow[0])
        {
            if (gps.location.lat() < releaseWindow[1])
            {
                if (gps.location.lng() > releaseWindow[2])
                {
                    if (gps.location.lng() < releaseWindow[3])
                    {
                        if (gps.altitude > releaseWindow[4])
                        {
                            if (module.getAltitude() > releaseWindow[4])
                            {
                                if (requestRelease())
                                {
                                    releaseCutdown();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        // we are in freefall
        if (gps.altitude < releaseWindow[5])
        {
            if (module.getAltitude() < releaseWindow[5])
            {
                releaseParachute();
            }
        }
    }
}

// use 900 radios to request Supersonic drop
bool requestRelease()
{

}

// drop Supersonic
void releaseCutdown()
{
    released = true;
}

void releaseParachute()
{

}

// Log data to internal SD card, send to Command via Xbee, and send to ground via 900
void log(String value)
{

}
