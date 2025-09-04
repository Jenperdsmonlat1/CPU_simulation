#ifndef _GATES_H
#define _GATES_H


#include <systemc.h>


SC_MODULE(NAND) {

    sc_in<bool> a, b;
    sc_out<bool> output;

    void process(void) {

        output.write(!(a.read() && b.read()));
    }

    SC_CTOR(NAND) {

        SC_METHOD(process);
        sensitive << a, b;
    }
};

SC_MODULE(AND) {
    
    sc_in<bool> a, b;
    sc_out<bool> output;

    void process(void) {

        output.write(a.read() && b.read());
    }

    SC_CTOR(AND) {

        SC_METHOD(process);
        sensitive << a, b;
    }
};

SC_MODULE(NOR) {

    sc_in<bool> a, b;
    sc_out<bool> output;

    void process(void) {

        output.write(!(a.read() || b.read()));
    }

    SC_CTOR(NOR) {

        SC_METHOD(process);
        sensitive << a, b;
    }
};

SC_MODULE(OR) {

    sc_in<bool> a, b;
    sc_out<bool> output;

    void process(void) {

        output.write(a.read() || b.read());
    }

    SC_CTOR(OR) {

        SC_METHOD(process);
        sensitive << a, b;
    }
};

SC_MODULE(OR3) {

    sc_in<bool> a, b, c;
    sc_out<bool> output;

    void process(void) {

        output.write(a.read() || b.read() || c.read());
    }

    SC_CTOR(OR3) {

        SC_METHOD(process);
        sensitive << a, b << c;
    }
};

SC_MODULE(XOR) {

    sc_in<bool> a, b;
    sc_out<bool> output;

    void process(void) {

        output.write(a.read() ^ b.read());
    }

    SC_CTOR(XOR) {

        SC_METHOD(process);
        sensitive << a, b;
    }
};

SC_MODULE(XNOR) {

    sc_in<bool> a, b;
    sc_out<bool> output;

    void process(void) {

        output.write(!(a.read() ^ b.read()));
    }

    SC_CTOR(XNOR) {

        SC_METHOD(process);
        sensitive << a, b;
    }
};

SC_MODULE(NOT) {

    sc_in<bool> a;
    sc_out<bool> output;

    void process(void) {

        output.write(!a.read());
    }

    SC_CTOR(NOT) {

        SC_METHOD(process);
        sensitive << a;
    }
};

#endif
