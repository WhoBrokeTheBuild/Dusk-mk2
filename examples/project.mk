
CXX = clang++

include ../../make/config.mk

OUTDIR = build

SRC = $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
OUT = $(OUTDIR)/$(PROGRAM)

CPPFLAGS += $(DUSK_CPPFLAGS)
LDFLAGS  += $(DUSK_LDFLAGS)
LDLIBS   += $(DUSK_LDLIBS)

all: $(OUT)

clean:
	rm -f $(OBJ)

run:
	@export LD_LIBRARY_PATH=$(DUSK_OUTDIR); $(OUT)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	@mkdir -p $(dir $(DEPDIR)/$*.d) >/dev/null;
	$(MAKEDEPEND)
	@mkdir -p $(dir $@) >/dev/null;
	$(COMPILE)

$(OUT): $(OBJ)
	@mkdir -p $(dir $@) >/dev/null;
	$(LINK)
