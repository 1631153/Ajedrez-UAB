//
//  Chessboard.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "Chessboard.hpp"
#include "../GraphicManager.h"
#include "Piece.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/*
ToString original:

for (int i = 7; i > -1; i--) {
		cout << NUM_ROWS - (NUM_ROWS - (i + 1)) << " ";
		for (int j = 0; j < NUM_COLS; j++)
		{
			color = m_board[j][i].getColor();
			type = m_board[j][i].getType();

			switch (color)
			{
			case 0:
				ret2 = 'b';
				break;
			case 1:
				ret2 = 'w';
				break;
			case 2:
				ret2 = '_';
				break;
			default:
				break;
			}
*/



//resumir lineas
ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosX()][pos.getPosY()].getColor();
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosX()][pos.getPosY()].getType();
}

void Chessboard::LoadBoardFromFile(const string& path) {

	ChessPosition PosicionPieza;
	ifstream fitxer;
	fitxer.open(path);

	if (fitxer.is_open())
	{
		string pieza;
		getline(fitxer, pieza);

		do
		{
			PosicionPieza.BoardTxtToGame(pieza);
			m_board[PosicionPieza.getPosY()][PosicionPieza.getPosX()].ChessPieceConversorToCode(pieza);
			getline(fitxer, pieza);
			if (fitxer.eof())
			{
				PosicionPieza.BoardTxtToGame(pieza);
				m_board[PosicionPieza.getPosY()][PosicionPieza.getPosX()].ChessPieceConversorToCode(pieza);
			}
		} while (!fitxer.eof());
		fitxer.close();
		ToString();
	}
}



string Chessboard::ToString() const {

	string ret, ret2;
	int color, type, temp;

	for (int i = 0; i < NUM_ROWS; i++) {
		cout << NUM_ROWS - i << " ";
		for (int j = 0; j < NUM_COLS; j++)
		{
			color = m_board[j][i].getColor();
			type = m_board[j][i].getType();

			switch (color)
			{
			case 0:
				ret2 = 'w';
				break;
			case 1:
				ret2 = 'b';
				break;
			case 2:
				ret2 = '_';
				break;
			default:
				break;
			}

			switch (type)
			{
			case 0:
				ret = 'R';
				break;
			case 1:
				ret = 'D';
				break;
			case 2:
				ret = 'T';
				break;
			case 3:
				ret = 'A';
				break;
			case 4:
				ret = 'C';
				break;
			case 5:
				ret = 'P';
				break;
			case 6:
				ret = '_';
				break;
			default:
				break;
			}

			cout << ret2 << ret << " ";
		}
		cout << endl;
	}
	cout << "  a  b  c  d  e  f  g  h " << endl;
	return " ";
}

void Chessboard::movimentVertical(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	int i = 0;
	bool trobat = false;
	bool trobat2 = false;
	int color = GetPieceColorAtPos(pos);

	while (i < NUM_ROWS)
	{
		//arriba
		if (!trobat)
		{
			if ((m_board[pos.getPosX()][pos.getPosY() + i].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat = true;
			}

			if ((m_board[pos.getPosX()][pos.getPosY() + i].getType() == CPT_EMPTY) && (pos.getPosY() + i < NUM_ROWS))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX());
				p1.setPosY(pos.getPosY() + i);
				v.push_back(p1);
			}
			else
				if ((m_board[pos.getPosX()][pos.getPosY() + i].getColor() != CPC_NONE) && ((pos.getPosY() + i) < NUM_ROWS))
				{
					if ((m_board[pos.getPosX()][pos.getPosY() + i].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX());
						p1.setPosY(pos.getPosY() + i);
						v.push_back(p1);
					}
				}
		}
		//abajo
		if (!trobat2)
		{
			if ((m_board[pos.getPosX()][pos.getPosY() - i].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat2 = true;

			}

			if ((m_board[pos.getPosX()][pos.getPosY() - i].getType() == CPT_EMPTY) && ((pos.getPosY() - i) >= 0))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX());
				p1.setPosY(pos.getPosY() - i);
				v.push_back(p1);
			}
			else
				if ((m_board[pos.getPosX()][pos.getPosY() - i].getColor() != CPC_NONE) && ((pos.getPosY() - i) >= 0))
				{
					if ((m_board[pos.getPosX()][pos.getPosY() - i].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX());
						p1.setPosY(pos.getPosY() - i);
						v.push_back(p1);
					}
				}
		}
		i++;
	}
}

