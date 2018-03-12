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
	char name[64]; char state[8];
	//int sz, mxsz;
	//int *sons; 
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

void add_proc(char* filename){
	FILE* fp = fopen(filename, "r");
	if (fp) {
	  if (fscanf(fp, "%d%s%s%d%d", &proc[pn].pid, proc[pn].name, &proc[pn].state, &proc[pn].ppid, &proc[pn].pgrp) > 0){
	  	//proc[pn].sz = 0, proc[pn].mxsz = 50, proc[pn].sons = (int *)malloc(50 * sizeof(int));
	  	int len = strlen(proc[pn].name);
		if (len >= 2){
		  	for (int i = 0; i < len - 1; i++){
		  		proc[pn].name[i] = proc[pn].name[i + 1];
		  	}
		  	proc[pn].name[len - 2] = '\0';
		}
	  	printf("%d : %d %s %s %d %d\n", pn,  proc[pn].pid, proc[pn].name, proc[pn].state, proc[pn].ppid, proc[pn].pgrp);
	  	++pn; puts("OK");

	  }else{puts("ERROR");}
	  fclose(fp);
	} else {
		printf("Not Opened\n");
	}
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
			add_proc(filename);
		}
	}
	closedir(dp);
}

int find_proc(int pid){
	for (int i = 0; i < pn; i++) if (proc[i].pid == pid) return i;
	return -1;
}

void dfs_print(){
	int idx = -1;
	if ((idx = find_proc(1)) >= 0){
		dfs(idx, idx);
	}else{puts("ERROR");}
}

void dfs(int x, int px, int indent){
	printf("|");
	for (int i = 0; i < indent; i++) printf(" ");
	int next_indent = printf("|---%d\n", proc[x].pid);
	for (int i = 0; i < pn; i++){
		if (i == x || i == px) continue;
		if (proc[i].ppid == proc[x].pid){
			dfs(i, x, next_indent - 1);
		} 
	}
}


int main(int argc, char *argv[]) {
  int i;
  for (i = 0; i < argc; i++) {
    assert(argv[i]); // specification
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  assert(!argv[argc]); // specification

  read_proc("/proc/");

  dfs_print();
  return 0;
}
