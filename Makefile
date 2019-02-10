FILES=fbsh.c main.c bmp.c get_conf.c

all: $(FILES)
	gcc -Wall -g $(FILES) -o to_screen

commit:
	git add --all && git commit -m "Auto commit" && git push -f

edit:
	nano $(FILES) && make && ./fbsh.c

proba:
	dat=date && echo '$dat'
clean:
	rm to_screen
