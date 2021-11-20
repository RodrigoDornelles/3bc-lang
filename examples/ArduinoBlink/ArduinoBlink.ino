#define _3BC_DISABLE_INTERPRETER
#include <3bc.h>

app_3bc_t VM;

void setup()
{ 
  VM = lang_3bc_init();
  
  lang_3bc_line(VM, MODE, NILL, MODE_MEMORY);
  lang_3bc_line(VM, MUSE, LED_BUILTIN, MEM_CONFIG_GPIO_SEND);
  lang_3bc_line(VM, NILL, NILL, LED_BUILTIN);
  lang_3bc_line(VM, ALOC, LED_BUILTIN, HIGH);
  lang_3bc_line(VM, MODE, NILL, MODE_SLEEP);
  lang_3bc_line(VM, MILI, NILL, 250);
  lang_3bc_line(VM, MODE, NILL, MODE_MEMORY);
  lang_3bc_line(VM, ALOC, LED_BUILTIN, LOW);
  lang_3bc_line(VM, MODE, NILL, MODE_SLEEP);
  lang_3bc_line(VM, MILI, NILL, 250);
  lang_3bc_line(VM, MODE, NILL, MODE_JUMP);
  lang_3bc_line(VM, GOTO, NILL, LED_BUILTIN);
}

void loop() {
  lang_3bc_update(VM);
}
