// ==========================================================================
//
// File      : main.cpp
// Part of   : Grove Gesture Library
// Copyright : Alexander de Graaff 2020
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
#include "gesture.hpp"
#include "hwlib.hpp"
#include <ctime>


uint8_t getReading(auto sensor){
    uint8_t data = 0;
    while(true){
        hwlib::wait_ms(200);
        data = sensor.read(0x43);
        
        if(data == RIGHT_FLAG){
            return RIGHT_FLAG;
        }

        else if(data == LEFT_FLAG){
            return LEFT_FLAG;
        }
        
        else if(data == UP_FLAG){
            return UP_FLAG;
        }

        else if(data == DOWN_FLAG){
            return DOWN_FLAG;
        }
    }
}


uint8_t randomGesture(){
    int result = 1 + (rand() % 4);

    if(result == 1){
        return LEFT_FLAG;
    }
    else if(result == 2){
        return RIGHT_FLAG;
    }
    else if(result == 3){
        return DOWN_FLAG;
    }
    else if(result == 4){
        return UP_FLAG;
    }
    return 255;
}


int main(){
    namespace target = hwlib::target;

    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 
    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::terminal_from( oled, font );

    uint8_t readable[9] = {RIGHT_FLAG, LEFT_FLAG, UP_FLAG, DOWN_FLAG};
    auto sensor = limited_paj7620(i2c_bus, 0x73, readable);

    sensor.initialise();

    uint8_t Sequence[12] = {};
    uint8_t reading = 0;
    bool stop = false;

    while(true){
        Sequence[12] = {};
        display 
            << "\f" << " -=Simon says=-" << "\n"
            << "\n" << "Repeat the" << "\n" << "gestures in the"
            << "\n" << "order they were" << "\n" << "given." 
            << "\n" << "\n" << "Swipe left"
            << hwlib::flush;

        while(true){
            reading = getReading(sensor);
            if(reading == LEFT_FLAG){
                break;
            }
        }
        
        display 
            << "\f" << " -=Simon says=-" << "\n"
            << "\n" << "Game will begin"
            << "\n" << "in 3.."
            << hwlib::flush;
        hwlib::wait_ms(1000);
        display 
            << "\f" << " -=Simon says=-" << "\n"
            << "\n" << "Game will begin"
            << "\n" << "in 2.."
            << hwlib::flush;
        hwlib::wait_ms(1000);
        display 
            << "\f" << " -=Simon says=-" << "\n"
            << "\n" << "Game will begin"
            << "\n" << "in 1.."
            << hwlib::flush;
        hwlib::wait_ms(1000);

        for(int i=0;i<12;i++){
            Sequence[i] = randomGesture();

            for(unsigned int j=0; j<(sizeof(Sequence)/sizeof(Sequence[0])); j++){
                if(Sequence[j]==0){
                    break;
                }
                else if(Sequence[j]==LEFT_FLAG){
                    display 
                        << "\f" << " -=Simon says=-" << "\n"
                        << "\n" << "Gesture: LEFT";
                }
                else if(Sequence[j]==RIGHT_FLAG){
                    display 
                        << "\f" << " -=Simon says=-" << "\n"
                        << "\n" << "Gesture: RIGHT";
                }
                else if(Sequence[j]==UP_FLAG){
                    display 
                        << "\f" << " -=Simon says=-" << "\n"
                        << "\n" << "Gesture: UP";
                }
                else if(Sequence[j]==DOWN_FLAG){
                    display 
                        << "\f" << " -=Simon says=-" << "\n"
                        << "\n" << "Gesture: DOWN";
                }
                display 
                    << "\n" << "\n" 
                    << "Number:" << j+1 
                    << hwlib::flush;

                hwlib::wait_ms(1500);
            }

            for(unsigned int j=0; j<(sizeof(Sequence)/sizeof(Sequence[0])); j++){
                if(Sequence[j]==0){
                    break;
                }
                display 
                    << "\f" << " -=Simon says=-" << "\n"
                    << "\n" << "Give Sequence:"
                    << hwlib::flush;
                reading = getReading(sensor);
                if(reading != Sequence[j]){
                    display 
                        << "\f" << " -=Simon says=-" << "\n"
                        << "\n" << "INCORRECT" << "\n"
                        << "\n" << "Your score is:" << i
                        << "\n" << "\n" << "Swipe left"
                        << hwlib::flush;

                    while(true){
                        reading = getReading(sensor);
                        if(reading == LEFT_FLAG){
                            break;
                        }
                    }
                    stop = true;
                    break;
                }
            }

            if(stop){
                stop = false;
                break;
            }

            if(i==11){
                display 
                    << "\f" << " -=Simon says=-" << "\n"
                    << "\n" << "You won!" << "\n"
                    << "\n" << "Swipe left"
                    << hwlib::flush;

                while(true){
                    reading = getReading(sensor);
                    if(reading == LEFT_FLAG){
                        break;
                    }
                }
            }
        }
    }
}
