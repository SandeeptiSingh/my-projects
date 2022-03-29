/*
 * COMP2011 (Fall 2021) Programming Assignment 1
 *
 * Student name: SINGH, Sandeepti 
 * Student ID: 20679259
 * Student email: ssinghaf@connect.ust.hk
 *
 */

#include <iostream>
#include <limits>
using namespace std;

// Global Constants
// You cannot modify these global constants
// You cannot use your own global variables
const int MAX_ARR_LEN = 16;
const int MAX_ROTATIONS = 1024;
// End of Global Constants

// Helper Functions
// Declare additional helper functions below when necessary
// int myHelperFunction(int argc, char *argv[])
// End of Helper Functions

// Tasks
// Please write your code under the TODO tag
// You cannot change the function declarations

// Task 1
int rotate(int arr[], int arrLen, int k)
{
    // Task 1 TODO

    if (k >= arrLen || k < 0)
    { // return error message if k is longer than the length or less than 0
        cout << "Error: Index k is out of range." << endl;
        return -1;
    }

    else
    {
        int temp_arr[arrLen]; //copying existing array into a temporary array
        for (int j = 0; j < arrLen; j++)
        {
            temp_arr[j] = arr[j];
        }
        for (int i = 0; i <= k; i++)
        { //swapping the elements and storing them in the tmep array
            temp_arr[i] = arr[k - i];
        }
        for (int k = 0; k < arrLen; k++)
        { //passing the value of temp array to main array
            arr[k] = temp_arr[k];
        }

        return arr[arrLen];
    }
    return 0; 
    // End of Task 1 TODO
}

//Task 2
int swapAndRecord(int arr[], int arrLen, int indexA, int indexB, int rotations[], int &rotationLen)
{
    // Task 2 TODO
    if (indexA >= arrLen || indexA < 0 || indexB >= arrLen || indexB < 0)
    { // to display the error message
        cout << "Error: Index out of range." << endl;
        return -1;
    }

    else
    {
        int k = 0;
        int R, L;
        int tempRotations[6] = {0, 0, 0, 0, 0, 0};

        if (indexA < indexB) // ensuring that the smaller of the indexes entered is L
        {
            R = indexB;
            L = indexA;
        }
        else
        {
            R = indexA;
            L = indexB;
        }

        int temp = 0; // var declared to keep track of the index of the rotations
        rotationLen = 0;

        // adding in the swap functions as explained in the logic
        // but checking if k is within the arrlen and also not already 0 before each swap

        k = L - 1;
        if (k < arrLen && k >= 0)
        {
            tempRotations[temp] = k;
            rotationLen = rotationLen + 1; //increasing rotationlen each time
            rotate(arr, arrLen, k);
            temp = temp + 1;
        }

        k = L;
        if (k < arrLen && k >= 0)
        {
            tempRotations[temp] = k;
            rotationLen = rotationLen + 1;
            rotate(arr, arrLen, L);
            temp = temp + 1;
        }

        k = R;
        if (k < arrLen && k >= 0)
        {
            tempRotations[temp] = k;
            rotationLen = rotationLen + 1;
            rotate(arr, arrLen, R);
            temp = temp + 1;
        }

        k = R - L - 1;
        if (k < arrLen && k >= 0)
        {
            tempRotations[temp] = k;
            rotationLen = rotationLen + 1;
            rotate(arr, arrLen, k);
            temp = temp + 1;
        }

        k = R - L - 2;
        if (k < arrLen && k >= 0)
        {
            tempRotations[temp] = k;
            rotationLen = rotationLen + 1;
            rotate(arr, arrLen, R - L - 2);
            temp = temp + 1;
        }

        k = R - 1;
        if (k < arrLen && k >= 0)
        {
            tempRotations[temp] = k;
            rotationLen = rotationLen + 1;
            rotate(arr, arrLen, R - 1);
            temp = temp + 1;
        }

        for (int i = 0; i < rotationLen; i++)
        {
            rotations[i] = tempRotations[i];
        }
        return 0;
    }

    // End of Task 2 TODO
}

