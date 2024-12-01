#include "Guard.h"
#include "io.h"
#include "board.h"
Guard::Guard(const Location& location)
	: m_location(location), m_first_location(location)
	, m_touch(false)
	
{
}

Location Guard::get_location()
{
	return m_location;
}

void Guard::set_location(Location& location)
{
	m_location = location;
}

Location Guard::get_first_location()
{
	return m_first_location;
}

bool Guard::getTouch()
{
	return m_touch;
}

void Guard::print(Location newLoc)
{
	Screen::setLocation(m_location);
	std::cout << ' ';
	Screen::setLocation(newLoc);
	std::cout << '!';
}


void Guard::move(Board& board)
{
	
	bool moved = false;

	while (!moved)
	{
		Location newLoc = chooseNewLocation(m_location);
		if (board.isInLevel(newLoc) && !board.isWall(newLoc) && !board.isRock(newLoc))
		{

			moved = true;
			print(newLoc);
			if (board.isRobot(newLoc))
			{
				m_touch = true;
				break;
			}
			board.setLocation(m_location, newLoc, '!');
			set_location(newLoc); // update
		}
	}
}


Location Guard::chooseNewLocation(Location loc)
{
	Location newLoc = loc;

	// random move.
	int direction = rand() % 4; // 0 = �����, 1 = ����, 2 = �����, 3 = �����
	//direction = 0;
	switch (direction)
	{
	case 0: // move up.
		newLoc.row--;
		break;

	case 1: // move down.
		newLoc.row++;
		break;

	case 2: // move left.
		newLoc.col--;
		break;

	case 3: // move right.
		newLoc.col++;
		break;
	}
	return newLoc;
}

void Guard::initialization()
{
	Screen::setLocation(m_location);
	std::cout << ' ';
	set_location(m_first_location);
	Screen::setLocation(m_location);
	std::cout << '!';
	m_touch = false;
}
