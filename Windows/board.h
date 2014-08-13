#ifndef _BOARD_H_
#define _BOARD_H_

//contains current state of the board
class Board
{
public:

	Board() {}
	~Board() { _memory_free(_size, _board); }

	short **board(void) { return _board; }

	void init(short size)
	{
		_size = size;
		_memory_alloc(_size, _board);
	}

private:
	short _size;
	short int **_board;

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
                _gameboard[j][i] = 0;
    }

};

#endif
