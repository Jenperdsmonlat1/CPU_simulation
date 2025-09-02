#ifndef _MUX_H
#define _MUX_H


#include <systemc.h>


SC_MODULE(Mux) {

    sc_in<sc_uint<5>> one, zero;
    sc_in<bool> select_add_port;
    sc_out<sc_uint<5>> port_selected;


    void process(void) {

        if (select_add_port.read()) port_selected.write(one.read());
        else port_selected.write(zero.read());
    }

    SC_CTOR(Mux) {
        
        SC_METHOD(process);
        sensitive << one << zero << select_add_port;
    }
};


#endif
