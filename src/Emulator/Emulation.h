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
    struct ProgramData {
        ProgramData(const RamMemory& memory)
            : ram(memory)
            , registers()
            , I(0)
            , PC(0)
            , SP(0)
            , delay(0)
            , sound(0)
        {
        }
        ~ProgramData() = default;

        static constexpr std::size_t CarryFlagIndex = 16;

        RamMemory ram;
        std::array<uint8_t, 16> registers; // from V0 to VF
        std::stack<uint16_t> stack;
        uint16_t I; // address pointer
        uint16_t PC; // program counter
        uint8_t SP; // stack pointer
        uint8_t delay;
        uint8_t sound;
    };

    struct Opcode {
        uint8_t _operation{ 0 }; // operationy to perform
        uint8_t _X{ 0 }; // second nibble
        uint8_t _Y{ 0 }; // third nibble
        uint8_t _N{ 0 }; // fourth nibble
        uint8_t _NN{ 0 }; // second and third nibble
        uint16_t _NNN{ 0 }; // second, third and fourth nibble
    };

    class OpcodeParser {
    public:
        explicit OpcodeParser(uint16_t opcode)
        {
            Parse(opcode);
        }
        ~OpcodeParser() = default;

        void Parse(uint16_t opcode)
        {
            _opcode._operation = static_cast<uint8_t>((opcode & 0xF000) >> 12);
            _opcode._X = static_cast<uint8_t>((opcode & 0x0F00) >> 8);
            _opcode._Y = static_cast<uint8_t>((opcode & 0x00F0) >> 4);
            _opcode._N = static_cast<uint8_t>(opcode & 0x000F);
            _opcode._NN = static_cast<uint8_t>((opcode & 0x00FF));
            _opcode._NNN = static_cast<uint16_t>(opcode & 0x0FFF);
        }
        Opcode GetOpcode() const
        {
            return _opcode;
        }

    private:
        Opcode _opcode;
    };

public:
    explicit Emulation(const RamMemory& ram, bool shiftUsingVY = false)
        : _data(ram)
        , _shiftUsingVY(false)
    {
    }
    ~Emulation() = default;

    void FetchAndDecode();
    void Execute();

private:
    ProgramData _data;
    Opcode _instruction;
    //TODO: Options struct
    bool _shiftUsingVY;
};
