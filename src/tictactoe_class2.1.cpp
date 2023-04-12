/*
 * TicTacToe class element functions implementation. v.1.1
 * 5.03.2013
 * No part of this code.... blah-blah-blah....
 * (c)A.Gerasimenko
 */
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
#include<cstdlib>
using std::srand;
using std::rand;
#include<ctime>
using std::time;
#include<cmath>
using std::abs;

#include"tictactoe_class2.h"

  TicTacToe::TicTacToe()
  {
    boardSize = 3;
    for ( int i = 0; i < boardSize; i++)
    {
      for ( int j = 0; j < boardSize; j++)
      {
	board[i][j].val = 0;
	board[i][j].priority = 0;
      }
    }
    srand(time(0));
  }

  TicTacToe::TicTacToe(int size)
  {
    boardSize = size;
    for ( int i = 0; i < boardSize; i++)
    {
      for ( int j = 0; j < boardSize; j++)
      {
	board[i][j].val = 0;
	board[i][j].priority = 0;
      }
    }
    srand(time(0));
  }
  
  void TicTacToe::startGame( int playerId )
  {    
    playerId = HUMAN;
    while ( nextTurn(playerId) == 0 )
    {
      playerId *= -1;
      printBoard();
    }
      
    
  }
  
  
  int TicTacToe::nextTurn(int playerIndex)// 1 - human, -1 - computer
  {
    int maxPrty = 0, maxSum = 0, flag = 0;
    int stackCount = 0;
    int *boardElemPtr[100];

    for ( int i = 0; i < boardSize; i++) // find max priority value       findMaxPriority();
    {
      for ( int j = 0; j < boardSize; j++)
      {
	if ( 0 == board[i][j].val )
	{
	  flag++;
	}
      }
    }
    if ( 0 == flag )
    {
      return 1;
    }
    if ( HUMAN == playerIndex )
    {
      int i, j;
      
      do
      {
      if ( updPriority() == 1 )
      {
        cout<< " Comp has you! " << endl;
	return 1;
      }
        cout << "Your turn! Enter coordinates: line = ";
        cin >> i;
        cout << ", column = ";
        cin >> j;
        cout << endl;
      }
      while ( board[i][j].val != 0 );
      board[i][j].val = playerIndex;
    }
    else
    {
      if ( updPriority() == 1 )
      {
	return 1;
      }
      for ( int i = 0; i < boardSize; i++) // find max priority value       findMaxPriority();
      {
	for ( int j = 0; j < boardSize; j++)
	{
	  if ( board[i][j].priority > maxPrty && 0 == board[i][j].val )
	  {
	     maxPrty = board[i][j].priority;
	  }
	}
      }
      for ( int i = 0; i < boardSize; i++) // form stack    formPriorityStack();
      {
	for ( int j = 0; j < boardSize; j++)
	{
	  if (maxPrty == board[i][j].priority && 0 == board[i][j].val )
	  {
	    boardElemPtr[ stackCount++ ] = &( board[i][j].val );
	    if ( board[i][j].maxSum > maxSum )
	    {
	      maxSum = board[i][j].maxSum;
	      stackCount = 0;
	      boardElemPtr[ stackCount++ ] = &( board[i][j].val );
	    }
	  }
	}
      }
      *boardElemPtr[ rand() % stackCount ] = -1;  //      chooseOneFromStack(); chooseMaxSum
    }
    return 0;
  }
  
  int TicTacToe::updPriority()
  {
    for ( int i = 0; i < boardSize; i++)
    {
      for (int j = 0; j < boardSize; j++)
      {
        board[i][j].priority = checkLine( i, j ) + checkCol( i, j ) + checkDiag( i, j );
	board[i][j].maxSum = findMaxSum( i, j );
	if ( boardSize == board[i][j].maxSum )
	{
	  return 1; 
	}
      }
    }
    return 0;
  }
  int TicTacToe::findMaxSum( const int i, const int j )
  {
    int max1 = 0, max2 = 0, maxDiag = 0;
    for ( int n = 0; n < boardSize; n++) // line sum
    {
      max1 += board[i][n].val;
    }
    for ( int n = 0; n < boardSize; n++) // column sum
    {
      max2 += board[n][j].val;
    }
    if ( abs(max1) < abs(max2) )
    {
      max1 = abs(max2);
    }
    max2 = 0;
    if ( i == j ) // left to right diag (main diag)
    {
      for ( int n = 0; n < boardSize; n++) // line sum
      {
        max2 += board[n][n].val;
      }
      if ( abs(max1) < abs(max2) )
      {
        max1 = abs(max2);
      }
      max2 = 0;
    }
    
    if ( (i + j) == boardSize - 1 ) //  secondary diag
    {
      for ( int n = 0; n < boardSize; n++) // line sum
      {
        max2 += board[n][ boardSize - 1 - n ].val;
      }
      if ( abs(max1) < abs(max2) )
      {
        max1 = abs(max2);
      }
      max2 = 0;
    }
    return abs(max1);
  }
  
  int TicTacToe::checkLine( const int i, const int j )
  {
    int sum = 0;
    for ( int n = 0; n < boardSize; n++)
    {
      sum += board[i][n].val;
    }
    sum = abs(sum);
    return sum;
  }
  
  int TicTacToe::checkCol( const int i, const int j )
  {
    int sum = 0;
    for ( int n = 0; n < boardSize; n++)
    {
      sum += board[n][j].val;
    }
    return abs(sum);
  }
  
  int TicTacToe::checkDiag( const int i, const int j )
  {
    int res = 0,sum = 0, sum1 = 0;
    if ( i == j && (i+j) != boardSize - 1 )
    {
      for ( int n = 0; n < boardSize; n++)
      {
        sum += board[n][n].val;
      }
    }
    res += abs(sum);
    sum = 0;
    if ( i != j && (i+j) == boardSize - 1 )
    {
      for ( int n = 0; n < boardSize; n++)
      {
        sum += board[ boardSize - 1 - n ][n].val;
      }
    }
    res += abs(sum);
    sum = 0;
    if ( i == j && (i+j) == boardSize - 1)
    {
      for ( int n = 0; n < boardSize; n++ )
      {
        sum += board[n][n].val;
      }
      for ( int n = 0; n < boardSize; n++)
      {
        sum1 += board[boardSize - 1 - n][n].val;
      }

    }
    res += ( abs(sum) + abs(sum1) );
    return res;
  }

  void TicTacToe::printBoard()
  {
    cout << endl;
    cout << "* ";   // upper boundary
    for ( int j = 0; j < boardSize; j++) 
    {
      cout << j << " ";
    }
    cout << "* ";
  
    for ( int i = 0; i < boardSize ; i++)  // board body
    {
      cout << endl << i << " ";
      for ( int j = 0; j < boardSize; j++)
      {
        switch ( board[i][j].val )
	{
	  case -1:
	    cout << "o ";
	    break;
	  case 1:
	    cout << "+ ";
	    break;
	  default:
	    cout << "  ";
	};
	
      }
      cout << i;
    }
    cout << endl;
    cout << "* "; // lower boundary
    for ( int j = 0; j < boardSize; j++) 
    {
      cout << j << " ";
    }
    cout << "* " << endl; 
  }
