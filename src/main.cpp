#include <iostream>
#include <vector>
#include <systemc.h>
#include "pc.h"
#include "monitor.h"
#include "instruction_memory.h"



int sc_main(int argc, char **argv) {

    sc_clock clk("clock", 5, SC_MS);
    sc_signal<sc_uint<32>> output, instruction;

    PC pc("pc");
    Monitor monitor("monitor");
    InstructionMemory<5> im("instruction_memory");

    pc.clock(clk);
    pc.output(output);
    im.pc_output(output);
    im.im_output(instruction);
    monitor.clk(clk);
    monitor.pc_output(output);
    monitor.im_output(instruction);


    std::vector<sc_uint<32>> program = {
        0xCCCCCCCC,
        0xAAAAAAAA,
        0xFFFFFFFF,
        0xDDDDDDDD,
        0x1D1D1d1D
    };

    im.load_instructions(program);

    sc_start(25, SC_MS);
    return EXIT_SUCCESS;
}