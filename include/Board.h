#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Location.h"
#include <fstream>
#include "io.h"
using namespace std;

class Board
{
public:
	Board(const string&);
	int getRows();
	void print() const;
	void setLocation(Location oldLoc, Location newLoc, char);
	bool isSpace(Location) const;
	bool isRobot(Location)const;
	bool isRock(Location)const;
	bool isDoor(Location)const;
	bool isGuard(Location) const;
	bool isWall(Location) const;
	bool isInLevel(Location) const;
	Location getRobotFirstLoc() const;
	vector<Location> getVecGuardFirstLoc() const;
	void printScoreAndLife(int score, int life)const;

private:
	string m_fileName;
	vector<string> m_level;
	vector<Location> m_guardLoc;
	Location m_robotLoc;
	int m_numRow;
	int m_numCol;

	void updateLevel(const string);

};