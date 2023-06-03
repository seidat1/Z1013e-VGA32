  /********************************************************************************************************************
 *  Für Deutsche
 *   
 *   Dies ist eine Emulation des Kleincomputerbausatzes Z1013. 
 *   Benötigt werden folgende Komponenten:
 *   - VGA32 V.1.4
 *   - VGA-Monitor mit VGA-Kabel urund Stromversorgungskabel
 *   - PS/2 Tastatur
 *   - 5V Stromversorgung mit Micro-USB-Kabel
 *   
 *   In dieser Version sind 16kB Arbeitsspeicher implementiert. Der EPROM-Bereich ist 4kB groß. Für den Bildspeicher 
 *   wurden 1kB reserviert. Die Ausgabe des Bildschirminhaltes erfolgt momentan noch auf die Serielle Schnittstelle. 
 *   Damit können aber die grafischen Symbole des Z1013 nicht dargestellt werden.
 *    
 *   Mein Dank gilt den Autoren der Bibliotheken 
 *   - Z80, Marat Fayzullin
 *   - DabGL, Fabrizio Di Vittorio
 *
 *   Bitte beachtet die Lizenzhinweise der Autoren!
 *   
 *   
 *   Ich kann keine Garantie für die Fehlerfreiheit des Programms geben. Für entstandene Schäden kann ich nicht
 *   Haftbar gemacht werden.
 *   
 *   Lizenz: Es ist gestattet, dieses Programm privat zu benutzen. Es ist nicht gestattet, dieses Programm für 
 *   kommerzielle Zwecke zu verwenden. Es ist nicht gestattet, das VG32-Modul mit dieser Software zu verkaufen.
 *   
 *   
 *   
 *
 ********************************************************************************************************************/

#include <Z80.h>
#include <fabgl.h>
#include <canvas.h>
#include "character_set.h"
#include "keyboard.h"
#include "memory.h"
#include "SD_card.h"
#include "progsel.h"


fabgl::PS2Controller    PS2Controller;
fabgl::VGA2Controller   DisplayController;
fabgl::Canvas           canvas(&DisplayController);


uint8_t  Taste;
uint8_t  Spalte1;
uint8_t  Zeile1;
uint8_t  Spalte2;
uint8_t  Zeile2;
uint8_t  zwSpalte1;
uint8_t  zwZeile1;
uint8_t  z80Port;
uint8_t  z80Val;
uint8_t  InputS7;


#define KassetteOut 13
#define KassetteIn 2
#define halfTakt 14
int16_t TaktDiff;
boolean Frequenzanpassung = false;
int16_t L_Buffer[6000];
int16_t counter = 0;

uint16_t count=100;

//struct Button {
//    const uint8_t PIN;
//    uint32_t numberKeyPresses;
//    bool pressed;
//};


//Button button2 = {13, 0, false};


auto keyboard = PS2Controller.keyboard();
hw_timer_t *Timer3_Cfg = NULL;
hw_timer_t *Timer1_Cfg = NULL; 

uint16_t Pruefsumme;
uint8_t bitcounter = 16;
uint8_t wordcounter = 16;
uint8_t onecounter = 2;
uint8_t halfcounter = 2;
uint16_t readword = 0;
uint16_t Ziel;
uint16_t Ende;
uint8_t Step;
uint16_t leader;
uint16_t firstleader = 100;

//--------------------------------------------------------------------------------------

