//
// Created by vitaliy on 15.07.17.
//

#ifndef NTPTIME_H
#define NTPTIME_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message


class NtpTime {
private:
    /* Don't hardwire the IP address or we won't get the benefits of the pool.
    *  Lookup the IP address for the host name instead */
    //IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
    IPAddress timeServerIP; // time.nist.gov NTP server address
    const char* ntpServerName = "time.nist.gov";

    byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
    // A UDP instance to let us send and receive packets over UDP

    WiFiUDP udp;

    unsigned long secsSince1900;

    const unsigned long seventyYears = 2208988800UL;

    int cb;

    unsigned long epoch;
    unsigned long utc_hour;
    unsigned long utc_minute;
    unsigned long utc_seconds;

    void getNtpTime();

    void printDebugData();

    String formatDigit(unsigned long dig);

    unsigned long sendNTPpacket(IPAddress& address);

public:
    String getUtcTimeForated();
    unsigned long getUtcTime();

};

#endif //NTPTIME_H
