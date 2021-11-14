//
// Created by zep on 11/13/21.
// Instruction implementation is based on the following two links:
//https://www.masswerk.at/6502/6502_instruction_set.html#DEC
//http://www.6502.org/tutorials/6502opcodes.html#BIT
#include "../header_files/CPU6502.h"
#include "../header_files/Bus.h"

CPU6502::CPU6502()
{
    //Corresponds to the CPU6502 datasheet insturction table
    using a = CPU6502;
    lookup =
            {
                    {"BRK", &a::BRK, &a::IMM, 7},
                    {"ORA", &a::ORA, &a::IZX, 6},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 3},
                    {"ORA", &a::ORA, &a::ZP0, 3},
                    {"ASL", &a::ASL, &a::ZP0, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"PHP", &a::PHP, &a::IMP, 3},
                    {"ORA", &a::ORA, &a::IMM, 2},
                    {"ASL", &a::ASL, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"ORA", &a::ORA, &a::ABS, 4},
                    {"ASL", &a::ASL, &a::ABS, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"BPL", &a::BPL, &a::REL, 2},
                    {"ORA", &a::ORA, &a::IZY, 5},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"ORA", &a::ORA, &a::ZPX, 4},
                    {"ASL", &a::ASL, &a::ZPX, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"CLC", &a::CLC, &a::IMP, 2},
                    {"ORA", &a::ORA, &a::ABY, 4},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"ORA", &a::ORA, &a::ABX, 4},
                    {"ASL", &a::ASL, &a::ABX, 7},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"JSR", &a::JSR, &a::ABS, 6},
                    {"AND", &a::AND, &a::IZX, 6},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"BIT", &a::BIT, &a::ZP0, 3},
                    {"AND", &a::AND, &a::ZP0, 3},
                    {"ROL", &a::ROL, &a::ZP0, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"PLP", &a::PLP, &a::IMP, 4},
                    {"AND", &a::AND, &a::IMM, 2},
                    {"ROL", &a::ROL, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"BIT", &a::BIT, &a::ABS, 4},
                    {"AND", &a::AND, &a::ABS, 4},
                    {"ROL", &a::ROL, &a::ABS, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"BMI", &a::BMI, &a::REL, 2},
                    {"AND", &a::AND, &a::IZY, 5},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"AND", &a::AND, &a::ZPX, 4},
                    {"ROL", &a::ROL, &a::ZPX, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"SEC", &a::SEC, &a::IMP, 2},
                    {"AND", &a::AND, &a::ABY, 4},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"AND", &a::AND, &a::ABX, 4},
                    {"ROL", &a::ROL, &a::ABX, 7},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"RTI", &a::RTI, &a::IMP, 6},
                    {"EOR", &a::EOR, &a::IZX, 6},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 3},
                    {"EOR", &a::EOR, &a::ZP0, 3},
                    {"LSR", &a::LSR, &a::ZP0, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"PHA", &a::PHA, &a::IMP, 3},
                    {"EOR", &a::EOR, &a::IMM, 2},
                    {"LSR", &a::LSR, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"JMP", &a::JMP, &a::ABS, 3},
                    {"EOR", &a::EOR, &a::ABS, 4},
                    {"LSR", &a::LSR, &a::ABS, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"BVC", &a::BVC, &a::REL, 2},
                    {"EOR", &a::EOR, &a::IZY, 5},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"EOR", &a::EOR, &a::ZPX, 4},
                    {"LSR", &a::LSR, &a::ZPX, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"CLI", &a::CLI, &a::IMP, 2},
                    {"EOR", &a::EOR, &a::ABY, 4},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"EOR", &a::EOR, &a::ABX, 4},
                    {"LSR", &a::LSR, &a::ABX, 7},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"RTS", &a::RTS, &a::IMP, 6},
                    {"ADC", &a::ADC, &a::IZX, 6},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 3},
                    {"ADC", &a::ADC, &a::ZP0, 3},
                    {"ROR", &a::ROR, &a::ZP0, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"PLA", &a::PLA, &a::IMP, 4},
                    {"ADC", &a::ADC, &a::IMM, 2},
                    {"ROR", &a::ROR, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"JMP", &a::JMP, &a::IND, 5},
                    {"ADC", &a::ADC, &a::ABS, 4},
                    {"ROR", &a::ROR, &a::ABS, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"BVS", &a::BVS, &a::REL, 2},
                    {"ADC", &a::ADC, &a::IZY, 5},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"ADC", &a::ADC, &a::ZPX, 4},
                    {"ROR", &a::ROR, &a::ZPX, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"SEI", &a::SEI, &a::IMP, 2},
                    {"ADC", &a::ADC, &a::ABY, 4},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"ADC", &a::ADC, &a::ABX, 4},
                    {"ROR", &a::ROR, &a::ABX, 7},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"STA", &a::STA, &a::IZX, 6},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"STY", &a::STY, &a::ZP0, 3},
                    {"STA", &a::STA, &a::ZP0, 3},
                    {"STX", &a::STX, &a::ZP0, 3},
                    {"???", &a::XXX, &a::IMP, 3},
                    {"DEY", &a::DEY, &a::IMP, 2},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"TXA", &a::TXA, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"STY", &a::STY, &a::ABS, 4},
                    {"STA", &a::STA, &a::ABS, 4},
                    {"STX", &a::STX, &a::ABS, 4},
                    {"???", &a::XXX, &a::IMP, 4},
                    {"BCC", &a::BCC, &a::REL, 2},
                    {"STA", &a::STA, &a::IZY, 6},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"STY", &a::STY, &a::ZPX, 4},
                    {"STA", &a::STA, &a::ZPX, 4},
                    {"STX", &a::STX, &a::ZPY, 4},
                    {"???", &a::XXX, &a::IMP, 4},
                    {"TYA", &a::TYA, &a::IMP, 2},
                    {"STA", &a::STA, &a::ABY, 5},
                    {"TXS", &a::TXS, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"???", &a::NOP, &a::IMP, 5},
                    {"STA", &a::STA, &a::ABX, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"LDY", &a::LDY, &a::IMM, 2},
                    {"LDA", &a::LDA, &a::IZX, 6},
                    {"LDX", &a::LDX, &a::IMM, 2},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"LDY", &a::LDY, &a::ZP0, 3},
                    {"LDA", &a::LDA, &a::ZP0, 3},
                    {"LDX", &a::LDX, &a::ZP0, 3},
                    {"???", &a::XXX, &a::IMP, 3},
                    {"TAY", &a::TAY, &a::IMP, 2},
                    {"LDA", &a::LDA, &a::IMM, 2},
                    {"TAX", &a::TAX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"LDY", &a::LDY, &a::ABS, 4},
                    {"LDA", &a::LDA, &a::ABS, 4},
                    {"LDX", &a::LDX, &a::ABS, 4},
                    {"???", &a::XXX, &a::IMP, 4},
                    {"BCS", &a::BCS, &a::REL, 2},
                    {"LDA", &a::LDA, &a::IZY, 5},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"LDY", &a::LDY, &a::ZPX, 4},
                    {"LDA", &a::LDA, &a::ZPX, 4},
                    {"LDX", &a::LDX, &a::ZPY, 4},
                    {"???", &a::XXX, &a::IMP, 4},
                    {"CLV", &a::CLV, &a::IMP, 2},
                    {"LDA", &a::LDA, &a::ABY, 4},
                    {"TSX", &a::TSX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 4},
                    {"LDY", &a::LDY, &a::ABX, 4},
                    {"LDA", &a::LDA, &a::ABX, 4},
                    {"LDX", &a::LDX, &a::ABY, 4},
                    {"???", &a::XXX, &a::IMP, 4},
                    {"CPY", &a::CPY, &a::IMM, 2},
                    {"CMP", &a::CMP, &a::IZX, 6},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"CPY", &a::CPY, &a::ZP0, 3},
                    {"CMP", &a::CMP, &a::ZP0, 3},
                    {"DEC", &a::DEC, &a::ZP0, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"INY", &a::INY, &a::IMP, 2},
                    {"CMP", &a::CMP, &a::IMM, 2},
                    {"DEX", &a::DEX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"CPY", &a::CPY, &a::ABS, 4},
                    {"CMP", &a::CMP, &a::ABS, 4},
                    {"DEC", &a::DEC, &a::ABS, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"BNE", &a::BNE, &a::REL, 2},
                    {"CMP", &a::CMP, &a::IZY, 5},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"CMP", &a::CMP, &a::ZPX, 4},
                    {"DEC", &a::DEC, &a::ZPX, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"CLD", &a::CLD, &a::IMP, 2},
                    {"CMP", &a::CMP, &a::ABY, 4},
                    {"NOP", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"CMP", &a::CMP, &a::ABX, 4},
                    {"DEC", &a::DEC, &a::ABX, 7},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"CPX", &a::CPX, &a::IMM, 2},
                    {"SBC", &a::SBC, &a::IZX, 6},
                    {"???", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"CPX", &a::CPX, &a::ZP0, 3},
                    {"SBC", &a::SBC, &a::ZP0, 3},
                    {"INC", &a::INC, &a::ZP0, 5},
                    {"???", &a::XXX, &a::IMP, 5},
                    {"INX", &a::INX, &a::IMP, 2},
                    {"SBC", &a::SBC, &a::IMM, 2},
                    {"NOP", &a::NOP, &a::IMP, 2},
                    {"???", &a::SBC, &a::IMP, 2},
                    {"CPX", &a::CPX, &a::ABS, 4},
                    {"SBC", &a::SBC, &a::ABS, 4},
                    {"INC", &a::INC, &a::ABS, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"BEQ", &a::BEQ, &a::REL, 2},
                    {"SBC", &a::SBC, &a::IZY, 5},
                    {"???", &a::XXX, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 8},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"SBC", &a::SBC, &a::ZPX, 4},
                    {"INC", &a::INC, &a::ZPX, 6},
                    {"???", &a::XXX, &a::IMP, 6},
                    {"SED", &a::SED, &a::IMP, 2},
                    {"SBC", &a::SBC, &a::ABY, 4},
                    {"NOP", &a::NOP, &a::IMP, 2},
                    {"???", &a::XXX, &a::IMP, 7},
                    {"???", &a::NOP, &a::IMP, 4},
                    {"SBC", &a::SBC, &a::ABX, 4},
                    {"INC", &a::INC, &a::ABX, 7},
                    {"???", &a::XXX, &a::IMP, 7},
            };
}

