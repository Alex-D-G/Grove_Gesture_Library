#ifndef GESTURE_HPP
#define GESTURE_HPP

/// @file
// This file contains doxygen lines

#include "hwlib.hpp"
#include <vector>


/// \brief    
/// Flags for the gestures
/// \details
/// These flags are defined here to make it easy to refer to by the user.
enum flags : uint8_t {
    //These flags are stored in the first register
    DOWN_FLAG          = 0x01,
    UP_FLAG            = 0x02,
	RIGHT_FLAG         = 0x04,
    LEFT_FLAG          = 0x08,
    CLOSE_FLAG         = 0x10,
    FURTHER_FLAG       = 0x20,
    CLOCK_FLAG         = 0x40,
    COUNTER_CLOCK_FLAG = 0x80,
    //this flag is stored in the second register
    WAVE_FLAG          = 0x01,
};

/// \brief    
/// Commands for the registers
/// \details
/// These commands are later written to the registers so the chip can work properly.
unsigned char registerCommands[][2] = {
	{0xEF,0x00},{0x32,0x29},{0x33,0x01},{0x34,0x00},{0x35,0x01},{0x36,0x00},{0x37,0x07},{0x38,0x17},{0x39,0x06},{0x3A,0x12},
	{0x3F,0x00},{0x40,0x02},{0x41,0xFF},{0x42,0x01},{0x46,0x2D},{0x47,0x0F},{0x48,0x3C},{0x49,0x00},{0x4A,0x1E},{0x4B,0x00},
    {0x4C,0x20},{0x4D,0x00},{0x4E,0x1A},{0x4F,0x14},{0x50,0x00},{0x51,0x10},{0x52,0x00},{0x5C,0x02},{0x5D,0x00},{0x5E,0x10},
	{0x5F,0x3F},{0x60,0x27},{0x61,0x28},{0x62,0x00},{0x63,0x03},{0x64,0xF7},{0x65,0x03},{0x66,0xD9},{0x67,0x03},{0x68,0x01},
	{0x69,0xC8},{0x6A,0x40},{0x6D,0x04},{0x6E,0x00},{0x6F,0x00},{0x70,0x80},{0x71,0x00},{0x72,0x00},{0x73,0x00},{0x74,0xF0},
	{0x75,0x00},{0x80,0x42},{0x81,0x44},{0x82,0x04},{0x83,0x20},{0x84,0x20},{0x85,0x00},{0x86,0x10},{0x87,0x00},{0x88,0x05},
	{0x89,0x18},{0x8A,0x10},{0x8B,0x01},{0x8C,0x37},{0x8D,0x00},{0x8E,0xF0},{0x8F,0x81},{0x90,0x06},{0x91,0x06},{0x92,0x1E},
	{0x93,0x0D},{0x94,0x0A},{0x95,0x0A},{0x96,0x0C},{0x97,0x05},{0x98,0x0A},{0x99,0x41},{0x9A,0x14},{0x9B,0x0A},{0x9C,0x3F},
	{0x9D,0x33},{0x9E,0xAE},{0x9F,0xF9},{0xA0,0x48},{0xA1,0x13},{0xA2,0x10},{0xA3,0x08},{0xA4,0x30},{0xA5,0x19},{0xA6,0x10},
	{0xA7,0x08},{0xA8,0x24},{0xA9,0x04},{0xAA,0x1E},{0xAB,0x1E},{0xCC,0x19},{0xCD,0x0B},{0xCE,0x13},{0xCF,0x64},{0xD0,0x21},
	{0xD1,0x0F},{0xD2,0x88},{0xE0,0x01},{0xE1,0x04},{0xE2,0x41},{0xE3,0xD6},{0xE4,0x00},{0xE5,0x0C},{0xE6,0x0A},{0xE7,0x00},
	{0xE8,0x00},{0xE9,0x00},{0xEE,0x07},{0xEF,0x01},{0x00,0x1E},{0x01,0x1E},{0x02,0x0F},{0x03,0x10},{0x04,0x02},{0x05,0x00},
	{0x06,0xB0},{0x07,0x04},{0x08,0x0D},{0x09,0x0E},{0x0A,0x9C},{0x0B,0x04},{0x0C,0x05},{0x0D,0x0F},{0x0E,0x02},{0x0F,0x12},
	{0x10,0x02},{0x11,0x02},{0x12,0x00},{0x13,0x01},{0x14,0x05},{0x15,0x07},{0x16,0x05},{0x17,0x07},{0x18,0x01},{0x19,0x04},
	{0x1A,0x05},{0x1B,0x0C},{0x1C,0x2A},{0x1D,0x01},{0x1E,0x00},{0x21,0x00},{0x22,0x00},{0x23,0x00},{0x25,0x01},{0x26,0x00},
	{0x27,0x39},{0x28,0x7F},{0x29,0x08},{0x30,0x03},{0x31,0x00},{0x32,0x1A},{0x33,0x1A},{0x34,0x07},{0x35,0x07},{0x36,0x01},
	{0x37,0xFF},{0x38,0x36},{0x39,0x07},{0x3A,0x00},{0x3E,0xFF},{0x3F,0x00},{0x40,0x77},{0x41,0x40},{0x42,0x00},{0x43,0x30},
	{0x44,0xA0},{0x45,0x5C},{0x46,0x00},{0x47,0x00},{0x48,0x58},{0x4A,0x1E},{0x4B,0x1E},{0x4C,0x00},{0x4D,0x00},{0x4E,0xA0},
	{0x4F,0x80},{0x50,0x00},{0x51,0x00},{0x52,0x00},{0x53,0x00},{0x54,0x00},{0x57,0x80},{0x59,0x10},{0x5A,0x08},{0x5B,0x94},
	{0x5C,0xE8},{0x5D,0x08},{0x5E,0x3D},{0x5F,0x99},{0x60,0x45},{0x61,0x40},{0x63,0x2D},{0x64,0x02},{0x65,0x96},{0x66,0x00},
	{0x67,0x97},{0x68,0x01},{0x69,0xCD},{0x6A,0x01},{0x6B,0xB0},{0x6C,0x04},{0x6D,0x2C},{0x6E,0x01},{0x6F,0x32},{0x71,0x00},
	{0x72,0x01},{0x73,0x35},{0x74,0x00},{0x75,0x33},{0x76,0x31},{0x77,0x01},{0x7C,0x84},{0x7D,0x03},{0x7E,0x01},
};


