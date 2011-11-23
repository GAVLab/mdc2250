#include "mdc2250/mdc2250.h"

int main(void) {
  mdc2250::MDC2250 my_mdc2250;
  
  my_mdc2250.connect("/dev/tty.usbmodemfd1341");
  my_mdc2250.setCommand(mdc2250::commanditem::_GO, 1, 20);
  my_mdc2250.setCommand(mdc2250::commanditem::_GO, 2, 20);
  mdc2250::sleep_ms(1000);
  my_mdc2250.setCommand(mdc2250::commanditem::_GO, 1, 0);
  my_mdc2250.setCommand(mdc2250::commanditem::_GO, 2, 0);
  my_mdc2250.disconnect();
  
  return 0;
}