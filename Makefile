include config.mk

client_sources = $(wildcard src/client/*.c)
client_headers = $(wildcard src/client/*.h)
client_objects = $(client_sources:.c=.o)
server_sources = $(wildcard src/server/*.c)
server_headers = $(wildcard src/server/*.h)
server_objects = $(server_sources:.c=.o)
common_sources = $(wildcard src/*.c)
common_headers = $(wildcard src/*.h)
common_objects = $(common_sources:.c=.o)

all: $(client) $(server)

clean:
	rm -f $(client) $(server) \
		$(client_objects) \
		$(server_objects) \
		$(common_objects)

debug: CFLAGS  += -g -O0 -DDEBUG
debug: LDFLAGS +=
debug: version := $(version)+debug
debug: all

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(client) $(server) $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/$(client) \
		$(DESTDIR)$(PREFIX)/bin/$(server)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(client) \
		$(DESTDIR)$(PREFIX)/bin/$(server)

$(client): $(client_objects) $(common_objects)
	$(CC) -o $@ $(client_objects) $(common_objects) $(client_ldflags)

$(server): $(server_objects) $(common_objects)
	$(CC) -o $@ $(server_objects) $(common_objects) $(server_ldflags)

src/client/%.o: src/client/%.c $(client_headers) $(common_headers)
	$(CC) -o $@ -c $(client_cflags) \
		-DPROGRAM_NAME=\"$(client)\" \
		-DPROGRAM_VERSION=\"$(version)\" $<

src/server/%.o: src/server/%.c $(server_headers) $(common_headers)
	$(CC) -o $@ -c $(server_cflags) \
		-DPROGRAM_NAME=\"$(server)\" \
		-DPROGRAM_VERSION=\"$(version)\" $<

src/%.o: src/%.c $(common_headers)
	$(CC) -o $@ -c $(CFLAGS) $<

.PHONY: all clean debug install uninstall
