#ifndef _SHIP_HEADER_
#define _SHIP_HEADER_

int move( int** pTab, int nRow, int nCol, int nDepth,
    int move, int x, int y, int* px, int* py, int** pRoot );
int root( int** pTab, int nRow, int nCol, int nDepth,
    int x, int y, int** pRoot, int x_dest, int y_dest );
void clearRoot( int** pRoot, int nRow, int nCol );
int setTab( char* sFile, int** pTab, int nRow, int nCol );

#endif