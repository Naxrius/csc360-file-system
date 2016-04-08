/*
 * Assignment 3
 *
 * Name: Nick Warwick
 * Student Number: V00773474
 */

#include "functions.h"

//Global vars
int blockSize, blockCount, fatStart, fatBlocks, rootDirStart, rootDirBlocks, numFatEntries;

void printFSInfo(){
	printf("Super block information:\n");
	printf("Block size: %d\n", blockSize);
	printf("Block count: %d\n", blockCount);
	printf("FAT starts: %d\n", fatStart);
	printf("FAT blocks: %d\n", fatBlocks);
	printf("Root directory start: %d\n", rootDirStart);
	printf("Root directory blocks: %d\n", rootDirBlocks);

}

//Get FAT information
void getFATInfo(FILE *fp){
	long val;
	int allocatedBlocks = 0,  reservedBlocks = 0, freeBlocks = 0;
	int loc = fatStart*DEFAULT_BLOCK_SIZE; // Fat start location (in bytes)
	int range = (numFatEntries*4)+loc; // address range (in bytes) = numEntries*4(bytes each)+fat location (account for superblock)

	fseek(fp, loc, SEEK_SET); //skip past super block
	//printf("currently at %lu\n", ftell(fp));

	while(ftell(fp)<range){ // iterate through each FAT entry
		//printf("currently at %lu\n", ftell(fp));
		fread(&val, 1, FAT_ENTRY_SIZE, fp);
		val = htonl(val);
		if(val == FAT_RESERVED){ // count each occurrence of free, reserved, and allocated entries
			++reservedBlocks;
		}else if(val == FAT_FREE){
			++freeBlocks;
		}else {
			++allocatedBlocks;
		}
	}
	printf("Free Blocks: %d\n", freeBlocks);
	printf("Reserved Blocks: %d\n", reservedBlocks);
	printf("Allocated Blocks: %d\n", allocatedBlocks);
}

int main(int argc, char** argv){
	FILE *fp;
	char *ident = malloc(sizeof(char)*IDENT_SIZE); // Set to size of Identifier 
	
	if((fp=fopen(argv[1], "r"))){
		//getIdent(fp, ident); // Read the identifier value into ident
		blockSize = getBlockSize(fp);
		blockCount = getBlockCount(fp);
		fatStart = getFATStart(fp);
		fatBlocks = getFATBlocks(fp);
		rootDirStart = getRootDirStart(fp);
		rootDirBlocks = getRootDirBlocks(fp);

		printFSInfo();

		printf("\nFAT information:\n");
		numFatEntries = (FAT_ENTRY_PER_BLOCK * fatBlocks);
		getFATInfo(fp);

		fclose(fp);
	}else{
		printf("Cannot find %s\n", argv[1]);
	}

	free(ident);
	return 0;
}