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


SC_MODULE(DoubleMux) {

    sc_in<bool> select_port_0, select_port_1;
    sc_in<sc_uint<32>> port_0_data, port_1_data, port_2_data;
    sc_out<sc_uint<32>> output;


    void process(void) {

        if (select_port_0.read()) output.write(port_0_data.read());
        else if (select_port_1.read()) output.write(port_1_data.read());
        else output.write(port_2_data.read());
    }

    SC_CTOR(DoubleMux) {

        SC_METHOD(process);
        sensitive << select_port_0 << select_port_1 << port_0_data << port_1_data << port_2_data;
    };
};


#endif
