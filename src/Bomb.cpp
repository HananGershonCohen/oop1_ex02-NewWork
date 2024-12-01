#include "Bomb.h"
#include <io.h>
#include <iostream>

Bomb::Bomb(const Location& location, int time)
    : m_location{ location }, m_time{ time }
    , m_killed_guard{false}, m_killed_robot{false}
{}

int Bomb::getTime() const 
{
    return m_time;
}

bool Bomb::isExploding() const 
{
   return (m_time == 0);
}

bool Bomb::isExploded() const
{
    return (m_time < 0);
}

void Bomb::renewTime()
{
    m_time--;
    print(m_location, (char) '0' +m_time);
}

void Bomb::print(Location& location, char c)
{
    Screen::setLocation(location);
    std::cout << c;
}

void Bomb::handle_NowExploding(Board& board)
{
    m_time--;
    set_explodingLocation(board);
    for (int i = 0; i < m_explodingLocation.size(); i++)
    {
        print(m_explodingLocation.at(i), '*');
    }

}

vector<Location> Bomb::handleExploded(Board &board)
{
    for (int i = 0; i < m_explodingLocation.size(); i++)
    {
        print(m_explodingLocation.at(i), ' ');
        if (board.isRock(m_explodingLocation.at(i)))
            board.setLocation(m_explodingLocation.at(i), m_explodingLocation.at(i), ' ');
        if (board.isGuard(m_explodingLocation.at(i)))
            m_killed_guard = true;
        if (board.isRobot(m_explodingLocation.at(i)))
            m_killed_robot = true;
    }
    return m_explodingLocation;
}


void Bomb::set_explodingLocation( Board& board)
{
   m_explodingLocation.push_back(m_location);
   Location up = Location{m_location.row-1,m_location.col};
   Location down = Location{ m_location.row +1,m_location.col };
   Location right = Location{ m_location.row ,m_location.col+1 };
   Location left = Location{ m_location.row ,m_location.col-1 };
    
   if (board.isInLevel(up) && !board.isWall(up))
        m_explodingLocation.push_back(up);
    
   if (board.isInLevel(down) && !board.isWall(down))
        m_explodingLocation.push_back(down);
    
   if (board.isInLevel(right) && !board.isWall(right))
        m_explodingLocation.push_back(right);
    
   if (board.isInLevel(left) && !board.isWall(left))
        m_explodingLocation.push_back(left);

}

