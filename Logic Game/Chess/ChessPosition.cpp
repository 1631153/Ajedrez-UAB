//
//  ChessPosition.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "ChessPosition.hpp"
#include "GameInfo.h"
#include <string>

#include <iostream>
using namespace std;



ChessPosition::ChessPosition(const string& pos)
{
    //posicion X
    switch (pos[0])
    {
    case 'a':
        setPosX(0);
        break;
    case 'b':
        setPosX(1);
        break;
    case 'c':
        setPosX(2);
        break;
    case 'd':
        setPosX(3);
        break;
    case 'e':
        setPosX(4);
        break;
    case 'f':
        setPosX(5);
        break;
    case 'g':
        setPosX(6);
        break;
    case 'h':
        setPosX(7);
        break;
    }

    //posicion Y
    switch (pos[1])
    {
    case '1':
        setPosY(0);
        break;
    case '2':
        setPosY(1);
        break;
    case '3':
        setPosY(2);
        break;
    case '4':
        setPosY(3);
        break;
    case '5':
        setPosY(4);
        break;
    case '6':
        setPosY(5);
        break;
    case '7':
        setPosY(6);
        break;
    case '8':
        setPosY(7);
        break;
    }
}
bool ChessPosition::operator==(const ChessPosition& p1) const
{
    return ((m_posX == p1.m_posX) && (m_posY == p1.m_posY));
}

ostream& operator<<(ostream& output, ChessPosition& p1)
{
    string palabra;
    switch (p1.getPosX())
    {
    case 0:
        palabra = "a";
        break;
    case 1:
        palabra = "b";
        break;
    case 2:
        palabra = "c";
        break;
    case 3:
        palabra = "d";
        break;
    case 4:
        palabra = "e";
        break;
    case 5:
        palabra = "f";
        break;
    case 6:
        palabra = "g";
        break;
    case 7:
        palabra = "h";
        break;
    }

    switch (p1.getPosY())
    {
    case 0:
        palabra = palabra + "1";
        break;
    case 1:
        palabra = palabra + "2";
        break;
    case 2:
        palabra = palabra + "3";
        break;
    case 3:
        palabra = palabra + "4";
        break;
    case 4:
        palabra = palabra + "5";
        break;
    case 5:
        palabra = palabra + "6";
        break;
    case 6:
        palabra = palabra + "7";
        break;
    case 7:
        palabra = palabra + "8";
        break;
    }

    output << palabra;

    return output;
}
string ChessPosition::posString()
{
    string pos;
    switch (getPosX())
    {
    case 0:
        pos = "a";
        break;
    case 1:
        pos = "b";
        break;
    case 3:
        pos = "c";
        break;
    case 4:
        pos = "d";
        break;
    case 5:
        pos = "e";
        break;
    case 6:
        pos = "f";
        break;
    case 7:
        pos = "g";
        break;
    case 8:
        pos = "h";
        break;
    }

    switch (getPosY())
    {
    case 0:
        pos = pos + "1";
        break;
    case 1:
        pos = pos + "2";
        break;
    case 2:
        pos = pos + "3";
        break;
    case 3:
        pos = pos + "4";
        break;
    case 4:
        pos = pos + "5";
        break;
    case 5:
        pos = pos + "6";
        break;
    case 6:
        pos = pos + "7";
        break;
    case 7:
        pos = pos + "8";
        break;
    }
    return pos;
}
/* Coordinate system:
    Y (rows)
  . ^
  . |  ***Black***
  4 |
  3 |
  2 |
  1 |  ***White***
 (0,0)----------> X (cols)
      a b c ...
*/

void ChessPosition::BoardTxtToGame(const string& PiezaTxt)
{
    switch (PiezaTxt[4])
    {
    case 'a':
        setPosY(0);
        break;
    case 'b':
        setPosY(1);
        break;
    case 'c':
        setPosY(2);
        break;
    case 'd':
        setPosY(3);
        break;
    case 'e':
        setPosY(4);
        break;
    case 'f':
        setPosY(5);
        break;
    case 'g':
        setPosY(6);
        break;
    case 'h':
        setPosY(7);
        break;
    default:
        break;
    }

    switch (PiezaTxt[5])
    {
    case '1':
        setPosX(0);
        break;
    case '2':
        setPosX(1);
        break;
    case '3':
        setPosX(2);
        break;
    case '4':
        setPosX(3);
        break;
    case '5':
        setPosX(4);
        break;
    case '6':
        setPosX(5);
        break;
    case '7':
        setPosX(6);
        break;
    case '8':
        setPosX(7);
        break;
    default:
        break;
    }

}

int ChessPosition::ConversorCol(const char& PiezaTxt)
{
    switch (PiezaTxt)
    {
    case 'a':
        return 0;
        break;
    case 'b':
        return 1;
        break;
    case 'c':
        return 2;
        break;
    case 'd':
        return 3;
        break;
    case 'e':
        return 4;
        break;
    case 'f':
        return 5;
        break;
    case 'g':
        return 6;
        break;
    case 'h':
        return 7;
        break;
    default:
        break;
    }
}