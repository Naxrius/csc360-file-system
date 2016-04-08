#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "Constants.h"


// Shared functions
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void getIdent(FILE *fp, char *ident);
int getBlockSize(FILE *fp);
int getBlockCount(FILE *fp);
int getFATStart(FILE *fp);
int getFATBlocks(FILE *fp);
int getBlock(FILE *fp, int offset);
int getRootDirStart(FILE *fp);
int getRootDirBlocks(FILE *fp);
int getEntStatus(FILE *fp, int offset);
void getFATInfo(FILE *fp);
int getEntStatus(FILE *fp, int offset);
int getEntStartBlock(FILE *fp, int offset);
int getEntFileSize(FILE *fp, int offset);
void getEntName(FILE *fp, int offset, char *entName);
void getEntModDate(FILE *fp, int offset, char *entName);

void setFATBlock(FILE *fp, int fatOffset, int block);
void setEntStatusFile(FILE *fp, int offset);
void setEntStartBlock(FILE *fp, int offset, int block);
void setEntNumBlocks(FILE *fp, int offset, int num);
void setEntFileSize(FILE *fp, int offset, int size);
void setEntCreateDate(FILE *fp, int offset, struct tm date);
void setEntModDate(FILE *fp, int offset, struct tm date);
void setEntName(FILE *fp, int offset, char *entName);

void writeFileData(FILE *fp, FILE *cpyFile, int dataOffset, int fileOffset, int size);
void copyFileData(FILE *fp,  FILE *newFile, int offset, int fileSize);

#endif