#include <iostream>
#include <string>

#include "TimeList.h"

/*
*
* This method parses the nlohmann::json array data from "Timecodes" field. 
* It takes over the data from each array element field (HiWord and LoWord) in a Time object.
* Each Time object is added by the end of TimeList for further computations.
* 
* /parameter _jsonData The nlohmann::json object with filled data.
*/

void timeList::TimeList::extractSamplePackagesJsonWrap(nlohmann::json _jsonData) {
  std::string stringData = _jsonData.dump();
  nlohmann::json const parsedData = nlohmann::json::parse(stringData);
  nlohmann::json const & arrayData = parsedData["Timecodes"];
  
  for (auto it = arrayData.begin(); it != arrayData.end(); ++it) {
    time::Time currentTime;
    if (it->contains("HiWord")) {
      currentTime.setHiWord((*it)["HiWord"].get<long>());
    }
    if (it->contains("LoWord")) {
      currentTime.setLoWord((*it)["LoWord"].get<long>());
    }
    timePackages.push_back(currentTime);
  }
}


/*
*
* This method concatenates the HiWord, LoWord values for each of the Time objects from TimeList.
* 
*/

void timeList::TimeList::mergeSamplePackages() {
  const std::list<time::Time>::iterator end = timePackages.end();
  for (std::list<time::Time>::iterator it = timePackages.begin(); it != end; ++it) {
    it->setConcatenatedSamples64Bits();
  }
}


/*
*
* This method extracts the time bits from concatenated sample values of HiWord and LoWord fields for each TimeList member.
* 
* 
*/

void timeList::TimeList::extractTimeFromSample() {
  const std::list<time::Time>::iterator end = timePackages.end();
  for (std::list<time::Time>::iterator it = timePackages.begin(); it != end; ++it) {
    it->getTimeBitsIsolated();
  }
}


/*
*
* This method calls the HiWord, LoWord sample merge function,
* extract the time bit fields by setting to zero the non-time bit fields from concatenated sample values and 
* the in the ascending way the TimeList elements.
* 
*/

void timeList::TimeList::run() {
  mergeSamplePackages();
  extractTimeFromSample();
  ascendingSortTime();
}

/*
* 
* This method displays the time extracted from HiWord, LoWord bit encoding
* in the "HH:MM:SS:FF" format required by LTC/SMPTE linear code.
* 
*/

void timeList::TimeList::displayTimeCodeReadableWrap() {
  const std::list<time::Time>::iterator end = timePackages.end();
  for (std::list<time::Time>::iterator time = timePackages.begin(); time != end; ++time) {
    time->displayTimeCodeReadable();
  }
}


/*
*
* This method sorts in an ascending way the TimeList elements.
* 
*/

void timeList::TimeList::ascendingSortTime() {
  timePackages.sort(CompareTimesAscending());
}


/*
*
* This method displays the minimum and the maximum values from the ascending sorted TimeList.
* In this case minimum value is the first element of the list and
* the maximum value is the last element of the list.
* 
*/

void timeList::TimeList::displayMinMaxWrap() {
  const std::list<time::Time>::iterator begin = timePackages.begin();
  std::list<time::Time>::iterator end = timePackages.end();
  --end; // decrementation needed because in the list it can be accessed maximum timePackages.size() - 1 element
  std::cout << "The minimum time found in the 'timecodes.json' is ";
  begin->displayTimeCodeReadable();
  std::cout << "The maximum time found in the 'timecodes.json' is ";
  end->displayTimeCodeReadable();
}


/*
*
* This method displays the yyy's element from maximum to minimum value in the ascending sorted TimeList.
* 
* /param _indexList Index of TimeList to identify the yyy's element from maximum to minimum values.
* 
*/

void timeList::TimeList::findSpecificValueWrap(const int _indexList) {
  const std::list<time::Time>::iterator it = std::next(timePackages.begin(), timePackages.size() - _indexList);
  std::cout << "The " << _indexList << "'rd timecode from maximum is ";
  it->displayTimeCodeReadable();
}