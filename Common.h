#ifndef __COMMON_H
#define __COMMON_H

#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

using Position        = std::pair<int, int>;
using Path            = std::queue<Position>;
using Command         = std::string;
using Shape           = std::vector<std::vector <char> >;
using Step            = std::pair<Position, Position>;
using VertexAndWeight = std::pair<Position, int>;

const char TOM_SYMBOL           = 'T';
const char JERRY_SYMBOL         = 'J';
const char DRONE_SYMBOL         = 'D';
const char PAINTED_PLACE_SYMBOL = 'P';
const char CAN_PAINT_SYMBOL     = 'C';
const char FURNITURE_SYMBOL     = '1';
const char FREE_SPACE_SYMBOL    = ' ';

#endif