#include "Emulation.h"

void Emulation::FetchAndDecode()
{
    assert(_data.PC + 1 < _data.ram.size());

    auto firstByte = _data.ram[_data.PC];
    auto secondByte = _data.ram[_data.PC + 1];

    uint16_t instruction = (secondByte << 8) | firstByte;
    _data.PC += 2;

    OpcodeParser parser(instruction);
    _instruction = parser.GetOpcode();
}

void Emulation::Execute()
{
    switch (_instruction._operation) {
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
        _data.registers[_instruction._X] = _instruction._N;
        break;
    case 0x7:
        // Adds NN to VX (carry flag is not changed).
        break;
    case 0x8:
        PerformArithmeticOperation();
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
        switch (_instruction._N) {
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
}

void Emulation::PerformArithmeticOperation()
{
    switch (_instruction._N) {
    case 0x0:
        // Sets VX to the value of VY.
        _data.registers[_instruction._X] = _data.registers[_instruction._Y];
        break;
    case 0x1:
        // Sets VX to VX or VY. (bitwise OR operation)
        _data.registers[_instruction._X] |= _data.registers[_instruction._Y];
        break;
    case 0x2:
        // Sets VX to VX and VY. (bitwise AND operation)
        _data.registers[_instruction._X] &= _data.registers[_instruction._Y];
        break;
    case 0x3:
        // Sets VX to VX xor VY.
        _data.registers[_instruction._X] ^= _data.registers[_instruction._Y];
        break;
    case 0x4: {
        // Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not.
        bool isCarry = (_data.registers[_instruction._X] + _data.registers[_instruction._Y]) > 0xFF;
        _data.registers[_instruction._X] += _data.registers[_instruction._Y];
        _data.registers[ProgramData::CarryFlagIndex] = static_cast<uint8_t>(isCarry);
        break;
    }
    case 0x5: {
        // VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not.
        bool isBorrow = _data.registers[_instruction._X] > _data.registers[_instruction._Y];
        _data.registers[_instruction._X] = _data.registers[_instruction._X] - _data.registers[_instruction._Y];
        _data.registers[ProgramData::CarryFlagIndex] = static_cast<uint8_t>(isBorrow);
        break;
    }
    case 0x6:
        // Stores the least significant bit of VX in VF and then shifts VX to the right by 1.[b] (ambigous)
        if (_shiftUsingVY) {
            _data.registers[ProgramData::CarryFlagIndex] = _data.registers[_instruction._Y] & 0x1;
            _data.registers[_instruction._X] = _data.registers[_instruction._Y] >> 1;
        } else {
            _data.registers[ProgramData::CarryFlagIndex] = _data.registers[_instruction._X] & 0x1;
            _data.registers[_instruction._X] = _data.registers[_instruction._X] >> 1;
        }

        break;
    case 0x7: {
        // Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not.
        bool isBorrow = _data.registers[_instruction._Y] > _data.registers[_instruction._X];
        _data.registers[_instruction._X] = _data.registers[_instruction._Y] - _data.registers[_instruction._X];
        _data.registers[ProgramData::CarryFlagIndex] = static_cast<uint8_t>(isBorrow);
        break;
    }
    case 0xE:
        // Stores the most significant bit of VX in VF and then shifts VX to the left by 1.[b] (ambigous)
        if (_shiftUsingVY) {
            _data.registers[ProgramData::CarryFlagIndex] = _data.registers[_instruction._Y] & 0x1;
            _data.registers[_instruction._X] = _data.registers[_instruction._Y] << 1;
        } else {
            _data.registers[ProgramData::CarryFlagIndex] = _data.registers[_instruction._X] & 0x1;
            _data.registers[_instruction._X] = _data.registers[_instruction._X] << 1;
        }
        break;
    }
}

Emulation::ProgramData Emulation::GetProgramState() const
{
    return _data;
}