/// \brief    
/// Default class for the paj7620
/// \details
/// This class requires both an uint_fast8_t address for the chip and a hwlib::i2c_bus.
/// These variables are asigned in the contructor and thus need to be provided upon creation of a paj7620.
class paj7620{
protected:

    hwlib::i2c_bus & bus;
    uint_fast8_t address;

public:
    /// \brief    
    /// standard constructor
    paj7620(hwlib::i2c_bus & bus, uint8_t address):
        bus( bus ), address( address )
    {hwlib::wait_ms(100);} //gives the terminal times to boot up


    /// \brief    
    /// Read function for the paj7620
    /// \details
    /// Since the chip has multiple registers the read function needs to write to the chip which register it wants to read before it can start reading.
    uint8_t read(uint8_t target){
        uint8_t data[] = { target };
        bus.write( address ).write( data, 1 ); 

        uint8_t buffer[1];
        int x_bytes = 1;
        bus.read( address ).read( buffer, x_bytes );

        return buffer[0];
    }


    /// \brief    
    /// Write function for the paj7620
    /// \details
    /// This function is used to write a single byte sized command to a register.
    void writeCommand( uint8_t adr, uint8_t cmd ){
       uint8_t data[] = { 
          adr, cmd
       };
       bus.write( address ).write( data, sizeof( data ) / sizeof( uint8_t ) );     
    } 