void Chessboard::movimentHoritzontal(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	int i = 0;
	bool trobat = false;
	bool trobat2 = false;
	int color = GetPieceColorAtPos(pos);

	while (i < NUM_ROWS)
	{
		//izquierda
		if (!trobat)
		{
			if ((m_board[pos.getPosX() - i][pos.getPosY()].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat = true;
			}

			if ((m_board[pos.getPosX() - i][pos.getPosY()].getType() == CPT_EMPTY) && (m_board[pos.getPosX() - i][pos.getPosY()].getColor() != color) && pos.getPosX() - i >= 0)
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() - i);
				p1.setPosY(pos.getPosY());
				v.push_back(p1);
			}
			else
				if ((m_board[pos.getPosX() - i][pos.getPosY()].getColor() != CPC_NONE) && ((pos.getPosX() - i) >= 0))
				{
					if ((m_board[pos.getPosX() - i][pos.getPosY()].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX() - i);
						p1.setPosY(pos.getPosY());
						v.push_back(p1);
					}
				}
		}
		//derecha
		if (!trobat2)
		{
			if ((m_board[pos.getPosX() + i][pos.getPosY()].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat2 = true;
			}

			if ((m_board[pos.getPosX() + i][pos.getPosY()].getType() == CPT_EMPTY) && (m_board[pos.getPosX() + i][pos.getPosY()].getColor() != color) && (pos.getPosX() + i < NUM_COLS))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() + i);
				p1.setPosY(pos.getPosY());
				v.push_back(p1);

			}
			else
				if ((m_board[pos.getPosX() + i][pos.getPosY()].getColor() != CPC_NONE) && ((pos.getPosX() + i) < NUM_COLS))
				{
					if ((m_board[pos.getPosX() + i][pos.getPosY()].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX() + i);
						p1.setPosY(pos.getPosY());
						v.push_back(p1);
					}
				}
		}
		i++;
	}
}

void Chessboard::movimentDiagonal(const ChessPosition& pos, vector <ChessPosition>& v) const //moviment diagonal en cualsevol pos
{
	int i = 0;
	bool trobat = false;
	bool trobat2 = false;
	bool trobat3 = false;
	bool trobat4 = false;
	int color = GetPieceColorAtPos(pos);
	while (i < NUM_ROWS)
	{
		//diagonal arriba izquierda
		if (!trobat)
		{
			if ((m_board[pos.getPosX() - i][pos.getPosY() + i].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat = true;
			}

			if ((m_board[pos.getPosX() - i][pos.getPosY() + i].getType() == CPT_EMPTY) && ((pos.getPosY() + i) < NUM_ROWS) && (pos.getPosX() - i >= 0))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() - i);
				p1.setPosY(pos.getPosY() + i);
				v.push_back(p1);
			}
			else
				if ((m_board[pos.getPosX() - i][pos.getPosY() + i].getColor() != CPC_NONE) && ((pos.getPosY() + i) < NUM_ROWS) && (pos.getPosX() - i >= 0))
				{
					if ((m_board[pos.getPosX() - i][pos.getPosY() + i].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX() - i);
						p1.setPosY(pos.getPosY() + i);
						v.push_back(p1);
					}
				}
		}
		//diagonal abajo derecha
		if (!trobat2)
		{
			if ((m_board[pos.getPosX() + i][pos.getPosY() - i].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat2 = true;
			}

			if ((m_board[pos.getPosX() + i][pos.getPosY() - i].getType() == CPT_EMPTY) && ((pos.getPosY() - i) >= 0) && (pos.getPosX() + i < NUM_ROWS))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() + i);
				p1.setPosY(pos.getPosY() - i);
				v.push_back(p1);
			}
			else
				if ((m_board[pos.getPosX() + i][pos.getPosY() - i].getColor() != CPC_NONE) && ((pos.getPosY() - i) >= 0) && (pos.getPosX() + i < NUM_ROWS))
				{
					if ((m_board[pos.getPosX() + i][pos.getPosY() - i].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX() + i);
						p1.setPosY(pos.getPosY() - i);
						v.push_back(p1);
					}
				}
		}
		//diagonal arriba derecha
		if (!trobat3)
		{
			if ((m_board[pos.getPosX() + i][pos.getPosY() + i].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat3 = true;
			}

			if ((m_board[pos.getPosX() + i][pos.getPosY() + i].getType() == CPT_EMPTY) && ((pos.getPosY() + i) < NUM_COLS) && (pos.getPosX() + i < NUM_ROWS))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() + i);
				p1.setPosY(pos.getPosY() + i);
				v.push_back(p1);
			}
			else
				if ((m_board[pos.getPosX() + i][pos.getPosY() + i].getColor() != CPC_NONE) && ((pos.getPosY() + i) < NUM_COLS) && (pos.getPosX() + i < NUM_ROWS))
				{
					if ((m_board[pos.getPosX() + i][pos.getPosY() + i].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX() + i);
						p1.setPosY(pos.getPosY() + i);
						v.push_back(p1);
					}
				}
		}
		//diagonal abajo izquierda
		if (!trobat4)
		{
			if ((m_board[pos.getPosX() - i][pos.getPosY() - i].getType() != CPT_EMPTY) && (i != 0))
			{
				trobat4 = true;
			}

			if ((m_board[pos.getPosX() - i][pos.getPosY() - i].getType() == CPT_EMPTY) && ((pos.getPosY() - i) >= 0) && ((pos.getPosX() - i) >= 0))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() - i);
				p1.setPosY(pos.getPosY() - i);
				v.push_back(p1);
			}
			else
				if ((m_board[pos.getPosX() - i][pos.getPosY() - i].getColor() != CPC_NONE) && ((pos.getPosY() - i) >= 0) && (pos.getPosX() - i >= 0))
				{
					if ((m_board[pos.getPosX() - i][pos.getPosY() - i].getColor() != color))
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX() - i);
						p1.setPosY(pos.getPosY() - i);
						v.push_back(p1);
					}
				}
		}
		i++;
	}
}

