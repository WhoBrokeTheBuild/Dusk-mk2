
MKPATH   := $(abspath $(lastword $(MAKEFILE_LIST)))
DUSK_DIR := $(dir $(patsubst %/,%,$(dir $(MKPATH))))

CXX = clang++

DUSK_OUT_DIR     = $(DUSK_DIR)build/
DUSK_INC_DIR     = $(DUSK_DIR)include/
DUSK_LIB_DIR     = $(DUSK_DIR)lib/
DUSK_THRDPTY_DIR = $(DUSK_DIR)thirdparty/

LUA_CPPFLAGS += $(shell pkg-config --silence-errors --cflags lua) \
				$(shell pkg-config --silence-errors --cflags lua5.2)
LUA_LDFLAGS  += $(shell pkg-config --silence-errors --libs-only-L lua) \
 				$(shell pkg-config --silence-errors --libs-only-L lua5.2)
LUA_LDLIBS   += $(shell pkg-config --silence-errors --libs-only-l lua) \
 				$(shell pkg-config --silence-errors --libs-only-l lua5.2)

ASIO_CPPFLAGS +=
ASIO_LDFLAGS  +=
ASIO_LDLIBS   += -l pthread

DUSK_CPPFLAGS += $(ASIO_CPPFLAGS) $(LUA_CPPFLAGS) -I $(DUSK_DIR)src
DUSK_LDFLAGS  += $(ASIO_LDFLAGS)  $(LUA_LDFLAGS)  -L $(DUSK_OUT_DIR)
DUSK_LDLIBS   += $(ASIO_LDLIBS)   $(LUA_LDLIBS)   -l Dusk

CPPFLAGS += -std=c++11 -Wall -Wpedantic