    /// \brief    
    /// Selects register bank
    void selectBank(int bank){
        writeCommand( 0xEF, uint8_t( bank ) );
    }

    
    /// \brief    
    /// function used for checking sensor
    /// \details
    /// Reads 10 times from the 2 registers that house the sensor's readings.
    /// If everything is normal it should always read 0, unless there is something wrong with the registers or the sensor itself.
    /// If everything is normal it return true, if it picks up to many readings it returns false.
    bool checkSensor(){
        int readings0 = 0;
        int readings1 = 0;

        for(int i=0;i<10;i++){
            hwlib::wait_ms(100);
            if(read(0x43) != 0 ){
                readings0 += 1;
            }
        }

        for(int i=0;i<10;i++){
            hwlib::wait_ms(100);
            if(read(0x44) != 0 ){
                readings1 += 1;
            }
        }

        if(readings0 >= 2 || readings1 >= 2){
            return false;
        }
        return true;
    }

    /// \brief    
    /// function used for initialising chip
    /// \details
    /// This function is the hart of the class and need to be run before accurate readings can be given.
    /// The function takes a single argument, if not provided it will be set to true. 
    /// This variable determines if output is provided, true = output, false = no output.
    /// The function does a couple of tasks including: testing if the registers, bank and sensors are in order 
    /// and finishes off with sending all commands to the appropriate registers.
    void initialise(bool cout = true){
        if(cout){
            hwlib::cout << "Initialising.. \n";
        }
        hwlib::wait_ms(500);

        uint8_t data0 = 0, data1 = 0;       
        selectBank(0);
        data0 = read(0);
        data1 = read(1);

        if(!(data0==0x20) || !(data1==0x76)){
            if(cout){
                hwlib::cout << "WARNING: Registers have incorrect default values \n";
            }
            return;
        }

        if(!checkSensor()){
            if(cout){
                hwlib::cout << "WARNING: Sensor is giving off too many readings \n";
            }
            return;
        }

        int array_size (sizeof(registerCommands)/sizeof(registerCommands[0]));
        for (int i = 0; i < array_size; i++) {
            writeCommand(registerCommands[i][0], registerCommands[i][1]);
        }

        selectBank(0);
        if(cout){
            hwlib::cout << "initialisation complete \n";
        }
    }

};


/// \brief    
/// Alternate paj7620 class for limited reading
/// \details
/// The limited_paj7620 class works almost identical to the standard class but takes a 3rd argument which determines which gesture can be read.
class limited_paj7620 : public paj7620{
private:

    uint8_t *readable;

public:

    /// \brief    
    /// standard constructor
    limited_paj7620(hwlib::i2c_bus & bus, uint8_t address, uint8_t readable[9] = {}):
        paj7620(bus, address),
        readable( readable )
    {}


    /// \brief    
    /// Read function for the paj7620
    /// \details
    /// Since the chip has multiple registers the read function needs to write to the chip which register it wants to read before it can start reading.
    /// After reading the register is checks if the reading is in the readable variable if that is the case it returns the reading if not it returns 0.
    uint8_t read(uint8_t target){
        uint8_t data[] = { target };
        bus.write( address ).write( data, 1 ); 

        uint8_t buffer[1];
        int x_bytes = 1;
        bus.read( address ).read( buffer, x_bytes );

        for(unsigned int i=0; i<(sizeof(readable)/sizeof(readable[0])); i++){
            if(buffer[0]==readable[i]){
                return buffer[0];
            }
        }

        return 0;
    }


    /// \brief    
    /// Function returns readable
    /// \details
    /// This function returns a pointer to readable so the user can see which gestures can be read.
    uint8_t giveReadable(){
        return *readable;
    }


    /// \brief    
    /// Function sets readable
    /// \details
    /// This function overwrites the current readable with a new provided one.
    void setReadable(uint8_t *newReadable){
        for(unsigned int i=0; i<(sizeof(readable)/sizeof(readable[0])); i++){
            readable[i] = newReadable[i];
        }
    }
};


#endif // GESTURE_HPP
