#pragma once
#include <vector>
#include "Guard.h"
#include <Bomb.h>
#include"Robot.h"



class Manger
{

public:
    void ran();
    void restart(Robot& robot, Board &board);
   bool equal(const Location &loc1, const Location &loc2);//
   void bombs(Board &board, Robot &robot);

  private:
     std:: vector <Guard> m_guardsMatrix;
     std::vector <Bomb> m_bombs_location;
     int m_score = 0;
    
};

