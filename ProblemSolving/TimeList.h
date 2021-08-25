#pragma once

#ifndef TIMELIST_H
#define TIMELIST_H

#include <nlohmann/json.hpp>
#include <list>

#include "Time.h"

// Utility struct for sorting algorithm.
struct CompareTimesAscending {
  bool operator()(time::Time &first, time::Time &second) {
    return (first.getTimeBitsIsolated() < second.getTimeBitsIsolated());
  }
};

namespace timeList {
  class TimeList {
    private:
      // List of Time's objects that stores HiWord, LoWord and merged value of them.
      std::list<time::Time> timePackages;

      void extractSamplePackagesJsonWrap (nlohmann::json);
      void mergeSamplePackages   ();
      void extractTimeFromSample ();
      void displayTimeCodeReadableWrap ();
      void ascendingSortTime ();
      void displayMinMaxWrap ();
      void findSpecificValueWrap (const int);

    public:

      // This function calls it's wrap-up function where computations are performed.
      void extractSamplePackagesJson(nlohmann::json _jsonData) {
        extractSamplePackagesJsonWrap(_jsonData);
      }
      
      // This function calls it's wrap-up function where computations are performed.
      void displayTimeCodeReadable (){
        displayTimeCodeReadableWrap ();
      }
 
      // This function calls it's wrap-up function where computations are performed.     
      void displayMinMax() {
        displayMinMaxWrap();
      }

      // This function calls it's wrap-up function where computations are performed.
      void findSpecificValue(const int _indexList) {
        findSpecificValueWrap(_indexList);
      }

      void run();
  };
}

#endif // TIMELIST_H