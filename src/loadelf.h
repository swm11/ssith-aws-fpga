#pragma once
#include <stdint.h>
#include "fpga.h"

class IMemory {
public:
    virtual ~IMemory() {};
    virtual uint32_t read32(uint32_t addr) = 0;
    virtual uint64_t read64(uint32_t addr) = 0;
    virtual void write32(uint32_t addr, uint32_t data) = 0;
    virtual void write64(uint32_t addr, uint64_t data) = 0;
    virtual void read(uint32_t start_addr, uint32_t *data, size_t num_bytes);
    virtual void write(uint32_t start_addr, const uint32_t *data, size_t num_bytes);
};

// read/write a buffer but mask off 0xC0000000 from addr
class P2Memory : public IMemory {
    uint8_t *buffer;
public:
    P2Memory(uint8_t *buffer);
    virtual uint32_t read32(uint32_t addr);
    virtual uint64_t read64(uint32_t addr);
    virtual void write32(uint32_t addr, uint32_t data);
    virtual void write64(uint32_t addr, uint64_t data);

};

class AWSP2_Memory : public IMemory {
    AWSP2 *fpga;
public:
    AWSP2_Memory(AWSP2 *fpga);
    virtual uint32_t read32(uint32_t addr);
    virtual uint64_t read64(uint32_t addr);
    virtual void write32(uint32_t addr, uint32_t data);
    virtual void write64(uint32_t addr, uint64_t data);
    virtual void write(uint32_t start_addr, const uint32_t *data, size_t num_bytes);
};

class PCIS_DMA_Memory : public IMemory {
    AWSP2 *fpga;
    uint32_t uncached_base_addr;
    uint32_t cached_base_addr;
    int helper_loaded;
    uint32_t helper_entry_point;
    int pcis_fd;
    uint8_t *pcis_buffer;
    size_t pcis_buffer_size;
public:
    PCIS_DMA_Memory(AWSP2 *fpga, uint32_t uncached_base_addr, uint32_t cached_base_addr);
    virtual ~PCIS_DMA_Memory();
    virtual uint32_t read32(uint32_t addr);
    virtual uint64_t read64(uint32_t addr);
    virtual void write32(uint32_t addr, uint32_t data);
    virtual void write64(uint32_t addr, uint64_t data);
    virtual void write(uint32_t start_addr, const uint32_t *data, size_t num_bytes);
 private:
    void load_helper();
    void p2_memcpy(uint32_t cached_dest, uint32_t uncached_source, uint32_t count, uint32_t done_addr);
};

uint64_t loadElf(IMemory *mem, const char *elf_filename, size_t max_mem_size, AWSP2 *fpga);
