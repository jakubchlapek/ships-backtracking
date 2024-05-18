#include <stdio.h>
#include <memory.h>
#include "ship.h"
#include <stdlib.h>

#define DEPTH_MIN 5    // glebokosc zanurzenia okretu 
#define N 10 // wiersze
#define M 10 // kolumny

void PrintMatrix( int** pTab, int nRow, int nCol );
void FreeMatrix( int*** pTab );
int** CreateTab2D( int nRow, int nCol );

int main( int argc, char** argv )
{
    //!!argc
    if( argc != 2 )
    {
        printf( "Usage: %s <input_file>\n", argv[0] );
        return 1;
    }
    printf( "argc = %d\n", argc );

    //Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary)
    int** pTab = CreateTab2D( N, M );
    if( !pTab )
    {
        perror( "Allocation Error: pTab\n\n" );
        return 2;
    }

    int** pRoot = CreateTab2D( N, M );
    if( !pRoot )
    {
        perror( " Allocation Error: pRoot\n\n" );
        return 3;
    }

    // wczytac dane glebokosci 
    if( !setTab( argv[1], pTab, N, M ) )
    {
        printf( "Error opening input file %s\n", argv[1]);
        return 4;   
    }

    printf( "Mapa glebokosci: \n" );
    PrintMatrix( pTab, N, M );
    printf( "\n\n" );

    // Jezeli nie znaleziono drogi od (0,0) do (N,M)- funkcja rekur root - wypisac
    if( !root( pTab, N, M, DEPTH_MIN, 0, 0, pRoot, N - 1, M - 1 ) )
    {
        printf( "Nie ma mozliwosci doplynac do portu!\n\n" );
    }

    // jesli ok to wypisac trase
    else
    {
        printf( "Trasa do portu: \n" );
        PrintMatrix( pRoot, N, M );
        printf( "\n" );
    }

    //zwolnic pamiec!!
    FreeMatrix( &pRoot );
    FreeMatrix( &pTab );
    return 0;
}

//==========================================================
//Funkcje z układu równań

void PrintMatrix( int** pTab, int nRow, int nCol ) // drukuje macierz 
{

    for( int i = 0; i < nRow; i++ )
    {
        int* pTemp = *pTab++;
        printf( "\n" );
        for( int j = 0; j < nCol; j++ )
        {
            printf( "%d ", *pTemp++ );
        }
    }
}

void FreeMatrix( int*** pTab ) //zwalnianie pamięci
{
    free( **pTab );
    free( *pTab );
    *pTab = NULL;
}

int** CreateTab2D( int nRow, int nCol ) //kreowanie druga metoda // z zerowaniem
{
    int** pTab = (int**)malloc( sizeof( int* ) * nRow );
    if( !pTab )
        return NULL;
    memset( pTab, 0, sizeof( int* ) * nRow );

    *pTab = (int*)malloc( sizeof( int ) * nRow * nCol );
    if( !*pTab )
        return NULL;
    memset( *pTab, 0, sizeof( int ) * nRow * nCol );

    int** pTemp = pTab + 1;
    int* pTemp2 = *pTab + nCol;

    for( int i = 1; i < nRow; i++, pTemp2 += nCol )
        *pTemp++ = pTemp2;
    return pTab;
}
