#ifndef _AUDIO_H
#define _AUDIO_H

#include <Arduino.h>
#include "I2S_Mic.h"

// 16bit, monoral, 16000Hz,  linear PCM
class Audio_Mic {
  I2S* i2s;
  static const int headerSize = 44;
  static const int i2sBufferSize = 12000;
  void CreateWavHeader(byte* header, int waveDataSize);

public:
  char i2sBuffer[i2sBufferSize];
  static const int wavDataSize = 90000;                   // It must be multiple of dividedWavDataSize. Recording time is about 1.9 second.
  static const int dividedWavDataSize = i2sBufferSize/4;
  char** wavData;                                         // It's divided. Because large continuous memory area can't be allocated in esp32.
  byte paddedHeader[headerSize + 4] = {0};                // The size must be multiple of 3 for Base64 encoding. Additional byte size must be even because wave data is 16bit.

  Audio_Mic(MicType micType);
  ~Audio_Mic();
  void Record();
};

#endif // _AUDIO_H
