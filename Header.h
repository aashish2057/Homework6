/*
 * Filename: Header.h
 * Date: 4/30/2020
 * Author: Aashish Sharma
 * Email: aashsish.sharma@utdallas.edu
 * Course: CS 3377.501 Spring 2020
 * Version: 1.0
 * Copyright: 2020, All Rights Reserved
 *
 * Description
 *
 * 	header file for project
 */

#include <stdint.h>

class BinaryFileHeader
{
  public:
   uint32_t magic;
   uint32_t version;
   uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
  public:
     uint8_t sLength;
     char stringBuffer[maxRecordStringLength];
};
