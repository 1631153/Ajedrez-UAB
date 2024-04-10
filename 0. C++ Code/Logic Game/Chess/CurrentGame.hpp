//
//  CurrentGame.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include "Chessboard.hpp"
#include "GameInfo.h"

using namespace std;

class Movement
{
public:
    Movement();
    Movement(ChessPosition primer, ChessPosition ultim);
    void setPrimer(const ChessPosition& primer) { m_primer = primer; }
    void setUltim(const ChessPosition& ultim) { m_ultim = ultim; }
    ChessPosition getPrimer() const { return m_primer; }
    ChessPosition getUltim() const { return m_ultim; }

private:
    ChessPosition m_primer;
    ChessPosition m_ultim;
};

class Node
{
public:
    Node() { m_next = nullptr; }
    Movement& getValor() { return m_valor; }
    Node* getNext() { return m_next; }
    void setValor(const Movement& valor) { m_valor = valor; }
    void setNext(Node* next) { m_next = next; }
private:
    Movement m_valor;
    Node* m_next;
};

class QueueMovements
{

public:
    void afegeix(Movement& valor);
    void treu();
    Movement& getPrimer() const;
    Movement& getUltim() const;
    bool esBuida() const;
private:
    Node* m_primer;
    Node* m_ultim;
};

class CurrentGame {

public:
    CurrentGame();

    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
    bool updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void end();

private:
    Chessboard Tauler_inform;
    QueueMovements cua;
    GameMode modo;
    ChessPosition pos, new_pos, actual, aux;
    Piece color;
    bool i = false;
    bool ganado = false;
};

#endif /* CurrentGame_hpp */