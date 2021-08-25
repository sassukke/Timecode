#include <iostream>
#include "Time.h"

/*
*
* This method isolates, extract the frames bits and stores the decimal value.
* 
*/

void time::Time::isolateFrameBits() {
  ulint unitBitFrames = loWord & 0x000F;
  ulint tensBitFrames = (loWord >> 8) & 0x0003;
  frames = tensBitFrames * 10 + unitBitFrames;
}


/*
*
* This method isolates, extract the seconds bits and stores the decimal value.
* 
*/

void time::Time::isolateSecondBits() {
  ulint unitBitSeconds = (loWord >> 16) & 0x000F;
  ulint tensBitSeconds = (loWord >> 24) & 0x0007;
  seconds = tensBitSeconds * 10 + unitBitSeconds;
}


/*
*
* This method isolates, extract the minutes bits and stores the decimal value.
* 
*/

void time::Time::isolateMinuteBits() {
  ulint unitBitMinutes = hiWord & 0x000F;
  ulint tensBitMinutes = (hiWord >> 8) & 0x0007;
  minutes = tensBitMinutes * 10 + unitBitMinutes;
}


/*
*
* This method isolates, extract the hours bits and stores the decimal value.
* 
*/

void time::Time::isolateHourBits() {
  ulint unitBitHours = (hiWord >> 16) & 0x000F;
  ulint tensBitHours = (hiWord >> 24) & 0x0003;
  hours = tensBitHours * 10 + unitBitHours;
}


/*
* 
* This method isolates and extracted the time bits from HiWord, LoWord bit encoding:
* - Bit encoding from LTC\SMPTE linear code: 00 - 03 Frame number units (0 - 9), 08 - 09 Frame number tens (0 - 2).                            
* - Bit encoding from LTC\SMPTE linear code: 16 - 19 Frame number units (0 - 9), 24 - 26 Frame number tens (0 - 5).                              
* - Bit encoding from LTC\SMPTE linear code: 32 - 35 Frame number units (0 - 9), 40 - 42 Frame number tens (0 - 5).                                  
* - Bit encoding from LTC\SMPTE linear code: 48 - 51 Frame number units (0 - 9), 56 - 57 Frame number tens (0 - 2).
*
* Resources:
* https://en.wikipedia.org/wiki/Linear_timecode#Longitudinal_timecode_data_format
* https://www2.d125.org/applied_arts/teched/courses/AV/files/timecode.pdf
* 
*/

void time::Time::calculateTimeUnits() {
  isolateFrameBits();
  isolateSecondBits();
  isolateMinuteBits();
  isolateHourBits();
}

/*
* 
* This method displays the time extracted from HiWord, LoWord bit encoding
* in the "HH:MM:SS:FF" format required by LTC/SMPTE linear code.
* 
*/

void time::Time::displayTimeCodeReadable() {
  calculateTimeUnits();
  std::cout << "time code in format HH:MM:SS:FF from array = " << hours << ":" << minutes << ":" << seconds << ":" << frames << "\n";
}