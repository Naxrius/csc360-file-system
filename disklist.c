/*
 * Assignment 3
 *
 * Name: Nick Warwick
 * Student Number: V00773474
 */

#include "functions.h"

int entStatus = 0, entStartBlock = 0, entNumBlocks = 0, entSize = 0, entUsed = 0;
char *entName;
char *entModDate;

void getRootInfo(FILE *fp){
	int i;
	int rootStart = getRootDirStart(fp);
	int numBlocks = getRootDirBlocks(fp);
	int numEntries = numBlocks*8;
	int offset = rootStart*DEFAULT_BLOCK_SIZE; // 


	for(i=0;i<numEntries; ++i){ // For each entry, get its info
		entStatus = getEntStatus(fp, offset); // Get status
		entSize = getEntFileSize(fp, offset); // Get file sze
		getEntName(fp, offset, entName); // Get file name
		getEntModDate(fp, offset, entModDate); // Get modfication date
		
		if(entStatus & 0x001){ // Is the entry free or used?
			if(entStatus & 0x03){ // Is it a file or a directory?
				printf("F ");
			}else{
				printf("D ");
			}
			printf("%10d ", entSize);
			printf("%30s ", entName);
			printf("%s\n", entModDate);
		}
		offset+=DIRECTORY_ENTRY_SIZE; // move offset to next directory location
	}
}

int main(int argc, char** argv){
	FILE *fp;
	entName = (char *)malloc(sizeof(char)*ENT_FILE_NAME_SIZE);
	entModDate = (char *)malloc(sizeof(char)*ENT_MOD_TIME_SIZE);

	if((fp=fopen(argv[1], "r"))){
		getRootInfo(fp);

		fclose(fp);
	}else{
		printf("Cannot find %s\n", argv[1]);
	}

	free(entName);
	free(entModDate);
	return 0;
}
