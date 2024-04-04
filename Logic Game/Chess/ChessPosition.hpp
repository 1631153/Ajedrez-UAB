//
//  ChessPosition.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class ChessPosition {

public:
    ChessPosition(int posX, int posY) { m_posX = posX; m_posY = posY; }
    ChessPosition() { m_posX = 0; m_posY = 0; }
    ChessPosition(const string& pos);
    int getPosX() const { return m_posX; }
    int getPosY() const { return m_posY; }
    void setPosX(int posX) { m_posX = posX; }
    void setPosY(int posY) { m_posY = posY; }
    string posString();
    bool operator==(const ChessPosition& p1) const;
    void BoardTxtToGame(const string& PiezaTxt);
    int ConversorCol(const char& PiezaTxt);
private:
    int m_posX; //Column
    int m_posY; //Row
};

ostream& operator<<(ostream& output, ChessPosition& p1);
typedef vector<ChessPosition> VecOfPositions;

#endif /* ChessPosition_hpp */