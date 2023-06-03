void progsel(boolean sdini)
{
  Serial.println("Marke progsel begin");
  delay(500);
  
  char filename[100] = "";
  char directory[200];
  char buf3[17];
  char buf[301];
  char buf2[301];
  head Header;
  String Fsys;


//  Serial.begin(115200); delay(500); Serial.write("\n\n\n"); // DEBUG ONLY

  // initializes input box
  InputBox ib;
  //ib.begin(VGA_640x480_60Hz, 640, 350);
  ib.begin(VGA_400x300_60Hz, 400, 300); 
  ib.setBackgroundColor(RGB888(0, 0, 0));

  ib.onPaint = [&](Canvas * canvas) {
    canvas->selectFont(&fabgl::FONT_SANSERIF_8x16);
    canvas->setPenColor(RGB888(3, 200, 200));
    canvas->drawText(85, 5, "VGA32 --> Z1013      Select file!");
  };

  
  char const * path = nullptr;
  if (FileBrowser::mountSDCard(false, "/SD"))
    path = "/SD";
  else if (FileBrowser::mountSPIFFS(true, "/Flash"))
    path = "/Flash";

  
  ////////////////////////////////////////////////////
  // File Select
  if (path) {
    strcpy(directory, path);
    if (ib.fileSelector("File Select", "Filename: ", directory, sizeof(directory) - 1, filename, sizeof(filename) - 1) == InputResult::Enter) {

      FileBrowser::unmountSDCard();
      FileBrowser::unmountSPIFFS();

      
      if (directory[0] == '/' and directory[1] == 'S' and directory[2] == 'D')
      {
        for (uint8_t i=3; i<200; i++)
        {
          directory[i-3] = directory[i];
        }
        // Lies die ersten 32 Byte der Datei
        sprintf(buf, "%s/%s", directory, filename);
        Header = readHead(SD, buf);
        Fsys = "SD";
      }
      else  // , dann ist es /Flash
      {
        for (uint8_t i=6; i<200; i++)
        {
          directory[i-6] = directory[i];
        }
        // Lies die ersten 32 Byte der Datei
        sprintf(buf, "%s/%s", directory, filename);
        //Header = readHeadSPIFF(buf);
        Header = readHead(SPIFF,buf);
        Fsys = "SPIFF";
      }

      delay(100);
      sprintf(buf2,"Begin: %.4X   End: %.4X   Start: %.4X", Header.begin, Header.end, Header.start);
      sprintf(buf3,"%s", Header.name); buf3[16] = (char)0;
      
      ib.onPaint = [&](Canvas * canvas) {
        canvas->selectFont(&fabgl::FONT_SANSERIF_8x16);
        canvas->setPenColor(RGB888(128, 255, 128));
        canvas->drawText(85,5, "VGA32 --> Z1013");
        canvas->drawText(85,25, buf2);
        canvas->drawText(85,45, buf3);
        //canvas->drawText(85,65, buf);
      };
      //ib.messageFmt("", nullptr, "OK", "Folder = %s, \r\nFile = %s", directory, filename);
      ib.messageFmt("", nullptr, "OK", "Folder = %s, File = %s", directory, buf);
    }
  }



  if (Fsys == "SPIFF")
  {
    Serial.println("SPIFF erkannt");
    readSPIFF(buf);
  }
  else 
  {
    Serial.println("SD Card erkannt");
    readFile(SD, buf);
  }
  //SDend();

  //ib.message("Restart", "Ok, press OK to restart!");


  // finalizes input box
  ib.end();

  Serial.println("Marke progsel end");
}
