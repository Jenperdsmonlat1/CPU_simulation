#ifndef _OPCODE_DECODER_H
#define _OPCODE_DECODER_H


#include <systemc.h>
#include "d_ff.h"
#include "gates.h"



SC_MODULE(OpcodeDecoder) {

    sc_in<bool> clk, reset;
    sc_in<sc_uint<6>> opcode;
    sc_out<bool> alu_selection, rs_selection, move_selection_port, load_selection_port, we_selection, add_instruction_selection;

    sc_signal<bool> add_d, add_q, move_d, move_q[3], store_d, store_q[2], load_d, load_q[3], rs_sig, alu_sig;
    OR3 *or3_gate;
    OR *or_gate;

    D_FLIP_FLOP<bool> *add_ff, *store_ff[2], *load_ff[3], *move_ff[3];

    void read_opcode(void) {

        add_d.write(false);
        store_d.write(false);
        move_d.write(false);
        load_d.write(false);

        switch (opcode.read()) {
            case ADD: add_d.write(true); break;
            case LOAD: load_d.write(true); break;
            case STORE: store_d.write(true); break;
            case MOVE: move_d.write(true); break;
        }
    }

    void assign_output(void) {

        alu_selection.write(alu_sig.read());
        we_selection.write(store_q[1].read());
        rs_selection.write(rs_sig.read());
        move_selection_port.write(move_q[2].read());
        load_selection_port.write(load_q[2].read());
        add_instruction_selection.write(add_q.read());
    }

    SC_CTOR(OpcodeDecoder) {

        add_ff = new D_FLIP_FLOP<bool>("add_flip_flop");
        add_ff->clk(clk);
        add_ff->d(add_d);
        add_ff->q(add_q);
        add_ff->reset(reset);

        
        for (uint8_t i = 0; i < 3; i++) {

            load_ff[i] = new D_FLIP_FLOP<bool>(("load_flip_flop_" + std::to_string(i)).c_str());
            load_ff[i]->clk(clk);
            load_ff[i]->reset(reset);
            load_ff[i]->d(i == 0 ? load_d : load_q[i - 1]);
            load_ff[i]->q(load_q[i]);
        }

        for (uint8_t i = 0; i < 3; i++) {

            move_ff[i] = new D_FLIP_FLOP<bool>(("move_flip_flop_" + std::to_string(i)).c_str());
            move_ff[i]->clk(clk);
            move_ff[i]->reset(reset);
            move_ff[i]->d(i == 0 ? move_d : move_q[i - 1]);
            move_ff[i]->q(move_q[i]);
        }

        for (uint8_t i = 0; i < 2; i++) {

            store_ff[i] = new D_FLIP_FLOP<bool>(("store_flip_flop_" + std::to_string(i)).c_str());
            store_ff[i]->clk(clk);
            store_ff[i]->reset(reset);
            store_ff[i]->d(i == 0 ? store_d : store_q[i - 1]);
            store_ff[i]->q(store_q[i]);
        }

        or3_gate = new OR3("or_3");
        or3_gate->a(add_q);
        or3_gate->b(load_q[0]);
        or3_gate->c(store_q[0]);
        or3_gate->output(alu_sig);

        or_gate = new OR("or");
        or_gate->a(add_q);
        or_gate->b(load_q[0]);
        or_gate->output(rs_sig);

        SC_METHOD(assign_output);
        sensitive << alu_sig << rs_sig << load_q[2] << move_q[2] << store_q[1] << add_instruction_selection;

        SC_METHOD(read_opcode);
        sensitive << opcode;
    }
};

#endif
