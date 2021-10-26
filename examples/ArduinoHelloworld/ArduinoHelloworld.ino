#include <3bc.h>

void setup()
{ 
  Serial.begin(9600);
  
  lang_io_call(tty_output, [](char* output){
    Serial.write(output);    
  });
  
  lang_init();
  lang_line(MODE, NILL, 2);
  lang_line(STRC, NILL, 'H');
  lang_line(STRC, NILL, 'e');
  lang_line(STRC, NILL, 'l');
  lang_line(STRC, NILL, 'l');
  lang_line(STRC, NILL, 'o');
  lang_line(STRC, NILL, ' ');
  lang_line(STRC, NILL, 'w');
  lang_line(STRC, NILL, 'o');
  lang_line(STRC, NILL, 'r');
  lang_line(STRC, NILL, 'l');
  lang_line(STRC, NILL, 'd');
  lang_line(STRC, NILL, '!');
  lang_line(STRC, NILL, '\n');
  lang_run();
  lang_exit();
}

void loop() {}
