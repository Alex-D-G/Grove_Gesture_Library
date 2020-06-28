#include "gesture.hpp"
#include "hwlib.hpp"


int main(){
    namespace target = hwlib::target;
    auto scl = target::pin_oc( target::pins::scl ); //Establishes scl pin
    auto sda = target::pin_oc( target::pins::sda ); //Establishes sda pin

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ); //Creates i2c bus

    auto sensor = paj7620(i2c_bus, 0x73); //Creates a paj7620, 0x73 is the address of the sensor

    sensor.initialise(); //Initialises all the sensors functions

    uint8_t data = 0;
    while(true){
        hwlib::wait_ms(500);
        data = sensor.read(0x43); //Reads the sensors readings from the register 0

        if(data == RIGHT_FLAG){
            hwlib::cout << "Right \n";
        }

        else if(data == LEFT_FLAG){
            hwlib::cout << "Left \n";
        }
        
        else if(data == UP_FLAG){
            hwlib::cout << "Up \n";
        }

        else if(data == DOWN_FLAG){
            hwlib::cout << "Down \n";
        }

        else if(data == CLOSE_FLAG){
            hwlib::cout << "Close \n";
        }

        else if(data == FURTHER_FLAG){
            hwlib::cout << "Further \n";
        }

        else if(data == CLOCK_FLAG){
            hwlib::cout << "Clockwise \n";
        }
        
        else if(data == COUNTER_CLOCK_FLAG){
            hwlib::cout << "Counter Clockwise \n";
        }

        data = sensor.read(0x44); //Reads the sensors readings from the register 1
        if(data == WAVE_FLAG){
            hwlib::cout << "Wave \n";
        }
        
    }
}
