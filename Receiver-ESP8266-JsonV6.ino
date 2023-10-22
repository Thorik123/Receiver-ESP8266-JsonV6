#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define RX 12
#define TX 14

SoftwareSerial node(RX, TX);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        continue;
    node.begin(9600);
}

void loop()
{
    if (node.available())
    {
        StaticJsonDocument<1024> doc;
        DeserializationError err = deserializeJson(doc, node);

        if (err == DeserializationError::Ok)
        {
            Serial.print("data1 = ");
            Serial.println(doc["data1"].as<String>());
            Serial.print("data2 = ");
            Serial.println(doc["data2"].as<float>());
            Serial.print("data3 = ");
            Serial.println(doc["data3"].as<int>());
        }

        else
        {
            Serial.print("deserializeJson() returned ");
            Serial.println(err.c_str());

            while (node.available() > 0)
                node.read();
        }
    }
}