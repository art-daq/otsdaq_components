#ifndef _ots_PurdueFirmwareCore_h_
#define _ots_PurdueFirmwareCore_h_

#include "otsdaq-components/DAQHardware/FirmwareSequence.h"
#include "otsdaq-components/DAQHardware/FrontEndFirmwareBase.h"

#include <string>
#include <cstdint>

namespace ots
{
class PurdueFirmwareCore : public FrontEndFirmwareBase
{

public:
    PurdueFirmwareCore                               (unsigned int version);
    virtual ~PurdueFirmwareCore                      (void);
    virtual int init                  			     (void);


    std::string read	  (char* address);
    std::string write	  (char* address, char* data);

    virtual unsigned int write                       (std::string& buffer, uint32_t address, uint32_t data);
    virtual unsigned int waitSet                     (std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout = 255);
    virtual unsigned int waitClear                   (std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout = 255);
    virtual unsigned int read                        (std::string& buffer, uint32_t address);
	/*TODO this prevents "hidden virtual" problem, since PurdueFirmwareCore, unlike the ots firmware
	 * only defines write/read for 32 bits. if, somehow, a 64 bit write/read gets called, it will
	 * use the write/read in FrontEndFirmwareBase (which does nothing) */
	//more: http://stackoverflow.com/questions/6727087/c-virtual-function-being-hidden
	using FrontEndFirmwareBase::write;
	using FrontEndFirmwareBase::read;

    virtual unsigned int getNumberOfBufferedCommands (std::string& buffer);
    virtual std::string  compareSendAndReceive       (const std::string& sentBuffer, std::string& acknowledgment);
    virtual uint32_t     createRegisterFromValue     (std::string& readBuffer, std::string& receivedValue);
protected:
    //FrontEndFirmwareBase* protocolInstance_;
};

}

#endif