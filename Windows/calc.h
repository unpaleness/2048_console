#ifndef _CALC_H_
#define _CALC_H_

namespace calc
{
	//allocates memory for some matrix
    void memory_alloc(short size, short **&matrix)
    {
        matrix = new short *[size];
        for(short i = 0; i < size; i++)
            matrix[i] = new short [size];
    }

    //frees memory from some matrix
    void memory_free(short size, short **&matrix)
    {
        for(short i = 0; i < size; i++)
            delete [] matrix[i];
        delete [] matrix;
    }
}

#endif
