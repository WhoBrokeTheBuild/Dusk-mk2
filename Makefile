.PHONY: all clean includes

include make/config.mk

OUT_DIR = $(DUSK_OUT_DIR)
SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ = $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC))
OUT = $(OUT_DIR)libDusk.so

CPPFLAGS += $(SFML_CPPFLAGS) $(LUA_CPPFLAGS) $(ASIO_CPPFLAGS) -I $(DUSK_INC_DIR) -I $(SRC_DIR)
LDFLAGS  += $(SFML_LDFLAGS)  $(LUA_LDFLAGS)  $(ASIO_LDFLAGS)  -L $(DUSK_LIB_DIR)
LDLIBS   += $(SFML_LDLIBS)   $(LUA_LDLIBS)   $(ASIO_LDLIBS) -l X11

all: $(OUT) includes

clean:
	rm -f $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@) >/dev/null
	$(CXX) -c $(CPPFLAGS) -o $@ $<

$(OUT): CPPFLAGS += -fPIC
$(OUT): $(OBJ)
	@mkdir -p $(dir $@) >/dev/null
	$(CXX) $(LDFLAGS) -o $@ -shared $^ $(LDLIBS)

# Includes

includes:
	$(info Copying Includes)
	@mkdir -p $(OUT_DIR)include
	@-cp -rf include/* $(OUT_DIR)include
	@cd $(SRC_DIR); find -type f -name '*.hpp' | cpio -updm ../$(OUT_DIR)include

# Testing

include make/gtest.mk

TEST_DIR = tests/
TEST_SRC = $(wildcard $(TEST_DIR)*.cpp)
TEST_OUT = $(OUT_DIR)Test

$(TEST_OUT): $(OBJS) $(TEST_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(TEST_OUT) $(TEST_SRC) $(OBJ) $(LDLIBS)

test: CPPFLAGS += $(GTEST_CPPFLAGS) -I $(SRC_DIR)
test: LDFLAGS  += $(GTEST_LDFLAGS)
test: LDLIBS   += $(GTEST_LDLIBS)
test: gtest $(TEST_OUT)
	$(TEST_OUT)
