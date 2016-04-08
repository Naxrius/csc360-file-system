// Nick Warwick

#include "functions.h"

char *fileName;
int fileSize = 0;
int fileBlock = 0;

int findFile(FILE *fp, char *fName){
	int i;
	int rootStart = getRootDirStart(fp);
	int numBlocks = getRootDirBlocks(fp);
	int numEntries = numBlocks*8; // 8 dir entries per block
	int offset = rootStart*DEFAULT_BLOCK_SIZE;
	char *entName = (char *)malloc(sizeof(char)*ENT_FILE_NAME_SIZE);

	for(i=0;i<numEntries; ++i){ // For each entry, get its info
		getEntName(fp, offset, entName); // Get file name
		fileSize = getEntFileSize(fp, offset);
		
		if(strcmp(fName, entName) == 0){
			printf("File %s found, Size = %d\n", entName, fileSize);
			fileBlock = getEntStartBlock(fp, offset); // If the file is found get the location of starting block of the file
			free(entName);
			return 1;
		}
		offset+=DIRECTORY_ENTRY_SIZE; // move offset to next directory location
	}

	printf("File not found\n");
	free(entName);
	return 0;
}


void copyFile(FILE *fp){
	FILE *newFile;
	newFile = fopen(fileName, "w");
	int fatStart = getFATStart(fp)*DEFAULT_BLOCK_SIZE; // FAT start (in bytes)
	int blockOffset = fatStart+(fileBlock*FAT_ENTRY_SIZE); // offset for blocks in the FAT
	int dataOffset = fileBlock*DEFAULT_BLOCK_SIZE; // offset for data in the data area
	//printf("Starting block %d\n", fileBlock);

	while(fileSize>DEFAULT_BLOCK_SIZE){ // While there is still data left to copy, copy it
		//printf("block = %d\n", fileBlock);
		fileSize -= DEFAULT_BLOCK_SIZE;
		copyFileData(fp, newFile, dataOffset, DEFAULT_BLOCK_SIZE);
		fileBlock = getBlock(fp, blockOffset); // Get the next block
		blockOffset = fatStart+(fileBlock*FAT_ENTRY_SIZE);
		dataOffset = fileBlock*DEFAULT_BLOCK_SIZE;
	}
	copyFileData(fp, newFile, dataOffset, fileSize); // Copy the remaining data of the file

	fclose(newFile);
}

int main(int argc, char** argv){
	FILE *fp;
	fileName = argv[2];

	if((fp=fopen(argv[1], "r"))){
		if(findFile(fp, fileName) == 1){ // If the file is found, copy it
			copyFile(fp);
		}

		fclose(fp);
	}else{
		printf("Cannot find %s\n", argv[1]);
	}

	return 0;
}