void IRAM_ATTR isr()
{
//  Serial.print(".");
  uint16_t timeX = timerRead(Timer1_Cfg);
  timerRestart(Timer1_Cfg);
//  Serial.println(timeX);
  if (counter > 4)  // die ersten 4 Werte werden ignoriert
  {
    uint8_t error = 0;
    if (timeX<3900 and timeX>2100 and Step == 0)
    { // Es wurde ein Pegelwechsel des Vorspanns erkannt
      // setze die Prüfgsumme auf 0
      Pruefsumme = 0;
      bitcounter = 0;
      wordcounter = 0;
      onecounter = 0;
      halfcounter = 0;
      readword = 0;
      leader++;
//      Serial.println(leader);
    }
    else if (timeX<1950 and timeX>1050 and Step == 20)
    { // jetzt wurde die zweite "1" erkannt
      onecounter++;
      Step = 30;
//      Serial.println("Y");
    }
    else if (timeX<1950 and timeX>1050 and Step == 0 and leader>firstleader)
    { // jetzt wurde eine "1" erkannt
      onecounter++;
      Step = 20;
//      Serial.println("X");
    }
    else if (timeX<1950 and timeX>1050 and Step == 30)
    { // das ist ein 1-Bit
      readword = readword >> 1;
      readword |= 0x8000;
      bitcounter++;
//      Serial.println("1");
    }
    else if (timeX<1001 and timeX>539 and halfcounter == 0 and Step == 30)
    { // das ist der erste Teil einer 0 
      halfcounter = 1;
    }
    else if (timeX<1001 and timeX>539 and halfcounter == 1 and Step == 30)
    { // jetzt wurde das ganze 0-Bit erkannt
      readword = readword >> 1;
      readword &= 0x7FFF;
      bitcounter++;
      halfcounter = 0;
//      Serial.println("0");
    }
//    else Error = 1;
//      Serial.println(readword, HEX);

    if (bitcounter == 16)
    { // ein Word wurde jetzt eingelesen
//      Serial.println(readword, HEX);
      if (wordcounter == 0)
      { // das erste word muss 0x0000 sein
        // hier kommt die Prüfung hin 
//        Serial.print("#");
        if (readword !=0) Serial.println("0-Fehler");
        wordcounter++;
      }
      else if (wordcounter==17)
      {
        // das ist die Prüfsumme
        // Serial.print("P");
        // Serial.print(readword, HEX);
        // Serial.println(Pruefsumme, HEX);
        if (readword - Pruefsumme == 0) 
        {
          Serial.println("OK");
        }
        else
        {
          Serial.println("P-Fehler");
        }
        if (Ziel>Ende) detachInterrupt(KassetteIn);
        Pruefsumme = 0;
        bitcounter = 0;
        wordcounter = 0;
        onecounter = 0;
        halfcounter = 0;
        readword = 0;
        leader = 0;
        firstleader = 8;
        counter = 0;
        Step = 0;
      }
      else if (wordcounter>0 and wordcounter<17)
      {
//       Serial.println(Ziel, HEX);
       // nun kann das Word abgelegt werden
        if (Ziel<=Ende) WrZ80(Ziel++, readword % 256);
        if (Ziel<=Ende) WrZ80(Ziel++, readword / 256);
        Pruefsumme += readword;
        wordcounter++;
      }
      bitcounter = 0;
    }
  }
  counter++;
}

void IRAM_ATTR Timer3_ISR()
{
//  digitalWrite(halfTakt, !digitalRead(halfTakt));
  TaktDiff = TaktDiff - 6;    // 6 => 1MHz; 12 => 2MHz  (2MHz geht nur für den S-Befehl)
}





// Memory write -- write the Value to memory location Addr
void WrZ80(register zword Addr, register byte Value)
{
  uint8_t blk = Addr / BLOCK_SIZE;
  Addr = Addr % BLOCK_SIZE;
  if (*(ptrRW+blk) == WRITE_READ) *(ptr[blk]+Addr) = Value;
  if (blk == 59)
  {
    PaintChar((uint8_t)(Addr % 32), uint8_t(Addr / 32), (uint8_t) Value);
  }
}


// Memory read -- read the value at memory location Addr
byte RdZ80(register zword Addr) 
{
  uint8_t blk = Addr / BLOCK_SIZE;
  Addr = Addr % BLOCK_SIZE;
  return *(ptr[blk]+Addr);
}


// IO -- output the Value on the Port (currently does nothing)
// This is generally optional unless your code uses IO
// Can be left blank.
void OutZ80(register zword Port, register byte Value)
          {
  z80Port = (byte) Port;
  z80Val = Value;
  if (z80Port == 8)
  {
    if (Spalte1 == Spalte2) Zeile1 = Zeile1 & Zeile2;
    if (Value == Spalte1) Taste = Zeile1;
    else if (Value == Spalte2) Taste = Zeile2;
    else Taste = 0x0F;
  }
  else if (z80Port == 2)
  {
    pinMode(KassetteOut, OUTPUT);    
    if ((Value & 0x80) == 0x80)
    {
      digitalWrite(KassetteOut, HIGH);
    }
    else
    {
      digitalWrite(KassetteOut, LOW);
    }
  }
}


// IO -- read a value from Port (currently defaults to 0)
// This is generally optional unless your code uses IO
// Can be left empty as long as it returns a byte.
byte InZ80(register zword Port)
{
  uint8_t Output = 0;
  if ((Port & 0x0F) == 2) // der Port für Input muss 2 sein
  {
    if ((z80Port) == 8) // der letze Ausgabeport muss 8 sein
    {
      if (z80Val == 7) InputS7++;
      else if (z80Val == 0) InputS7 = 0;
      Output = Taste;
    }
    if (digitalRead(KassetteOut) == HIGH)
    {
      Output |= 0x80; 
    }
    else
    {
      Output &= ~0x80; // also 0x7F
    }
    // vom Tonband einlesen
    if (digitalRead(KassetteIn) == HIGH)
    {
      Output |= 0x40;
    }
    else
    {
      Output &= ~0x40;
    }
  }
  return Output;
}


