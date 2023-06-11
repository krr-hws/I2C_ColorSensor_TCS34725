// Example program connecting to the TCS34725 Color Sensor to the K64F using I2C

#include "mbed.h"

I2C i2c(I2C_SDA, I2C_SCL); //pins for I2C communication (SDA, SCL)
//Serial pc(USBTX, USBRX);

int sensor_addr = 41 << 1;

DigitalOut green(LED1);

int main() {
    //pc.baud(9600);
    green = 1; // off
    
    // Connect to the Color sensor and verify whether we connected to the correct sensor. 
    
    i2c.frequency(200000);
    
    char id_regval[1] = {146};
    char data[1] = {0};
    i2c.write(sensor_addr,id_regval,1, true);
    i2c.read(sensor_addr,data,1,false);
    
    if (data[0]==68) {
        green = 0;
        wait_us(2000); 
        green = 1;
        } else {
        green = 1; 
    }
    
    // Initialize color sensor
    
    char timing_register[2] = {129,0};
    i2c.write(sensor_addr,timing_register,2,false);
    
    char control_register[2] = {143,0};
    i2c.write(sensor_addr,control_register,2,false);
    
    char enable_register[2] = {128,3};
    i2c.write(sensor_addr,enable_register,2,false);
    
    // Read data from color sensor (Clear/Red/Green/Blue)

    char clear_reg[1] = {148};
    char clear_data[2] = {0,0};
    int clear_value;
    char red_reg[1] = {150};
    char red_data[2] = {0,0};
    int red_value;
    char green_reg[1] = {152};
    char green_data[2] = {0,0};
    int green_value;
    char blue_reg[1] = {154};
    char blue_data[2] = {0,0};
    int blue_value;
    
    while (true) { 
        clear_reg[0] = 148;
        clear_data[0] = 0;
        clear_data[1] = 0;
        i2c.write(sensor_addr,clear_reg,1, true);
        i2c.read(sensor_addr,clear_data,2, false);
        
        clear_value = ((int)clear_data[1] << 8) | clear_data[0];
        
        red_reg[0] = 150;
        red_data[0] = 0;
        red_data[1] = 0;
        i2c.write(sensor_addr,red_reg,1, true);
        i2c.read(sensor_addr,red_data,2, false);
        
        red_value = ((int)red_data[1] << 8) | red_data[0];
        
        green_reg[0] = 152;
        green_data[0] = 0;
        green_data[1] = 0;
        i2c.write(sensor_addr,green_reg,1, true);
        i2c.read(sensor_addr,green_data,2, false);
        
        green_value = ((int)green_data[1] << 8) | green_data[0];
        
        blue_reg[0] = 154;
        blue_data[0] = 0;
        blue_data[1] = 0;
        i2c.write(sensor_addr,blue_reg,1, true);
        i2c.read(sensor_addr,blue_data,2, false);
        
        blue_value = ((int)blue_data[1] << 8) | blue_data[0];
        
        // print sensor readings
        
        printf("Clear (%d), Red (%d), Green (%d), Blue (%d)\n", clear_value, red_value, green_value, blue_value);
        wait_us(500000);
    }
    
}