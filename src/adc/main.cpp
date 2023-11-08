#include <iostream>
#include <stdexcept>

#include "adc/mcp3424.hpp"

int
main(int argc, char** argv)
{
    try {
        mcp3424 adc1(0x68);
        mcp3424 adc2(0x69);

        std::cout << "Adcs initialized, starting read" << std::endl;

        //reads do not work, check i2c bus comms
        while (true) {
            if (adc1.read()) {
                for (int i = 0; i < 4; i++){
                    // std::cout << "Read value: " << adc1.get(i) << std::endl;
                }
            }

            if (adc2.read()) {
                for (int i = 0; i < 4; i++){
                    // std::cout << "Read value: " << adc2.get(i) << std::endl;
                }
            }
        }
    } catch (std::runtime_error& e) {
        std::cout << "Error initializing adcs: " << e.what() << std::endl;
        exit(1);
    } catch (...) {
        std::cout << "Unknown exception." << std::endl;
        exit(1);
    }

    return 0;    
}