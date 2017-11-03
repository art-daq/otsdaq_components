#ifndef _ots_FrontEndFirmwareBase_h_
#define _ots_FrontEndFirmwareBase_h_

#include <string>
#include <iostream>
#include <vector>
#include <assert.h>
//#include "otsdaq-core/ConfigurationInterface/DACStream.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include "otsdaq-components/DetectorConfiguration/ROCStream.h"

namespace ots
{


class FrontEndFirmwareBase
{

public:
	//factory method for choosing network protocol
	FrontEndFirmwareBase          (void);
    FrontEndFirmwareBase          (unsigned int version);
    virtual ~FrontEndFirmwareBase (void);
    virtual void init             (void);

    //ryan's firmware
    //TODO: these should never be called directly if the factory is used correctly, but
    //not all classes will implement every function (so no pure virtuals). should be obvious
    //that the wrong thing is happening if these are called
    virtual std::string  read	  					 (char* address){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual std::string  write	  					 (char* address, char* data){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};

    virtual void  		 setDataDestination          (std::string& buffer, const std::string& ip, const uint16_t port){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return;};
    //virtual unsigned int write                       (std::string& buffer, uint64_t address, const std::string& value);
    virtual unsigned int write                       (std::string& buffer, uint64_t address, uint64_t data){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual unsigned int write                       (std::string& buffer, uint32_t address, uint32_t data){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual unsigned int waitSet                     (std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout = 255){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual unsigned int waitClear                   (std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout = 255){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual unsigned int read                        (std::string& buffer, uint64_t address){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual unsigned int read                        (std::string& buffer, uint32_t address){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual unsigned int getNumberOfBufferedCommands (std::string& buffer){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};
    virtual std::string  compareSendAndReceive       (const std::string& sentBuffer, std::string& acknowledgment){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return "";};
    virtual uint32_t     createRegisterFromValue     (std::string& readBuffer, std::string& receivedValue){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function"); return 0;};

    //purdue firmware
//    virtual std::string  setDataDestination          (std::string ip, unsigned int port);
//    virtual unsigned int waitSet                     (std::string& buffer, unsigned int address, unsigned int data, unsigned int timeout = 255);
//    virtual unsigned int waitClear                   (std::string& buffer, unsigned int address, unsigned int data, unsigned int timeout = 255);
//    virtual unsigned int getNumberOfBufferedCommands (std::string& buffer);
//    virtual std::string  compareSendAndReceive       (const std::string& sentBuffer, std::string& acknowledgment);
//    virtual uint32_t     createRegisterFromValue     (std::string& readBuffer, std::string& receivedValue);

    //FSSROtsFirmware
//    virtual void makeDACSequence 				(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeMaskSequence				(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeDACSequence 				(FirmwareSequence<uint32_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeDACBuffer   				(std::string& buffer, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeDACBuffer   				(std::vector<std::string>& buffer, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeMaskSequence				(FirmwareSequence<uint32_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeMaskBuffer  				(std::string& buffer, unsigned int channel, const ROCStream& rocStream);

    //for generic interface
    /*these functions have to be in FirmwareBase because the FEWOtsGenericInterface wants to access them
     *through a pointer to FirmwareBase. Might want to change how that works.
     */
    virtual std::string readCSRRegister(void)
    {
    	__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");
    	std::cout << __COUT_HDR_FL__ << "Something bad happened!" << std::endl;
    	return "";
    };
//    virtual void makeDACBuffer(std::vector<std::string>& buffer, unsigned int channel, const ROCStream& rocStream){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");  return;};
//    virtual void makeMaskBuffer(std::string& buffer, unsigned int channel, const ROCStream& rocStream){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");  return;};

	static FrontEndFirmwareBase* getInstance(std::string choice, unsigned int version);
protected:
    unsigned int version_;
};

}

#endif
