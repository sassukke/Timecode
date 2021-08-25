
// Timecode programmer test.

#include <nlohmann/json.hpp>

#include <iostream>
#include <string>
#include <fstream>

#include <assert.h>
#include "ProblemSolving/Time.h"
#include "ProblemSolving/TimeList.h"


int main(int argc, char** argv)
{
    std::string filename = (argc == 2) ? argv[1] : "timecodes.json";
    std::cout << "Running program with timecodes from file named '" << filename <<  "'\n";

    nlohmann::json data;
    std::ifstream file(filename);
    file >> data; // This parses the file's contents into the data JSON object.

    assert(data.contains("Timecodes") && data["Timecodes"].is_array());

    // TODO: See README.md

    timeList::TimeList timeProcessing;
    const int indexList = 333;

   timeProcessing.extractSamplePackagesJson(data); // 1. Process the full JSON file.
   timeProcessing.run(); // Intermediate steps: Merge the HiWord and LoWord. Remove the bits that are not related to time from the merged number. Sort the list ascending.
   timeProcessing.displayTimeCodeReadable(); // 2. Print the timecodes within the JSON file in format "HH:MM:SS:FF".
   timeProcessing.displayMinMax(); // 3. Print the minimum and the maximum timecode from the JSON file in format "HH:MM:SS:FF".
   timeProcessing.findSpecificValue(indexList); // 4. Print the timecode that is the yyy'rd from the maximum from the JSON file in format "HH:MM:SS:FF".

    return 0;
}
