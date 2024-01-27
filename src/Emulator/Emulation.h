#pragma once
#include "cassert"
#include <array>
#include <cstdint>
#include <iostream>
#include <stack>

class Emulation {
public:
    using RamMemory = const std::array<uint8_t, 4096>;

public:
    struct Data {
        Data(const RamMemory& memory)
            : ram(memory)
            , registers()
            , I(0)
            , PC(0)
            , SP(0)
            , delay(0)
            , sound(0)
        {
        }
        ~Data() = default;

        RamMemory ram;
        std::array<uint8_t, 16> registers; // from V0 to VF
        std::stack<uint16_t> stack;
        uint16_t I; // address pointer
        uint16_t PC; // program counter
        uint8_t SP; // stack pointer
        uint8_t delay;
        uint8_t sound;
    };

public:
    explicit Emulation(const RamMemory& ram);
    ~Emulation() = default;

    void ReadInstruction()
    {
        assert(_data.PC + 1 < _data.ram.size());

        auto firstByte = _data.ram[_data.PC];
        auto secondByte = _data.ram[_data.PC + 1];

        uint16_t instruction = (secondByte << 8) | firstByte;
        _data.PC += 2;

        auto [firstNibble, secondNibble, thirdNibble, fourthNibble] = SplitToNibbles(instruction);
        switch (firstNibble) {
        case 0x00E0:
            // clear screen
            break;
        case 0x00EE:
            // return from subrutine
            break;
        case 0x1:
            // read NNN and jump to it
            break;
        case 0x2:
            // read NNN and call subrutine here
            break;
        case 0x3:
            // Skips the next instruction if VX equals NN (usually the next instruction is a jump to skip a code block).
            break;
        case 0x4:
            // Skips the next instruction if VX does not equal NN (usually the next instruction is a jump to skip a code
            // block).
            break;
        case 0x5:
            // Skips the next instruction if VX equals VY (usually the next instruction is a jump to skip a code block).
            break;
        case 0x6:
            // Sets VX to NN.
            break;
        case 0x7:
            // Adds NN to VX (carry flag is not changed).
            break;
        case 0x8:
            switch (fourthNibble) {
            case 0x0:
                // Sets VX to the value of VY.
                break;
            case 0x1:
                // Sets VX to VX or VY. (bitwise OR operation)
                break;
            case 0x2:
                // Sets VX to VX and VY. (bitwise AND operation)
                break;
            case 0x3:
                // Sets VX to VX xor VY.
                break;
            case 0x4:
                // Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not.
                break;
            case 0x5:
                // VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not.
                break;
            case 0x6:
                // Stores the least significant bit of VX in VF and then shifts VX to the right by 1.[b] (ambigous)
                break;
            case 0x7:
                // Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not. (ambigous)
                break;
            case 0xE:
                // Stores the most significant bit of VX in VF and then shifts VX to the left by 1.[b] (ambigous)
                break;
            }
            break;
        case 0x9:
            // Skips the next instruction if VX does not equal VY. (Usually the next instruction is a jump to skip a
            // code block);
            break;
        case 0xA:
            // Sets I to the address NNN.
            break;
        case 0xB:
            // Jumps to the address NNN plus V0.
            break;
        case 0xC:
            // Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
            break;
        case 0xD:
            // draw
            break;
        case 0xE:
            switch (fourthNibble) {
            case 0xE:
                // Skips the next instruction if the key stored in VX is pressed (usually the next instruction is a jump
                // to skip a code block).
                break;
            case 0x1:
                // Skips the next instruction if the key stored in VX is not pressed (usually the next instruction is a
                // jump to skip a code block).
                break;
            }
            break;
        }

        // std::cerr << "First nibble: " << std::hex << (int)firstNibble << std::endl;
        // std::cerr << "Second nibble: " << std::hex << (int)secondNibble << std::endl;
        // std::cerr << "Third nibble: " << std::hex << (int)thirdNibble << std::endl;
        // std::cerr << "Fourth nibble: " << std::hex << (int)fourthNibble << std::endl;

        if (firstNibble == 0x0) {
            std::cerr << "GOT 0\n";
        }
        // std::cerr << std::hex << "FIRST BYTE: " << (int)firstByte << " SECOND BYTE: " << (int)secondByte <<
        // std::endl;
    }

private:
    // TODO: Endianess
    std::array<uint8_t, 4> SplitToNibbles(uint16_t instruction)
    {
        return { static_cast<uint8_t>((instruction & 0xF000) >> 12), static_cast<uint8_t>((instruction & 0x0F00) >> 8),
            static_cast<uint8_t>((instruction & 0x00F0) >> 4), static_cast<uint8_t>(instruction & 0x000F) };
    }
    std::array<uint8_t, 4> SplitToNibblesAndSwapEndianess(uint16_t instruction)
    {
        return { static_cast<uint8_t>((instruction & 0x00F0) >> 4), static_cast<uint8_t>(instruction & 0x000F),
            static_cast<uint8_t>((instruction & 0xF000) >> 12), static_cast<uint8_t>((instruction & 0x0F00) >> 8) };
    }

private:
    Data _data;
};
