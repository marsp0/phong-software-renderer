# https://en.wikipedia.org/wiki/Makefile

CXX           	:= g++
SRCDIR 			:= .
OBJDIR			:= ./out
EXECUTABLE    	:= renderer
EXECUTABLE_GCOV := gcov
CXXFLAGS      	:= -std=c++14
SRCFILES	 	:= $(shell find $(SRCDIR) -name "*.cpp")
SRCNAMES		:= $(notdir $(SRCFILES))
OBJFILES 	    := $(SRCNAMES:%.cpp=$(OBJDIR)/%.o)
LDFLAGS       	:= -lX11 -lXi -lSDL2
space :=
VPATH := $(subst $(space),:,$(shell find . -type d))

# MAIN

.PHONY: all
all: out/$(EXECUTABLE)

out/$(EXECUTABLE): $(OBJFILES)
	@$(CXX) $(CXXFLAGS) $(OBJFILES) -o $@ $(LDFLAGS) && echo "[OK] $@"

$(OBJDIR)/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c -g $< -o $@ $(LDFLAGS) && echo "[OK]  $@"

# # TEST

# TESTDIR			:= ./test
# TESTEXECUTABLE  := test
# TESTFILES		:= $(shell find $(SRCDIR) -name "*.cpp") $(shell find $(TESTDIR) -name "*.cpp")
# TESTNAMES      	:= $(notdir $(TESTFILES))
# TESTOBJFILES	:= $(filter-out ./out/main.o, $(TESTNAMES:%.cpp=$(OBJDIR)/%.o))

# .PHONY: test
# test: out/$(TESTEXECUTABLE)

# out/$(TESTEXECUTABLE): $(TESTOBJFILES)
# 	@$(CXX) $(CXXFLAGS) $(TESTOBJFILES) -o $@ $(LDFLAGS) && echo "[OK] $@"


# # GCOV

# GCOVEXECUTABLE := gcov_exe

# .PHONY: gcov
# gcov: out/$(GCOVEXECUTABLE)
# gcov: CXXFLAGS += --coverage

# out/$(GCOVEXECUTABLE): $(TESTOBJFILES)
# 	@$(CXX) $(CXXFLAGS) $(TESTOBJFILES) -o $@ $(LDFLAGS) && echo "[OK] $@"

# CLEAN


.PHONY: clean
clean:
	@rm -f out/* && echo "[CL]  out/"