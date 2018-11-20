FILES=to_screen.c bmp.c

all: $(FILES)
	gcc $(FILES) -o to_screen

commit:
	git add --all && git commit -m "$date" && git push -f

edit:
	nano $(FILES) && make && ./to_screen
