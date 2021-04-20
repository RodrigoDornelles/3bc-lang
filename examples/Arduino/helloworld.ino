#include <3bc.h>

void setup() {
  lang_driver_init();
  lang_line(MODE, NILL, 0x02);
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
  lang_driver_run();
  lang_driver_exit(0);
}

void loop() {}