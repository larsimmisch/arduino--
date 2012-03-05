#include "arduino++.h"
#include "rf12star.h"
#include "serial.h"

class SerialObserver
    {
public:
    static void cantSend() { Serial.write('.'); }
    static void gotPacket(byte id, byte type, byte length, const byte *data)
	{
	Serial.write("Got packet, id: ");
	Serial.writeDecimal(id);
	Serial.write(" type: ");
	Serial.writeDecimal(type);
	Serial.write(" data: ");
	Serial.writeHex(data, length);
	Serial.write("\r\n");
	}
    static void idSent(byte id, byte length, const byte *mac)
	{
	Serial.write("ID sent, id: ");
	Serial.writeDecimal(id);
	Serial.write(" mac: ");
	Serial.writeHex(mac, length);
	Serial.write("\r\n");
	}
    static void sentPacket(byte id, byte type, byte length, const byte *data)
	{
	Serial.write("Sent packet, id: ");
	Serial.writeDecimal(id);
	Serial.write(" type: ");
	Serial.writeDecimal(type);
	Serial.write(" data: ");
	Serial.writeHex(data, length);
	Serial.write("\r\n");
	}
    };

StarMaster<RF12Star, SerialObserver> master;

int main()
    {
    Arduino::init();
    Serial.begin(57600);
    master.init();

    Serial.write("Start\r\n");

    for ( ; ; )
	master.poll();
    }
