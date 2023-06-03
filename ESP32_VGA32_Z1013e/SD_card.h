/********************************************************************************************************************
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 ********************************************************************************************************************/

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "SPIFFS.h"

typedef struct
{
  boolean  valid = true;
  String   Filesystem = "";
  uint16_t begin;
  uint16_t end;
  uint16_t start;
  char name[16];
} head ;

#define SCK 14
#define MISO 2
#define MOSI 12
#define CS 13

SPIClass spi = SPIClass(VSPI);


void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


//void createDir(fs::FS &fs, const char * path){
//    Serial.printf("Creating Dir: %s\n", path);
//    if(fs.mkdir(path)){
//        Serial.println("Dir created");
//    } else {
//        Serial.println("mkdir failed");
//    }
//}


//void removeDir(fs::FS &fs, const char * path){
//    Serial.printf("Removing Dir: %s\n", path);
//    if(fs.rmdir(path)){
//        Serial.println("Dir removed");
//    } else {
//        Serial.println("rmdir failed");
//    }
//}



head readHeadSPIFF(const char * path)
{
    head Header;
    byte *Ziel = ptr[0];
    byte buffer[0x21]; 
    buffer[0x20] = 0;
    
    if(!SPIFFS.begin(true)){
      Serial.print("Failed to open head for reading: ");
      Serial.println(path);
      Header.valid = false;
      return Header;
    }

    File file = SPIFFS.open(path);
    Header.Filesystem="SPIFF";
 
    if(!file)
    {
        Serial.print("Failed to open head for reading: ");
        Serial.println(path);
        Header.valid = false;
        return Header;
    }

    // Serial.print("Read from file: ");
    for (uint8_t i=0; i<0x20; i++)
    {
      if (file.available()) 
          buffer[i] = file.read();
    }
//    Serial.print("Begin: ");
    Header.begin = buffer[1]*256+buffer[0];
//    if (Header.begin < 0x1000) Serial.print("0");
//    Serial.print(Header.begin, HEX);
    
//    Serial.print("   End: ");
    Header.end = buffer[3]*256+buffer[2];
//    if (Header.end < 0x1000); Serial.print("0");
//    Serial.print(Header.end, HEX);
    
//    Serial.print("   Start: ");
    Header.start = buffer[5]*256+buffer[4];
//    if (Header.start < 0x1000) Serial.print("0");
//    Serial.println(Header.start, HEX);

//    Serial.print("Name: ");
    for (uint8_t i=0; i<16; i++)
    {
//      Serial.print((char)buffer[0x10+i]);
      Header.name[i] = (char)buffer[0x10+i];
    }
//    Serial.println();

    file.close();
    SPIFFS.end();
    return Header;
}
 
