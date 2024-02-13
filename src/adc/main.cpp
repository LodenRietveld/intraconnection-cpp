#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include <string.h>
#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h>

#include <zmq.hpp>

#include "util/util.hpp"
#include "adc/mcp3424.hpp"

// #define debug_msg


int
main(int argc, char** argv)
{
    using namespace std::chrono_literals;
    
    zmq::context_t zmq_ctx;
    zmq::socket_t sock(zmq_ctx, zmq::socket_type::radio);
    sock.set(zmq::sockopt::ipv6, 1);
    sock.connect("udp://::1:5555");

    try {
        mcp3424 adc1(0x68);
        mcp3424 adc2(0x69);
	
        std::vector<float> adc_values;

        while (true) {
	        uint8_t idx = 0;
	        bool change = false;

            if (adc1.read()) {
	           	change = true;
                for (int i = 0; i < 4; i++){
                    adc_values.push_back(adc1.get(i));
                }
            }

            if (adc2.read()) {
	        	change = true;
                for (int i = 0; i < 4; i++){
		            adc_values.push_back(adc2.get(i));
                }
            }

#ifdef debug_msg
            // change random value
            int ridx = rand() % 8;
            adc_values[ridx] = (rand() % 1000) / 100.f;
            std::cout << "changing idx " << ridx << std::endl;
            std::cout << "adc_values size " << adc_values.size() << std::endl;
#endif

	        if (change) {
                std::string msg = "msg ";
                msg.append(intra::to_string(adc_values));
                msg.append(";");

#ifdef debug_msg
                std::cout << "Sending message:" << std::endl;
                std::cout << msg << std::endl;
#endif

                sock.send(zmq::message_t(msg), zmq::send_flags::none);
	        }
            
            adc_values.clear();
            std::this_thread::sleep_for(16ms);
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
