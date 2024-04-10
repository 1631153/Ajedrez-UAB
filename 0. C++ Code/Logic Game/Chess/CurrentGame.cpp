//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "CurrentGame.hpp"
#include "Chessboard.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
using namespace std;


CurrentGame::CurrentGame()
{
    modo = GM_NORMAL;
}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    modo = mode;

    if (mode == GM_NORMAL)
    {
        Tauler_inform.LoadBoardFromFile(intitialBoardFile);
        color.setColor(CPC_White);
        remove("data/Games/movements.txt");
    }
    else
    {
        Tauler_inform.LoadBoardFromFile(intitialBoardFile);
        //color.setColor(CPC_White);
        if (mode == GM_REPLAY)
        {
            ifstream fitxer;
            ChessPosition pos0, pos1;
            Movement m_pos;
            string msg;

            fitxer.open(movementsFile);
            int i = 0;

            while (!fitxer.eof())
            {
                getline(fitxer, msg);

                if (msg != "")
                    pos0.BoardTxtToGame(msg);

                pos1.setPosX(pos0.getPosY());
                pos1.setPosY(pos0.getPosX());

                if (i == 0)
                {
                    m_pos.setPrimer(pos1);
                    i = 1;
                }
                else
                {
                    m_pos.setUltim(pos1);
                }

            }
            cua.afegeix(m_pos);
        }
    }
    //añadir mode
}

void escribir(ChessPieceColor color, ChessPieceType tipus, int row, int cols) {

    char Tipus, Row;

    switch (tipus)
    {
    case 0:
        Tipus = 'R';
        break;
    case 1:
        Tipus = 'D';
        break;
    case 2:
        Tipus = 'T';
        break;
    case 3:
        Tipus = 'A';
        break;
    case 4:
        Tipus = 'C';
        break;
    case 5:
        Tipus = 'P';
        break;
    default:
        break;
    }

    switch (row)
    {
    case 0:
        Row = 'a';
        break;
    case 1:
        Row = 'b';
        break;
    case 2:
        Row = 'c';
        break;
    case 3:
        Row = 'd';
        break;
    case 4:
        Row = 'e';
        break;
    case 5:
        Row = 'f';
        break;
    case 6:
        Row = 'g';
        break;
    case 7:
        Row = 'h';
    default:
        break;
    }


    ofstream fitxer;

    fitxer.open("data/Games/movements.txt", ios::app);

    if (fitxer.fail()) {
        cout << "No se pudo";
        exit(1);
    }

    fitxer << color << ". " << Tipus << Row << cols + 1 << endl;
    fitxer.close();

}


