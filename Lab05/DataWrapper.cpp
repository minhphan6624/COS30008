#include "DataWrapper.h"

#include <iostream>
#include <fstream>
#include <assert.h>

//Constructor
DataWrapper::DataWrapper() :
    fSize(0),
    fData(nullptr)
{}

//Destructor
DataWrapper::~DataWrapper()
{
    delete[] fData;
}

//Member functions
//Load data from a file
bool DataWrapper::load(const std::string& aFileName)
{
    bool Result = false;

    std::ifstream lInput(aFileName, std::ifstream::in);

    if (lInput)
    {
        if (lInput >> fSize)
        {
            fData = new DataMap[fSize];

            for (size_t i = 0; i < fSize; i++)
            {
                lInput >> fData[i];
            }

            Result = true;
        }

        lInput.close();
    }

    return Result;
}
//Return the size of the data array.
size_t DataWrapper::size() const noexcept
{
    return fSize;
}

//Return a constant reference to the Map object in the array fData
const DataMap& DataWrapper::operator[](size_t aIndex) const
{
    assert(aIndex < fSize);

    return fData[aIndex];
}