bool CPU6502::complete()
{
    return cycles == 0;
}

CPU6502::~CPU6502()
{
}

uint8_t CPU6502::read(uint16_t a)
{
    return bus->read(a, false);
}

void CPU6502::write(uint16_t a, uint8_t d)
{

    return bus->write(a, d);
}

void CPU6502::clock()
{
    if (cycles == 0)
    {
        opcode = read(pc);
        pc++;

        // Always set the unused status flag bit to 1
        setFlag(U, true);

        //Get starting number of cycles
        cycles = lookup[opcode].cycles;
        uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();
        //The operation returns the number of additional cycles if needed
        uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();


        cycles += (additional_cycle1 & additional_cycle2);
        clock_count++;
    }
    cycles--;
}

void CPU6502::reset()
{
    addr_abs = 0xFFFC;
    uint16_t lo = read(addr_abs + 0);
    uint16_t hi = read(addr_abs + 1);

    pc = (hi << 8) | lo;

    //reset registers
    a = 0;
    x = 0;
    y = 0;
    stkp = 0xFD;
    status = 0x00 | U;

    //clear helper variables
    addr_rel = 0x0000;
    addr_abs = 0x0000;
    fetched = 0x00;

    cycles = 8;
}
void CPU6502::setFlag(FLAGS6502 f, bool v)
{
    if (v)
        status |= f;
    else
        status &= ~f;
}

