//
//  Chessboard.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"
#include "ChessPosition.hpp"



class Chessboard {

public:
    Chessboard() { taulerInicialRender = false; }
    void            LoadBoardFromFile(const string& path);
    void            movimentDiagonal(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            movimentVertical(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            movimentHoritzontal(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            getMovimentQueen(const ChessPosition& pos, vector <ChessPosition>& v) const;
    bool            comprovaRei();
    void            getMovimentsRei(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            getMovimentTorre(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            getMovimentAlfil(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            getMovimentCavall(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            getMovimentPeo(const ChessPosition& pos, vector <ChessPosition>& v) const;
    void            Render_board();
    VecOfPositions  GetValidMoves(const ChessPosition& pos) const;
    bool            MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo);
    string          ToString() const;
    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType  GetPieceTypeAtPos(const ChessPosition& pos) const;


private:
    Piece m_board[NUM_COLS][NUM_ROWS];
    bool taulerInicialRender;
};

ostream& operator<<(ostream& output, ChessPosition& p1);

#endif /* Chessboard_hpp */

