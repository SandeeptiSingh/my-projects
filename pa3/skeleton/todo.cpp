//modify and submit this file only
#include "pa3.h"
#include <iostream>
using namespace std;
//you are NOT allowed to include any additional library; see FAQ

TrainCar *createTrainHead()
{
    TrainCar *head = new TrainCar;
    head-> prev = head -> next = nullptr; 
    head->maxLoad = 0;
    head->load = 0;
    head -> type = HEAD; 
    return head;
}

bool addCar(TrainCar *head, int position, CarType type, int maxLoad)
{
    
    
    //retun false if the entered postion is less than 0 or head
    if (position <= 0)
    {
        return false;
    }

    else
    {

        //otherwise I'm creating a temporary node that allows me to move through the list
        TrainCar *newCar = new TrainCar;
        newCar->type = type;
        newCar->next = nullptr;
        newCar->prev = nullptr;
        newCar->load = 0;
        newCar->maxLoad = maxLoad;

        TrainCar *ptr = head;
        int temp = 1;
        

        while (temp < position)
        {
            if (ptr != nullptr)
            {
                ptr = ptr->next;
            }

            temp = temp + 1;
        }

        if (ptr != nullptr)
        {
            newCar->next = ptr->next;
            newCar->prev = ptr;
            ptr->next = newCar;

            if (newCar->next != nullptr)
            {
                newCar->next->prev = newCar;
            }
        }

        else
        { 
            return false;
        }
        
        return true;
    }

    return true;
}

bool deleteCar(TrainCar *head, int position)
{

    //newCar->type = type;
    //newCar->load = 0;
    //newCar->maxLoad = maxLoad;

    if (position <= 0)
    {
        return false;
    }

    else
    {
        TrainCar *pointer = head;
        int temp = 1;
        while (temp < position)
        {
            if (pointer != nullptr)
            {
                pointer = pointer->next;
            }

            else
            {
                return false;
            }
            temp = temp + 1;
        }

        if (pointer->next != nullptr && pointer != nullptr)
        {

            TrainCar *removedCar = pointer->next;
            pointer->next = pointer->next->next;
            if (pointer->next != nullptr)
            {
                pointer->next->prev = pointer;
            }

            delete removedCar;
            removedCar = nullptr; 
        }
        else
        {
            return false;
        }

        return true;
    }

    return true;
}

bool swapCar(TrainCar *head, int a, int b)
{
    if (a <= 0 || b <= 0)
    {
        return false;
    }
    
    if (a == b)
    {
        return true;
    }

    TrainCar *positionOne = head;
    TrainCar *positionTwo = head;

    int tempOne = 1;

    while (tempOne <= a)
    {
        if (positionOne != nullptr)
        {
            positionOne = positionOne->next;
        }
        tempOne++;
    }
    tempOne = 1;

    while (tempOne <= b)
    {
        if (positionTwo != nullptr)
        {
            positionTwo = positionTwo->next;
        }
        tempOne++;
    }

    //if a and b are not adjacent
    //int k = abs(a - b);

    int k = a - b; 
    if (k < 0)
    {
        k = -k; 
    }


    if (k != 1)
    {
        positionTwo->prev->next = positionOne;
        if (positionOne->prev != nullptr)
        {
            positionOne->prev->next = positionTwo;
        }
        positionOne->next->prev = positionTwo;
        if (positionTwo->next != nullptr)
        {
            positionTwo->next->prev = positionOne;
        }
        TrainCar *ptr = positionOne->prev;
        positionOne->prev = positionTwo->prev;
        positionTwo->prev = ptr;
        TrainCar *ptr2 = positionTwo->next;
        positionTwo->next = positionOne->next;
        positionOne->next = ptr2;
    }

    else if (k == 1)
    {
        positionOne->next = positionTwo->next;
        positionTwo->prev = positionOne->prev;
        positionOne->prev = positionTwo;
        positionTwo->next = positionOne;
        if (positionTwo->prev != nullptr)
        {
            positionTwo->prev->next = positionTwo;
        }
        if (positionOne->next != nullptr)
        {
            positionOne->next->prev = positionOne;
        }
    }

    return true;
}

