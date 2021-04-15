# https://en.wikipedia.org/wiki/Makefile

CXX           	:= g++
SRCDIR 			:= .
OBJDIR			:= ./out
EXECUTABLE    	:= renderer
EXECUTABLE_GCOV := gcov
CXXFLAGS      	:= -std=c++14
SRCFILES	 	:= $(shell find $(SRCDIR) -name "*.c")
SRCNAMES		:= $(notdir $(SRCFILES))
OBJFILES 	    := $(SRCNAMES:%.c=$(OBJDIR)/%.o)
LDFLAGS       	:= -lX11 -lXi -lSDL2
space :=
VPATH := $(subst $(space),:,$(shell find . -type d))

# MAIN

.PHONY: all
all: out/$(EXECUTABLE)

out/$(EXECUTABLE): $(OBJFILES)
	@$(CXX) $(OBJFILES) -o $@ $(LDFLAGS) && echo "[OK] $@"

$(OBJDIR)/%.o: %.c
	@$(CXX) -c -g $< -o $@ $(LDFLAGS) && echo "[OK]  $@"


# CLEAN
.PHONY: clean
clean:
	@rm -f out/* && echo "[CL]  out/"