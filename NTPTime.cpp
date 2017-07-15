//
// Created by vitaliy on 15.07.17.
//

#include "NTPTime.h"

// send an NTP request to the time server at the given address
unsigned long NtpTime::sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

void NtpTime::getNtpTime() {

    unsigned int localPort = 2390;      // local port to listen for UDP packets

    udp.begin(localPort);
    
    //get a random server from the pool
    WiFi.hostByName(ntpServerName, timeServerIP);

    sendNTPpacket(timeServerIP); // send an NTP packet to a time server
    // wait to see if a reply is available
    delay(1000);

    cb = udp.parsePacket();
    if (cb) {
        // We've received a packet, read the data from it
        udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

        //the timestamp starts at byte 40 of the received packet and is four bytes,
        // or two words, long. First, esxtract the two words:

        unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
        unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
        // combine the four bytes (two words) into a long integer
        // this is NTP time (seconds since Jan 1 1900):
        secsSince1900 = highWord << 16 | lowWord;
        // subtract seventy years:
        epoch = secsSince1900 - seventyYears;
        utc_hour = (epoch  % 86400L) / 3600;
        utc_minute = (epoch  % 3600) / 60;
        utc_seconds = (epoch % 60);

        printDebugData();
    }
}

void NtpTime::printDebugData() {
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
  
    if (!cb) {
        Serial.println("no packet yet");
    }
    else {
        Serial.print("packet received, length=");
        Serial.println(cb);

        Serial.print("Seconds since Jan 1 1900 = " );
        Serial.println(secsSince1900);

        // now convert NTP time into everyday time:
        Serial.print("Unix time = ");

        // print Unix time:
        Serial.println(epoch);


        // print the hour, minute and second:
        Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)

        Serial.print(utc_hour); // print the hour (86400 equals secs per day)
        Serial.print(':');
        if ( utc_minute < 10 ) {
            // In the first 10 minutes of each hour, we'll want a leading '0'
            Serial.print('0');
        }
        Serial.print(utc_minute); // print the minute (3600 equals secs per minute)
        Serial.print(':');
        if ( utc_seconds < 10 ) {
            // In the first 10 seconds of each minute, we'll want a leading '0'
            Serial.print('0');
        }
        Serial.println(utc_seconds); // print the second
    }
}

unsigned long NtpTime::getUtcTime() {
    getNtpTime();
    return epoch;
}

String NtpTime::formatDigit(unsigned long dig) {
    String str = "";
    if ( dig < 10 ) {
        // In the first 10 minutes of each hour, we'll want a leading '0'
        str += "0";
    }
    str += dig;
    return str;
}

String NtpTime::getUtcTimeForated() {

    getNtpTime();
  
    String strTime = "";

    strTime = formatDigit(utc_hour)+":"+formatDigit(utc_minute)+":"+formatDigit(utc_seconds);

    return strTime;
}