uint8_t CPU6502::getFlag(CPU6502::FLAGS6502 f) {
    return (status & f) > 0 ? 1 : 0;
}

// Addressing Modes

//read is 8 bit
//16 bit address is stored as two 8 bit variables
//DEFINITION OF addressing mode is: OPC $LLHH
//So first read low byte then high byte and construct them together
uint8_t CPU6502::ABS()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    return 0;
}

uint8_t CPU6502::ABX()
{

    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    addr_abs += x;

    //If the high byte of the absolute address added with the x register
    // is different from the original hi byte, the page has changed requiring an additional clock cycle
    if ((addr_abs & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Same as ABX but using y register
uint8_t CPU6502::ABY()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    addr_abs += y;

    //If the high byte of the absolute address added with the x register
    // is different from the original hi byte, the page has changed requiring an additional clock cycle
    if ((addr_abs & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Loads next byte
uint8_t CPU6502::IMM()
{
    addr_abs = pc++;
    return 0;
}

// Implied means that the operand is implied in the instruction itself
// Example Push Accumulator instruction (PHA) has no operand
uint8_t CPU6502::IMP()
{
    fetched = a;
    return 0;
}

uint8_t CPU6502::IND()
{
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    uint16_t ptr = (hi << 8) | lo;

    if (lo == 0x00FF) // Simulate page boundary hardware bug
    {
        addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
    }
    else // Behave normally
    {
        addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
    }

    return 0;
}

uint8_t CPU6502::IZX()
{
    uint16_t t = read(pc);
    pc++;

    uint16_t lo = read((t + (uint16_t)x) & 0x00FF);
    uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);
    addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t CPU6502::IZY()
{
    //pc has the index from which the actual value should be read
    uint16_t t = read(pc);
    pc++;

    //Read the contents
    uint16_t lo = read((uint16_t)t & 0x00FF);
    uint16_t hi = read((uint16_t)(t + +1) & 0x00FF);

    addr_abs = (hi << 8) | lo;

    //Add y to the contents
    addr_abs += y;

    return 0;
}
uint8_t CPU6502::REL()
{
    addr_rel = read(pc);
    pc++;

    if (addr_rel & 0x80)
        addr_rel |= 0xFF00;
    return 0;
}
//Zero page indexing
uint8_t CPU6502::ZP0()
{
    addr_abs = read(pc);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

// Zero page X indexed
uint8_t CPU6502::ZPX()
{
    addr_abs = (read(pc) + x);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

// Zero page Y indexed
uint8_t CPU6502::ZPY()
{
    addr_abs = (read(pc) + y);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

/* Read byte from current addr_abs*/
uint8_t CPU6502::fetch()
{
    if (!(lookup[opcode].addrmode == &CPU6502::IMP))
        fetched = read(addr_abs);
    return fetched;
}

/* Write byte to current addr_abs*/
void CPU6502::writeToFetchAddress(uint8_t val)
{
    if (!(lookup[opcode].addrmode == &CPU6502::IMP))
        write(addr_abs, val);
}

/**********************************************************/
/**********************INSTRUCTIONS************************/
/**********************************************************/
uint8_t CPU6502::ADC()
{
    fetch();

    //Instruction
    temp = (uint16_t)a + (uint16_t)fetched + getFlag(C);

    //Set carry flag
    setFlag(C, temp > 255);

    //set zero flag
    setFlag(Z, temp == 0x00);

    //set negative flag, if MSB is set nubmer is negative
    setFlag(N, temp & 0x80);

    setFlag(V, ((((uint16_t)a ^ temp) & ((uint16_t)fetched ^ temp)) & 0x80));

    a = temp & 0x00FF;

    return 1;
}

/* And memomory with accumulator */
uint8_t CPU6502::AND()
{
    fetch();

    a = a & fetched;

    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);

    return 1;
}

/* Arithmetic shift left */
uint8_t CPU6502::ASL()
{
    fetch();

    temp = (uint16_t)fetched << 1;

    setFlag(N, temp & 0x80);
    setFlag(Z, temp == 0x00);
    setFlag(C, temp & 0x100);

    //ASL only write to accumulator if implied mode is used else it writes to memory on the address
    if (lookup[opcode].addrmode == &CPU6502::IMP)
    {
        a = temp & 0x00FF;
    }
    else
    {
        write(addr_abs, temp & 0x00FF);
    }

    return 0;
}

/* Branch on carry clear */
uint8_t CPU6502::BCC()
{
    if(getFlag(C) == 0)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

/* Branch on carry set */
uint8_t CPU6502::BCS() {
    if(getFlag(C) == 1)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

/* Branch on zero set */
uint8_t CPU6502::BEQ() {
    if(getFlag(Z) == 1)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

/* Test bits in memory with accumulator */
uint8_t CPU6502::BIT() {
    fetch();

    setFlag(Z, ((fetched & a) & 0x00FF )== 0);
    setFlag(N, (fetched & (1 << 7) == 1));
    setFlag(V, (fetched & (1 << 6) == 1));

    return 0;
}

/* Branch on result minus */
uint8_t CPU6502::BMI() {
    if(getFlag(N) == 1)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}
 /* Branch on result not zero */
uint8_t CPU6502::BNE() {
    if(getFlag(Z) == 0)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

/* Branch on result plus */
uint8_t CPU6502::BPL() {
    if(getFlag(N) == 0)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU6502::BRK() {
    return 0;
}

/* Branch on overflow clear */
uint8_t CPU6502::BVC() {
    if(getFlag(V) == 0)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

/* Branch on overflow set */
uint8_t CPU6502::BVS() {
    if(getFlag(V) == 1)
    {
        addr_abs = pc + addr_rel;
        cycles++;

        /* If branch goes to different page the add extra cycle */
        if(pc & 0xFF00 != addr_abs & 0xFF00)
        {
            cycles++;
        }

        pc = addr_abs;
    }
    return 0;
}

/* Clear carry flag */
uint8_t CPU6502::CLC() {
    setFlag(C, 0);
    return 0;
}

/* Clear decimal flag */
uint8_t CPU6502::CLD() {
    setFlag(D, 0);
    return 0;
}

/* Clear interupt flag */
uint8_t CPU6502::CLI() {
    setFlag(I, 0);
    return 0;
}

/* Clear overflow flag */
uint8_t CPU6502::CLV() {
    setFlag(V, 0);
    return 0;
}

/* Compare with accumulator */
uint8_t CPU6502::CMP() {
    fetch();

    setFlag(Z, ((fetched == a) & 0x00FF) == 0x0000);
    setFlag(C, fetched >= a);
    setFlag(N, a & (1 << 7));

    return 1;
}

/* Compare with y register */
uint8_t CPU6502::CPX() {
    fetch();

    setFlag(Z, ((fetched == x) & 0x00FF) == 0x0000);
    setFlag(C, fetched >= x);
    setFlag(N, x & (1 << 7));

    return 1;
}

/* Compare with x register */
uint8_t CPU6502::CPY() {
    fetch();

    setFlag(Z, ((fetched == y) & 0x00FF) == 0x0000);
    setFlag(C, fetched >= y);
    setFlag(N, y & (1 << 7));

    return 1;
}

/* Decrement memory by one */
uint8_t CPU6502::DEC() {
    fetch();

    temp = (fetched - 1) & 0x00FF;

    writeToFetchAddress(temp);

    setFlag(Z, (temp & 0x00FF) == 0x0000);
    setFlag(N, temp & 0x80);
    return 0;
}

/* Decrement index X by one */
uint8_t CPU6502::DEX() {
    x = x - 1;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 0;
}

/* Decrement index Y by one */
uint8_t CPU6502::DEY() {
    y = y - 1;
    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);
    return 0;
}

/* Exclusive-OR memory with Accumulator */
uint8_t CPU6502::EOR() {
    fetch();
    a = fetched ^ a;
    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;
}

/* Incremenet memory by one */
uint8_t CPU6502::INC() {
    fetch();

    temp = (fetched + 1) & 0x00FF;

    writeToFetchAddress(temp);
    setFlag(Z, (temp & 0x00FF) == 0x0000);
    setFlag(N, temp & 0x80);

    return 0;
}

uint8_t CPU6502::INX() {
    x++;
    setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
    return 0;
}

uint8_t CPU6502::INY() {
    y++;
    setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);
    return 0;
}

uint8_t CPU6502::JMP() {
    return 0;
}

uint8_t CPU6502::JSR() {
    return 0;
}

uint8_t CPU6502::LDA() {
    return 0;
}

uint8_t CPU6502::LDX() {
    return 0;
}

uint8_t CPU6502::LDY() {
    return 0;
}

uint8_t CPU6502::LSR() {
    return 0;
}

uint8_t CPU6502::NOP() {
    return 0;
}

uint8_t CPU6502::ORA() {
    return 0;
}

uint8_t CPU6502::PHA() {
    return 0;
}

uint8_t CPU6502::PHP() {
    return 0;
}

uint8_t CPU6502::PLA() {
    return 0;
}

uint8_t CPU6502::PLP() {
    return 0;
}

uint8_t CPU6502::ROL() {
    return 0;
}

uint8_t CPU6502::ROR() {
    return 0;
}

uint8_t CPU6502::RTI() {
    return 0;
}

uint8_t CPU6502::RTS() {
    return 0;
}

uint8_t CPU6502::SBC() {
    return 0;
}

uint8_t CPU6502::SEC() {
    return 0;
}

uint8_t CPU6502::SED() {
    return 0;
}

uint8_t CPU6502::SEI() {
    return 0;
}

uint8_t CPU6502::STA() {
    return 0;
}

uint8_t CPU6502::STX() {
    write(addr_abs, x)  ;
	return 0;
}

uint8_t CPU6502::STY() {
    return 0;
}

uint8_t CPU6502::TAX() {
    return 0;
}

uint8_t CPU6502::TAY() {
    return 0;
}

uint8_t CPU6502::TSX() {
    return 0;
}

uint8_t CPU6502::TXA() {
    return 0;
}

uint8_t CPU6502::TXS() {
    return 0;
}

uint8_t CPU6502::TYA() {
    return 0;
}

uint8_t CPU6502::XXX() {
    return 0;
}

void CPU6502::irq() {

}

void CPU6502::nmi() {

}

// It is merely a convenience function to turn the binary instruction code into
// human readable form. Its included as part of the emulator because it can take
// advantage of many of the CPUs internal operations to do this.
std::map<uint16_t, std::string> CPU6502::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
    	uint16_t line_addr = 0;

	// A convenient utility to convert variables into
	// hex strings because "modern C++"'s method with 
	// streams is atrocious
	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	// Starting at the specified address we read an instruction
	// byte, which in turn yields information from the lookup table
	// as to how many additional bytes we need to read and what the
	// addressing mode is. I need this info to assemble human readable
	// syntax, which is different depending upon the addressing mode

	// As the instruction is decoded, a std::string is assembled
	// with the readable output
	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		// Prefix line with instruction address
		std::string sInst = "$" + hex(addr, 4) + ": ";

		// Read instruction, and get its readable name
		uint8_t opcode = bus->read(addr, true); addr++;
		sInst += lookup[opcode].name + " ";

		// Get oprands from desired locations, and form the
		// instruction based upon its addressing mode. These
		// routines mimmick the actual fetch routine of the
		// 6502 in order to get accurate data as part of the
		// instruction
		if (lookup[opcode].addrmode == &CPU6502::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IMM)
		{
			value = bus->read(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ZP0)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ZPX)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ZPY)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IZX)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IZY)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ABS)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ABX)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::ABY)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::IND)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrmode == &CPU6502::REL)
		{
			value = bus->read(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + value, 4) + "] {REL}";
		}

		// Add the formed string to a std::map, using the instruction's
		// address as the key. This makes it convenient to look for later
		// as the instructions are variable in length, so a straight up
		// incremental index is not sufficient.
		mapLines[line_addr] = sInst;
	}

	return mapLines;
}