void Chessboard::getMovimentsRei(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	ChessPieceColor color = GetPieceColorAtPos(pos);

	//diagonal arriba izquierda
	if ((m_board[pos.getPosX() - 1][pos.getPosY() + 1].getType() == CPT_EMPTY) && (m_board[pos.getPosX() - 1][pos.getPosY() + 1].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() - 1);
		p1.setPosY(pos.getPosY() + 1);
		v.push_back(p1);
	}
	//izqueirda
	if ((m_board[pos.getPosX() - 1][pos.getPosY()].getType() == CPT_EMPTY) && (m_board[pos.getPosX() - 1][pos.getPosY()].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() - 1);
		p1.setPosY(pos.getPosY());
		v.push_back(p1);
	}
	//diagonal abajo izquierda
	if ((m_board[pos.getPosX() - 1][pos.getPosY() - 1].getType() == CPT_EMPTY) && (m_board[pos.getPosX() - 1][pos.getPosY() - 1].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() - 1);
		p1.setPosY(pos.getPosY() - 1);
		v.push_back(p1);
	}
	//arriba
	if (pos.getPosY() < 7)
	{
		if ((m_board[pos.getPosX()][pos.getPosY() + 1].getType() == CPT_EMPTY) && (m_board[pos.getPosX()][pos.getPosY() + 1].getColor() != color))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX());
			p1.setPosY(pos.getPosY() + 1);
			v.push_back(p1);
		}
	}
	//abajo
	if ((m_board[pos.getPosX()][pos.getPosY() - 1].getType() == CPT_EMPTY) && (m_board[pos.getPosX()][pos.getPosY() + 1].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX());
		p1.setPosY(pos.getPosY() - 1);
		v.push_back(p1);
	}
	//diagonal arriba derecha
	if ((m_board[pos.getPosX() + 1][pos.getPosY() + 1].getType() == CPT_EMPTY) && (m_board[pos.getPosX() + 1][pos.getPosY() + 1].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() + 1);
		p1.setPosY(pos.getPosY() + 1);
		v.push_back(p1);
	}
	//derecha
	if ((m_board[pos.getPosX() + 1][pos.getPosY()].getType() == CPT_EMPTY) && (m_board[pos.getPosX() + 1][pos.getPosY()].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() + 1);
		p1.setPosY(pos.getPosY());
		v.push_back(p1);
	}
	//diagonal abajo derecha
	if ((m_board[pos.getPosX() + 1][pos.getPosY() - 1].getType() == CPT_EMPTY) && (m_board[pos.getPosX() + 1][pos.getPosY() - 1].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() + 1);
		p1.setPosY(pos.getPosY() - 1);
		v.push_back(p1);
	}
}

