
DUSK_MKPATH  := $(abspath $(lastword $(MAKEFILE_LIST)))
DUSK_BASEDIR := $(patsubst %/,%,$(dir $(patsubst %/,%,$(dir $(DUSK_MKPATH)))))

DUSK_OUTDIR = $(DUSK_BASEDIR)/build
DUSK_INCDIR = $(DUSK_BASEDIR)/include
DUSK_LIBDIR = $(DUSK_BASEDIR)/lib

DUSK_COMPILE    = $(CXX) -c $(CPPFLAGS) -o $@ $<
DUSK_LINK       = $(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
DUSK_MAKEDEPEND = $(CXX) $(CPPFLAGS) -MM -MP -MT $@ -o $(DEPDIR)/$*.d $<

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

ASIO_CPPFLAGS += -DASIO_STANDALONE
ASIO_LDFLAGS  +=
ASIO_LDLIBS   += -lpthread

DUSK_CPPFLAGS += $(ASIO_CPPFLAGS) $(LUA_CPPFLAGS) $(SFML_CPPFLAGS) -I$(DUSK_BASEDIR)/src
DUSK_LDFLAGS  += $(ASIO_LDFLAGS)  $(LUA_LDFLAGS)  $(SFML_LDFLAGS)  -L$(DUSK_OUTDIR)
DUSK_LDLIBS   += $(ASIO_LDLIBS)   $(LUA_LDLIBS)   $(SFML_LDLIBS)   -lDusk -lX11

CPPFLAGS += -g -std=c++11 -Wall -Wpedantic
