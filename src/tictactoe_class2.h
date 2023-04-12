/*
 * TicTacToe,BoardElem class implementation. v.1.0
 * 5.03.2013
 * No part of this code.... blah-blah-blah....
 * (c)A.Gerasimenko
 */


#ifndef BOARDELEM_H
#define BOARDELEM_H
class BoardElem
{
  public:
  int val;
  int priority;
  int maxSum;
};
#endif

#ifndef TICTACTOE_H
#define TICTACTOE_H


class TicTacToe
{
public:
  TicTacToe();
  TicTacToe(int);
  void startGame();
private:
  int nextTurn(int playerIndex);
  int updPriority();
  int findMaxSum(const int, const int);
  int checkLine(const int, const int );
  int checkCol(const int, const int );
  int checkDiag(const int, const int );
  void printBoard();
  
  int boardSize;
  BoardElem board[10][10];
  enum{COMP = -1,HUMAN = 1 };
};
#endif