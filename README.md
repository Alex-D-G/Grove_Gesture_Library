# Grove_Gesture_Library
This library is designed for use of the Grove Gesture without the use of Seeed shield or a Seeeduino.

## How to start

First thing that I should mention is that this library heavily depends on the hwlib library and will not function properly without it.
If you have both library correctly installed you are all set to go. Since the sensors works via i2c you need to first define your scl and sda pins as demonstrated below.
After defining them you create the i2c bus which you use to create the paj7620 dubbed as sensor in this example.

```c
int main(){
    namespace target = hwlib::target;
    auto scl = target::pin_oc( target::pins::scl ); //Establishes scl pin
    auto sda = target::pin_oc( target::pins::sda ); //Establishes sda pin

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ); //Creates i2c bus

    auto sensor = paj7620(i2c_bus, 0x73); //Creates a paj7620, 0x73 is the address of the sensor
```

Once that is done it is time to initialise the sensor, this done by running the command shown below.
This function also reports back to you via prints if something is wrong with the sensor, if you do not want these messages you can turn them off by giving false as a paramter.
```c
    sensor.initialise(); //reports back
```
```c
    sensor.initialise(false); //stays quiet
```