// Advanced -- called when an emulator-specific opcode of
// ED FE is encountered. Generally can be left empty.
void PatchZ80(register Z80 *R) {}

// create a CPU core object
Z80 cpu;

void setup()
{
  Serial.begin(115200);
  delay(500);

  // die Blöcke den Zeigern zuordnen, jetzt braucht nur der Zeiger geändert werden, um andere Programme zu starten
  for (uint8_t i=0; i < 59; i++)
  {
    ptr[i] = ram[i];
  }
  ptr[59] = ram_bild[0];
  ptr[60] = eprom[0];
  ptr[61] = eprom[1];
  ptr[62] = eprom[2];
  ptr[63] = eprom[3];

  // Zeiger auf die Berechtigung Lesen oder Lesen und Schreiben
  ptrRW = sto_rw;
  progsel(true);
 
  // Reset the CPU to 0x00 and zero the regs/flags
  ResetZ80(&cpu);

  PS2Controller.begin(PS2Preset::KeyboardPort0_MousePort1 );

  DisplayController.begin();
  DisplayController.setResolution(VGA_400x300_60Hz);    // VGA_640x480_60Hz);

  Spalte1 = 0;
  Zeile1 = 0xF;
  Spalte2 = 0x0;
  Zeile2  = 0xF;
  zwSpalte1 = 0;
  zwZeile1 = 0xF;

 
//  pinMode(halfTakt, OUTPUT);
//  pinMode(KassetteOut, OUTPUT);

  keyboard = PS2Controller.keyboard();
  keyboard->setLayout(&fabgl::GermanLayout);

//  Timer3_Cfg = timerBegin(0, 20, true);
//  timerAttachInterrupt(Timer3_Cfg, &Timer3_ISR, true);
//  timerAlarmWrite(Timer3_Cfg, 80, true);
//  timerAlarmEnable(Timer3_Cfg);

  Serial.println("Marke Setup End");
}


