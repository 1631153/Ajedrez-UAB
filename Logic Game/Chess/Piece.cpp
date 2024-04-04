//
//  Piece.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "Piece.hpp"
#include <string>
#include <iostream>
#include "../GraphicManager.h"

using namespace std;

void Piece::ChessPieceConversorToCode(const string& PiezaTxt) { // construye las piezas a partir de un fichero de txt (Funciona como el chessConversor)
	/*
		CPT_King, //rey
			CPT_Queen, // reina
			CPT_Rook, // torre
			CPT_Bishop, //Alfil
			CPT_Knight, //caballo
			CPT_Pawn, //peon
			CPT_EMPTY //vacío
			*/

	if (PiezaTxt[0] == '1')
		setColor(CPC_Black);
	else
		setColor(CPC_White);


	switch (PiezaTxt[3])
	{
	case 'R':
		setType(CPT_King);
		break;

	case 'T':
		setType(CPT_Rook);
		break;

	case 'A':
		setType(CPT_Bishop);
		break;

	case 'C':
		setType(CPT_Knight);
		break;

	case 'P':
		setType(CPT_Pawn);
		break;

	case 'D':
		setType(CPT_Queen);
		break;
	}

}

void Piece::Render(ChessPieceType type, ChessPieceColor color, int posX, int posY)
{
	if (color == CPC_White)
	{
		switch (type)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Queen:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Rook:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Bishop:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Knight:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Pawn:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		default:
			break;
		}
	}
	else
	{
		switch (type)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Queen:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Rook:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Bishop:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Knight:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		case CPT_Pawn:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			break;
		default:
			break;
		}
	}
}
