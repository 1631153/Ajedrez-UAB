//
//  Piece.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <vector>
#include "GameInfo.h"


using namespace std;

typedef enum {
    CPT_King,
    CPT_Queen,
    CPT_Rook,
    CPT_Bishop,
    CPT_Knight,
    CPT_Pawn,
    CPT_EMPTY
} ChessPieceType;

typedef enum {
    CPC_Black,
    CPC_White,
    CPC_NONE
} ChessPieceColor;

class Piece {

public:
    //constructores:
    Piece() : m_type(CPT_EMPTY), m_color(CPC_NONE) {}
    Piece(ChessPieceType type, ChessPieceColor color) : m_type(type), m_color(color) {}

    //getters:
    //(cambiar char/int por el correcto)
    ChessPieceType getType() const { return m_type; }
    ChessPieceColor getColor() const { return m_color; }

    //setters:
    void setType(ChessPieceType tipus) { m_type = tipus; }
    void setColor(ChessPieceColor color) { m_color = color; }

    //funciones:

    void ChessPieceConversorToCode(const string& tipus);
    void Render(ChessPieceType type, ChessPieceColor color, int posX, int posY);



private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;
};


#endif /* Piece_hpp */

