#include <Balloonduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

Balloonduino module;
TinyGPSPlus gps;
SoftwareSerial ss(4, 5);

double minLatitude = 0;
double maxLatitude = 90;
double minLongitude = 0;
double maxLongitude = 180;
double dropAltitude = 36575;
double parachuteAltitude = 1000;
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
        if (gps.location.lat() > minLatitude)
        {
            if (gps.location.lat() < maxLatitude)
            {
                if (gps.location.lng() > minLongitude)
                {
                    if (gps.location.lng() < maxLongitude)
                    {
                        if (gps.altitude > dropAltitude)
                        {
                            if (module.getAltitude() > dropAltitude)
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
        if (gps.altitude < parachuteAltitude)
        {
            if (module.getAltitude() < parachuteAltitude)
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
