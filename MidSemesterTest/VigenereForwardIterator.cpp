#include "VigenereForwardIterator.h"

#include <cctype>
#include <string>

//Conver a character to its correponding index
int charToIndex(char c) {
    return c - 'A';
}

//Conver an index to its corresponding character
char indexToChar(int i) {
    return 'A' + (i % 26);
}

//Decoding a character
void VigenereForwardIterator::encodeCurrentChar() noexcept
{
    if (fIndex >= fSource.size()) 
        return; // Beyond the end of the source
    else
    {
        char lSourceChar = fSource[fIndex];

        if (!isalpha(lSourceChar)) 
        {
            fCurrentChar = lSourceChar; // Non-alphabetic characters are not encoded
            return;
        }
        else
        {   
            bool isLowerCase = islower(lSourceChar); //Check for source character's case
            
            lSourceChar = toupper(lSourceChar); // Convert source character to uppercase for table lookup

            char lKeyChar = *fKeys; // Convert key character to uppercase

            // Advance key provider and check if it's at the end
            KeyProvider lTemp = fKeys;
            if (++lTemp == fKeys.end()) {
                fKeys = fKeys.begin(); // Reset to start
            }
            else {
                ++fKeys; // Normal increment
            }

            //Convert the characters to indices for lookup
            int lRow = charToIndex(lKeyChar); 
            int lCol = charToIndex(lSourceChar); 

            char encodedChar = fMappingTable[lRow][lCol]; // Get encoded character from the table

            fCurrentChar = isLowerCase ? tolower(encodedChar) : encodedChar; // Preserve case
        }
       
    }
}

void VigenereForwardIterator::decodeCurrentChar() noexcept
{
    if (fIndex >= fSource.size()) 
        return; // Beyond the end of the source
    else
    {
        char lSourceChar = fSource[fIndex];
        if (!isalpha(lSourceChar)) {
            fCurrentChar = lSourceChar; // Non-alphabetic characters are not decoded
            return;
        }
        else
        {
            bool isLowerCase = islower(lSourceChar); //Check for source character's case

            lSourceChar = toupper(lSourceChar); // Convert cipher character to uppercase for table lookup

            char keyChar = *fKeys; // Convert key character to uppercase

            // Advance key provider and check if it's at the end
            KeyProvider temp = fKeys;
            if (++temp == fKeys.end()) {
                fKeys = fKeys.begin(); // Reset to start
            }
            else {
                ++fKeys; // Normal increment
            }

            //Convert the key character to index for lookup
            int lRow = charToIndex(keyChar);

            // Find the column index in the `row` that matches the `lSourceChar`
            int lCol = 0;
            while (fMappingTable[lRow][lCol] != lSourceChar) {
                lCol++;
            }

            char decodedChar = indexToChar(lCol); // Get the decoded character by finding the column index

            fCurrentChar = isLowerCase ? tolower(decodedChar) : decodedChar; // Preserve case
        }
    }

    
}

//Constructor
VigenereForwardIterator::VigenereForwardIterator(
    const std::string& aKeyword,
    const std::string& aSource,
    EVigenereMode aMode) noexcept :
    fKeys(aKeyword, aSource),
    fSource(aSource),
    fMode(aMode),
    fIndex(0)
{
    initializeTable();
    if (fIndex < fSource.size()) {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        }
        else {
            decodeCurrentChar();
        }
    }
}

//Dereference operator: return the current character
char VigenereForwardIterator::operator*() const noexcept
{
    return fCurrentChar;
}

//Prefix advance operator
VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept
{
    fIndex++;

    //Check for out-of-bound
    if (fIndex < fSource.size()) 
    {
        if (fMode == EVigenereMode::Encode) 
        {
            encodeCurrentChar();
        }
        else 
        {
            decodeCurrentChar();
        }
    }

    return *this;
}

//Postfix advance operator
VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept
{
    VigenereForwardIterator lTemp = *this;

    ++(*this);

    return lTemp;
}

//Equivalence operator
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept
{
    return (fIndex == aOther.fIndex && fSource == aOther.fSource);
}

//Inequivalence operator
bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept
{
    return !(*this == aOther);
}

//Return an VigenereForwardIterator iterator at the first character
VigenereForwardIterator VigenereForwardIterator::begin() const noexcept
{
    VigenereForwardIterator lResult(*this); // Make a copy of the current iterator

    //Reset the index to 0
    lResult.fIndex = 0;
    
    //Reset the key iterator to the beginning
    lResult.fKeys = fKeys.begin();

    if (lResult.fIndex < lResult.fSource.size()) {
        if (lResult.fMode == EVigenereMode::Encode) {
            lResult.encodeCurrentChar(); // Encode the first character if in encode mode
        }
        else {
            lResult.decodeCurrentChar(); // Decode the first character if in decode mode
        }
    }

    return lResult;
}
//Return an VigenereForwardIterator iterator after the last character
VigenereForwardIterator VigenereForwardIterator::end() const noexcept
{
    VigenereForwardIterator lResult(*this); // Make a copy of the current iterator
    
    lResult.fIndex = fSource.size(); // Set the index past the last character

    lResult.fKeys = fKeys.end(); // Set fKeys to the end of the key sequence

    // No need to encode or decode since lResult represents the end position

    return lResult;
}