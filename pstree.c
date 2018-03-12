#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1 
#define false 0
#define maxp 5000

int pn = 0; 
struct Proc{
	int pid, ppid, pgrp; 
	char name[64]; char state;
	int sz, mxsz;
	int *sons; 

	void init(){
	 size = 0; mxsz = 50; 
	 sons = = (int *)malloc(50 * sizeof(int));
	}
	//Proc(int pid, int ppid, int pgrp, char name[64]):pid(pid),ppid(ppid),pgrp(pgrp),name(name){}
}proc[maxp];

bool str_is_digit(char *s){
	bool ok = true;
	for (int i = 0; i < strlen(s); i++){
		if (!isdigit(s[i])) {
			ok = false; break;
		}
	}
	return ok;
}

int add_proc(char* filename){
	FILE* fp = fopen(filename, "r");
	if (fp) {
	  if (fscanf(fp, "%d%s%c%d%d", &proc[pn].pid, proc[pn].name, &proc[pn].state, &proc[pn].ppid, &proc[pn].pgrp) > 0){
	  	proc[pn].init(); ++pn;
	  	puts("OK");
	  }else{puts("ERROR");}
	  fclose(fp);
	} else {
		printf("Not Opened\n");
	}
	return pn;
}

void read_proc(char* dir){
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir)) == NULL) {
		printf("Can't open %s\n", dir); 
		return;
	}
	while ((dirp = readdir(dp)) != NULL) {
		if (!str_is_digit(dirp->d_name)) continue;
		else {
			char filename[256];
			sprintf(filename, "%s%s/stat", dir, dirp->d_name);
			printf("cnt: %d\n", add_proc(filename));
		}
	}
	closedir(dp);
}

int main(int argc, char *argv[]) {
  int i;
  for (i = 0; i < argc; i++) {
    assert(argv[i]); // specification
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  assert(!argv[argc]); // specification

  read_proc("/proc/");
  return 0;
}
