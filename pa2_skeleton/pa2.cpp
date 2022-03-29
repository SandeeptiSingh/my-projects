#include <iostream>
#include <cstring>
#include "cleaning_robot.h"
using namespace std;

/*
 *    COMP 2011 2021 Fall Programming Assignment 2
 *    Student Name        : Singh Sandeepti
 *    Student ID          : 20679259
 *    Student ITSC email  : ssinghaf@connect.ust.hk
 *
 * You are not allowed to use extra library
*/

// Please do all your work in this file. You just need to submit this file.

int findMaximumPlace(int robot_x, int robot_y, int robot_energy, int robot_full_energy, char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{

   //check if robot is within bounds and also that it is not at the same postion as a blocked postion
   if (robot_x < MAP_WIDTH && robot_x >= 0 && robot_y >= 0 && robot_y < MAP_HEIGHT && result_map[robot_y][robot_x] != 'B')
   {

      //initialising a boolean variable originally set to false
      bool check = false;
      int checkValue = 0; 

      if (result_map[robot_y][robot_x] == 'V')
      {
         //if the robot is at V then the var check needs to be changed to true so that it isn't double counted
         check = true;
      }
      if (result_map[robot_y][robot_x] == 'C')
      {
         //the energy of the robot becomes full if it goes through a charger
         robot_energy = robot_full_energy;
      }
      if (check == false)
      {
         //if the robot's position isn't already a V only then does it need to be changed to V
         result_map[robot_y][robot_x] = 'V';
      }

      robot_energy = robot_energy - 1; //decrease the robot energy by 1 during each iteration 
      if (robot_energy == -1)
      {
         if (check)
         {
            return 0;
         }
         else if (check == false)
         {
            return 1;
         }
      }
      //the total V is the sum of all the iterations of the robot in all 4 directions starting up and then going clockwise
      return (check == true ? 0 : 1) + findMaximumPlace(robot_x, robot_y - 1, robot_energy, robot_full_energy, result_map, result_map) +
             findMaximumPlace(robot_x + 1, robot_y, robot_energy, robot_full_energy, result_map, result_map) +
             findMaximumPlace(robot_x, robot_y + 1, robot_energy, robot_full_energy, result_map, result_map) +
             findMaximumPlace(robot_x - 1, robot_y, robot_energy, robot_full_energy, result_map, result_map);
   }
   else
   {
      return 0;
   }
}

//Helper function 1 used for task 2
int Helper(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy,
           const char map[MAP_HEIGHT][MAP_WIDTH], int temp, int tempOne)
{

   // checking if robot it within range and not on a blocked spot
   if (robot_x >= 0 && robot_y >= 0 && map[robot_y][robot_x] != 'B' && robot_y < MAP_HEIGHT && robot_x < MAP_WIDTH && temp < tempOne)
   {
      //full energy is it reaches a charger
      if (map[robot_y][robot_x] == 'C')
         robot_energy = robot_full_energy;
      robot_energy--;

      // if robot has reached target it returns 1
      if ((robot_x == target_x) && (robot_y == target_y))
      {
         return 1;
      }

      //robot has run out of energy
      if (robot_energy < 0)
      {
         return 0;
      }

      int count = 0;
      int f = 0; 
      // adding up the values returned by the recursion function 
      count = count + Helper(robot_x, robot_y - 1, target_x, target_y, robot_energy, robot_full_energy, map, temp + 1, tempOne);
      count = count + Helper(robot_x + 1, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp + 1, tempOne);
      count = count + Helper(robot_x, robot_y + 1, target_x, target_y, robot_energy, robot_full_energy, map, temp + 1, tempOne);
      count = count + Helper(robot_x - 1, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp + 1, tempOne);

      return count;
   }
   else
   {
      return 0;
   }
}

int limit(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy,
          const char map[MAP_HEIGHT][MAP_WIDTH], int temp, int tempOne)
{

   if (Helper(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, 0, tempOne) > 0)
   {
      return tempOne;
   }

   else
   {
      tempOne = tempOne + 1;
      return limit(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, 0, tempOne);
   }
}

int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy,
                         const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{

   copyMap(temp_map, map);
   int a = findMaximumPlace(robot_x, robot_y, robot_energy, robot_full_energy, temp_map, temp_map);

   //only calclulating the distance if the robot can reach that place based on it's charge
   if (temp_map[target_y][target_x] == 'V')
   {
      int tempTwo = 0;
      int count = 1;
      count = limit(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, 0, tempTwo);
      return count;
   }
   else
   {
      //const returned if unable to reach it
      return PA2_MAX_PATH;
   }
}

//using the same logic and functions as task 2 but creating new ones due to an additional parameter
int HelperTwo(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], int temp, int tempOne)
{

   if (robot_x >= 0 && robot_y >= 0 && map[robot_y][robot_x] != 'B' && robot_y < MAP_HEIGHT && robot_x < MAP_WIDTH && temp < tempOne)
   {
      if (map[robot_y][robot_x] == 'C')
      {
         robot_energy = robot_full_energy; // robot energy goes to full
      }

      robot_energy = robot_energy - 1;
      if ((robot_x == target_x) && (robot_y == target_y))
      {
         return 1;
      }
      if (robot_energy < 0)
      {
         return 0;
      }
      int check = 0;

      // returning the characters of where the robot has gone in the opposite order to make sure the priority is correct
      int tmp = HelperTwo(robot_x - 1, robot_y, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, temp + 1, tempOne);
      check = check + tmp;
      if (tmp != 0)
         result_sequence[temp] = 'L';
      tmp = HelperTwo(robot_x, robot_y + 1, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, temp + 1, tempOne);
      check = check + tmp;
      if (tmp != 0)
         result_sequence[temp] = 'D';
      tmp = HelperTwo(robot_x + 1, robot_y, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, temp + 1, tempOne);
      check = check + tmp;
      if (tmp != 0)
         result_sequence[temp] = 'R';
      tmp = HelperTwo(robot_x, robot_y - 1, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, temp + 1, tempOne);
      check = check + tmp;
      if (tmp != 0)
         result_sequence[temp] = 'U';

      return check;
   }
   else
   {
      return 0;
   }
}

