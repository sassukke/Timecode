#pragma once
#include <string>

#ifndef TIME_H
#define TIME_H

typedef unsigned long ulint;
typedef unsigned long long ullint;

namespace time {
  // Bit encoding: 0 - 31 bits (LoWord) and 32 - 63 bits (HiWord)
  class Time {
  private:
    // Contains the "HiWord" extracted from nlohman::json object
    ulint hiWord;
    // Contains the "LoWord" extracted from nlohman::json object
    ulint loWord;
    // Contains the bit combination of "HiWord" and "LoWord" extracted from nlohman::json object
    ullint samples64Bits; 
    // Contains the time bits (frames, seconds, minutes, hours) from concatenated "HiWord" and "LoWord" field value from nlohman::json object
    ullint time64Bits; 

    // Contains the bit encoding from SMPTE linear code: 00 - 03 Frame number units (0 - 9), 08 - 09 Frame number tens (0 - 2)
    unsigned int frames;                                      
    // Contains the bit encoding from SMPTE linear code: 16 - 19 Frame number units (0 - 9), 24 - 26 Frame number tens (0 - 5)
    unsigned int seconds;                                     
    // Contains the bit encoding from SMPTE linear code: 32 - 35 Frame number units (0 - 9), 40 - 42 Frame number tens (0 - 5)
    unsigned int minutes;                                     
    // Contains the bit encoding from SMPTE linear code: 48 - 51 Frame number units (0 - 9), 56 - 57 Frame number tens (0 - 2)
    unsigned int hours;

    void isolateFrameBits();
    void isolateSecondBits();
    void isolateMinuteBits();
    void isolateHourBits();

  public:
    // This method returns the HiWord time value.
    ulint getHiWord() const {
      return hiWord;
    }

    // This method returns the LoWord time value.
    ulint getLoWord() const {
      return loWord;
    }

    // This method returns the concatenated HiWord field value and LoWord field.
    ullint getSamples64Bits() const {
      return samples64Bits;
    }

    // This method returns just the time bits from the 64 bits sample according to the SMPTE linear code. The non-time bits are set to 0 by a mask.
    ullint getTimeBitsIsolated() {
      time64Bits = samples64Bits & 0x30F070F070F030F;
      return time64Bits;
    }

    // This method sets the "HiWord" value from JSON file in Time object data.
    void setHiWord(const ulint _hiWord) {
      hiWord = _hiWord;
    }

    // This method sets the "LoWord" value from JSON file in Time object data.
    void setLoWord(const ulint _loWord) {
      loWord = _loWord;
    }

    // This method concatenates the HiWord field value and LoWord field value.
    void setConcatenatedSamples64Bits() {
      samples64Bits = std::stoull(std::to_string(hiWord) + std::to_string(loWord));
    }

    // This method combines bitwise the HiWord field value and LoWord field value. Value is not human readable in it's brute form.
    void setSamples64Bits() {
      samples64Bits = ( (ullint) hiWord << 32) | loWord;
    }

    void calculateTimeUnits      ();
    void displayTimeCodeReadable ();
  };
}

#endif // TIME_H