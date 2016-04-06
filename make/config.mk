
MKPATH   := $(abspath $(lastword $(MAKEFILE_LIST)))
DUSK_DIR := $(dir $(patsubst %/,%,$(dir $(MKPATH))))

CXX = clang++

DUSK_OUT_DIR     = $(DUSK_DIR)build/
DUSK_INC_DIR     = $(DUSK_DIR)include/
DUSK_LIB_DIR     = $(DUSK_DIR)lib/
DUSK_THRDPTY_DIR = $(DUSK_DIR)thirdparty/

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

DUSK_CPPFLAGS += $(ASIO_CPPFLAGS) $(LUA_CPPFLAGS) $(SFML_CPPFLAGS) -I $(DUSK_DIR)src
DUSK_LDFLAGS  += $(ASIO_LDFLAGS)  $(LUA_LDFLAGS)  $(SFML_LDFLAGS)  -L $(DUSK_OUT_DIR)
DUSK_LDLIBS   += $(ASIO_LDLIBS)   $(LUA_LDLIBS)   $(SFML_LDLIBS)   -l Dusk -l X11

CPPFLAGS += -g -std=c++11 -Wall -Wpedantic
