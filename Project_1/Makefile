# Makefile for hello pass

# Path to top level of LLVM hierarchy
LEVEL = ../../../

# Name of the library to build
LIBRARYNAME = Semantic_Analysis


# Make the shared library become a loadable module so the tools can
# dlopen/dlsym on the resulting library.
LOADABLE_MODULE = 1

# Might need to change this to .so in LINUX
LIB_EXT = .so

#TEST_PRINT = $(LEVEL)/../bin/opt -load $(LEVEL)/../lib/$(LIBRARYNAME)$(LIB_EXT) -proj1 <
#TEST_PRINT2 = $(LEVEL)/../bin/opt -load $(LEVEL)/../lib/$(LIBRARYNAME2)$(LIB_EXT) -proj1b <

# Include the makefile implementation stuff
include $(LEVEL)/Makefile.common

#testPrint:
#	$(TEST_PRINT) ../tests/linked.bc > /dev/null
#testPrint2
#	$(TEST_PRINT2) ../tests/test_no.bc > /dev/null

