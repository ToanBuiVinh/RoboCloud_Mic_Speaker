#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

void setup()
{
  Serial.begin(115200);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin("3Cham", "12345678");

  while (WiFi.status() != WL_CONNECTED)
    delay(1500);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(125);
}
int i = 0;
void loop()
{
  if( i == 0){
    //audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Olsen-Banden.mp3"); 
    audio.connecttospeech("Xin chào hôm nay bạn thế nào", "vi");
    i = 1;
  }

  audio.loop(); 
}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}
