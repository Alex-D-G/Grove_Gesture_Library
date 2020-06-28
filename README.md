# Grove_Gesture_Library
This library is designed for use of the Grove Gesture without the use of Seeed shield or a Seeeduino.

## How to start

```c
int main(){
    namespace target = hwlib::target;
    auto scl = target::pin_oc( target::pins::scl ); //Establishes scl pin
    auto sda = target::pin_oc( target::pins::sda ); //Establishes sda pin

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ); //Creates i2c bus

    auto sensor = paj7620(i2c_bus, 0x73); //Creates a paj7620, 0x73 is the address of the sensor
```
