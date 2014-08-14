#ifndef _BOARD_H_
#define _BOARD_H_

#include "calc.h"

//contains current state of the board
class Board
{
public:

	Board() {}
	~Board() { calc::memory_free(_size, _board); }

	short **board(void) { return _board; }
    short size(void) { return _size; }

	void init(short size)
	{
		_size = size;
		calc::memory_alloc(_size, _board);
        _nullification();
	}

    Board &operator =(const Board &fromboard)
    {
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                _board[j][i] = const_cast<Board &>(fromboard).board()[j][i];
    }

    bool operator ==(const Board &fromboard)
    {
        if(_size != const_cast<Board &>(fromboard).size())
            return false;
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                if(_board[j][i] != const_cast<Board &>(fromboard).board()[j][i])
                    return false;
        return true;
    }

    bool operator !=(const Board &fromboard)
    {
        if(_size != const_cast<Board &>(fromboard).size())
            return true;
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                if(_board[j][i] != const_cast<Board &>(fromboard).board()[j][i])
                    return true;
        return false;
    }

private:
	short _size;
	short **_board;

	//allocates memory for some matrix
    void _memory_alloc(short size, short **&matrix)
    {
        matrix = new short *[size];
        for(short i = 0; i < size; i++)
            matrix[i] = new short [size];
    }

    //frees memory from some matrix
    void _memory_free(short size, short **&matrix)
    {
        for(short i = 0; i < size; i++)
            delete [] matrix[i];
        delete [] matrix;
    }

    //nullificates gameboard
    void _nullification()
    {
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                _board[j][i] = 0;
    }

};

#endif
