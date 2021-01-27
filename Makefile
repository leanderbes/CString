cstring : cstring.c
	$(CC) -o cstring cstring.c

install : cstring
	mkdir -p $(DESTDIR)/usr/bin/
	cp -f cstring $(DESTDIR)/usr/bin/

uninstall :
	$(RM) $(DESTDIR)/usr/bin/cstring
