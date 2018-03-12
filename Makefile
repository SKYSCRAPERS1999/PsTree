# Do *NOT* modify the existing build rules.
# You may add your own rules, e.g., "make run" or "make test".

LAB = pstree

include Makefile.git

.PHONY: build submit

build: $(LAB).c
	$(call git_commit, "compile")
	gcc -std=c99 -O1 -Wall -ggdb -o $(LAB) $(LAB).c

submit:
	cd .. && tar cj $(LAB) > submission.tar.bz2