void readSPIFF(const char * path)
{
    byte *Ziel = ptr[0];
    byte buffer[0x21]; 
    buffer[0x20] = 0;
 
    if(!SPIFFS.begin(true)){
      Serial.print("Failed to open head for reading: ");
      Serial.println(path);
      return;
    }

    File file = SPIFFS.open(path);
    
    if(!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    // Serial.print("Read from file: ");
    for (uint8_t i=0; i<0x20; i++)
    {
      if (file.available()) 
          buffer[i] = file.read();
    }
    Serial.print("Begin: ");
    Serial.print(buffer[1]*256+buffer[0], HEX);
    Serial.print("   End: ");
    Serial.print(buffer[3]*256+buffer[2], HEX);
    Serial.print("   Start: ");
    Serial.println(buffer[5]*256+buffer[4], HEX);
    Serial.print("Name: ");
    for (uint8_t i=0; i<16; i++)
    {
      Serial.print((char)buffer[0x10+i]);
    }
    Serial.println();
    
    uint16_t i = buffer[1] * 256 + buffer[0];
    while(file.available())
    {
      ram[0][i] = file.read();
      i++;
    }
    file.close();
    Serial.print("Bytes geladen: ");
    Serial.println(i-256, HEX);
    SPIFFS.end();
}


head readHead(fs::FS &fs, const char * path)
{
    head Header;
    byte *Ziel = ptr[0];
    byte buffer[0x21]; 
    buffer[0x20] = 0;
 
    spi.begin(SCK, MISO, MOSI, CS);
    if(!SD.begin(CS, spi, 80000000))
    {
      Serial.println("Card Mount Failed");
      Header.valid = false;
      return Header;
    }

    Serial.printf("Reading head: %s\n", path);

    File file = fs.open(path); 
    Header.Filesystem="SD";
    
    if(!file)
    {
        Serial.print("Failed to open head for reading: ");
        Serial.println(path);
        Header.valid = false;
        return Header;
    }

    // Serial.print("Read from file: ");
    for (uint8_t i=0; i<0x20; i++)
    {
      if (file.available()) 
          buffer[i] = file.read();
    }
//    Serial.print("Begin: ");
    Header.begin = buffer[1]*256+buffer[0];
//    if (Header.begin < 0x1000) Serial.print("0");
//    Serial.print(Header.begin, HEX);
    
//    Serial.print("   End: ");
    Header.end = buffer[3]*256+buffer[2];
//    if (Header.end < 0x1000); Serial.print("0");
//    Serial.print(Header.end, HEX);
    
//    Serial.print("   Start: ");
    Header.start = buffer[5]*256+buffer[4];
//    if (Header.start < 0x1000) Serial.print("0");
//    Serial.println(Header.start, HEX);

//    Serial.print("Name: ");
    for (uint8_t i=0; i<16; i++)
    {
//      Serial.print((char)buffer[0x10+i]);
      Header.name[i] = (char)buffer[0x10+i];
    }
//    Serial.println();

    file.close();
    SD.end();
    spi.end();
    return Header;
}


void readFile(fs::FS &fs, const char * path)
{
    byte *Ziel = ptr[0];
    byte buffer[0x21]; 
    buffer[0x20] = 0;
 
    spi.begin(SCK, MISO, MOSI, CS);
    if(!SD.begin(CS, spi, 80000000))
    {
      Serial.println("Card Mount Failed");
      return;
    }

    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path); 
    
    if(!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    // Serial.print("Read from file: ");
    for (uint8_t i=0; i<0x20; i++)
    {
      if (file.available()) 
          buffer[i] = file.read();
    }
    Serial.print("Begin: ");
    Serial.print(buffer[1]*256+buffer[0], HEX);
    Serial.print("   End: ");
    Serial.print(buffer[3]*256+buffer[2], HEX);
    Serial.print("   Start: ");
    Serial.println(buffer[5]*256+buffer[4], HEX);
    Serial.print("Name: ");
    for (uint8_t i=0; i<16; i++)
    {
      Serial.print((char)buffer[0x10+i]);
    }
    Serial.println();
    
    uint16_t i = buffer[1] * 256 + buffer[0];
    while(file.available())
    {
      ram[0][i] = file.read();
      i++;
    }
    file.close();
    Serial.print("Bytes geladen: ");
    Serial.println(i-256, HEX);
    SD.end();
    spi.end();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}

void SDend()
{
  spi.end();
}

void SDsetup()
{
    spi.begin(SCK, MISO, MOSI, CS);
    if(!SD.begin(CS, spi, 80000000))
    {
        Serial.println("Card Mount Failed");
        return;
    }

    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }
    Serial.println("-------------------------------");
    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

//    listDir(SD, "/", 0);
//    createDir(SD, "/mydir");
//    listDir(SD, "/Z1013", 0);
//    removeDir(SD, "/mydir");
//    listDir(SD, "/", 2);
//    writeFile(SD, "/hello.txt", "Hello ");
//    appendFile(SD, "/hello.txt", "World!\n");
//    readFile(SD, "/hello.txt");
//    deleteFile(SD, "/foo.txt");
//    renameFile(SD, "/hello.txt", "/foo.txt");
//    readFile(SD, "/foo.txt");
//    testFileIO(SD, "/test.txt");
//    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
//    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}
