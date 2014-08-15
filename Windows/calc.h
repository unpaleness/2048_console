#ifndef _CALC_H_
#define _CALC_H_

namespace calc
{
    //allocates memory for some array
    template <class AnyClass>
    void memory_alloc(short size, AnyClass *&array)
    {
        array = new AnyClass [size];
    }

    //frees memory from some array
    template <class AnyClass>
    void memory_free(AnyClass *&array)
    {
        delete [] array;
    }

	//allocates memory for some matrix
    template <class AnyClass>
    void memory_alloc(short size, AnyClass **&matrix)
    {
        matrix = new AnyClass *[size];
        for(short i = 0; i < size; i++)
            matrix[i] = new AnyClass [size];
    }

    //frees memory from some matrix
    template <class AnyClass>
    void memory_free(short size, AnyClass **&matrix)
    {
        for(short i = 0; i < size; i++)
            delete [] matrix[i];
        delete [] matrix;
    }
}

#endif
