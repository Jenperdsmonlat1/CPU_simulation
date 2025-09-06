#ifndef _MONITOR_H
#define _MONITOR_H


/*#include <iostream>
#include <systemc.h>


SC_MODULE(Monitor) {

    sc_in<sc_uint<32>> pc_output;
    sc_in<sc_uint<32>> im_output;
    sc_in<bool> clk, alu_selection, rs_selection, move_selection_port, load_selection_port, we_selection;

    sc_in<sc_uint<5>> rs1, rs2, rd;
    sc_in<sc_uint<6>> opcode;
    sc_in<sc_uint<16>> immediate;
    sc_in<sc_uint<32>> d_out1, d_out2, d_in;


    void process(void) {

        std::cout << "PC: " << pc_output.read() << " Instruction: " << std::hex << im_output.read() << std::endl;
        std::cout << "Opcode: " << opcode.read() << " RS1: " << std::hex << rs1.read() << " RS2: " << rs2.read() << " RD: " << rd.read() << " Immediate: " << immediate.read() << std::endl;
        std::cout << "D_Out1: " << d_out1.read() << " D_Out2: " << d_out2.read() << std::endl;

        std::cout << "Output from Opcode Decoder :" << std::endl;
        std::cout << "ALU Selection: " << alu_selection.read() << std::endl;
        std::cout << "RS Selection: " << rs_selection.read() << std::endl;
        std::cout << "MOVE Selection: " << move_selection_port.read() << std::endl;
        std::cout << "LOAD Selection: " << load_selection_port.read() << std::endl;
        std::cout << "WE Selection: " << we_selection.read() << std::endl;

        std::cout << std::endl;
    }

    SC_CTOR(Monitor) {

        SC_METHOD(process);
        sensitive << clk.pos();

    }
};*/

#include <iostream>
#include <deque>
#include <systemc.h>
#include "opcode.h"



SC_MODULE(Monitor) {

    sc_in<sc_uint<32>> pc_output;
    sc_in<sc_uint<32>> im_output;
    sc_in<bool> clk, alu_selection, rs_selection, move_selection_port, load_selection_port, we_selection;

    sc_in<sc_uint<5>> rs1, rs2, rd;
    sc_in<sc_uint<6>> opcode;
    sc_in<sc_uint<16>> immediate;
    sc_in<sc_uint<32>> d_out1, d_out2, d_in;

    struct InstrSnapshot {
        sc_uint<32> pc;
        sc_uint<32> instr;
        sc_uint<6>  opcode;
        sc_uint<5>  rs1, rs2, rd;
        sc_uint<16> imm;
        sc_uint<32> d1, d2;
    };

    std::deque<InstrSnapshot> history;

    int latency_for(sc_uint<6> opc) {
        if (opc == ADD)    return 1; // ADD : 1 cycle
        if (opc == STORE)  return 2; // STORE: 2 cycles (si c'est bien le cas)
        if (opc == MOVE)   return 3; // MOVE: 3 cycles
        if (opc == LOAD)   return 3; // LOAD: 3 cycles
        return 1; // fallback
    }


    void process(void) {
        InstrSnapshot snap {
            pc_output.read(),
            im_output.read(),
            opcode.read(),
            rs1.read(),
            rs2.read(),
            rd.read(),
            immediate.read(),
            d_out1.read(),
            d_out2.read()
        };

        // pousser l'instruction courante
        history.push_back(snap);

        // on parcourt l'historique pour voir si la plus vieille est "mûre"
        if (!history.empty()) {
            InstrSnapshot &oldest = history.front();
            int latency = latency_for(oldest.opcode);


            // on affiche uniquement si on a attendu assez de cycles
            if ((int)history.size() >= latency) {
                std::cout << "PC: " << oldest.pc
                          << " Instruction: " << std::hex << oldest.instr << std::endl;
                std::cout << "Opcode: " << oldest.opcode
                          << " RS1: " << std::hex << oldest.rs1
                          << " RS2: " << oldest.rs2
                          << " RD: " << oldest.rd
                          << " Immediate: " << oldest.imm << std::endl;
                std::cout << "D_Out1: " << oldest.d1
                          << " D_Out2: " << oldest.d2 << std::endl;

                std::cout << "Output from Opcode Decoder :" << std::endl;
                std::cout << "ALU Selection: " << alu_selection.read() << std::endl;
                std::cout << "RS Selection: " << rs_selection.read() << std::endl;
                std::cout << "MOVE Selection: " << move_selection_port.read() << std::endl;
                std::cout << "LOAD Selection: " << load_selection_port.read() << std::endl;
                std::cout << "WE Selection: " << we_selection.read() << std::endl;

                std::cout << std::endl;

                // retirer de l’historique après affichage
                history.pop_front();
            }
        }
    }

    SC_CTOR(Monitor) {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

#endif
