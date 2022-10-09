CC      = cc
CFLAGS  = -Isrc/ -std=c99 -Wall -Wextra -Wpedantic
LDFLAGS =
PREFIX  ?= /usr/local

client = game
client_cflags  = $(CFLAGS)
client_ldflags = $(LDFLAGS) -lraylib -lm
server = game-server
server_cflags  = $(CFLAGS)
server_ldflags = $(LDFLAGS)
version = 0.1
