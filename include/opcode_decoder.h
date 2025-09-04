#ifndef _OPCODE_DECODER_H
#define _OPCODE_DECODER_H


#include <systemc.h>
#include "d_ff.h"
#include "gates.h"



SC_MODULE(OpcodeDemux) {

    sc_in<sc_uint<6>> opcode;
    sc_out<sc_bv<4>> line_selected;

    void process(void) {

        sc_bv<4> wl = 0;
        wl[opcode.read()] = '1';

        line_selected.write(wl);
    }

    SC_CTOR(OpcodeDemux) {

        SC_METHOD(process);
        sensitive << opcode;
    }
};


SC_MODULE(OpcodeDecoder) {

    sc_in<bool> clk;
    sc_in<sc_uint<6>> opcode;
    sc_out<sc_bv<4>> line;

    sc_signal<sc_bv<4>> line_selected;
    sc_signal<sc_uint<1>> line_selected_bit[4];
    sc_signal<sc_uint<4>> rf;

    OpcodeDemux *demux;
    D_FLIP_FLOP<1> *d_ff_opcode[4];
    OR3 *load_store_or_add_select_port;
    OR *load_or_add_select_port;


    void process(void) {
        return;
    }

    SC_CTOR(OpcodeDecoder) {

        demux = new OpcodeDemux("demux");
        load_store_or_add_select_port = new OR3("or3");
        load_or_add_select_port = new OR("or");

        demux->opcode(opcode);
        demux->line_selected(line_selected);

        for (uint8_t i = 0; i < 4; i++) {

            line_selected_bit[i].write(line_selected.read()[i] == '1' ? 1 : 0);
            d_ff_opcode[i] = new D_FLIP_FLOP<1>("d_ff");
            d_ff_opcode[i]->clk(clk);
            d_ff_opcode[i]->d(line_selected_bit[i]);
            d_ff_opcode[i]->q(line_selected_bit[i]);
        }

        SC_METHOD(process);
    }
};

#endif
