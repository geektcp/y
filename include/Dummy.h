#pragma once
#include <stdint.h>

typedef uint32_t uint32;
/**
 * This is a dummy class to demonstrate features of the boiler plate.
 */


class Dummy {
public:

    /**
     * Default constructor for Dummy (does nothing).
     */
    Dummy() = default;

    /**
     * Returns a bool.
     * @return Always True.
     */
    bool DoSomething();

    void Init(uint32_t constAccountId, uint32 constGuid);

};


