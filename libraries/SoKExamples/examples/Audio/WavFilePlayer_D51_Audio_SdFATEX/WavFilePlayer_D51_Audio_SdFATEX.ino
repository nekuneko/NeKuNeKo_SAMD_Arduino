// Simple WAV file player example for SD or QSPI flash storage
//
// Three types of output may be used, by configuring the code below.
//
//   1: Digital I2S - Normally used with the audio shield:
//         http://www.pjrc.com/store/teensy3_audio.html
//
//   2: Digital S/PDIF - Connect pin 22 to a S/PDIF transmitter
//         https://www.oshpark.com/shared_projects/KcDBKHta
//
//   3: Analog DAC - Connect the DAC pin to an amplified speaker
//         http://www.pjrc.com/teensy/gui/?info=AudioOutputAnalog
//
// To configure the output type, first uncomment one of the three
// output objects.  If not using the audio shield, comment out
// the sgtl5000_1 lines in setup(), so it does not wait forever
// trying to configure the SGTL5000 codec chip.
//
// The SD card may connect to different pins, depending on the
// hardware you are using.  Uncomment or configure the SD card
// pins to match your hardware.
//
// Data files to put on your SD card can be downloaded here:
//   http://www.pjrc.com/teensy/td_libs_AudioDataFiles.html
//
// This example code is in the public domain.

#include <Audio.h>
#include <play_fs_wav.h>

AudioPlayFSWav           playWav1;
// Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
AudioOutputI2S           audioOutput;
//AudioOutputSPDIF       audioOutput;
//AudioOutputAnalogStereo  audioOutput;    // Dual DACs
AudioConnection          patchCord1(playWav1, 0, audioOutput, 1);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 0);


//Adafruit_SPIFlash flash(&flashTransport);
SdFatEX SD;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);
  Serial.println("Wave player demo");
  delay(100);
  
  for (int i=49; i<=51; ++i)
  Serial.println("Port: "  + String(g_APinDescription[i].ulPort) + 
                 ", Pin: " + String(g_APinDescription[i].ulPin) +
                 ", Type: " + String(g_APinDescription[i].ulPinType));
  //Serial.println(SPI_COJONES);
  
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  if (!(SD.begin())) {
    Serial.println("Unable to access the SD card");
    while(true);
  } else {
    Serial.println("SD card OK!");
  }


}

void playFile(const char *filename)
{
  Serial.print("Playing file: "); Serial.println(filename);

  File f = SD.open(filename);
  
  // Start playing the file.  This sketch continues to
  // run while the file plays.
  if (!playWav1.play(f)) { 
    Serial.println("Failed to play");
    return;
  }

  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
    Serial.print(".");
    delay(100);
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // sgtl5000_1.volume(vol);
  }
  Serial.println("End Playing");
}


void loop() {


        playFile("utada.WAV");
    delay(500);
        playFile("deponia.WAV");
    delay(500);
    /*
  playFile("SDTEST1.WAV");
  delay(500);
  playFile("SDTEST2.WAV");
  delay(500);
  playFile("SDTEST3.WAV");
  delay(500);
  playFile("SDTEST4.WAV");
  delay(1500);*/
}
