#include "otsdaq-components/DAQHardware/OtsUDPFirmwareDataGen.h"
#include "otsdaq/Macros/CoutMacros.h"
#include "otsdaq/MessageFacility/MessageFacility.h"

using namespace ots;

//==============================================================================
OtsUDPFirmwareDataGen::OtsUDPFirmwareDataGen(unsigned int version)
    : OtsUDPFirmwareCore(version)
{
}

//==============================================================================
OtsUDPFirmwareDataGen::~OtsUDPFirmwareDataGen(void) {}

//==============================================================================
void OtsUDPFirmwareDataGen::init(void) {}

//==============================================================================
void OtsUDPFirmwareDataGen::setNumberOfBurstWords(std::string& buffer,
                                                  uint64_t     numberOfWords)
{
	__COUT__ << std::endl;
	OtsUDPFirmwareCore::writeAdvanced(buffer, 0x1001, numberOfWords);
}

//==============================================================================
void OtsUDPFirmwareDataGen::setBurstWordsRate(std::string& buffer, uint64_t interval)
{
	__COUT__ << std::endl;
	OtsUDPFirmwareCore::writeAdvanced(buffer, 0x1002, interval);
}
