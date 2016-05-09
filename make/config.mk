
MKPATH   := $(abspath $(lastword $(MAKEFILE_LIST)))
DUSK_BASEDIR := $(patsubst %/,%,$(dir $(patsubst %/,%,$(dir $(MKPATH)))))

CXX = clang++

DUSK_OUTDIR = $(DUSK_BASEDIR)/build
DUSK_INCDIR = $(DUSK_BASEDIR)/include
DUSK_LIBDIR = $(DUSK_BASEDIR)/lib

OUTDIR = $(DUSK_OUTDIR)
SRCDIR = src
OBJDIR = obj
DEPDIR = .dep

COMPILE    = $(CXX) -c $(CPPFLAGS) -o $@ $<
LINK       = $(CXX) $(LDFLAGS) -o $@ -shared $^ $(LDLIBS)
MAKEDEPEND = $(CXX) $(CPPFLAGS) -MM -MP -MT $@ -o $(DEPDIR)/$*.d $<

LUA_CPPFLAGS += $(shell pkg-config --silence-errors --cflags      lua) \
				$(shell pkg-config --silence-errors --cflags      lua5.2)
LUA_LDFLAGS  += $(shell pkg-config --silence-errors --libs-only-L lua) \
 				$(shell pkg-config --silence-errors --libs-only-L lua5.2)
LUA_LDLIBS   += $(shell pkg-config --silence-errors --libs-only-l lua) \
 				$(shell pkg-config --silence-errors --libs-only-l lua5.2)

SFML_MODS = sfml-graphics sfml-audio sfml-system sfml-window
SFML_CPPFLAGS += $(shell pkg-config --silence-errors --cflags      $(SFML_MODS))
SFML_LDFLAGS  += $(shell pkg-config --silence-errors --libs-only-L $(SFML_MODS))
SFML_LDLIBS   += $(shell pkg-config --silence-errors --libs-only-l $(SFML_MODS))

ASIO_CPPFLAGS += -D ASIO_STANDALONE
ASIO_LDFLAGS  +=
ASIO_LDLIBS   += -l pthread

DUSK_CPPFLAGS += $(ASIO_CPPFLAGS) $(LUA_CPPFLAGS) $(SFML_CPPFLAGS) -I $(DUSK_BASEDIR)src
DUSK_LDFLAGS  += $(ASIO_LDFLAGS)  $(LUA_LDFLAGS)  $(SFML_LDFLAGS)  -L $(DUSK_OUTDIR)
DUSK_LDLIBS   += $(ASIO_LDLIBS)   $(LUA_LDLIBS)   $(SFML_LDLIBS)   -l Dusk -l X11

CPPFLAGS += -g -std=c++11 -Wall -Wpedantic
