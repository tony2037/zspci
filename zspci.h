#ifndef ZSPCI_H
#define ZSPCI_H

#include <stdint.h>

#define MAX_BUS 256
#define MAX_DEVICE 32
#define MAX_FUNCTION 8

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

#define ENABLE_BIT 0x80000000

#define TO_ADDRESS(bus,dev,func,reg) (ENABLE_BIT | (bus << 16) | (dev << 11) | (func << 8) | (reg << 2))

#endif
