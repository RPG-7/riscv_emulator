#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "bus.h"

//CPU privilege: 00:U 01:S 10:RESERVE 11:M

typedef struct CPU {
    uint64_t regs[32];          // 32 64-bit registers (x0-x31)
    uint64_t pc;                // 64-bit program counter
    uint8_t cpu_status;           //  [7] Jump_occured [6] C instruction encountered [1:0]current privilege lvel
    uint64_t csr[4069];
    struct BUS bus;             // CPU connected to BUS
} CPU;

#define SET_REG_BIT(reg,bit) (reg|(1<<bit))
#define CLR_REG_BIT(reg,bit) (reg&(~(1<<bit)))

#define SET_JUMP_FLAG(cpu_status)  cpu_status|=0x80
#define CLR_JUMP_FLAG(cpu_status)  cpu_status&=0x7F

#define SET_CINST_FLAG(cpu_status)  cpu_status|=0x40
#define CLR_CINST_FLAG(cpu_status)  cpu_status&=0xBF

#define GET_CURR_PRIV(cpu_status)       cpu_status&0x03
#define SET_CURR_PRIV(cpu_status,priv)  (cpu_status&0xFC)|GET_CURR_PRIV

#define PRIV_LVL_M 0x03
#define PRIV_LVL_S 0x01
#define PRIV_LVL_U 0x00 


void cpu_init(struct CPU *cpu);
uint32_t cpu_fetch(struct CPU *cpu);
int cpu_execute(struct CPU *cpu, uint32_t inst);
void dump_registers(struct CPU *cpu); 

#endif
