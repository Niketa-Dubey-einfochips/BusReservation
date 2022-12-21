#ifndef _StationCode_H_
#define _StationCode_H_
#include<iostream>
#include<vector>

namespace stationcode
{
    const std::vector<std::string> Station {
        "Ahmedabad",
        "Baroda",
        "Surat",
        "Bharuch",
        "Mumbai",
        "Pune"
    };
    enum stCode
    {
        AHM = 0,
        BOD,
        SUT,
        BHA,
        MBI,
        PUN

    };
};

#endif