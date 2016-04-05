
CXX = clang++

include ../../make/config.mk

OUT_DIR = build/
SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ = $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC))
OUT = $(OUT_DIR)$(PROGRAM)

CPPFLAGS += $(DUSK_CPPFLAGS)
LDFLAGS  += $(DUSK_LDFLAGS)
LDLIBS   += $(DUSK_LDLIBS)

all: $(OUT)

clean:
	rm -f $(OBJ)

run:
	@export LD_LIBRARY_PATH=$(DUSK_OUT_DIR); $(OUT)

$(OUT): $(OBJ)
	@mkdir -p $(dir $@) >/dev/null
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@) >/dev/null
	$(CXX) -c -fPIC $(CPPFLAGS) -o $@ $<

include ../../make/gtest.mk

TEST_DIR = tests/
TEST_SRC = $(wildcard $(TEST_DIR)*.cpp)
TEST_OUT = $(OUT_DIR)Test

$(TEST_OUT): $(OBJS) $(TEST_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(TEST_OUT) $(TEST_SRC) \
		$(filter-out $(OBJ_DIR)Main.o,$(OBJ)) $(LDLIBS)

test: CPPFLAGS += $(GTEST_CPPFLAGS) -I $(SRC_DIR)
test: LDFLAGS  += $(GTEST_LDFLAGS)
test: LDLIBS   += $(GTEST_LDLIBS)
test: gtest $(TEST_OUT)
	@export LD_LIBRARY_PATH=$(DUSK_OUT_DIR); $(TEST_OUT)
