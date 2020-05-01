/*        
 * Filename: cdk.cc
 * Date: 4/30/2020
 * Author: Aashish Sharma
 * Course: CS 3377.501, Spring 2020
 * Version: 1.0
 * Copyright: 2020, All Rights Reserved
 * 
 * Description                                                                                                                                                                                                  
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <sstream>
#include "Header.h"

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH maxRecordStringLength
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{
  WINDOW *window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"", "a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
  {
    printf("Natrix error");
    _exit(1);
  }

  ifstream bFile;
  bFile.open("/scratch/perkins/cs3377.bin",  ios::in |  ios::binary);

  if(!bFile.is_open())
  {
    cout << "File couldn't be opened" <<  endl;
    exit(EXIT_FAILURE);
  }
  
  BinaryFileHeader *head = new BinaryFileHeader();
  bFile.read((char*)head ,sizeof(BinaryFileHeader));
  
  stringstream s;
  s << "Magic: 0x" << hex << uppercase << head->magic;  
  setCDKMatrixCell(myMatrix, 1, 1, s.str().c_str());
  s.str( string());
  stringstream s2;
  s2 << "Version: " << (int)head->version;
  setCDKMatrixCell(myMatrix, 1, 2, s2.str().c_str());
  s2.str( string());
  s2 << "NumRecords: " << head->numRecords;
  setCDKMatrixCell(myMatrix, 1, 3, s2.str().c_str());
  int mRecords = (int)head->numRecords;
  if(mRecords > 4)
  {
    mRecords = 4;
  } 
  int x = 2;
  while(x < mRecords + 2)
  {
    s2.str( string());
    BinaryFileRecord *record = new BinaryFileRecord();
    bFile.read((char *) record, sizeof(BinaryFileRecord));
    s2 << "strlen: " << (int)record->sLength;
    setCDKMatrixCell(myMatrix, x, 1, s2.str().c_str());
    setCDKMatrixCell(myMatrix, x, 2, record->stringBuffer);
    delete record;
    x++;
  }
  drawCDKMatrix(myMatrix, true);
  sleep (10);
  endCDK();
  return 0;
}
