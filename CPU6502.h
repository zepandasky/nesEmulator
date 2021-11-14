//
// Created by zep on 11/13/21.
//

#ifndef INC_6502EMULATOR_CPU6502_H
#define INC_6502EMULATOR_CPU6502_H
#include <vector>
#include <string>
#include <cstdint>
#include <map>

class Bus;
class CPU6502
{
public:
    CPU6502();
    ~CPU6502();

    enum FLAGS6502
    {
        C = (1 << 0), //Carry bit
        Z = (1 << 1), //Zero
        I = (1 << 2), //Disable interrupts
        D = (1 << 3), //Decimal mode (unused at the moment)
        B = (1 << 4), //Break
        U = (1 << 5), //Unused
        V = (1 << 6), //Overflow
        N = (1 << 7), //Negative
    };

    uint8_t a      = 0x00;      //Accumulator register
    uint8_t x      = 0x00;      //X register
    uint8_t y      = 0x00;      //Y register
    uint8_t stkp   = 0x00;   //Stack pointer
    uint16_t pc    = 0x00;     //Program Counter
    uint8_t status = 0x00; //Status register

    void ConnectBus(Bus *n) { bus = n; }

    #pragma region Addressing_mode
    uint8_t ABS();
    uint8_t ABX();
    uint8_t ABY();
    uint8_t IMM();
    uint8_t IMP();
    uint8_t IND();
    uint8_t IZX();
    uint8_t IZY();
    uint8_t REL();
    uint8_t ZP0();
    uint8_t ZPX();
    uint8_t ZPY();
    #pragma endregion Addressing_mode

    #pragma region Instructions
    uint8_t ADC();
    uint8_t AND();
    uint8_t ASL();
    uint8_t BCC();
    uint8_t BCS();
    uint8_t BEQ();
    uint8_t BIT();
    uint8_t BMI();
    uint8_t BNE();
    uint8_t BPL();
    uint8_t BRK();
    uint8_t BVC();
    uint8_t BVS();
    uint8_t CLC();
    uint8_t CLD();
    uint8_t CLI();
    uint8_t CLV();
    uint8_t CMP();
    uint8_t CPX();
    uint8_t CPY();
    uint8_t DEC();
    uint8_t DEX();
    uint8_t DEY();
    uint8_t EOR();
    uint8_t INC();
    uint8_t INX();
    uint8_t INY();
    uint8_t JMP();
    uint8_t JSR();
    uint8_t LDA();
    uint8_t LDX();
    uint8_t LDY();
    uint8_t LSR();
    uint8_t NOP();
    uint8_t ORA();
    uint8_t PHA();
    uint8_t PHP();
    uint8_t PLA();
    uint8_t PLP();
    uint8_t ROL();
    uint8_t ROR();
    uint8_t RTI();
    uint8_t RTS();
    uint8_t SBC();
    uint8_t SEC();
    uint8_t SED();
    uint8_t SEI();
    uint8_t STA();
    uint8_t STX();
    uint8_t STY();
    uint8_t TAX();
    uint8_t TAY();
    uint8_t TSX();
    uint8_t TXA();
    uint8_t TXS();
    uint8_t TYA();
    #pragma endregion Instructions

    //Illegal opcode
    uint8_t XXX();

    void clock();
    void reset();
    void irq();
    void nmi(); //non maskable interrupbt
    bool complete();

    uint8_t fetch(); //function to fetch data
    uint8_t fetched = 0x00;

    //Memory address
    uint16_t addr_abs = 0x0000;
    uint16_t addr_rel = 0x00; //Branch instructions work with relative offset from current address
    uint8_t opcode    = 0x00;
    uint8_t cycles    = 0; //Counts how many cycles the instruction has remaining

    /*Variables for conveince */
    uint16_t temp     = 0x0000;
    uint64_t clock_count = 0;

    std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);
private:
    /* Pointer to the memory bus */
    Bus *bus = nullptr;

    /* Wrappers for reading/writing to memory */
    uint8_t read(uint16_t a);
    void    write(uint16_t a, uint8_t d);

    // Functions to access status register
    uint8_t getFlag(FLAGS6502 f);
    void    setFlag(FLAGS6502 f, bool V);

    struct INSTRUCTION
    {
        std::string name;
        uint8_t (CPU6502::*operate)(void) = nullptr;  //Function pointer to opcode function to be performed
        uint8_t (CPU6502::*addrmode)(void) = nullptr; //Function pointer to address mode
        uint8_t cycles = 0;                           //Cycles the instruction requires
    };

    std::vector<INSTRUCTION> lookup;
};

#endif //INC_6502EMULATOR_CPU6502_H