void sortTrain(TrainCar *head, bool ascending)
{
    bool temp = true;
    TrainCar *ptr1;
    int count;

    do
    {
        temp = false;
        ptr1 = head->next;
        count = 1;

        while (ptr1->next != nullptr)
        {
            if (ascending && ptr1->load > ptr1->next->load || !ascending && ptr1->load < ptr1->next->load)
            {
                swapCar(head, count, count + 1);
                temp = true;
            }
            else
            {
                ptr1 = ptr1->next;
            }
            count++;
        }
    } while (temp);
}

bool load(TrainCar *head, CarType type, int amount)
{

    int tempLoad = 0;
    TrainCar *pointer = head;

    while (pointer != nullptr)
    {

        if (pointer->type == type)
        {
            tempLoad = tempLoad + pointer->maxLoad;
        }
        pointer = pointer->next;
    }

    if (tempLoad < amount)
    {
        delete pointer; 
        pointer = nullptr; 
        return false;
    }

    else
    {

        TrainCar *ptr = head;
        while (ptr != nullptr)
        {
            if (ptr->type == type)
            {
                int temp = 0;
                temp = ptr->load;
                if (amount <= ptr->maxLoad + temp)
                {
                    ptr->load = temp + amount;
                }

                else
                {
                    ptr->load = ptr->maxLoad;
                    amount = amount - (ptr->maxLoad) + temp;
                }
            }

            ptr = ptr->next;
        }

        return true;
    }

    return true;
}

bool unload(TrainCar *head, CarType type, int amount)
{

    int tempLoad = 0;
    TrainCar *pointer = head;

    while (pointer != nullptr)
    {

        if (pointer->type == type)
        {
            tempLoad = tempLoad + pointer->load;
        }

        pointer = pointer->next;
    }

    if (tempLoad < amount)
    {
        delete pointer; 
        pointer = nullptr; 
        return false;
    }

    else
    {

        TrainCar *ptr = head;
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        while (ptr != head)
        {
            if (ptr->type == type)
            {
                int temp = 0;
                temp = ptr->load;
                if (amount <= ptr->load)
                {
                    ptr->load = temp - amount;
                }

                else
                {
                    amount = amount - (ptr->load);
                    ptr->load = 0;
                }
            }
            ptr = ptr->prev;
        }

        return true;
    }

    return true;
}

int typeCount = 0;

