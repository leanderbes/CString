cstring : cstring.c
	$(CC) -o cstring cstring.c

install : cstring
	mkdir -p $(DESTDIR)/usr/bin/
	cp -f cstring $(DESTDIR)/usr/bin/
	mkdir -p $(DESTDIR)/usr/local/man/man1/
	cp -f cstring.1 $(DESTDIR)/usr/local/man/man1/cstring.1

uninstall :
	$(RM) $(DESTDIR)/usr/bin/cstring
	$(RM) $(DESTDIR)/usr/local/man/man1/cstring.1
