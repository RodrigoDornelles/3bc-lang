#define _3BC_DISABLE_INTERPRETER
#include <3bc.h>

struct app_3bc_s *const VM;

void setup()
{ 
  Serial.begin(9600);
  
  VM = lang_3bc_init();

  lang_3bc_print(VM, tty_output, [](char* output){
    Serial.write(output);    
  });
  
  lang_3bc_line(VM, MODE, NILL, 2);
  lang_3bc_line(VM, STRC, NILL, 'H');
  lang_3bc_line(VM, STRC, NILL, 'e');
  lang_3bc_line(VM, STRC, NILL, 'l');
  lang_3bc_line(VM, STRC, NILL, 'l');
  lang_3bc_line(VM, STRC, NILL, 'o');
  lang_3bc_line(VM, STRC, NILL, ' ');
  lang_3bc_line(VM, STRC, NILL, 'w');
  lang_3bc_line(VM, STRC, NILL, 'o');
  lang_3bc_line(VM, STRC, NILL, 'r');
  lang_3bc_line(VM, STRC, NILL, 'l');
  lang_3bc_line(VM, STRC, NILL, 'd');
  lang_3bc_line(VM, STRC, NILL, '!');
  lang_3bc_line(VM, STRC, NILL, '\n');
}

void loop() {
  lang_3bc_update(VM);
}