//Task 3
void sortAndRecord(int arr[], int arrLen, int rotations[], int &rotationLen)
{
    // Task 3 TODO
    rotationLen = 0;
    int tempArray[MAX_ROTATIONS]; // creating a temporary array to store the roations
    int l = 0;                    // to prevent rotations from being reset to 0 each time
    int m = 0;

    for (int i = 0; i < arrLen - 1; i++)
    {
        for (int j = 0; j < arrLen - 1 - i; j++)
        {

            if (arr[j] > arr[j + 1])
            {
                swapAndRecord(arr, arrLen, j, j + 1, rotations, rotationLen);
                for (int k = 0; k < rotationLen; k++)
                {
                    tempArray[l] = rotations[k];
                    l = l + 1;
                    m = m + 1;
                }
            }
        }
    }
    int n = 0;
    rotationLen = m;

    while (n < l)
    {
        rotations[n] = tempArray[n];
        n = n + 1;
    }

    // End of Task 3 TODO
}

//Task 4
int transformAndRecord(int src[], int tgt[], int arrLen, int rotations[], int &rotationLen)
{
    // Task 4 TODO
    int tempsrc[16];
    int temptgt[16];
    int temparray[16];

    for (int p = 0; p < arrLen; p++)
    { // copying src into a tempsrc to sort it
        tempsrc[p] = src[p];
    }

    for (int i = 0; i < arrLen; i++)
    { // copying tgt into a temptgt to sort it
        temptgt[i] = tgt[i];
    }
    sortAndRecord(tempsrc, arrLen, rotations, rotationLen); //sorting both the temp functions
    sortAndRecord(temptgt, arrLen, rotations, rotationLen); // so that their digits can be compared

    int count = 0;
    for (int j = 0; j < arrLen; j++)
    {
        if (tempsrc[j] == temptgt[j]) // counting the number of matching digits
        {
            count = count + 1;
        }
    }
    if (count != arrLen) // if all digits don't match then error message is sent
    {
        return -1;
    }

    else
    {

        rotationLen = 0;
        int temp = 0;
        int l = 0;
        int p = 0;
        int tempArrayTwo [MAX_ARR_LEN]; // temp array to hold rotations

        for (int m = 0; m < arrLen; m++)
        {
            while (src[m] != tgt[m])
            {

                for (int n = 0; n < arrLen; n++)
                {
                    if (tgt[m] == src[n])
                    {
                        
                        swapAndRecord(src, arrLen, m, n, rotations, rotationLen);
                        for (int k = 0; k < rotationLen; k++)
                        {
                            tempArrayTwo[l] = rotations[k];
                            l = l + 1;
                            p = p + 1;
                        }
                    }
                }
            }
        }

    
    int r = 0;
    rotationLen = p;

    while (r < l)
    {
        rotations[r] = tempArrayTwo[r]; // copying temp array to rotations
        r = r + 1;
    }
    }
    return 0;
    // End of Task 4 TODO
 }

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

int init(int arr[], int arrLen)
{
    char buffer;
    cout << "? Please enter one digit at a time and press return:" << endl;
    for (int i = 0; i < arrLen; i++)
    {
        cin >> buffer;
        if (buffer > '9' || buffer < '0')
        {
            cout << "Error: Illegal digit input." << endl;
            return -1;
        }
        else
        {
            arr[i] = (int)buffer - 48;
        }
    }
    return 0;
}

void printArr(int arr[], int arrLen)
{
    for (int i = 0; i < arrLen; i++)
    {
        cout << arr[i];
        if (i < arrLen - 1)
        {
            cout << ',';
        }
    }
    cout << endl;
}

