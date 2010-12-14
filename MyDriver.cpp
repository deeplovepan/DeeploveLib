basic mac driver
code

/* add your code here */

#include <IOKit/IOLib.h>
#include "MyDriver.h"

// This required macro defines the class's constructors, destructors,
// and several other methods I/O Kit requires.
OSDefineMetaClassAndStructors(com_MyCompany_driver_MyDriver, IOService)

// Define the driver's superclass.
#define super IOService

bool com_MyCompany_driver_MyDriver::init(OSDictionary *dict)
{
    bool result = super::init(dict);
    IOLog("Initializing\n");
    return result;
}

void com_MyCompany_driver_MyDriver::free(void)
{
    IOLog("Freeing\n");
    super::free();
}

IOService *com_MyCompany_driver_MyDriver::probe(IOService *provider,
												SInt32 *score)
{
    IOService *result = super::probe(provider, score);
    IOLog("Probing\n");
    return result;
}

bool com_MyCompany_driver_MyDriver::start(IOService *provider)
{
    bool result = super::start(provider);
    IOLog("Starting\n");
    return result;
}

void com_MyCompany_driver_MyDriver::stop(IOService *provider)
{
    IOLog("Stopping\n");
    super::stop(provider);
}
