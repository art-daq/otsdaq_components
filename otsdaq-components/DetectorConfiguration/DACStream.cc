#include "otsdaq-components/DetectorConfiguration/DACStream.h"
#include "otsdaq-core/ConfigurationInterface/ConfigurationTree.h"
#include "otsdaq-components/DetectorConfiguration/FSSRDACsConfiguration.h"

using namespace ots;


//==============================================================================
DACStream::DACStream(void)
{}

//==============================================================================
DACStream::~DACStream(void)
{}

//==============================================================================
void DACStream::makeStream(const ConfigurationTree& feToDetectorTree)
{
	theChannelStreamMap_.clear();
	std::multimap<unsigned int, ROCStream>::iterator currentElement;
	std::string detectorType = "";
	auto feWriterDetectorList = feToDetectorTree.getChildren();

	FSSRDACsConfiguration dacsMaker;
	for(auto& it : feWriterDetectorList)
	{
		const ConfigurationTree& detectorConfiguration = it.second.getNode("LinkToDetectorConfiguration");
		const ConfigurationTree& dacsConfiguration = detectorConfiguration.getNode("LinkToDACsConfiguration");
		const ConfigurationTree& maskConfiguration = detectorConfiguration.getNode("LinkToMaskConfiguration");
		__MOUT__ << feToDetectorTree << std::endl;
		__MOUT__ << detectorConfiguration << std::endl;
		//__MOUT__ << dacsConfiguration << std::endl;
		//__MOUT__ << dacsConfiguration << std::endl;
		currentElement = theChannelStreamMap_.insert(std::pair<unsigned int, ROCStream>(it.second.getNode("FEWriterChannel").getValue<unsigned int>(),ROCStream()));
		currentElement->second.setDetectorID   (it.first);
		detectorType = detectorConfiguration.getNode("DetectorType").getValue<std::string>();
		currentElement->second.setROCType      (detectorType);
		currentElement->second.setROCStatus    (detectorConfiguration.getNode("Status").getValue<bool>());
		currentElement->second.setFEWROCAddress(it.second.getNode("FEWriterDetectorAddress").getValue<unsigned int>());
		currentElement->second.setROCDACs      (dacsMaker.getROCDACs(dacsConfiguration));
		currentElement->second.setROCMask      (maskConfiguration.getNode("KillMask").getValue<std::string>());
	}


}