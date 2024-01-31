#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096
#define WORD_SIZE 16
#define REGISTER_COUNT 16

unsigned short memory[MEMORY_SIZE];
unsigned short registers[REGISTER_COUNT] ={};
unsigned short pc = 0;
unsigned short flags = 0;
unsigned short value;
short offset;

// Define opcodes
#define ADD_OPCODE 0x0
#define SUB_OPCODE 0x1
#define MUL_OPCODE 0x2
#define DIV_OPCODE 0x3
#define AND_OPCODE 0x4
#define ORR_OPCODE 0x5
#define NOT_OPCODE 0x6
#define SHL_OPCODE 0x7
#define SHR_OPCODE 0x8
#define CMP_OPCODE 0x9
#define MOV_OPCODE 0xA
#define LDR_OPCODE 0xB
#define STR_OPCODE 0xC
#define NOP_OPCODE 0xD
#define JMP_OPCODE 0xE
#define JEQ_OPCODE 0xF

// Function declarations for instruction execution
// (Please make sure these are defined correctly)
void executeADD(unsigned short dest, unsigned short src1, unsigned short src2);
void executeSUB(unsigned short dest, unsigned short src1, unsigned short src2);
void executeMUL(unsigned short dest, unsigned short src1, unsigned short src2);
void executeDIV(unsigned short dest, unsigned short src1, unsigned short src2);
void executeAND(unsigned short dest, unsigned short src1, unsigned short src2);
void executeORR(unsigned short dest, unsigned short src1, unsigned short src2);
void executeNOT(unsigned short dest, unsigned short src);
void executeSHL(unsigned short dest, unsigned short src1, unsigned short src2);
void executeSHR(unsigned short dest, unsigned short src1, unsigned short src2);
void executeCMP(unsigned short src1, unsigned short src2);
void executeMOV(unsigned short dest, unsigned short value);
void executeLDR(unsigned short dest, unsigned short src);
void executeSTR(unsigned short src, unsigned short dest);
void executeNOP();
void executeJMP(short offset);
void executeJEQ(short offset);

void loadInstructions(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s.\n", filename);
        exit(1);
    }

    unsigned short instruction;
    int i = 0;

    while (fscanf(file, "%hx", &instruction) != EOF) {
        if (i >= MEMORY_SIZE) {
            fprintf(stderr, "Error: Too many instructions. Exceeding MEMORY_SIZE.\n");
            fclose(file);
            exit(1);
        }
        
        memory[i++] = instruction;
    }

    // Append the termination instruction if there's space
    if (i < MEMORY_SIZE) {
        memory[i++] = 0xDEAD;
    }
    fclose(file);
}

void printRegisterDump() {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("Register  %d: 0x%04X\n", i, registers[i]);
    }
    printf("Register  PC: 0x%04X\n", pc);
}

void printMemoryDump() {
    for (int i = 0; i < MEMORY_SIZE; i += 8) {
        if (i % 16 == 0) {
            printf("0x%04X:", i);
            for (int j = 0; j < 8; j++) {
                if (i + j < MEMORY_SIZE) {
                    printf(" %04X", memory[i + j]);
                }
            }
            printf("\n");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    loadInstructions(argv[1]);

    while (memory[pc] != 0xDEAD) {
        unsigned short instruction = memory[pc];
        unsigned short opcode = (instruction >> 12) & 0xF;
        unsigned short dest = (instruction >> 8) & 0xF;
        unsigned short src1 = (instruction >> 4) & 0xF;
        unsigned short src2 = instruction & 0xF;

        switch (opcode) {
            case ADD_OPCODE:
                executeADD(dest, src1, src2);
                break;
            case SUB_OPCODE:
                executeSUB(dest, src1, src2);
                break;
            case MUL_OPCODE:
                executeMUL(dest, src1, src2);
                break;
            case DIV_OPCODE:
                executeDIV(dest, src1, src2);
                break;
            case AND_OPCODE:
                executeAND(dest, src1, src2);
                break;
            case ORR_OPCODE:
                executeORR(dest, src1, src2);
                break;
            case NOT_OPCODE:
                executeNOT(dest, src1);
                break;
            case SHL_OPCODE:
                executeSHL(dest, src1, src2);
                break;
            case SHR_OPCODE:
                executeSHR(dest, src1, src2);
                break;
            case CMP_OPCODE:
                executeCMP(src1, src2);
                break;
            case MOV_OPCODE:
                executeMOV(dest, value);
                break;
            case LDR_OPCODE:
                executeLDR(dest, src1);
                break;
            case STR_OPCODE:
                executeSTR(src1, dest);
                break;
            case NOP_OPCODE:
                executeNOP();
                break;
            case JMP_OPCODE:
                executeJMP(offset);
                break;
            case JEQ_OPCODE:
                executeJEQ(offset);
                break;
            default:
                fprintf(stderr, "Error: Invalid opcode %X\n", opcode);
                exit(1);
        }
        pc++;
    }

    printRegisterDump();
    printMemoryDump();

    return 0;
}
