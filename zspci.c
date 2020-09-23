#include <sys/io.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#include "zspci.h"

void Hexdump32(uint32_t data) {
    unsigned char *iter = (unsigned char *)((void *)&data);
    size_t i = 0;
    for (i = 0; i < 4; i++, iter++) {
        printf("%02x ", *iter);
    }
}

void ReadData(uint32_t bus, uint32_t dev, uint32_t func, uint32_t regoffset, uint32_t *data)
{
    uint32_t address = 0;
    address = TO_ADDRESS(bus, dev, func, regoffset);
    outl(address, CONFIG_ADDRESS);
    *data = inl(CONFIG_DATA);
}

int Traverse()
{
    uint32_t bus = 0;
    uint32_t device = 0;
    uint32_t func = 0;
    uint32_t regoffset = 0;
    uint32_t data = 0;
    uint32_t address = 0;
    int ret = 0;

    ret = iopl(3);
    if(ret < 0)
    {
        perror("iopl wrong\n");
        goto fail;
    }

    for(bus = 0; bus < MAX_BUS; bus++) {
        for(device = 0; device < MAX_DEVICE; device++) {
            for(func = 0; func < MAX_FUNCTION; func++) {
                ReadData(bus, device, func, 0, &data);
                if ((data != 0xffffffff) && (data != 0)) {
                    printf("\n%02x:%02x:%02x\n", bus, device, func);
                    for (regoffset = 0; regoffset < 16; regoffset++) {
                        if(regoffset % 4 == 0) {
                            printf("%02x:", regoffset * 4);
                        }
                        ReadData(bus, device, func, regoffset, &data);
                        Hexdump32(data);
                        if(regoffset % 4 == 3) {
                            printf("\n");
                        }
                    }
                }
            }
        }
    }

    iopl(0);
    if(ret < 0)
    {
        perror("iopl wrong\n");
        goto fail;
    }

    ret = 0;
fail:
    return ret;
}

int main(int argc, char **argv)
{
    int ret = 0;
    ret = Traverse();
    return ret;
}
