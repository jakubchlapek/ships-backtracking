#include "ship.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

// zdefiniowac typ wyliczeniowy: kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne od 0)
typedef enum{
    UP, DOWN, RIGHT, LEFT
}MoveDirection;

int move( int** pTab, int nRow, int nCol, int nDepth,
    int move, int x, int y, int* px, int* py, int** pRoot )
{
    // x  y - wsporzedne skad robimy nowy ruch
    //  wykonac kolejny ruch w kierunku move obliczajac nowe wspolrzedne *px *py
    //(switch)
    switch( move )
    {
    case UP: *px = x - 1; *py = y; break;
    case DOWN: *px = x + 1; *py = y; break;
    case RIGHT: *px = x; *py = y + 1; break;
    case LEFT: *px = x; *py = y - 1; break;
    default: perror( "Wrong direction" );
    }

    //sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
    if( (*px < 0) || (*py < 0) || (*px >= nRow) || (*py >= nCol) ) return 0;

    // a nastepnie sprawdzic warunek czy nie jest za plytko ">nDepth " 
    if( pTab[*px][*py] <= nDepth ) return 0;

    // oraz czy nie bylo sie juz w lokalizacji (*px,*py) - wg tabl pRoot (wart 0 w nowej lokalicacji)
    if( pRoot[*px][*py] != 0 ) return 0;

    return 1;
}

int root( int** pTab, int nRow, int nCol, int nDepth,
    int x, int y, int** pRoot, int x_dest, int y_dest ) //--- rekurencyja
{
    // tabl pRoot pamieta droge   -   numer ruchu pole przez ktore odwiedzono (plynie statek) 
    //                                0 pole nie odwiedzone
    // wstawic do tablicy pRoot kolejny numer ruchu
    static int move_count = 1;
    pRoot[x][y] = move_count++;

    // jeœli dotarto do portu zwróæ 1
    if( x == x_dest && y == y_dest )
        return 1;

    // else
    // zdefiniowac nowe wspolrzedne
    int px = x;
    int py = y;

    for( int i = UP; i <= LEFT; i++ )   // sprawdzic wszystkie mozliwosci ruchu        
        if( move( pTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) )    //jesli ruch jest mozliwy w zadanym kierunku 
            if( root( pTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) )    //jesli wykonanie kolejnego kroku sie powiodlo
                return 1;

    // jesli wracamy to ustawiamy w pRoot ze ruch byl zly
    return 0;
}


void clearRoot( int** pRoot, int nRow, int nCol )
{
    // zeruje tablice  
    memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
    // wczytuje dane z pliku
    FILE* fin = NULL;
    if( (fin = fopen( sFile, "rt" )) == NULL )
    {
        return 0;
    }

    for( int i = 0; i < nRow; i++, pTab++ )
    {
        int* pTemp = *pTab;
        for( int j = 0; j < nCol; j++, pTemp++ )
            fscanf( fin, "%d", pTemp );
    }
    fclose( fin );
    return 1;
}