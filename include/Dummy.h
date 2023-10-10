#pragma once

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

    void Init(unsigned int constAccountId, unsigned int constGuid);

};