void printCargoStats(const TrainCar *head)
{

    int arrayMax[5] = {0, 0, 0, 0, 0};
    int arraythree[5] = {0, 0, 0, 0, 0};
    int arrayTwo[5] = {0, 0, 0, 0, 0};
    //int typeCount = 0;
    /*
    char firstName; 
    char secondName; 
    char thirdName; 
    char fourthName; 
    char fifthName; 
    */
    //int typeCount = 0;
    
    int countOil = 0;
    int countCoal = 0;
    int countWood = 0;
    int countSteel = 0;
    int countSugar = 0;

    int array[5] = {0,0,0,0,0}; 

    
    /*
     while(head->next != NULL)
    {
        char temp = head->next -> type; 
        switch (temp)
        {
            case OIL: array[0]++; break; 
            case COAL: array[1]++; break; 
            case WOOD: array[2]++; break; 
            case STEEL: array[3]++; break;
            case SUGAR: array[4]++; break;

        }
        head = head -> next; 
    }

    
    for (int i = 0; i < 5; i++)
    {
        if (array[i] != 0)
        {
            typeCount++; 
        }
    }

    for (int n; n < 5; n++)
    {
        cout << array[n] << endl;
    }
    
    */
    

    int oilLoad = 0; int mo = 0;
    int coalLoad = 0; int mc = 0;
    int woodLoad = 0; int mw = 0;
    int steelLoad = 0; int mst = 0;
    int sugarLoad = 0; int msu = 0;
    int count = 0;
    int countTwo = 0;

    while (head != nullptr)
    {
        int totalSum = head->load;
        char tempType = head -> type; 
        int tempMaxLoad = head->maxLoad;
        
        switch (tempType){
            case (OIL):
            
                if (oilLoad == 0)
                {
                    count = count + 1;
                    oilLoad = count;
                }
                arrayTwo[oilLoad] = 1;
                countOil++;
                if (tempMaxLoad != mo)
                {
                    arrayMax[oilLoad] = arrayMax[oilLoad] + tempMaxLoad;
                    mo = tempMaxLoad;
                }

                if (countOil > 0)
                {
                    arraythree[oilLoad] = arraythree[oilLoad] + totalSum;
                }

                break; 

           case(COAL):
            
                if (coalLoad == 0)
                {
                    count = count + 1;
                    coalLoad = count;
                }
                arrayTwo[coalLoad] = 2;
                countCoal++;
                if (tempMaxLoad != mc)
                {
                    arrayMax[coalLoad] = arrayMax[coalLoad] + tempMaxLoad;
                    mc = tempMaxLoad;
                }

                if (countCoal > 0)
                {
                    arraythree[coalLoad] = arraythree[coalLoad] + totalSum;
                }
                break;
            

            case (WOOD):
            
                if (woodLoad == 0)
                {
                    count = count + 1;
                    woodLoad = count;
                }
                arrayTwo[woodLoad] = 3;
                countWood++;
                if (tempMaxLoad != mw)
                {
                    arrayMax[woodLoad] = arrayMax[woodLoad] + tempMaxLoad;
                    mw = tempMaxLoad;
                }

                if (countWood > 0)
                {
                    arraythree[woodLoad] = arraythree[woodLoad] + totalSum;
                }
                break; 
            

            case (STEEL):
            
                if (steelLoad == 0)
                {
                    count = count + 1;
                    steelLoad = count;
                }
                arrayTwo[steelLoad] = 4;
                countSteel++;
                if (tempMaxLoad != mst)
                {
                    arrayMax[steelLoad] = arrayMax[steelLoad] + tempMaxLoad;
                    mst = tempMaxLoad;
                }

                if (countSteel > 0)
                {
                    arraythree[steelLoad] = arraythree[steelLoad] + totalSum;
                }

                break; 
            

            case (SUGAR):
            
                if (sugarLoad == 0)
                {
                    count = count + 1;
                    sugarLoad = count;
                }
                arrayTwo[sugarLoad] = 5;
                countSugar++;
                if (tempMaxLoad != msu)
                {
                    arrayMax[sugarLoad] = arrayMax[sugarLoad] + tempMaxLoad;
                    msu = tempMaxLoad;
                }

                if (countSugar > 0)
                {
                    arraythree[sugarLoad] = arraythree[sugarLoad] + totalSum;
                }
                break; 
            
        }


        head = head->next;
    }

    int countComma = 0;

    for (int x = 0; x < 5; x++)
    {
        if (arrayTwo[x] == 1)
        {
            if (countComma > 0)
            {
                cout << ",";
            }
            cout << "OIL:" << arraythree[x] << "/" << arrayMax[x];
            countComma = countComma + 1;
        }

        if (arrayTwo[x] == 2)
        {
            if (countComma > 0)
            {
                cout << ",";
            }
            cout << "COAL:" << arraythree[x] << "/" << arrayMax[x];
            countComma = countComma + 1;
        }

        if (arrayTwo[x] == 3)
        {
            if (countComma > 0)
            {
                cout << ",";
            }
            cout << "WOOD:" << arraythree[x] << "/" << arrayMax[x];
            countComma = countComma + 1;
        }

        if (arrayTwo[x] == 4)
        {
            if (countComma > 0)
            {
                cout << ",";
            }
            cout << "STEEL:" << arraythree[x] << "/" << arrayMax[x];
            countComma = countComma + 1;
        }

        if (arrayTwo[x] == 5)
        {
            if (countComma > 0)
            {
                cout << ",";
            }
            cout << "SUGAR:" << arraythree[x] << "/" << arrayMax[x];
            countComma = countComma + 1;
        }
    }

    cout << endl;
}

