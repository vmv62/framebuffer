FILES=to_screen.c

all: $(FILES)
	gcc $(FILES) -o to_screen

commit:
	git add --all && git commit -m "auto commit" && git push -f

edit_amd_run:
	nano $(FILES) && make && ./to_screen
