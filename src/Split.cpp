#include "Split.h"

namespace Split
{
    void split(String toSplit, char delimiter, String* array, int arraySize, int &count)
    {
        count = 0;

        // Split the string into substrings
        while (toSplit.length() > 0)
        {
            if (count >= arraySize-1) // No more space in array
            {
                array[count++] = toSplit;
                break;
            }

            int index = toSplit.indexOf(delimiter);

            if (index == -1) // No delimiter found
            {
                array[count++] = toSplit;
                break;
            }
            else
            {
                array[count++] = toSplit.substring(0, index);
                toSplit = toSplit.substring(index+1);
            }
        }
    }
}

    