void loop() 
{
  // Tastaur abragen und wandeln für Folientastatur
  if (InputS7 == 0x40) // Dieser Teil ist ganz wichtig, Es wird gewartet, bis die Folientastatur 
                       // erfolglos abgefragt ist, also ganzer Durchlauf ohne Tastendruck. Damit 
                       // wird sichergestell, dass S-Tasten garantiert erkannt werden.
  {
    Spalte1 = zwSpalte1;
    Zeile1 = zwZeile1;
  }
  else if (keyboard->virtualKeyAvailable()) 
  {
    // ascii mode (show ASCIIl, VirtualKeys and scancodes)
    VirtualKeyItem item;
    if (keyboard->getNextVirtualKey(&item)) 
    {
      char ASCII = item.ASCII;
      String vkStr = keyboard->virtualKeyToString(item.vk);
      if (vkStr == "VK_LEFT" and item.down) {zwSpalte1 = 4; zwZeile1  = ~8; Spalte2 = 0xF; Zeile2  = 0xF;}
      else if (vkStr == "VK_AT" and item.down) {zwSpalte1 = 0; zwZeile1  = ~1; Spalte2 = 0xF; Zeile2  = 0xF;}
      else if (vkStr == "VK_RIGHT" and item.down) {zwSpalte1 = 6; zwZeile1  = ~8; Spalte2 = 0xF; Zeile2  = 0xF;}
      else if (vkStr == "VK_F2" and item.down)
      {
        //Serial.println("Marke 1");
        DisplayController.end();
        delay(50);

        //Serial.println("Tschuess ich gehe zu progsel");
        progsel(true);
        //Serial.println("Guten Tag zurueck im Hauptprogramm");
        DisplayController.begin();
        DisplayController.setResolution(VGA_400x300_60Hz);    // VGA_640x480_60Hz);
        // Bildschirm wiederherstellen
        for (uint16_t i=0xEC00; i<0xF000; i++)
        {
          WrZ80(i,RdZ80(i));
        }
      }
      else if (item.down)
      {
        zwSpalte1 = tasttable[ASCII][0];
        zwZeile1  = ~tasttable[ASCII][1];
        Spalte2 = tasttable[ASCII][2];
        Zeile2  = ~tasttable[ASCII][3];
      }
      else if (~item.down) 
      {
        Spalte1 = 9;
        Zeile1  = 0xF;
        zwZeile1 = 0xF;
      }
    }
  } // Ende der Tastaturabfrage


  // hier wird 1 Befehl ausgeführt
  StepZ80(&cpu);

 
  if (Frequenzanpassung)
  {
    TaktDiff += cpu.Cycles;
    while (TaktDiff > 0)
    {
      digitalWrite(halfTakt, !digitalRead(halfTakt));
    }
  }


  // Verlangsamung für S-Befehl
  if (cpu.PC.W == 0xF369)   // starte die Frequenzanpassung
  {
    Serial.printf("Start Timer Interrupt\n");
    pinMode(halfTakt, OUTPUT);
    pinMode(KassetteOut, OUTPUT);
    Timer3_Cfg = timerBegin(0, 20, true);
    timerAttachInterrupt(Timer3_Cfg, &Timer3_ISR, true);
    timerAlarmWrite(Timer3_Cfg, 25, true);
    timerAlarmEnable(Timer3_Cfg);
    Frequenzanpassung = true;
    TaktDiff = 0;
  } 


//  if (counter >= 6000)
//  {
//    detachInterrupt(KassetteIn);
//    counter = 0;
//
//    for(uint16_t i=0; i<6000; i++)
//    {
//      Serial.print("pos: ");
//      Serial.print(i);
//      Serial.print("  Zeit: ");
//      Serial.println(L_Buffer[i]);
//    }
//  }


//    if (button2.pressed) {
//        Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
//        button2.pressed = false;
//    }
  
  
  // Verlangsamung für L-Befehl
  if (cpu.PC.W == 0xF3F8)   // starte die Frequenzanpassung
  {
    pinMode(KassetteIn, INPUT_PULLUP);
    attachInterrupt(KassetteIn, isr, CHANGE);

leader = 0;
Step = 0;
firstleader = 100;

    Ziel = RdZ80(0x001B);
    Ziel += 256 * RdZ80(0x001C);

    Ende = RdZ80(0x001D);
    Ende += 256 * RdZ80(0x001E);

    Serial.print("Ziel: ");
    Serial.print(Ziel, HEX);
    Serial.print("   Ende: ");
    Serial.println(Ende, HEX);

//    pinMode(KassetteIn, INPUT_PULLUP);
    // Versuche den Vorspann zu erkennen

 //   attachInterrupt(KassetteIn, Ext_INT1_ISR, CHANGE);
    //detachInterrupt(KassetteIn);    
    
    // Timer 1 benutzen 
    // Timer soll hochlaufen,  damit ein Puls gemessen werden kann
    // 
    uint8_t num = 1;
    uint16_t divider = 40;    // damit wird alle 0,5 µs gezählt
    boolean countUp = true;
    Timer1_Cfg = timerBegin(num, divider, countUp);
    timerWrite(Timer1_Cfg, 0);
    counter = 0;
    timerStart(Timer1_Cfg);  
   
    
    cpu.PC.W = 0xF3F7;
    
    
//    Serial.printf("Start Timer Interrupt\n");
//    pinMode(halfTakt, OUTPUT);
//    pinMode(KassetteIn, INPUT);
//    Timer3_Cfg = timerBegin(0, 20, true);
//    timerAttachInterrupt(Timer3_Cfg, &Timer3_ISR, true);
//    timerAlarmWrite(Timer3_Cfg, 25, true);
//    timerAlarmEnable(Timer3_Cfg);
//    Frequenzanpassung = true;
//    TaktDiff = 0;
  } 

  
  // Ende der Verlangsamung
  // Da beide Programme mit einem "RET C" verlassen werden, muss auch das C-Flag ausgewertet werden
  if (cpu.PC.W == 0xF377 or cpu.PC.W == 0xF414)   // stoppe die Frequenzanpassung
  {
    if (cpu.AF.B.l & C_FLAG == C_FLAG)
    {
      Frequenzanpassung = false;
      timerAlarmDisable(Timer3_Cfg);
      pinMode(halfTakt, INPUT);
      pinMode(KassetteOut, INPUT);
      Serial.printf("Ende Timer Interrupt\n");
      Serial.print("Counter: ");
      Serial.println(counter);
    }
  }


}



void PaintChar(uint8_t x, uint8_t y, uint8_t Zeichen)
{
  uint8_t OffsetX = 80;
  uint8_t OffsetY = 20;
  uint8_t Char_Size = 1;         // 1 | 2 | 3
  for (uint8_t j=0; j<8; j++)
  {
    uint8_t Zeile = character[Zeichen*8+j];
    for (uint8_t i=0; i<8; i++)
    {
      if ((Zeile & 0x80) > 0)
      {
        canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y);
        if (Char_Size >= 2)
        {
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y);
        }
        if (Char_Size >= 3)
        {
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y);
        }
     }
     else
     {
        canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y, (fabgl::Color)0);
        if (Char_Size >= 2)
        {
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y, (fabgl::Color)0);
        }
        if (Char_Size >= 3)
        {
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+0+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+1+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+0+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+1+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y, (fabgl::Color)0);
          canvas.setPixel(i*Char_Size+OffsetX+2+8*Char_Size*x, j*Char_Size+OffsetY+2+8*Char_Size*y, (fabgl::Color)0);
        }
     }
      Zeile = Zeile << 1;
    }
  }
}
