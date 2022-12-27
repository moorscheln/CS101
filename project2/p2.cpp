#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>

using namespace std;

void Merge(int numbers[], int i, int j, int k)
{
    int mergedSize; // Size of merged partition
    int mergePos;   // Position to insert merged number
    int leftPos;    // Position of elements in left partition
    int rightPos;   // Position of elements in right partition
    int *mergedNumbers = nullptr;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                         // Initialize left partition position
    rightPos = j + 1;                    // Initialize right partition position
    mergedNumbers = new int[mergedSize]; // Dynamically allocates temporary array
                                         // for merged numbers

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k)
    {
        if (numbers[leftPos] < numbers[rightPos])
        {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        }
        else
        {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j)
    {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k)
    {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
    {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
    delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k)
{
    int j;

    if (i < k)
    {
        j = (i + k) / 2; // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}

string Lowercase(string inputString)
{
    for (int i = 0; i < inputString.length(); i++)
    {
        if (isalpha(inputString[i]) && (isupper(inputString[i])))
            inputString[i] = inputString[i] + 32;
    }
    return inputString;
}

int Partition(string strings[], int i, int k)
{
    int l;
    string strL;
    int h;
    string strH;
    int midpoint;
    string strMidpoint;
    string strPivot;
    string strTemp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    strPivot = strings[midpoint];

    done = false;
    l = i;
    h = k;

    while (!done)
    {

        /* Increment l while numbers[l] < pivot */
        while (strings[l] < strPivot)
        {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (strPivot < strings[h])
        {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h)
        {
            done = true;
        }
        else
        {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            strTemp = strings[l];
            strings[l] = strings[h];
            strings[h] = strTemp;

            ++l;
            --h;
        }
    }

    return h;
}

void Quicksort(string strings[], int i, int k)
{
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k)
    {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(strings, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    Quicksort(strings, i, j);
    Quicksort(strings, j + 1, k);
}

ifstream OpenFile(int argc, string argv)
{
    if (argc != 4)
    {
        cout << "Usage: ./a i/s input1.txt input2.txt" << endl;
        exit(0);
    }

    string filename = argv;
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Could not open file " << filename << endl;
        exit(0);
    }
    return infile;
}

// int DoesExist(int search, int input1[], int input1size, int input2[], int input2size)
// {
//     for (int i = 0; i < input1size; i++)
//     {
//         if (search == input1[i])
//         {
//         }
//     }
// }

bool SearchExist(int search, int input[], int inputsize)
{
    if (inputsize == 0)
    {
        return false;
    }
    for (int i = 0; i < inputsize; i++)
    {
        if (search == input[i])
        {
            return true;
        }
    }
    return false;
}

bool StringExist(string search, string input[], int inputsize)
{
    if (inputsize == 0)
    {
        return false;
    }
    for (int i = 0; i < inputsize; i++)
    {
        if (search == input[i])
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    // argv1 is either "i" or "s"
    string iors = argv[1];
    string filename1 = argv[2];
    string filename2 = argv[3];
    ifstream infile1(filename1);
    ifstream infile2(filename2);

    int both = 0;

    string str1[20000];
    string str2[20000];
    string bothStrArray[20000];

    int bothIntArray[20000];
    int int1[20000];
    // int int2[20000];

    int i1 = 0;
    // int i2 = 0;

    // int bothCount = 0;
    // int integerCounter = 0;

    int inputInt1 = 0;
    int inputInt2 = 0;
    string inputStr1 = "";
    string inputStr2 = "";

    bool doesIntExist1 = false;
    bool doesIntExist2 = false;
    bool DoesStrExist1 = false;
    bool DoesStrExist2 = false;

    if (iors == "i")
    {
        while (1) // while loop for 1st File
        {
            if (infile1.eof())
            {
                break;
            }
            infile1 >> inputInt1;

            int1[i1] = inputInt1;
            i1++;
            // see if number already exists, if it does, do not add to array (dont't increment i1), else input into array and increment i1
            // if (i1 == 0)
            // {
            //     intArray[0] = inputInt1;
            //     i1 = 1;
            // }
            // else
            // {
            //     for (int i = 0; i < i1; i++)
            //     {
            //         // cout << id[i];
            //         if (intArray[i] == inputInt1 )
            //         {
            //             doesIntExist = true;
            //             bothIntArray[bothCount] = inputInt1;
            //             bothCount++;

            //             intArray[i1] = inputInt1;
            //             i1++;
            //             break;
            //         }
            //         else
            //         {
            //             intArray[i1] = inputInt1;
            //             i1++;
            //             break;
            //         }
            //     }
            // }

            // int1[i1] = inputInt1;
            // i1++;
        }
        while (1) // while loop for 2nd File
        {
            if (infile2.eof())
            {
                break;
            }
            infile2 >> inputInt2;
            doesIntExist1 = SearchExist(inputInt2, int1, i1);
            if (doesIntExist1)
            {
                doesIntExist2 = SearchExist(inputInt2, bothIntArray, both);
                if (!doesIntExist2)
                {
                    bothIntArray[both] = inputInt2;
                    both++;
                }
            }
            // int2[i2] = inputInt2;
            // i2++;
            // see if number already exists, if it does, do not add to array (dont't increment i1), else input into array and increment i1
        }

        // for (int j = 0; j < i1; j++)
        // {
        //     for (int q = 0; q < i2; q++)
        //     {
        //         // cout << "int1[" << j << "] == " << int1[j] << " | int2[" << q << "] == " << int2[q] << endl;
        //         if (int1[j] == int2[q])
        //         {
        //             if (both > 0)
        //             {
        //                 for (int a = both - 1; a >= 0; a--)
        //                 {

        //                     if ((bothIntArray[a] != int1[j]) && (bothIntArray[a] != int2[q]))
        //                     {

        //                         doubleCount++;
        //                         if (doubleCount == 1)
        //                         {

        //                             bothIntArray[both] = int1[j];
        //                             cout << both << " " << bothIntArray[both] << endl;
        //                             both++;
        //                         }
        //                     }
        //                     else
        //                     {
        //                         break;
        //                     }
        //                 }
        //             }
        //             else
        //             {

        //                 bothIntArray[both] = int1[j];
        //                 cout << both << " " << bothIntArray[both] << endl;
        //                 both++;
        //             }
        //         }
        //     }
        //     doubleCount = 0;
        //     check++;
        // }

        // for (int i = 0; i < both; i++)
        // {
        //     // cout << "sizedBothInt[" << i << "] == " << sizedBothInt[i] << endl;
        //     cout << bothIntArray[i] << endl;
        // }

        // for (int i = 0; i < numBig; i++)
        // {

        //     if (int1[check] == int2[i])
        //     {

        //         doubleCount++;
        //         // cout << intArray[check] << " " << intArray[i] << " " << doubleCount << endl;
        //         if (doubleCount == 1)
        //         {
        //             bothIntArray[both] = int1[check];
        //             both++;
        //         }
        //     }
        // }
        // doubleCount = 0;
        // check++;
        // }
        // cout << "both == " << both << endl;
        // both = both - 1;
        // cout << "both == " << both << endl;
        // int sizedBothInt[both];

        // PERFORM MERGE SORT ON bothIntArray
        // bothIntArray should be of size both after 1 is subtracted

        MergeSort(bothIntArray, 0, both - 1);
        for (int i = 0; i < both; i++)
        {
            // cout << "sizedBothInt[" << i << "] == " << sizedBothInt[i] << endl;
            cout << bothIntArray[i] << endl;
        }
    }
    else if (iors == "s")
    {
        while (1) // while loop for 1st File
        {
            if (infile1.eof())
            {
                break;
            }
            infile1 >> inputStr1;
            // Lowercase(inputStr1);

            str1[i1] = inputStr1;

            i1++;
        }
        while (1) // while loop for 2nd File
        {
            if (infile2.eof())
            {
                break;
            }
            infile2 >> inputStr2;
            DoesStrExist1 = StringExist(inputStr2, str1, i1);
            if (DoesStrExist1)
            {
                DoesStrExist2 = StringExist(inputStr2, bothStrArray, both);
                if (!DoesStrExist2)
                {
                    bothStrArray[both] = inputStr2;
                    both++;
                }
            }
            // str2[i2] = inputStr2;
            // i2++;
        }
        // check = 0;
        // int numBig = 0;
        // int numSmall = 0;
        // if (i1 <= i2)
        // {
        //     numBig = i2;
        //     numSmall = i1;
        // }
        // else
        // {
        //     numBig = i1;
        //     numSmall = i2;
        // }
        // for (int j = 0; j < i1; j++)
        // {
        //     for (int q = 0; q < i2; q++)
        //     {
        //         if (str1[j] == str2[q])
        //         {
        //             if (both > 0)
        //             {
        //                 for (int a = both - 1; a >= 0; a--)
        //                 {
        //                     if ((bothStrArray[a] != str1[j]) && (bothStrArray[a] != str2[q]))
        //                     {
        //                         doubleCount++;
        //                         if (doubleCount == 1)
        //                         {
        //                             bothStrArray[both] = str1[j];
        //                             both++;
        //                         }
        //                     }
        //                     else
        //                     {
        //                         break;
        //                     }
        //                 }
        //             }
        //             else
        //             {
        //                 bothStrArray[both] = str1[j];
        //                 both++;
        //             }
        //         }
        //     }
        //     doubleCount = 0;
        //     check++;
        // }
        // check = 0;
        // cout << both << endl;
        // for (int i = 0; i < both; i++)
        // {
        //     cout << bothStrArray[i] << endl;
        // }

        Quicksort(bothStrArray, 0, both - 1);

        for (int i = 0; i < both; i++)
        {
            cout << bothStrArray[i] << endl;
        }
    }

    infile1.close();
    infile2.close();

    return 0;
}