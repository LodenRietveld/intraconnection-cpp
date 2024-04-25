#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include <string.h>
#include <stdlib.h> 
#include <unistd.h>

#include <zmq.hpp>

#include "util/util.hpp"
#include "util/mock_adc.hpp"
#include "adc/mcp3424.hpp"
#include "adc/adcs.hpp"

#ifdef MOCK_VALUES
using adc_t = mock_adc;
#else
using adc_t = mcp3424;
#endif

serial_t Serial;

#define DEBUG_LOG

#ifdef DEBUG_LOG
void
debug(const std::string& msg, bool endl = true)
{
    std::cout << msg;
    if (endl)
        std::cout << std::endl;
}
#else
void
debug(const std::string& msg, bool endl = true)
{
}
#endif

int
main(int argc, char** argv)
{
    using namespace std::chrono_literals;
    
    zmq::context_t zmq_ctx;
    zmq::socket_t sock(zmq_ctx, zmq::socket_type::radio);
    sock.set(zmq::sockopt::ipv6, 1);
    sock.connect("udp://::1:5555");

    try {
        adcs<adc_t> adcs(0x68, 0x69, true);

        while (true) {
	        if (adcs.read()) {
                auto msg = adcs.to_string();

                debug(msg);

                sock.send(zmq::message_t(msg), zmq::send_flags::none);
	        }
            
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
