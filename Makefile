# https://en.wikipedia.org/wiki/Makefile

CXX           	:= g++
SRCDIR 			:= .
OBJDIR			:= ./out
EXECUTABLE    	:= renderer
# CXXFLAGS      	:= -std=c++17 -DGOURAUD_SHADER -O2 #-pg -g
CXXFLAGS      	:= -std=c++17 -DPHONG_SHADER -O2 #-pg -g
SRCFILES	 	:= $(shell find $(SRCDIR) -name "*.cpp")
SRCNAMES		:= $(notdir $(SRCFILES))
OBJFILES 	    := $(SRCNAMES:%.cpp=$(OBJDIR)/%.o)
LDFLAGS       	:= -lX11 -lXi -lSDL2
space 			:=
VPATH 			:= $(subst $(space),:,$(shell find . -type d))

########################
######### MAIN #########
########################

.PHONY: all
all: out/$(EXECUTABLE)

out/$(EXECUTABLE): $(OBJFILES)
	@$(CXX) $(CXXFLAGS) $(OBJFILES) -o $@ $(LDFLAGS) && echo "[OK] $@"

$(OBJDIR)/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c -g $< -o $@ $(LDFLAGS) && echo "[OK]  $@"

####### CLEAN #######
.PHONY: clean
clean:
	@rm -f out/* && echo "[CL]  out/"