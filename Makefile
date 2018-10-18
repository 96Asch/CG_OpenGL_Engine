CXX = g++
CFLAGS =	-std=c++14 -Wall -g -Wextra -pedantic
OBJDIR = build
FILES = $(wildcard $(SRC)/*/) $(wildcard $(SRC)/*/*/) dep/
OBJDIRS = $(sort $(dir $(addprefix $(OBJDIR)/, $(FILES:$(SRC)/%=%))))
SOURCES = $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*/*.cpp) $(wildcard $(SRC)/*/*/*.cpp)
OBJS =	$(addprefix $(OBJDIR)/, $(patsubst $(SRC)/%.cpp, %.o, $(SOURCES)))
SRC = src
INC = -Iinclude/ -I$(SRC)/global/
DEP = $(wildcard dep/*.c)
DEPOBJS = $(addprefix $(OBJDIR)/, $(DEP:.c=.o))
LDFLAGS = -lGL -lglfw -lGLU -lpng -ldl
TARGET =	main


.PHONY: all clean

all: $(OBJDIR) $(TARGET)
	@echo Done Building...

test:
	@echo $(OBJDIRS)

$(OBJDIR):
	@echo Making bin directory
	@mkdir $(OBJDIRS)

$(DEPOBJS): $(DEP)
	@echo Building Dependency $@
	@$(CXX) -c $(INC) $< -o $@ $(LDFLAGS)

$(OBJDIR)/%.o:	$(SRC)/%.cpp
	@echo Building $@
	@$(CXX) $(CFLAGS) -c $(INC) $< -o $@ $(LDFLAGS)


$(TARGET):	$(DEPOBJS) $(OBJS)
	@echo Building executable $@
	@$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run:
	@./$(TARGET)

clean:
	@echo Cleaning $(OBJDIR) $(TARGET) $(wildcard *.o)...
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJDIR)
	@echo Done Cleaning...
