FLAGS=
DEPEN= src/graph.c

all: compile run clean_w clean_l

compile:
	mkdir -p out
	gcc $(FLAGS) main.c -o ./out/graph $(DEPEN)

run:
	./out/graph

# clean for windows
clean_w:
	powershell -Command "Remove-Item .\out\* -Recurse -Force"

# clean for linux
clean_l:
	rm -rf out/*