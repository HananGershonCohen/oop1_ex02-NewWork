﻿#include "Guard.h"
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

// Prints the guard's movement visually on the screen
void Guard::print(Location newLoc)
{
	Screen::setLocation(m_location); // Clear the previous location
	std::cout << ' ';
	Screen::setLocation(newLoc);// Draw the guard at the new location
	std::cout << '!';
}

void Guard::move(Board& board, const Location& robotLocation)
{
	bool moved = false;

	while (!moved)
	{
		Location bestLoc = m_location;// Initialize the best location as the current one
		int bestDistance = abs(m_location.row - robotLocation.row) + abs(m_location.col - robotLocation.col);// Calculate the initial distance from the robot

		// Check all possible movement directions
		for (int direction = 0; direction < 4; ++direction)
		{
			Location potentialLoc = m_location;
			switch (direction)
			{
			case 0: // up
				potentialLoc.row--;
				break;
			case 1: // down
				potentialLoc.row++;
				break;
			case 2: // left
				potentialLoc.col--;
				break;
			case 3: // right
				potentialLoc.col++;
				break;
			}

			// Check if the potential location is valid
			if (board.isInLevel(potentialLoc) && !board.isWall(potentialLoc) && !board.isRock(potentialLoc))
			{
				int distance = abs(potentialLoc.row - robotLocation.row) + abs(potentialLoc.col - robotLocation.col);
				if (distance < bestDistance)
				{
					bestLoc = potentialLoc;
					bestDistance = distance;
				}
			}
		}

		// If a valid move that reduces the distance is found
		if (bestLoc.row != m_location.row || bestLoc.col != m_location.col)
		{
			moved = true;
			print(bestLoc);
			if (board.isRobot(bestLoc))
			{
				m_touch = true;
				break;
			}
			board.setLocation(m_location, bestLoc, '!');
			set_location(bestLoc); 
		}
		else
		{
			// No valid move was found, the guard stays in place
			break;
		}
	}
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

// OLD MOVE FUNCTION.

/*
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
*/