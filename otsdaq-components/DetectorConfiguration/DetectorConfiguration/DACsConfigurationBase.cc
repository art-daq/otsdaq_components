#include "otsdaq-core/ConfigurationDataFormats/DACsConfigurationBase.h"

#include <iostream>

using namespace ots;

//==============================================================================
DACsConfigurationBase::DACsConfigurationBase(std::string configurationName, unsigned int rocNameColumn,
                                             unsigned int firstDAC, unsigned int lastDAC)
    : ConfigurationBase(configurationName), rocNameColumn_(rocNameColumn), firstDAC_(firstDAC), lastDAC_(lastDAC) {}

//==============================================================================
DACsConfigurationBase::~DACsConfigurationBase(void) {}

//==============================================================================
void DACsConfigurationBase::init(ConfigurationManager* configManager) {
  nameToROCDACsMap_.clear();

  std::string tmpDetectorID;
  std::string tmpDACName;
  unsigned int tmpDACValue;
  for (unsigned int row = 0; row < ConfigurationBase::activeConfigurationView_->getNumberOfRows(); row++) {
    ConfigurationBase::activeConfigurationView_->getValue(tmpDetectorID, row, rocNameColumn_);
    nameToROCDACsMap_[tmpDetectorID] = ROCDACs();
    ROCDACs& aROCDACs = nameToROCDACsMap_[tmpDetectorID];
    for (unsigned int col = firstDAC_; col <= lastDAC_; col++) {
      ConfigurationBase::activeConfigurationView_->getValue(tmpDACValue, row, col);
      tmpDACName = ConfigurationBase::activeConfigurationView_->getColumnInfo(col).getName();
      aROCDACs.setDAC(tmpDACName, dacNameToDACAddress_[tmpDACName], tmpDACValue);
      // std::cout << __COUT_HDR_FL__ << "DAC. Name: " << tmpDACName << " addr: " << dacNameToDACAddress_[tmpDACName] <<
      // " val: " << tmpDACValue << std::endl;
    }
  }
}

//==============================================================================
const ROCDACs& DACsConfigurationBase::getROCDACs(std::string rocName) const {
  // FIXME This check should be removed when you are sure you don't have inconsistencies between configurations
  if (nameToROCDACsMap_.find(rocName) == nameToROCDACsMap_.end()) {
    std::cout << __COUT_HDR_FL__ << "ROC named " << rocName << " doesn't exist in any DAC configuration." << std::endl;
    assert(0);
  }
  //
  // for(ots::DACList::const_iterator it = nameToROCDACsMap_.find(rocName)->second.getDACList().begin(); it !=
  // nameToROCDACsMap_.find(rocName)->second.getDACList().end(); ++it) 	std::cout << __COUT_HDR_FL__ << "DAC Name :" <<
  //it->first << ", value: " << it->second.second << std::endl;
  return nameToROCDACsMap_.find(rocName)->second;
}