void runInit(int arr[], int &arrLen)
{
    cout << "##################################################" << endl;
    cout << "# Initializing" << endl;
    cout << endl;

    int initResult = -1;
    while (initResult < 0)
    {
        cout << "? Enter the length of your array:" << endl;
        cin >> arrLen;
        if (arrLen < 1)
        {
            cout << "! Error: Length should be larger than 0." << endl;
            continue;
        }
        else if (arrLen > MAX_ARR_LEN)
        {
            cout << "Error: arrLen of should be less than or equal to " << MAX_ARR_LEN << endl;
            continue;
        }
        cout << "? Enter " << arrLen << " elements of your array." << endl;
        initResult = init(arr, arrLen);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "! Initialization succeeded!" << endl;
    cout << "! Printing the array:" << endl;
    cout << endl;
    printArr(arr, arrLen);
    cout << endl;
}

void runPrint(int arr[], int arrLen)
{
    cout << "##################################################" << endl;
    cout << "# Printing the array" << endl;
    cout << endl;
    printArr(arr, arrLen);
    cout << endl;
}

void runRotate(int arr[], int arrLen)
{
    int k, output;
    cout << "##################################################" << endl;
    cout << "# Rotating the array:" << endl;
    cout << "? Enter the index k:";
    cin >> k;
    output = rotate(arr, arrLen, k);
    if (output < 0)
    {
        cout << "! Error: Rotation failed." << endl;
    }
    else
    {
        cout << "! Rotated." << endl;
        cout << "! Array after rotation:" << endl;
        cout << endl;
        printArr(arr, arrLen);
        cout << endl;
    }
}

void runSwap(int arr[], int arrLen)
{
    int indexA, indexB, rotations[MAX_ROTATIONS], rotationLen, output;
    cout << "##################################################" << endl;
    cout << "# Swapping elements:" << endl;
    cout << "? Enter the 1st index:";
    cin >> indexA;
    cout << "? Enter the 2nd index:";
    cin >> indexB;
    output = swapAndRecord(arr, arrLen, indexA, indexB, rotations, rotationLen);
    if (output < 0)
    {
        cout << "! Error: Swap failed." << endl;
    }
    else
    {
        cout << "! Swapped." << endl;
        cout << "! Array after swap:" << endl;
        cout << endl;
        printArr(arr, arrLen);
        cout << endl;
        cout << "! Rotations:" << endl;
        cout << endl;
        printArr(rotations, rotationLen);
        cout << endl;
    }
}

void runSort(int arr[], int arrLen)
{
    int from, to, rotations[MAX_ROTATIONS], rotationLen, output;
    cout << "##################################################" << endl;
    cout << "# Sorting the array:" << endl;
    sortAndRecord(arr, arrLen, rotations, rotationLen);
    cout << "! Sorted." << endl;
    cout << "! Array after sorting:" << endl;
    cout << endl;
    printArr(arr, arrLen);
    cout << endl;
    cout << "! Rotations:" << endl;
    cout << endl;
    printArr(rotations, rotationLen);
    cout << endl;
}

void runTransform(int arr[], int arrLen)
{
    int from, to, rotations[MAX_ROTATIONS], rotationLen, output;
    cout << "##################################################" << endl;
    cout << "# Transforming src array to the tgt:" << endl;
    int tgt[MAX_ARR_LEN], initResult = -1;
    while (initResult < 0)
    {
        cout << "? Enter " << arrLen << " elements of the tgt array." << endl;
        initResult = init(tgt, arrLen);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "! The target array:" << endl;
    cout << endl;
    printArr(tgt, arrLen);
    cout << endl;
    output = transformAndRecord(arr, tgt, arrLen, rotations, rotationLen);
    if (output < 0)
    {
        cout << "! Error: Cannot transform array to target." << endl;
    }
    else
    {
        cout << "! Transformed." << endl;
        cout << "! Array after transformation:" << endl;
        cout << endl;
        printArr(arr, arrLen);
        cout << endl;
        cout << "! Rotations:" << endl;
        cout << endl;
        printArr(rotations, rotationLen);
        cout << endl;
    }
}

void runOption()
{
    int arrLen = 0;
    bool is_initialized = false;
    int src[MAX_ARR_LEN];
    int tgt[MAX_ARR_LEN];
    int option;
    cout << "===========================================" << endl;
    cout << "= Welcome to COMP2011 PA1 1D Rubik's Cube =" << endl;
    cout << "===========================================" << endl;

    while (true)
    {
        if (!is_initialized)
        {
            runInit(src, arrLen);
            is_initialized = true;
        }
        else
        {
            cout << "##################################################" << endl;
            cout << "# Main Menu" << endl;
            cout << endl;
            cout << "1 Initialize" << endl;
            cout << "2 Print" << endl;
            cout << "3 Rotate" << endl;
            cout << "4 Swap" << endl;
            cout << "5 Sort" << endl;
            cout << "6 Transform" << endl;
            cout << "0 Exit" << endl;
            cout << endl;
            cout << "? Please enter an option (0-6): ";
            cin >> option;
            switch (option)
            {
            case 0:
                cout << "! Bye Bye." << endl;
                return;
            case 1:
                runInit(src, arrLen);
                break;
            case 2:
                runPrint(src, arrLen);
                break;
            case 3:
                runRotate(src, arrLen);
                break;
            case 4:
                runSwap(src, arrLen);
                break;
            case 5:
                runSort(src, arrLen);
                break;
            case 6:
                runTransform(src, arrLen);
                break;
            default:
                cout << "Illegal Choice, please try again." << endl;
                break;
            }
            cout << "! Returning to main menu." << endl;
        }
    }
}

int main()
{
    runOption();
    return 0;
}