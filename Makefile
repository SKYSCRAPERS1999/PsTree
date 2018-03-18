# Do *NOT* modify the existing build rules.
# You may add your own rules, e.g., "make run" or "make test".

LAB = pstree

include Makefile.git

.PHONY: build submit

build: $(LAB).c
	$(call git_commit, "compile")
	gcc -std=c99 -O1 -Wall -ggdb -o $(LAB) $(LAB).c

submit:
<<<<<<< HEAD
	cd .. && tar cj $(LAB) > submission.tar.bz2
=======
	cd .. && tar cj $(LAB) > submission.tar.bz2
	curl -F "task=M1" -F "id=$(STUID)" -F "name=$(STUNAME)" -F "submission=@../submission.tar.bz2" 114.212.81.90:5000/upload
>>>>>>> 9c1eb6e8e5c8d4f903ace764d627b3698a4f5bd0