void Chessboard::getMovimentQueen(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	movimentDiagonal(pos, v);
	movimentHoritzontal(pos, v);
	movimentVertical(pos, v);
}

void Chessboard::getMovimentTorre(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	movimentHoritzontal(pos, v);
	movimentVertical(pos, v);
}

void Chessboard::getMovimentAlfil(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	movimentDiagonal(pos, v);
}

void Chessboard::getMovimentCavall(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	//resumir Cavall/Rey variables y quitar 7 linias a 1
	ChessPieceColor color = GetPieceColorAtPos(pos);
	//arriba izquierda
	if ((m_board[pos.getPosX() - 1][pos.getPosY() + 2].getType() == CPT_EMPTY) && (pos.getPosX() - 1 >= 0) && (pos.getPosY() + 2 < NUM_ROWS) && (m_board[pos.getPosX() - 1][pos.getPosY() + 2].getColor() != color))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() - 1);
		p1.setPosY(pos.getPosY() + 2);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() - 1][pos.getPosY() + 2].getColor() != color) && ((pos.getPosX() - 1 >= 0) && (pos.getPosY() + 2 < NUM_ROWS)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() - 1);
			p1.setPosY(pos.getPosY() + 2);
			v.push_back(p1);
		}
	}
	//abajo derecha
	if ((m_board[pos.getPosX() + 1][pos.getPosY() - 2].getType() == CPT_EMPTY) && (pos.getPosX() + 1 < NUM_ROWS) && (pos.getPosY() - 2 >= 0))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() + 1);
		p1.setPosY(pos.getPosY() - 2);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() + 1][pos.getPosY() - 2].getColor() != color) && ((pos.getPosX() + 1 < NUM_ROWS) && (pos.getPosY() - 2 >= 0)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() + 1);
			p1.setPosY(pos.getPosY() - 2);
			v.push_back(p1);
		}
	}
	//arriba derecha
	if ((m_board[pos.getPosX() + 1][pos.getPosY() + 2].getType() == CPT_EMPTY) && (pos.getPosX() + 1 < NUM_ROWS) && (pos.getPosY() + 2 < NUM_COLS))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() + 1);
		p1.setPosY(pos.getPosY() + 2);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() + 1][pos.getPosY() + 2].getColor() != color) && ((pos.getPosX() + 1 < NUM_ROWS) && (pos.getPosY() + 2 < NUM_COLS)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() + 1);
			p1.setPosY(pos.getPosY() + 2);
			v.push_back(p1);
		}
	}
	//abajo izquierda
	if ((m_board[pos.getPosX() - 1][pos.getPosY() - 2].getType() == CPT_EMPTY) && (pos.getPosX() - 1 >= 0) && (pos.getPosY() - 2 >= 0))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() - 1);
		p1.setPosY(pos.getPosY() - 2);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() - 1][pos.getPosY() - 2].getColor() != color) && ((pos.getPosX() - 1 >= 0) && (pos.getPosY() - 2 >= 0)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() - 1);
			p1.setPosY(pos.getPosY() - 2);
			v.push_back(p1);
		}
	}
	//izquierda abajo
	if ((m_board[pos.getPosX() - 2][pos.getPosY() - 1].getType() == CPT_EMPTY) && (pos.getPosX() - 2 >= 0) && (pos.getPosY() - 1 >= 0))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() - 2);
		p1.setPosY(pos.getPosY() - 1);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() - 2][pos.getPosY() - 1].getColor() != color) && ((pos.getPosX() - 2 >= 0) && (pos.getPosY() - 1 >= 0)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() - 2);
			p1.setPosY(pos.getPosY() - 1);
			v.push_back(p1);
		}
	}
	//izquierda arriba
	if ((m_board[pos.getPosX() - 2][pos.getPosY() + 1].getType() == CPT_EMPTY) && (pos.getPosX() - 2 >= 0) && (pos.getPosY() + 1 < NUM_COLS))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() - 2);
		p1.setPosY(pos.getPosY() + 1);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() - 2][pos.getPosY() + 1].getColor() != color) && ((pos.getPosX() - 2 >= 0) && (pos.getPosY() + 1 < NUM_COLS)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() - 2);
			p1.setPosY(pos.getPosY() + 1);
			v.push_back(p1);
		}
	}
	//derecha abajo
	if ((m_board[pos.getPosX() + 2][pos.getPosY() - 1].getType() == CPT_EMPTY) && (pos.getPosX() + 2 < NUM_ROWS) && (pos.getPosY() - 1 >= 0))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() + 2);
		p1.setPosY(pos.getPosY() - 1);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() + 2][pos.getPosY() - 1].getColor() != color) && ((pos.getPosX() + 2 < NUM_ROWS) && (pos.getPosY() - 1 >= 0)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() + 2);
			p1.setPosY(pos.getPosY() - 1);
			v.push_back(p1);
		}
	}
	//derecha arriba
	if ((m_board[pos.getPosX() + 2][pos.getPosY() + 1].getType() == CPT_EMPTY) && (pos.getPosX() + 2 < NUM_ROWS) && (pos.getPosY() + 1 < NUM_COLS))
	{
		ChessPosition p1;
		p1.setPosX(pos.getPosX() + 2);
		p1.setPosY(pos.getPosY() + 1);
		v.push_back(p1);
	}
	else
	{
		if ((m_board[pos.getPosX() + 2][pos.getPosY() + 1].getColor() != color) && ((pos.getPosX() + 2 < NUM_ROWS) && (pos.getPosY() + 1 < NUM_COLS)))
		{
			ChessPosition p1;
			p1.setPosX(pos.getPosX() + 2);
			p1.setPosY(pos.getPosY() + 1);
			v.push_back(p1);
		}
	}
}

