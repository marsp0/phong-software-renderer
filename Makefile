# https://en.wikipedia.org/wiki/Makefile

SRCDIR 			:= .
OBJDIR			:= ./out
EXECUTABLE    	:= renderer
SRCFILES	 	:= $(shell find $(SRCDIR) -name "*.cpp")
SRCNAMES		:= $(notdir $(SRCFILES))
OBJFILES 	    := $(SRCNAMES:%.cpp=$(OBJDIR)/%.o)
LDFLAGS       	:= -lX11 -lXi -lSDL2
space 			:=
VPATH 			:= $(subst $(space),:,$(shell find . -type d))
GCCFLAGS      	:= -std=c++17

# select shader
ifeq ($(shader), gouraud)
	GCCFLAGS += -DGOURAUD_SHADER
else ifeq ($(shader), phong)
	GCCFLAGS += -DPHONG_SHADER
else
	GCCFLAGS += -DPHONG_SHADER
endif

# select reflection model
ifeq ($(reflection), phong)
	GCCFLAGS += -DPHONG_REFLECTION
else ifeq ($(reflection), blinn)
	GCCFLAGS += -DBLINN_REFLECTION
endif

# select release or debug
ifeq ($(config), debug)
	GCCFLAGS += -g -pg
else 
	GCCFLAGS += -O2
endif

.PHONY: all
all: out/$(EXECUTABLE)

out/$(EXECUTABLE): $(OBJFILES)
	g++ $(GCCFLAGS) $(OBJFILES) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	g++ $(GCCFLAGS) -c $< -o $@


.PHONY: clean
clean:
	@rm -f out/* && echo "[CL]  out/"