#include <Audio.h>
#include <play_fs_wav.h>

const char fileName[] = "sound.WAV";

//write wav
unsigned long ChunkSize = 0L;
unsigned long Subchunk1Size = 16;
unsigned int AudioFormat = 1;
unsigned int numChannels = 1;
unsigned long sampleRate = 44100;
unsigned int bitsPerSample = 16;
unsigned long byteRate = sampleRate*numChannels*(bitsPerSample/8);// samplerate x channels x (bitspersample / 8)
unsigned int blockAlign = numChannels*bitsPerSample/8;
unsigned long Subchunk2Size = 0L;
unsigned long recByteSaved = 0L;
unsigned long NumSamples = 0L;
byte byte1, byte2, byte3, byte4;

AudioPlayFSWav           audioSD;
AudioOutputI2S           audioOutput;
AudioInputI2S            audioInput;
AudioRecordQueue         queue1;

//recod from mic
// AudioConnection          patchCord1(audioInput, 0, queue1, 0);  // RIGHT CHANNEL - 3.3V
AudioConnection          patchCord1(audioInput, 1, queue1, 0);  // LEFT CHANNEL - GND
AudioConnection          patchCord2(audioSD, 0, audioOutput, 0);
AudioConnection          patchCord3(audioSD, 0, audioOutput, 1);

int mode = 0;  // 0=stopped, 1=recording, 2=playing
SdFatEX SD;
File frec;
//elapsedMillis  msecs;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  AudioMemory(60);
  
  while (!(SD.begin())) {
    // stop here, but print a message repetitively
    Serial.println("Unable to access the SD card");
    delay(500);
  }

  Serial.println("Teensy record WAV");
  Serial.println("1 - Record Button Press");
  Serial.println("2 - Stop Button Press");
  Serial.println("3 - Play Button Press");
}


void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    byte incomingByte = Serial.read();
    // Respond to button presses
    if ( incomingByte == '1' ) {
      Serial.println("Record Button Press");
      if (mode == 2) stopPlaying();
      if (mode == 0) startRecording();
    }
    if ( incomingByte == '2' ) {
      Serial.println("Stop Button Press");
      if (mode == 1) stopRecording();
      if (mode == 2) stopPlaying();
    }
    if ( incomingByte == '3' ) {
      Serial.println("Play Button Press");
      if (mode == 1) stopRecording();
      if (mode == 0) startPlaying();   
    }
  }
  if (mode == 1) {
    continueRecording();
  }

  if (mode == 2 && !audioSD.isPlaying())
  {
    stopPlaying();
  }
}

void startRecording() {
  Serial.println("startRecording");
  if (SD.exists(fileName)) {
    SD.remove(fileName);
  }
  frec = SD.open(fileName, FILE_WRITE);
  if (frec) {
    queue1.begin();
    mode = 1;
    recByteSaved = 0L;
  }
}

void continueRecording() {
  
  if (queue1.available() >= 2) {
    byte buffer[512];
    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(buffer + 256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    // write all 512 bytes to the SD card
    frec.write(buffer, 512);
    recByteSaved += 512;
//    elapsedMicros usec = 0;
//    Serial.print("SD write, us=");
//    Serial.println(usec);
  }
}

void stopRecording() {
  Serial.println("stopRecording");
  queue1.end();
  if (mode == 1) {
    while (queue1.available() > 0) {
      frec.write((byte*)queue1.readBuffer(), 256);
      queue1.freeBuffer();
      recByteSaved += 256;
    }
    writeOutHeader();
    frec.close();
  }
  mode = 0;
}


void startPlaying() {
  Serial.println("startPlaying");
  frec = SD.open(fileName);
  audioSD.play(frec); // change: fileName
  mode = 2;
  delay(1000);
}


void stopPlaying() {
  Serial.println("stopPlaying");
  if (mode == 2) audioSD.stop();
  mode = 0;
}
void writeOutHeader() { // update WAV header with final filesize/datasize

//  NumSamples = (recByteSaved*8)/bitsPerSample/numChannels;
//  Subchunk2Size = NumSamples*numChannels*bitsPerSample/8; // number of samples x number of channels x number of bytes per sample
  Subchunk2Size = recByteSaved;
  ChunkSize = Subchunk2Size + 36;
  frec.seek(0);
  frec.write("RIFF");
  byte1 = ChunkSize & 0xff;
  byte2 = (ChunkSize >> 8) & 0xff;
  byte3 = (ChunkSize >> 16) & 0xff;
  byte4 = (ChunkSize >> 24) & 0xff;  
  frec.write(byte1);  frec.write(byte2);  frec.write(byte3);  frec.write(byte4);
  frec.write("WAVE");
  frec.write("fmt ");
  byte1 = Subchunk1Size & 0xff;
  byte2 = (Subchunk1Size >> 8) & 0xff;
  byte3 = (Subchunk1Size >> 16) & 0xff;
  byte4 = (Subchunk1Size >> 24) & 0xff;  
  frec.write(byte1);  frec.write(byte2);  frec.write(byte3);  frec.write(byte4);
  byte1 = AudioFormat & 0xff;
  byte2 = (AudioFormat >> 8) & 0xff;
  frec.write(byte1);  frec.write(byte2); 
  byte1 = numChannels & 0xff;
  byte2 = (numChannels >> 8) & 0xff;
  frec.write(byte1);  frec.write(byte2); 
  byte1 = sampleRate & 0xff;
  byte2 = (sampleRate >> 8) & 0xff;
  byte3 = (sampleRate >> 16) & 0xff;
  byte4 = (sampleRate >> 24) & 0xff;  
  frec.write(byte1);  frec.write(byte2);  frec.write(byte3);  frec.write(byte4);
  byte1 = byteRate & 0xff;
  byte2 = (byteRate >> 8) & 0xff;
  byte3 = (byteRate >> 16) & 0xff;
  byte4 = (byteRate >> 24) & 0xff;  
  frec.write(byte1);  frec.write(byte2);  frec.write(byte3);  frec.write(byte4);
  byte1 = blockAlign & 0xff;
  byte2 = (blockAlign >> 8) & 0xff;
  frec.write(byte1);  frec.write(byte2); 
  byte1 = bitsPerSample & 0xff;
  byte2 = (bitsPerSample >> 8) & 0xff;
  frec.write(byte1);  frec.write(byte2); 
  frec.write("data");
  byte1 = Subchunk2Size & 0xff;
  byte2 = (Subchunk2Size >> 8) & 0xff;
  byte3 = (Subchunk2Size >> 16) & 0xff;
  byte4 = (Subchunk2Size >> 24) & 0xff;  
  frec.write(byte1);  frec.write(byte2);  frec.write(byte3);  frec.write(byte4);
  frec.close();
  Serial.println("header written"); 
  Serial.print("Subchunk2: "); 
  Serial.println(Subchunk2Size); 
}
