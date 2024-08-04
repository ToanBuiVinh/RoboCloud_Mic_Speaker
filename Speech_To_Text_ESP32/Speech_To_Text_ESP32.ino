#include "Audio.h"
#include "CloudSpeechClient.h"
#include <base64.h>
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\r\nRecord start!\r\n");
  Audio* audio = new Audio(ICS43434);
  //Audio* audio = new Audio(M5STACKFIRE);
  audio->Record();
  
  Serial.print("Recording Completed. Now Processing...");
  CloudSpeechClient* cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
  cloudSpeechClient->Transcribe(audio);
  delete cloudSpeechClient;
  
  String enc = base64::encode(audio->paddedHeader, sizeof(audio->paddedHeader));
  enc.replace("\n", "");  // delete last "\n"
  char** wavData = audio->wavData;
  for (int j = 0; j < audio->wavDataSize / audio->dividedWavDataSize; ++j) {
    enc += base64::encode((byte*)wavData[j], audio->dividedWavDataSize);
    enc.replace("\n", "");// delete last "\n"
  }
  Serial.println("Data: ");
  Serial.print(enc);
  delete audio;
}

void loop() {
}