void addCarToEnd(TrainCar *head, CarType type, int load, int maxLoad)
{
    TrainCar *ptr = head;
    while (ptr->next != nullptr)
    {
        ptr = ptr->next;
    }
    TrainCar *newCar = new TrainCar;
    newCar->type = type;
    newCar->next = nullptr;
    newCar->prev = ptr;
    newCar->load = load;
    newCar->maxLoad = maxLoad;
    ptr->next = newCar;
}

void divide(const TrainCar *head, TrainCar *results[CARGO_TYPE_COUNT])
{

    int i;
    for (i = 0; i < CARGO_TYPE_COUNT; i++)
    {
        results[i] = nullptr;
    }
    CarType types[5] = {HEAD, HEAD, HEAD, HEAD, HEAD};
    TrainCar *ptr = head->next;
    while (ptr != nullptr)
    {
        for (i = 0; i < 5; i++)
        {
            if (ptr->type == types[i] || types[i] == HEAD)
            {
                break;
            }
        }
        if (results[i] == nullptr)
        {
            results[i] = createTrainHead();
            types[i] = ptr->type;
        }
        addCarToEnd(results[i], ptr->type, ptr->load, ptr->maxLoad);
        ptr = ptr->next;
    }
}

TrainCar *getCar(TrainCar *ptr, int num)
{
    while (num > 0)
    {
        ptr = ptr->next;
        num--;
    }
    return ptr;
}

int printknapSack(int upperbound, int loadOne[], int loadTwo[], int n, int values[])
{
    int i, j;
    int tempArray[n + 1][upperbound + 1];
    int count = 0;

    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= upperbound; j++)
        {
            if (i == 0 || j == 0)
                tempArray[i][j] = 0;
            else if (loadOne[i - 1] <= j)
                tempArray[i][j] = max(loadTwo[i - 1] +
                                          tempArray[i - 1][j - loadOne[i - 1]],
                                      tempArray[i - 1][j]);
            else
                tempArray[i][j] = tempArray[i - 1][j];
        }
    }

    int result = tempArray[n][upperbound];

    j = upperbound;
    for (i = n; i > 0 && result > 0; i--)
    {

        if (result == tempArray[i - 1][j])
            continue;

        else
        {
            values[count] = i;
            count++;
            result = result - loadTwo[i - 1];
            j = j - loadOne[i - 1];
        }
    }
    return count;
}

TrainCar *optimizeForMaximumPossibleCargos(const TrainCar *head, int upperBound)
{
    TrainCar *ptr = head->next;
    int count = 0;
    while (ptr != nullptr)
    {
        ptr = ptr->next;
        count++;
    }
    int arr[count];
    int arr2[count];
    int i;
    ptr = head->next;
    for (i = 0; i < count; i++)
    {
        arr[i] = ptr->load;
        arr2[i] = ptr->load;
        ptr = ptr->next;
    }

    ptr = head->next;
    int values[count];

    int numCars = printknapSack(upperBound, arr, arr2, count, values);
    int a;
    int b;
    int n = numCars;
    int temptwo;

    for (a = 0; a < (n - 1); a++)
    {
        for (b = 0; b < (n - a - 1); b++)
        {
            if (values[b] > values[b + 1])
            {
                temptwo = values[b];
                values[b] = values[b + 1];
                values[b + 1] = temptwo;
            }
        }
    }

    /*
    for (int x; x < numCars; x++)
    {
        cout << values[x]<<endl; 
    }
    */

    TrainCar *newTrain = createTrainHead();
    for (i = 0; i < numCars; i++)
    {
        TrainCar *tempCar = getCar(ptr, values[i] - 1);
        addCarToEnd(newTrain, tempCar->type, tempCar->load, tempCar->maxLoad);
    }
    return newTrain;
}

void deallocateTrain(TrainCar *head)
{

    
    TrainCar * ptr = head; 
    //ptr = nullptr; 
    TrainCar* tempPointer = nullptr; 

    for(int i; ptr != nullptr; i++)
    {
        tempPointer =ptr -> next; 
        delete ptr;
        ptr = nullptr; 
        ptr = tempPointer; 
       
    }
 


}
