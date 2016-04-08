all: createDiskInfo createDiskList createDiskGet createDiskPut

clean: removeStuff

createDiskInfo:
	gcc -Wall -g diskinfo.c functions.c -o diskinfo

createDiskList:
	gcc -Wall -g disklist.c functions.c -o disklist

createDiskGet:
	gcc -Wall -g diskget.c functions.c -o diskget

createDiskPut:
	gcc -Wall -g diskput.c functions.c -o diskput	

removeStuff: 
	rm -rf *.o diskinfo diskget disklist diskput