void CurrentGame::end()
{
    string movementsFile = "data/Games/movements.txt";

    ofstream fitxer;
    fitxer.open("movementsFile");

    while (!cua.esBuida())
    {
        Movement m1;
        m1 = cua.getPrimer();
        ChessPosition posInicial = m1.getPrimer();
        ChessPosition posFinal = m1.getUltim();
        fitxer << posInicial << " " << posFinal << endl;
        cua.treu();
    }
    fitxer.close();
}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus)
{

    if (modo == GM_NORMAL)
    {
        GraphicManager::getInstance()->drawSprite(IMAGE_FONDO, 0, 0);
        GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);

        int new_posX, new_posY;

        Tauler_inform.Render_board();

        if (!ganado)
        {

            if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) && (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) && (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
            {

                if (!i)
                {
                    int posX = (mousePosX - CELL_INIT_X) / CELL_W;
                    int posY = (mousePosY - CELL_INIT_Y) / CELL_H;

                    ChessPosition position;
                    position.setPosX(posX);
                    position.setPosY(posY);

                    if (Tauler_inform.GetPieceColorAtPos(position) != color.getColor())
                    {
                        pos.setPosX(posX);
                        pos.setPosY(posY);

                        if (Tauler_inform.GetPieceTypeAtPos(pos) != CPT_EMPTY)
                        {
                            i = true;
                        }
                    }

                }
                else
                {
                    new_posX = (mousePosX - CELL_INIT_X) / CELL_W;
                    new_posY = (mousePosY - CELL_INIT_Y) / CELL_H;

                    ChessPosition position;
                    position.setPosX(new_posX);
                    position.setPosY(new_posY);

                    int j = 0;
                    if (color.getColor() == 1)
                        j = 0;
                    else
                        j = 1;

                    if (Tauler_inform.GetPieceColorAtPos(position) == j)
                    {
                        pos.setPosX(new_posX);
                        pos.setPosY(new_posY);
                    }
                    else
                    {
                        new_pos.setPosX(new_posX);
                        new_pos.setPosY(new_posY);
                        i = false;
                    }
                }

                Sleep(100);

            }

            int posTextX = CELL_INIT_X;
            int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
            std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
            string colorin;

            if (color.getColor() == 1)
                colorin = "Color: Negro";
            else
                colorin = "Color: Blanco";

            GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);
            GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY + 50, 0.8, colorin);

            if (i)
            {
                Tauler_inform.GetValidMoves(pos);
            }

            if (!i && Tauler_inform.MovePiece(pos, new_pos))
            {
                Tauler_inform.ToString();
                escribir(color.getColor(), Tauler_inform.GetPieceTypeAtPos(new_pos), new_pos.getPosX(), new_pos.getPosY());

                if (color.getColor() == 1)
                    color.setColor(CPC_Black);
                else
                    color.setColor(CPC_White);
            }
            Movement cua_insercio;
            cua_insercio.setPrimer(pos);
            cua_insercio.setUltim(new_pos);
            cua.afegeix(cua_insercio);

            bool res = Tauler_inform.comprovaRei();
            if (res == true)
                ganado = true;
        }
        else
        {
            if (color.getColor() == 0)
                GraphicManager::getInstance()->drawSprite(IMAGE_WHITE_WIN, 0, 200);
            else
                GraphicManager::getInstance()->drawSprite(IMAGE_BLACK_WIN, 0, 200);
        }
        return false;
    }
    else
    {
        if (modo == GM_REPLAY)
        {   
            int posTextX = CELL_INIT_X;
            int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
            GraphicManager::getInstance()->drawSprite(IMAGE_FONDO, 0, 0);
            GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
            string mensaje = "Gamemode: Replay";
            bool prueba = true;
            string colorin;
            if (!i)
            {
                if (color.getColor() == CPC_Black)
                    colorin = "Color: Negro";
                else
                    colorin = "Color: Blanco";

                GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY + 50, 0.8, colorin);

                

                if (mouseStatus && mousePosX >= CELL_INIT_X && mousePosY >= CELL_INIT_Y)
                {
                    if (!cua.esBuida() && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) && (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) && (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)) && mouseStatus)
                    {
                        Movement moviment;
                        moviment = cua.getPrimer();
                        ChessPosition inici, final;

                        inici = moviment.getPrimer();
                        final = moviment.getUltim();

                        cua.treu();

                        if (Tauler_inform.comprovaRei())
                        {
                            i = true;
                        }
                        else
                        {
                            Tauler_inform.MovePiece(inici, final);
                            if (cua.esBuida())
                            {
                                i = true;
                            }
                            if (color.getColor() == 1)
                                color.setColor(CPC_Black);
                            else
                                color.setColor(CPC_White);
                        }
                    }
                }

                if (!Tauler_inform.comprovaRei() && i)
                {
                    if (color.getColor() == 0)
                        GraphicManager::getInstance()->drawSprite(IMAGE_WHITE_WIN, 0, 200);
                    else
                        GraphicManager::getInstance()->drawSprite(IMAGE_BLACK_WIN, 0, 200);
                }
                else if (cua.esBuida() && i)
                {
                    GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, ((CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60) + 100), 0.8, "No mes moviments a fer");
                }
            }
            GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY + 100, 0.8, mensaje);
            Tauler_inform.Render_board();
        }

        return i;
    }
}

Movement::Movement()
{
    m_primer.setPosX(0);
    m_primer.setPosY(0);
    m_ultim.setPosX(0);
    m_ultim.setPosY(0);
}
Movement::Movement(ChessPosition primer, ChessPosition ultim)
{
    m_primer.setPosX(primer.getPosX());
    m_primer.setPosY(primer.getPosY());
    m_ultim.setPosX(ultim.getPosX());
    m_ultim.setPosY(ultim.getPosY());
}
void QueueMovements::afegeix(Movement& valor)
{
    Node* aux = new Node();
    aux->setNext(nullptr);
    aux->setValor(valor);

    if (esBuida())
        m_primer = aux;
    else
        m_ultim->setNext(aux);

    m_ultim = aux;

}
void QueueMovements::treu()
{
    if (!esBuida())
    {
        Node* aux;
        aux = m_primer;
        m_primer = aux->getNext();
        delete aux;
    }
}

bool QueueMovements::esBuida() const
{
    bool buit = false;
    if (m_primer == nullptr)
        buit = true;

    return buit;
}
Movement& QueueMovements::getPrimer() const
{
    return m_primer->getValor();
}
Movement& QueueMovements::getUltim() const
{
    return m_ultim->getValor();
}