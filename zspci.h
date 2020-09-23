/* Copyright (c) ztex. All rights reserved.
 * Release under WTFPL, Do What The Fuck You Want To Public License
 */

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

struct Header {
    uint16_t DeviceID;
    uint16_t VendorID;
    uint16_t Status;
    uint16_t Command;
    uint8_t ClassCode;
    uint8_t Subclass;
    uint8_t ProgIF;
    uint8_t RevisionID;
    uint8_t BIST;
    uint8_t HeaderType;
    uint8_t LatencyTimer;
    uint8_t CacheLineSize;
    union {
        uint32_t BAR0;
    };
    union {
        uint32_t BAR1;
    };
    union {
        uint32_t BAR2;
        uint32_t SecondaryLatencyTimer: 8,
                 SubordinateBusNumber: 8,
                 SecondaryBusNumber: 8,
                 PrimaryBusNumber: 8;
    };
    union {
        uint32_t BAR3;
        uint32_t SecondarySatus: 16,
                 IOLimit: 8,
                 IOBase: 8;
    };
    union {
        uint32_t BAR4;
        uint32_t MemoryLimit: 16,
                 MemoryBase: 16;
    };
    union {
        uint32_t BAR5;
        uint32_t PrefetchableMemoryLimit: 16,
                 PrefetchableMemoryBase: 16;
    };
    union {
        uint32_t CardbusCISPointer;
        uint32_t PrefetchableBaseUpper;
    };
    union {
        uint32_t SubsystemID: 16,
                 SubsystemVendorID: 16;
        uint32_t PrefetchableLimitUpper;
    };
    union {
        uint32_t ExpansionROMBaseAddress;
        uint32_t IOLimitUpper: 16,
                 IOBaseUpper: 16;
    };
    union {
        uint32_t Reserved0: 16,
                 CapabilitesPointer: 16;
        uint32_t Reserved: 24,
                 CapabilityPointer: 8;
    };
    union {
        uint32_t Reserved1;
        uint32_t ExpansionROMBaseAddressType01;
    };
    union {
        uint32_t MaxLatency: 8,
                 MinGrant: 8,
                 InterruptPIN: 8,
                 InterruptLine: 8;
        uint32_t BridgeControl: 16,
                 InterruptPINType01: 8,
                 InterruptLineType01: 8;
    };
};

#endif
