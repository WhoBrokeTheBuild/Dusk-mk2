.PHONY: all clean includes

include make/config.mk

CXX = clang++

OUTDIR = $(DUSK_OUTDIR)
SRCDIR = src
OBJDIR = obj
DEPDIR = .dep

SRC = $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
OUT = $(OUTDIR)/libDusk.so

CPPFLAGS += $(SFML_CPPFLAGS) $(LUA_CPPFLAGS) $(ASIO_CPPFLAGS) -I$(DUSK_INCDIR) -I$(SRCDIR)
LDFLAGS  += $(SFML_LDFLAGS)  $(LUA_LDFLAGS)  $(ASIO_LDFLAGS)  -L$(DUSK_LIBDIR)
LDLIBS   += $(SFML_LDLIBS)   $(LUA_LDLIBS)   $(ASIO_LDLIBS) -lX11

all: $(OUT) includes

clean:
	rm -f $(OBJ)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	@mkdir -p $(dir $(DEPDIR)/$*.d) >/dev/null;
	$(DUSK_MAKEDEPEND)
	@mkdir -p $(dir $@) >/dev/null;
	$(DUSK_COMPILE)

$(OUT): CPPFLAGS += -fPIC
$(OUT): LDFLAGS += -shared
$(OUT): $(OBJ)
	@mkdir -p $(dir $@) >/dev/null;
	$(DUSK_LINK)

# Includes

includes:
	$(info Copying Includes)
	@mkdir -p $(OUTDIR)/include
	@-cp -rf include/* $(OUTDIR)/include
	cd $(SRCDIR); find -type f -name '*.hpp' -exec cp {} $(OUTDIR)/include \;
	cd $(DUSK_INCDIR); find -type f -name '*.hpp' -exec cp {} $(OUTDIR)/include \;

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(SRC:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