void Chessboard::getMovimentPeo(const ChessPosition& pos, vector <ChessPosition>& v) const
{
	int i = 7;
	bool trobat = false;
	bool trobat2 = false;
	int color = GetPieceColorAtPos(pos);
	int col = 0;
	ChessPosition p2;

	while (i > -1)
	{
		if (m_board[pos.getPosX()][pos.getPosY()].getColor() == CPC_Black)
		{
			p2.setPosX(i); // p2[0]
			p2.setPosY(6);// p2[1]
			col = 1;

		}
		else
		{
			p2.setPosX(i); // p2[0]
			p2.setPosY(1);// p2[1]
			col = -1;
		}

		for (int j = 1; j < 3; j++)
		{
			if ((pos.getPosX() == p2.getPosX()) && (pos.getPosY() == p2.getPosY())) //comprueba si está en la posición inicial
			{
				if ((m_board[pos.getPosX()][pos.getPosY() - col].getType() == CPT_EMPTY) && (pos.getPosY() - col < NUM_ROWS)) //la posicion arriba a abajo está vacia y dentro de los limites? (+1)
				{
					ChessPosition p1;
					p1.setPosX(pos.getPosX());
					p1.setPosY(pos.getPosY() - col);
					v.push_back(p1);
					trobat = true;
				}
				else
				{
					if (m_board[pos.getPosX()][pos.getPosY() - col].getType() != CPT_EMPTY)
					{
						if (m_board[pos.getPosX()][pos.getPosY() - col].getColor() != color)
						{
							ChessPosition p1;
							p1.setPosX(pos.getPosX());
							p1.setPosY(pos.getPosY() - col);
							v.push_back(p1);
							trobat = true;
						}
						else
						{
							break;
						}

					}
				}
			}

			if (m_board[pos.getPosX()][pos.getPosY()].getColor() == CPC_Black)
			{
				col = 2;

			}
			else
			{
				col = -2;
			}
		}
		i--;
	}
	if (m_board[pos.getPosX()][pos.getPosY()].getColor() == CPC_Black)
	{
		col = 1;
	}
	else
	{
		col = -1;
	}

		if (!trobat && !trobat2)
		{
			if ((m_board[pos.getPosX()][pos.getPosY() - col].getType() == CPT_EMPTY) && (pos.getPosY() - col < NUM_ROWS))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX());
				p1.setPosY(pos.getPosY() - col);
				v.push_back(p1);
			}
			else
			{
				if ((m_board[pos.getPosX()][pos.getPosY() - col].getType() != CPT_EMPTY) && (pos.getPosY() - col < NUM_ROWS))
				{
					if (m_board[pos.getPosX()][pos.getPosY()].getColor() != color)
					{
						ChessPosition p1;
						p1.setPosX(pos.getPosX());
						p1.setPosY(pos.getPosY() - col);
						v.push_back(p1);
					}
				}
					
			}
		}

	if ((m_board[pos.getPosX() - 1][pos.getPosY() + 1].getType() == CPT_EMPTY) && ((pos.getPosY() + 1) < NUM_ROWS) && (pos.getPosX() - 1 >= 0))
	{

	}
	else
		if ((m_board[pos.getPosX() - 1][pos.getPosY() + 1].getColor() != CPC_NONE) && ((pos.getPosY() + 1) < NUM_ROWS) && (pos.getPosX() - 1 >= 0))
		{
			if ((m_board[pos.getPosX() - 1][pos.getPosY() + 1].getColor() != color))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() - 1);
				p1.setPosY(pos.getPosY() + 1);
				v.push_back(p1);
			}
		}

	if ((m_board[pos.getPosX() + 1][pos.getPosY() + 1].getType() == CPT_EMPTY) && ((pos.getPosY() + 1) < NUM_ROWS) && (pos.getPosX() + 1 < NUM_ROWS))
	{

	}
	else
		if ((m_board[pos.getPosX() + 1][pos.getPosY() + 1].getColor() != CPC_NONE) && ((pos.getPosY() + 1) < NUM_ROWS) && (pos.getPosX() + 1 < NUM_ROWS))
		{
			if ((m_board[pos.getPosX() + 1][pos.getPosY() + 1].getColor() != color))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() + 1);
				p1.setPosY(pos.getPosY() + 1);
				v.push_back(p1);
			}
		}

	if ((m_board[pos.getPosX() - 1][pos.getPosY() - 1].getType() == CPT_EMPTY) && ((pos.getPosY() - 1) >= 0) && (pos.getPosX() - 1 >= 0))
	{

	}
	else
		if ((m_board[pos.getPosX() - 1][pos.getPosY() - 1].getColor() != CPC_NONE) && ((pos.getPosY() - 1) >= 0) && (pos.getPosX() - 1 >= 0))
		{
			if ((m_board[pos.getPosX() - 1][pos.getPosY() - 1].getColor() != color))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() - 1);
				p1.setPosY(pos.getPosY() - 1);
				v.push_back(p1);
			}
		}

	if ((m_board[pos.getPosX() + 1][pos.getPosY() - 1].getType() == CPT_EMPTY) && ((pos.getPosY() - 1) >= 0) && (pos.getPosX() + 1 < NUM_COLS))
	{

	}
	else
		if ((m_board[pos.getPosX() + 1][pos.getPosY() - 1].getColor() != CPC_NONE) && ((pos.getPosY() - 1) >= 0) && (pos.getPosX() + 1 < NUM_ROWS))
		{
			if ((m_board[pos.getPosX() + 1][pos.getPosY() - 1].getColor() != color))
			{
				ChessPosition p1;
				p1.setPosX(pos.getPosX() + 1);
				p1.setPosY(pos.getPosY() - 1);
				v.push_back(p1);
			}
		}
}

VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos) const
{
	int posX = pos.getPosX();
	int posY = pos.getPosY();
	ChessPieceType tipus = GetPieceTypeAtPos(pos);
	vector <ChessPosition> v;

	switch (tipus)
	{
	case CPT_King:
	{
		getMovimentsRei(pos, v);
		for (int i = 0; i < v.size(); i++)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (v[i].getPosX() * CELL_W), CELL_INIT_Y + (v[i].getPosY() * CELL_H));
		}
	}
	break;
	case CPT_Queen:
	{
		getMovimentQueen(pos, v);
		for (int i = 0; i < v.size(); i++)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (v[i].getPosX() * CELL_W), CELL_INIT_Y + (v[i].getPosY() * CELL_H));
		}
	}
	break;
	case CPT_Rook:
	{
		getMovimentTorre(pos, v);
		for (int i = 0; i < v.size(); i++)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (v[i].getPosX() * CELL_W), CELL_INIT_Y + (v[i].getPosY() * CELL_H));
		}
	}
	break;
	case CPT_Bishop:
	{
		getMovimentAlfil(pos, v);
		for (int i = 0; i < v.size(); i++)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (v[i].getPosX() * CELL_W), CELL_INIT_Y + (v[i].getPosY() * CELL_H));
		}
	}
	break;
	case CPT_Knight:
	{
		getMovimentCavall(pos, v);
		for (int i = 0; i < v.size(); i++)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (v[i].getPosX() * CELL_W), CELL_INIT_Y + (v[i].getPosY() * CELL_H));
		}
	}
	break;
	case CPT_Pawn:
	{
		getMovimentPeo(pos, v);
		for (int i = 0; i < v.size(); i++)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (v[i].getPosX() * CELL_W), CELL_INIT_Y + (v[i].getPosY() * CELL_H));
		}
	}
	break;
	}
	return v;
}

bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{

	int posX = posFrom.getPosX();
	int posY = posFrom.getPosY();
	int finalPosX = posTo.getPosX();
	int finalPosY = posTo.getPosY();
	bool trobat = false;

	ChessPieceColor color = m_board[posX][posY].getColor();
	ChessPieceType type = m_board[posX][posY].getType();
	VecOfPositions validPositions;
	validPositions = GetValidMoves(posFrom); //pasamos las posiciones válidas a un vector para comparar
	vector<ChessPosition>::iterator start, end;
	start = validPositions.begin();
	end = validPositions.end();



	while (!trobat && start != end)
	{
		posX = start->getPosX();
		posY = start->getPosY();

		if (ChessPosition(posX, posY) == posTo)
		{
			trobat = true;
		}
		else
		{
			start++;
		}
	}
	// cogemos las iniciales para poder vaciar la posicion de la  pieza que se mueve
	posX = posFrom.getPosX();  
	posY = posFrom.getPosY();



	if (trobat == true) //como ya hicimos el cambio de posiciones no hace falta volverlo hacer, por eso, en esta parte, podemos dejar las variables en su forma convencional
	{
		//vaciamos
		m_board[posX][posY].setColor(CPC_NONE);
		m_board[posX][posY].setType(CPT_EMPTY);

		//modificamos
		m_board[finalPosX][finalPosY].setColor(color); 
		m_board[finalPosX][finalPosY].setType(type);

		return true;

	}
	else
	{
		return false;
	}
}

void Chessboard::Render_board()
{
	Piece Renderizar;
	ChessPieceColor color = CPC_Black;
	int cols;

	if (taulerInicialRender == false)
	{
		for (int j = 0; j < 2; j++)
		{
			if (color == CPC_Black)
				cols = 0;
			else
				cols = 7;

			//cambiar rows y cols por posicion o no se moverán
			Renderizar.Render(CPT_King, color, 4, cols);
			Renderizar.Render(CPT_Queen, color, 3, cols);
			Renderizar.Render(CPT_Rook, color, 0, cols);
			Renderizar.Render(CPT_Rook, color, 7, cols);
			Renderizar.Render(CPT_Bishop, color, 2, cols);
			Renderizar.Render(CPT_Bishop, color, 5, cols);
			Renderizar.Render(CPT_Knight, color, 1, cols);
			Renderizar.Render(CPT_Knight, color, 6, cols);


			for (int i = 0; i < NUM_COLS; i++)
			{
				if (color == CPC_Black)
					Renderizar.Render(CPT_Pawn, color, i, cols + 1);
				else
					Renderizar.Render(CPT_Pawn, color, i, cols - 1);

			}
			color = CPC_White;
		}
		taulerInicialRender = true;
	}
	else
	{
		for (int i = 0; i < NUM_ROWS; i++)
		{
			for (int j = 0; j < NUM_COLS; j++)
			{
				if (m_board[i][j].getType() != CPT_EMPTY)
				{
					ChessPieceColor colorFicha = m_board[i][j].getColor();
					ChessPieceType tipusFicha = m_board[i][j].getType();
					Renderizar.Render(tipusFicha, colorFicha, i, j);
				}
			}
		}
	}

}
bool Chessboard::comprovaRei()
{
	bool reiblanc = false;
	bool reinegre = false;

	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (m_board[i][j].getType() == CPT_King && m_board[i][j].getColor() == CPC_Black)
				reinegre = true;
			else
			{
				if (m_board[i][j].getType() == CPT_King && m_board[i][j].getColor() == CPC_White)
					reiblanc = true;
			}
		}
	}

	if ((reinegre == true && reiblanc == false) || (reinegre == false && reiblanc == true))
	{
		return true;
	}
	else
		return false;
}