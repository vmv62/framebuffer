FILES=to_screen.c

all: $(FILES)
	gcc $(FILES) -o to_screen

commit:
	git add --all && git commit -m "auto commit" && git push -f

