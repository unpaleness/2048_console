#ifndef _COUNT_H_
#define _COUNT_H_

#include <cmath>

short max_val(short **, short);
short status_checking(short *, short);
short shift(short **, short, short);

//counts max value on the board
short max_val(short **a, short W)
{
    short res = 0;
    for(short j = 0; j < W; j++)
        for(short i = 0; i < W; i++)
            if(a[j][i] > res) res = a[j][i];
    return res;
}

//0 - continue, 1 - lose, 2 - win
short status_checking(short **a, short W)
{
    short counter = 0, movements = 0;
    for(short j = 0; j < W; j++)
        for(short i = 0; i < W; i++)
        {
            if(a[j][i] == 11)
                return 2;
            if(a[j][i] != 0)
                counter++;
        }
    if(counter == W * W)
    {
        short **a_temp = new short *[W];
        for(short i = 0; i < W; i++)
            a_temp[i] = new short [W];
        for(short j = 0; j < W; j++)
            for(short i = 0; i < W; i++)
                a_temp[j][i] = a[j][i];
        for(short i = 0; i < 4; i++)
            movements += shift(a_temp, W, i);
        for(short i = 0; i < W; i++)
            delete [] a_temp[i];
        delete [] a_temp;
        if(movements == 0)
            return 1;
    }
    return 0;
}

//dir: odd - horizontal, even - vertical
//0 - not shifted, 1 - shifted
short shift(short **a, short W, short dir)
{
    bool changed = false;
    short **a_rec = new short *[W];
    for(short i = 0; i < W; i++)
        a_rec[i] = new short [W];
    for(short j = 0; j < W; j++)
        for(short i = 0; i < W; i++)
            a_rec[j][i] = a[j][i];
    //^
    if(dir == 0)
    {
        //every row..
        for(short i = 0; i < W; i++)
        {
            short not_0 = 0;
            //erasing spaces
            for(short j = 0; j < W; j++)
                if(a[j][i] != 0)
                {
                    not_0++;
                    if(j != not_0 - 1)
                    {
                        a[not_0 - 1][i] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short j = 0; j < W - 1; j++)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j + 1][i])
                    {
                        a[j][i]++;
                        a[j + 1][i] = 0;
                    }
                }
                else
                {
                    for(short k = j; k < W - 1; k++)
                        a[k][i] = a[k + 1][i];
                    a[W - 1][i] = 0;
                    if(a[j][i] != 0)
                        j--;
                }
            }
        }
    }
    //<-
    if(dir == 1)
    {
        //every row..
        for(short j = 0; j < W; j++)
        {
            short not_0 = 0;
            //erasing spaces
            for(short i = 0; i < W; i++)
                if(a[j][i] != 0)
                {
                    not_0++;
                    if(i != not_0 - 1)
                    {
                        a[j][not_0 - 1] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short i = 0; i < W - 1; i++)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j][i + 1])
                    {
                        a[j][i]++;
                        a[j][i + 1] = 0;
                    }
                }
                else
                {
                    for(short k = i; k < W - 1; k++)
                        a[j][k] = a[j][k + 1];
                    a[j][W - 1] = 0;
                    if(a[j][i] != 0)
                        i--;
                }
            }
        }
    }
    //\/
    if(dir == 2)
    {
        //every row..
        for(short i = 0; i < W; i++)
        {
            short not_0 = W - 1;
            //erasing spaces
            for(short j = W - 1; j >= 0; j--)
                if(a[j][i] != 0)
                {
                    not_0--;
                    if(j != not_0 + 1)
                    {
                        a[not_0 + 1][i] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short j = W - 1; j > 0; j--)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j - 1][i])
                    {
                        a[j][i]++;
                        a[j - 1][i] = 0;
                    }
                }
                else
                {
                    for(short k = j; k > 0; k--)
                        a[k][i] = a[k - 1][i];
                    a[0][i] = 0;
                    if(a[j][i] != 0)
                        j++;
                }
            }
        }
    }
    //\/
    if(dir == 3)
    {
        //every row..
        for(short j = 0; j < W; j++)
        {
            short not_0 = W - 1;
            //erasing spaces
            for(short i = W - 1; i >= 0; i--)
                if(a[j][i] != 0)
                {
                    not_0--;
                    if(i != not_0 + 1)
                    {
                        a[j][not_0 + 1] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short i = W - 1; i > 0; i--)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j][i - 1])
                    {
                        a[j][i]++;
                        a[j][i - 1] = 0;
                    }
                }
                else
                {
                    for(short k = i; k > 0; k--)
                        a[j][k] = a[j][k - 1];
                    a[j][0] = 0;
                    if(a[j][i] != 0)
                        i++;
                }
            }
        }
    }
    //checking for changes
    for(short j = 0; j < W & !changed; j++)
        for(short i = 0; i < W; i++)
            if(a[j][i] != a_rec[j][i])
            {
                changed = true;
                break;
            }

    for(short i = 0; i < W; i++)
        delete [] a_rec[i];
    delete [] a_rec;

    if(changed)
        return 1;
    return 0;
}

#endif
