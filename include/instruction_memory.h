#ifndef _INSTRUCTION_MEMORY_H
#define _INSTRUCTION_MEMORY_H


#include <systemc.h>
#include <vector>
#include <algorithm>


template<int N>
SC_MODULE(InstructionMemory) {

    sc_in<sc_uint<32>> pc_output;
    sc_out<sc_uint<32>> im_output;

    sc_uint<32> memory[N];

    void process(void) {

        im_output.write(memory[pc_output.read()]);
    }

    void load_instructions(std::vector<sc_uint<32>> &instructions) {

        for (uint32_t i = 0; i < instructions.size(); i++) memory[i] = instructions[i];
    }

    SC_CTOR(InstructionMemory) {

        SC_METHOD(process);
        sensitive << pc_output;
    }
};

#endif
