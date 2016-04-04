#include <Balloonduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

Balloonduino module;
TinyGPSPlus gps;
SoftwareSerial ss;

double releaseWindow[] = { 36575, 0, 90, 0, 180 };    // [altitude, min latitude, max latitude, min longitude, max longitude] in meters

void setup()
{
    module.begin();
}

void loop()
{
    if (module.getAltitude() > releaseWindow[0])
    {
        if (gps.altitude > releaseWindow[0])
        {
            if (gps.location.lat() > releaseWindow[1])
            {
                if (gps.location.lat() < releaseWindow[2])
                {
                    if (gps.location.lng() > releaseWindow[3])
                    {
                        if (gps.location.lng() < releaseWindow[4])
                        {

                        }
                    }
                }
            }
        }
    }
}

void releaseCutdown()
{

}

void releaseParachute()
{

}
