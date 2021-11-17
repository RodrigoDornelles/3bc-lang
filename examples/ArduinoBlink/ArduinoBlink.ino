#define _3BC_DISABLE_INTERPRETER
#include <3bc.h>

app_3bc_t VM;

void setup()
{ 
  VM = lang_3bc_init();
  
  lang_line(MODE, NILL, MODE_MEMORY);
  lang_line(MUSE, LED_BUILTIN, MEM_CONFIG_GPIO_SEND);
  lang_line(NILL, NILL, LED_BUILTIN);
  lang_line(ALOC, LED_BUILTIN, HIGH);
  lang_line(MODE, NILL, MODE_SLEEP);
  lang_line(MILI, NILL, 250);
  lang_line(MODE, NILL, MODE_MEMORY);
  lang_line(ALOC, LED_BUILTIN, LOW);
  lang_line(MODE, NILL, MODE_SLEEP);
  lang_line(MILI, NILL, 250);
  lang_line(MODE, NILL, MODE_JUMP);
  lang_line(GOTO, NILL, LED_BUILTIN);
}

void loop() {
  lang_3bc_update(VM);
}
