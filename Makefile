build:
	gcc mpdaddtoplaylist.c -o mpdaddtoplaylist -lmpdclient

clean:
	rm mpdaddtoplaylist

install: build
	cp mpdaddtoplaylist ~/.config/polybar/scripts/
