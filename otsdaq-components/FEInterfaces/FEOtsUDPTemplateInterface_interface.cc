#include "otsdaq-components/FEInterfaces/FEOtsUDPTemplateInterface.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutMacros.h"
#include "otsdaq-core/Macros/InterfacePluginMacros.h"
#include <iostream>
#include <set>

using namespace ots;

#undef 	__MF_SUBJECT__
#define __MF_SUBJECT__ "FE-FEOtsUDPTemplateInterface"

//========================================================================================================================
FEOtsUDPTemplateInterface::FEOtsUDPTemplateInterface(const std::string& interfaceUID, const ConfigurationTree& theXDAQContextConfigTree, const std::string& interfaceConfigurationPath)
: Socket (
		theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostIPAddress").getValue<std::string>()
		, theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostPort").getValue<unsigned int>())
, FEVInterface (interfaceUID, theXDAQContextConfigTree, interfaceConfigurationPath)
, OtsUDPHardware (theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("InterfaceIPAddress").getValue<std::string>()
		, theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("InterfacePort").getValue<unsigned int>())
, OtsUDPFirmwareDataGen(theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("FirmwareVersion").getValue<unsigned int>())
{
	//registration of FEMacro 'varTest2' generated, Oct-11-2018 02:28:57, by 'admin' using MacroMaker.
	registerFEMacroFunction("varTest2",//feMacroName 
		static_cast<FEVInterface::frontEndMacroFunction_t>(&FEOtsUDPTemplateInterface::varTest2), //feMacroFunction 
		std::vector<std::string>{"myOtherArg"}, //namesOfInputArgs 
		std::vector<std::string>{"myArg","outArg1"}, //namesOfOutputArgs 
		1); //requiredUserPermissions 



	//registration of FEMacro 'varTest' generated, Oct-11-2018 11:36:28, by 'admin' using MacroMaker.
	registerFEMacroFunction("varTest",//feMacroName 
		static_cast<FEVInterface::frontEndMacroFunction_t>(&FEOtsUDPTemplateInterface::varTest), //feMacroFunction 
		std::vector<std::string>{"myOtherArg"}, //namesOfInputArgs 
		std::vector<std::string>{"myArg","outArg1"}, //namesOfOutputArgs 
		1); //requiredUserPermissions

	universalAddressSize_ = 8;
	universalDataSize_ = 8;
}

//========================================================================================================================
FEOtsUDPTemplateInterface::~FEOtsUDPTemplateInterface(void)
{}

//========================================================================================================================
void FEOtsUDPTemplateInterface::configure(void)
{
//	unsigned int i = VStateMachine::getIterationIndex();
//	unsigned int j = VStateMachine::getSubIterationIndex();
//	if(i == 0 && j < 5)
//		VStateMachine::indicateSubIterationWork();
//	else if(i < 10)
//		VStateMachine::indicateIterationWork();


	__CFG_COUTV__(VStateMachine::getSubIterationIndex());
	__CFG_COUTV__(VStateMachine::getSubIterationWork());
	__CFG_COUTV__(VStateMachine::getIterationIndex());
	__CFG_COUTV__(VStateMachine::getIterationWork());


//	return;

	__CFG_COUT__ << "configure" << __E__;
	__CFG_COUT__ << "Clearing receive socket buffer: " << OtsUDPHardware::clearReadSocket() << " packets cleared." << __E__;

	std::string sendBuffer;
	std::string recvBuffer;
	uint64_t 	readQuadWord;

	__CFG_COUT__ << "Configuration Path Table: " <<
				theXDAQContextConfigTree_.getNode(theConfigurationPath_).getConfigurationName() <<
				"-v" <<
				theXDAQContextConfigTree_.getNode(theConfigurationPath_).getConfigurationVersion() <<
				__E__;

	__CFG_COUT__ << "Interface name: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_) << __E__;

	__CFG_COUT__ << "Configured Firmware Version: " <<
				theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("FirmwareVersion").getValue<unsigned int>()
				<< __E__;

	__CFG_COUT__ << "Setting Destination IP: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToIPAddress").getValue<std::string>()
			<< __E__;
	__CFG_COUT__ << "And Destination Port: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToPort").getValue<unsigned int>()
			<< __E__;

	OtsUDPFirmwareCore::setDataDestination(sendBuffer,
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToIPAddress").getValue<std::string>(),
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToPort").getValue<uint64_t>()
	);
	OtsUDPHardware::write(sendBuffer);

	__CFG_COUT__ << "Reading back burst dest MAC/IP/Port: " << __E__;

	OtsUDPFirmwareCore::readDataDestinationMAC(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	OtsUDPFirmwareCore::readDataDestinationIP(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	OtsUDPFirmwareCore::readDataDestinationPort(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);



	OtsUDPFirmwareCore::readControlDestinationPort(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	//Run Configure Sequence Commands
	FEVInterface::runSequenceOfCommands("LinkToConfigureSequence");

	__CFG_COUT__ << "Done with ots Template configuring." << __E__;
}

//========================================================================================================================
//void FEOtsUDPTemplateInterface::configureDetector(const DACStream& theDACStream)
//{
//	__CFG_COUT__ << "\tconfigureDetector" << __E__;
//}

//========================================================================================================================
void FEOtsUDPTemplateInterface::halt(void)
{
	__CFG_COUT__ << "\tHalt" << __E__;
	stop();
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::pause(void)
{
	__CFG_COUT__ << "\tPause" << __E__;
	stop();
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::resume(void)
{
	__CFG_COUT__ << "\tResume" << __E__;
	start("");
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::start(std::string )//runNumber)
{
	__CFG_COUT__ << "\tStart" << __E__;


	unsigned int i = VStateMachine::getIterationIndex();
	unsigned int j = VStateMachine::getSubIterationIndex();
	if(i == 0 && j < 5)
		VStateMachine::indicateSubIterationWork();
	else if(i < 10)
		VStateMachine::indicateIterationWork();


	__CFG_COUTV__(VStateMachine::getSubIterationIndex());
	__CFG_COUTV__(VStateMachine::getSubIterationWork());
	__CFG_COUTV__(VStateMachine::getIterationIndex());
	__CFG_COUTV__(VStateMachine::getIterationWork());


	return;



	//Run Start Sequence Commands
	FEVInterface::runSequenceOfCommands("LinkToStartSequence");

	std::string sendBuffer;
	OtsUDPFirmwareCore::startBurst(sendBuffer);
	OtsUDPHardware::write(sendBuffer);
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::stop(void)
{
	__CFG_COUT__ << "\tStop" << __E__;

	//Run Stop Sequence Commands

	FEVInterface::runSequenceOfCommands("LinkToStopSequence");

	std::string sendBuffer;
	OtsUDPFirmwareCore::stopBurst(sendBuffer);
	OtsUDPHardware::write(sendBuffer);
}

//========================================================================================================================
bool FEOtsUDPTemplateInterface::running(void)
{
	__CFG_COUT__ << "\tRunning" << __E__;

	//__SS__ << "?" << __E__; //test exceptions during running
	//__SS_THROW__;


	int state = -1;
	while(WorkLoop::continueWorkLoop_)
	{
		//while running
		//play with the LEDs at address 0x1003

		++state;
		if(state < 8)
			sleep(1);
		else
			break;
	}

	//		//example!
	//		//play with array of 8 LEDs at address 0x1003

	//
	//	bool flashLEDsWhileRunning = false;
	//	if(flashLEDsWhileRunning)
	//	{
	//		std::string writeBuffer;
	//		int state = -1;
	//		while(WorkLoop::continueWorkLoop_)
	//		{
	//			//while running
	//			//play with the LEDs at address 0x1003
	//
	//			++state;
	//			if(state < 8)
	//			{
	//				writeBuffer.resize(0);
	//				OtsUDPFirmwareCore::write(writeBuffer, 0x1003,1<<state);
	//				OtsUDPHardware::write(writeBuffer);
	//			}
	//			else if(state%2 == 1 && state < 11)
	//			{
	//				writeBuffer.resize(0);
	//				OtsUDPFirmwareCore::write(writeBuffer, 0x1003, 0xFF);
	//				OtsUDPHardware::write(writeBuffer);
	//			}
	//			else if(state%2 == 0 && state < 11)
	//			{
	//				writeBuffer.resize(0);
	//				OtsUDPFirmwareCore::write(writeBuffer, 0x1003,0);
	//				OtsUDPHardware::write(writeBuffer);
	//			}
	//			else
	//				state = -1;
	//
	//			sleep(1);
	//		}
	//	}

	return false;
}

//========================================================================================================================
//NOTE: buffer for address must be at least size universalAddressSize_
//NOTE: buffer for returnValue must be max UDP size to handle return possibility
int ots::FEOtsUDPTemplateInterface::universalRead(char *address, char *returnValue)
{
	__CFG_COUT__ << "address size " << universalAddressSize_ << __E__;

	__CFG_COUT__ << "Request: ";
	for(unsigned int i=0;i<universalAddressSize_;++i)
		printf("%2.2X",(unsigned char)address[i]);
	std::cout << __E__;

	std::string readBuffer, sendBuffer;
	OtsUDPFirmwareCore::readAdvanced(sendBuffer,address,1 /*size*/);

	//OtsUDPHardware::read(FSSRFirmware::universalRead(address), readBuffer) < 0;
	try
	{
		OtsUDPHardware::read(sendBuffer, readBuffer); // data reply
	}
	catch(std::runtime_error &e)
	{
		__CFG_COUT__ << "Caught it! This is when it's getting time out error" << __E__;
		__CFG_COUT_ERR__ << e.what() << __E__;
		return -1;
	}

	__CFG_COUT__ << "Result SIZE: " << readBuffer.size() << __E__;
	std::memcpy(returnValue,readBuffer.substr(2).c_str(),universalDataSize_);
	return 0;
} //end universalRead()

//========================================================================================================================
//NOTE: buffer for address must be at least size universalAddressSize_
//NOTE: buffer for writeValue must be at least size universalDataSize_
void ots::FEOtsUDPTemplateInterface::universalWrite(char* address, char* writeValue)
{
	__CFG_COUT__ << "address size " << universalAddressSize_ << __E__;
	__CFG_COUT__ << "data size " << universalDataSize_ << __E__;
	__CFG_COUT__ << "Sending: ";
	for(unsigned int i=0;i<universalAddressSize_;++i)
		printf("%2.2X",(unsigned char)address[i]);
	std::cout << __E__;

	std::string sendBuffer;
	OtsUDPFirmwareCore::writeAdvanced(sendBuffer,address,writeValue,1 /*size*/);
	OtsUDPHardware::write(sendBuffer); // data request
} //end universalWrite()




//========================================================================================================================
//varTest
//	FEMacro 'varTest' generated, Oct-11-2018 11:36:28, by 'admin' using MacroMaker.
//	Macro Notes: This is a great test!
void FEOtsUDPTemplateInterface::varTest(__ARGS__)
{
	__CFG_COUT__ << "# of input args = " << argsIn.size() << __E__; 
	__CFG_COUT__ << "# of output args = " << argsOut.size() << __E__; 
	for(auto &argIn:argsIn) 
		__CFG_COUT__ << argIn.first << ": " << argIn.second << __E__; 

	//macro commands section 
	{
		char *address 	= new char[universalAddressSize_]{0};	//create address buffer of interface size and init to all 0
		char *data 		= new char[universalDataSize_]{0};		//create data buffer of interface size and init to all 0
		uint64_t macroAddress;		//create macro address buffer (size 8 bytes)
		uint64_t macroData;			//create macro address buffer (size 8 bytes)
		std::map<std::string /*arg name*/,uint64_t /*arg val*/> macroArgs; //create map from arg name to 64-bit number

		// command-#0: Read(0x1002 /*address*/,myArg /*data*/);
		macroAddress = 0x1002; memcpy(address,&macroAddress,8);	//copy macro address to buffer
		universalRead(address,data);		memcpy(&macroArgs["myArg"],data,8); //copy buffer to argument map
		__SET_ARG_OUT__("myArg",macroArgs["myArg"]); //update output argument result

		// command-#1: Read(0x1001 /*address*/,data);
		macroAddress = 0x1001; memcpy(address,&macroAddress,8);	//copy macro address to buffer
		universalRead(address,data);		memcpy(&macroArgs["outArg1"],data,8); //copy buffer to argument map
		__SET_ARG_OUT__("outArg1",macroArgs["outArg1"]); //update output argument result

		// command-#2: Write(0x1002 /*address*/,myOtherArg /*data*/);
		macroAddress = 0x1002; memcpy(address,&macroAddress,8);	//copy macro address to buffer
		macroArgs["myOtherArg"] = __GET_ARG_IN__("myOtherArg", uint64_t); //initialize from input arguments	//get macro data argument
		memcpy(data,&macroArgs["myOtherArg"],8); //copy macro data argument to buffer
		universalWrite(address,data);

		// command-#3: Write(0x1001 /*address*/,myArg /*data*/);
		macroAddress = 0x1001; memcpy(address,&macroAddress,8);	//copy macro address to buffer	//get macro data argument
		memcpy(data,&macroArgs["myArg"],8); //copy macro data argument to buffer
		universalWrite(address,data);

		// command-#4: delay(4000);
__CFG_COUT__ << "Sleeping for... " << 4000 << " milliseconds " << __E__;
		usleep(4000*1000 /* microseconds */);


		delete[] address; //free the memory
		delete[] data; //free the memory
	}

	for(auto &argOut:argsOut) 
		__CFG_COUT__ << argOut.first << ": " << argOut.second << __E__; 

} //end varTest()


//========================================================================================================================
//varTest2
//	FEMacro 'varTest2' generated, Oct-11-2018 02:28:57, by 'admin' using MacroMaker.
//	Macro Notes: [Modified 14:28 10/11/2018] This is a great test!
void FEOtsUDPTemplateInterface::varTest2(__ARGS__)
{
	__CFG_COUT__ << "# of input args = " << argsIn.size() << __E__; 
	__CFG_COUT__ << "# of output args = " << argsOut.size() << __E__; 
	for(auto &argIn:argsIn) 
		__CFG_COUT__ << argIn.first << ": " << argIn.second << __E__; 

	//macro commands section 
	{
		char *address 	= new char[universalAddressSize_]{0};	//create address buffer of interface size and init to all 0
		char *data 		= new char[universalDataSize_]{0};		//create data buffer of interface size and init to all 0
		uint64_t macroAddress;		//create macro address buffer (size 8 bytes)
		uint64_t macroData;			//create macro address buffer (size 8 bytes)
		std::map<std::string /*arg name*/,uint64_t /*arg val*/> macroArgs; //create map from arg name to 64-bit number

		// command-#0: Read(0x1002 /*address*/,myArg /*data*/);
		macroAddress = 0x1002; memcpy(address,&macroAddress,8);	//copy macro address to buffer
		universalRead(address,data);		memcpy(&macroArgs["myArg"],data,8); //copy buffer to argument map
		__SET_ARG_OUT__("myArg",macroArgs["myArg"]); //update output argument result

		// command-#1: Read(0x1001 /*address*/,data);
		macroAddress = 0x1001; memcpy(address,&macroAddress,8);	//copy macro address to buffer
		universalRead(address,data);		memcpy(&macroArgs["outArg1"],data,8); //copy buffer to argument map
		__SET_ARG_OUT__("outArg1",macroArgs["outArg1"]); //update output argument result

		// command-#2: Write(0x1002 /*address*/,myOtherArg /*data*/);
		macroAddress = 0x1002; memcpy(address,&macroAddress,8);	//copy macro address to buffer
		macroArgs["myOtherArg"] = __GET_ARG_IN__("myOtherArg", uint64_t); //initialize from input arguments	//get macro data argument
		memcpy(data,&macroArgs["myOtherArg"],8); //copy macro data argument to buffer
		universalWrite(address,data);

		// command-#3: Write(0x1001 /*address*/,myArg /*data*/);
		macroAddress = 0x1001; memcpy(address,&macroAddress,8);	//copy macro address to buffer	//get macro data argument
		memcpy(data,&macroArgs["myArg"],8); //copy macro data argument to buffer
		universalWrite(address,data);

		// command-#4: delay(4000);
		__CFG_COUT__ << "Sleeping for... " << 4000 << " milliseconds " << __E__;
		usleep(4000*1000 /* microseconds */);


		delete[] address; //free the memory
		delete[] data; //free the memory
	}

	for(auto &argOut:argsOut) 
		__CFG_COUT__ << argOut.first << ": " << argOut.second << __E__; 

} //end varTest2()

DEFINE_OTS_INTERFACE(FEOtsUDPTemplateInterface)
