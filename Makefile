CXX = g++
CFLAGS =	-std=c++14 -Wall -g -Wextra
OBJDIR = build
FILES = $(wildcard $(SRC)/*/) $(wildcard $(SRC)/*/*/) dep/
OBJDIRS = $(sort $(dir $(addprefix $(OBJDIR)/, $(FILES:$(SRC)/%=%))))
SOURCES = $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*/*.cpp) $(wildcard $(SRC)/*/*/*.cpp)
OBJS =	$(addprefix $(OBJDIR)/, $(patsubst $(SRC)/%.cpp, %.o, $(SOURCES)))
SRC = src
INC = -Iinclude/ -I$(SRC)/global/ -Ideps/glfw/include
STATIC = -lglfw
DEP = $(wildcard dep/*.c)
DEPOBJS = $(addprefix $(OBJDIR)/, $(DEP:.c=.o))
LDFLAGS = -lGL -ldl
PRECOMPILE = include/Global.h include/Uniforms.h include/Components.h \
  					 include/Systems.h
PRECOMPILED = $(PRECOMPILE:.h=.h.gch)
TARGET =	main


.PHONY: all clean

all: $(OBJDIR) $(PRECOMPILED) $(TARGET)
	@echo Done Building...

test:
	@echo $(PRECOMPILED)

$(OBJDIR):
	@echo Making bin directory
	@mkdir $(OBJDIRS)

$(PRECOMPILED):
	@echo Precompiling $(PRECOMPILE)
	@$(CXX) $(CFLAGS) $(PRECOMPILE) $(INC)

$(DEPOBJS): $(DEP)
	@echo Building Dependency $@
	@$(CXX) -c $(INC) $< -o $@ $(LDFLAGS)

$(OBJDIR)/%.o:	$(SRC)/%.cpp
	@echo Building $@
	@$(CXX) $(CFLAGS) -c $(INC) $< -o $@ $(LDFLAGS)


$(TARGET):	$(DEPOBJS) $(OBJS)
	@echo Building executable $@
	@$(CXX) $(CFLAGS) -o $@ $^ $(STATIC) $(LDFLAGS)

run:
	@./$(TARGET)

clp:
	@echo Cleaning precompiled headers: $(PRECOMPILED)
	@rm -f $(PRECOMPILED)

clean:
	@echo Cleaning $(OBJDIR) $(PRECOMPILED) $(TARGET) $(wildcard *.o)...
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -f $(PRECOMPILED)
	@rm -rf $(OBJDIR)
	@echo Done Cleaning...