int limitTwo(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], int temp, int tempOne)
{

   if (HelperTwo(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, 0, tempOne) > 0)
   {
      return tempOne;
   }

   else
   {
      tempOne = tempOne + 1;
      return limitTwo(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, 0, tempOne);
   }
}

int findPathSequence(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{

   /*
   if (robot_x == target_x && robot_y == target_y)
   {
      result_sequence[0] = 'T';
      return 1; 
   }

   */ 

  
   copyMap(temp_map, map);
   int tempVarFuntion = findMaximumPlace(robot_x, robot_y, robot_energy, robot_full_energy, temp_map, temp_map);
   if (temp_map[target_y][target_x] == 'V')
   {
      int tempTwo = 0;
      int count = 1;
      count = limitTwo(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, 0, tempTwo);
      result_sequence[count - 1] = 'T';
      return count;
   }
   else
   {
      return PA2_MAX_PATH;
   }
   return 0;
}

int findFarthestPossibleCharger(int robot_x, int robot_y, int robot_original_x, int robot_original_y, int &target_x, int &target_y, int robot_energy, int robot_full_energy,
                                const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   if (temp_map[robot_y][robot_x] != 'V' && robot_y == robot_original_y && robot_x == robot_original_x)
   {
      copyMap(temp_map, map);
      temp_map[robot_y][robot_x] = 'V';
      target_y = robot_y;
      target_x = robot_x;
   }

   if (map[robot_y][robot_x] != 'B' && robot_x > -1 && robot_x < MAP_WIDTH && robot_y > -1 && robot_y < MAP_HEIGHT)
   {
      if (map[robot_y][robot_x] == 'C')
      {
         temp_map[robot_y][robot_x] = 'V';
         int distanceOne = findShortestDistance(robot_original_x, robot_original_y, robot_x, robot_y, robot_full_energy, robot_full_energy, map, temp_map);
         int distanceTwo = findShortestDistance(robot_original_x, robot_original_y, target_x, target_y, robot_full_energy, robot_full_energy, map, temp_map);
         if (distanceTwo < distanceOne)
         {
            target_y = robot_y;
            target_x = robot_x;
         }
         return distanceOne;
         robot_energy = robot_full_energy;
      }
      temp_map[robot_y][robot_x] = 'V';

      robot_energy = robot_energy - 1;

      if (robot_energy < 0)
      {
         return 0;
      }

      int u = findFarthestPossibleCharger(robot_x, robot_y - 1, robot_original_x, robot_original_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);
      int r = findFarthestPossibleCharger(robot_x + 1, robot_y, robot_original_x, robot_original_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);
      int d = findFarthestPossibleCharger(robot_x, robot_y + 1, robot_original_x, robot_original_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);
      int l = findFarthestPossibleCharger(robot_x - 1, robot_y, robot_original_x, robot_original_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);

      int maxValue = 0;

      //finding the max value by creating a variable and then comparing the 4 values returned

      if (u != 0)
      {
         maxValue = u;
      }

      if (r != 0 && maxValue == 0)
      {
         maxValue = r;
      }

      if (r != 0 && r > maxValue)
      {
         maxValue = r;
      }
      if (d != 0 && maxValue == 0)
      {
         maxValue = d;
      }

      if (d != 0 && d > maxValue)
      {
         maxValue = d;
      }

      if (l != 0 && maxValue == 0)
      {
         maxValue = l;
      }

      if (l != 0 && l > maxValue)
      {
         maxValue = l;
      }

      return maxValue;
   }

   else
   {
      return -1;
   }
}
