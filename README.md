# Grove Gesture Library
This library is designed for use of the Grove Gesture without the need for a Seeed shield or a Seeeduino.

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
Once initialised you can begin reading from the sensor by using the following command.
Something that i should note is that not all gestures are stored in register 0, the ninth gesture, the wave is stored in register 1 which can be acces by reading 0x44 instead of 0x43.
```c
    uint8_t data = 0;
    data = sensor.read(0x43); //Reads the sensors readings from the register 0
```
The sensors readings are stored in 'data' in the example, data will have a different value depending on what gesture was detected the values are shown below:
```c
    //These flags are stored in the first register
    DOWN_FLAG          = 0x01,
    UP_FLAG            = 0x02,
    RIGHT_FLAG         = 0x04,
    LEFT_FLAG          = 0x08,
    CLOSE_FLAG         = 0x10,
    FURTHER_FLAG       = 0x20,
    CLOCK_FLAG         = 0x40,
    COUNTER_CLOCK_FLAG = 0x80,
    //This flag is stored in the second register
    WAVE_FLAG          = 0x01
```
If nothing is read data will equal 0.

These flags can also be used while coding for ease of use.
```c
    if(data == RIGHT_FLAG){
        hwlib::cout << "Right \n";
    }
```

## Limited readings

Say you only want to read left and right gestures, well I got you covered.
Instead of creating sensor like shown above you can also create it like this:
```c
    uint8_t readable[9] = {RIGHT_FLAG, LEFT_FLAG};
    auto sensor = limited_paj7620(i2c_bus, 0x73, readable);
```
In this example the sensor will only be able to read left and right + any other flags you decide to put into readable and if you decide that you dont want to read anything you can also leave readable blank.

You can always check which gestures you set to read by giving the following command:
```c
    uint8_t readable[9] = sensor.giveReadable();
```

Grown tired of only reading right and left gestures? No worries! You can always set readable to something else:
```c
    uint8_t newReadable[9] = {WAVE_FLAG};
    sensor.setReadable(newReadable);
```

