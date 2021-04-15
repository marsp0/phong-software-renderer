# https://en.wikipedia.org/wiki/Makefile

CXX         	:= gcc
SRCDIR 			:= .
OBJDIR			:= ./out
EXECUTABLE    	:= renderer
leak		 	:= 
FLAGS.leak 		:= -fsanitize=address
CXXFLAGS      	:= -std=c11 ${FLAGS.${leak}} 
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
	@$(CXX) $(OBJFILES) -o $@ $(LDFLAGS) $(CXXFLAGS) && echo "[OK] $@"

$(OBJDIR)/%.o: %.c
	@$(CXX) -c -g $< -o $@ $(LDFLAGS) $(CXXFLAGS) && echo "[OK]  $@"


# CLEAN
.PHONY: clean
clean:
	@rm -f out/* && echo "[CL]  out/"