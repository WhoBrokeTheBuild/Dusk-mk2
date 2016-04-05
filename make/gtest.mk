
GTEST_DIR = $(DUSK_THRDPTY_DIR)googletest/
GTEST_OUT = $(GTEST_DIR)libgtest.a

GTEST_CPPFLAGS += -I $(GTEST_DIR)include
GTEST_LDFLAGS  += -L $(GTEST_DIR)
GTEST_LDLIBS   += -l pthread -l gtest

gtest: $(GTEST_OUT)

$(GTEST_OUT):
	cd $(GTEST_DIR)make; make gtest.a
	mv $(GTEST_DIR)make/gtest.a $@
