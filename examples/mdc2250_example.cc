#include "mdc2250/mdc2250.h"

int main(void) {
  mdc2250::MDC2250 my_mdc2250;
  mdc2250::MDC2250 my_mdc2250_1;

  
  my_mdc2250.connect("/dev/ttyACM0");
  my_mdc2250_1.connect("/dev/ttyACM1");

  for(size_t i = 0; i < 10; ++i) {
    my_mdc2250.setCommand(mdc2250::commanditem::_GO, -255, 1);
    my_mdc2250.setCommand(mdc2250::commanditem::_GO, 255, 2);
    my_mdc2250_1.setCommand(mdc2250::commanditem::_GO, -255, 1);
    my_mdc2250_1.setCommand(mdc2250::commanditem::_GO, 255, 2);
    usleep(1000*1000);
  }

  for(size_t i = 0; i < 10; ++i) {
    my_mdc2250.setCommand(mdc2250::commanditem::_GO, 255, 1);
    my_mdc2250.setCommand(mdc2250::commanditem::_GO, -255, 2);
    my_mdc2250_1.setCommand(mdc2250::commanditem::_GO, 255, 1);
    my_mdc2250_1.setCommand(mdc2250::commanditem::_GO, -255, 2);
    usleep(1000*1000);
  }

  my_mdc2250.setCommand(mdc2250::commanditem::_GO, 0, 1);
  my_mdc2250.setCommand(mdc2250::commanditem::_GO, 0, 2);
  my_mdc2250_1.setCommand(mdc2250::commanditem::_GO, 0, 1);
  my_mdc2250_1.setCommand(mdc2250::commanditem::_GO, 0, 2);

  my_mdc2250.disconnect();
  my_mdc2250_1.disconnect();

  return 0;
}
