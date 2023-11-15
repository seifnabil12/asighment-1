#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

class Register {
private:
    std::string value;

public:
    // Constructor initializes register with "00"
    Register() : value("00") {}

    // Set the register with a new value
    void setValue(const std::string& newValue) {
        value = newValue;
    }

    // Get the current value of the register
    const std::string& getValue() const {
        return value;
    }

    // Clear the register by setting it to "00"
    void clearRegister() {
        value = "00";
    }
};

class Memory {
private:
    std::vector<int> data;

public:
    Memory(int size) : data(size, 0) {}

    int read(int address) const {
        return data[address];
    }

    void write(int address, int value) {
        data[address] = value;
    }

    int size() const {
        return data.size();
    }
};


class Screen {
private:
    int width;
    int height;
    std::vector<std::vector<int>> pixels;

public:
    Screen(int width, int height) : width(width), height(height), pixels(height, std::vector<int>(width, 0)) {}

    void setPixel(int x, int y, int value) {
        pixels[y][x] = value;
    }

    int getPixel(int x, int y) const {
        return pixels[y][x];
    }

    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }
};

class Instruction {
        private:
        int opcode;
        int operand;

        public:
        Instruction(int opcode, int operand) : opcode(opcode), operand(operand) {}

        void execute(std::vector<Register>& registers, Memory& memory, Screen& screen) {
            // Execute the instruction based on the opcode and operand
            if (opcode == 0) {
                // Perform some operation based on the operand
            } else if (opcode == 1) {
                // Perform another operation based on the operand
            }
            // ...
        }
};


class Machine {
private:
    std::vector<Register> registers;
    Memory memory;
    Screen screen;
    int programCounter;

public:
    Machine() : registers(16), memory(256), screen(640, 480), programCounter(0) {}

    void loadProgramFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open the input file" << std::endl;
            return;
        }

        int address = 0;
        int value;
        bool readSingleDigit = false; // Flag to handle single digit after '0x'

        while (file >> std::hex >> value) {
            if (readSingleDigit) {
                // Add the single digit to the next digit after '0x'
                memory.write(address - 1, (memory.read(address - 1) << 4) | value);
                readSingleDigit = false;
            } else {
                memory.write(address++, value);
                // Check if the current value is a single digit
                if (value < 0x10)

                    readSingleDigit = true;
            }
        }

        file.close();
    }


    void executeProgram() {
        int memorySize = memory.size();
        while (programCounter < memorySize) {
            Instruction currentInstruction(memory.read(programCounter), memory.read(programCounter + 1));
            currentInstruction.execute(registers, memory, screen);
            programCounter += 2;
        }
    }

    void displayStatus() const {
        // Display the status of the machine, registers, memory, and screen
        std::cout << "Machine Status:" << std::endl;

        // Display Registers
        std::cout << "Registers:" << std::endl;
        for (int i = 0; i < registers.size(); ++i) {
            std::cout << "R" << std::setfill('0') << std::setw(1) << i << ":" << std::hex << std::setfill('0') << std::setw(2) << memory.read(i) << std::dec << std::endl;
        }


// Display Memory
        std::cout << "Memory:" << std::endl;
        for (int i = 0; i < memory.size(); ++i) {
            std::cout << "M" << std::setfill('0') << std::setw(1) << i << ":" << std::hex << std::setfill('0') << std::setw(2) << memory.read(i) << std::dec << std::endl;
        }
    }
};


int main() {
    Machine machine;
    machine.loadProgramFromFile("file1.txt");

    // Reset the machine for full program execution
    machine = Machine();
    machine.loadProgramFromFile("file1.txt");

    // Execute the program all at once
    machine.executeProgram();
    machine.displayStatus();

    return 0;
}
