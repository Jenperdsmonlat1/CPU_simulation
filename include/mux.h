#ifndef _MUX_H
#define _MUX_H


#include <systemc.h>


template<typename N>
SC_MODULE(Mux) {

    sc_in<N> one, zero;
    sc_in<bool> select_add_port;
    sc_out<N> port_selected;


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
