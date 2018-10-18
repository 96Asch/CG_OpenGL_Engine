CXX = g++
CFLAGS =	-std=c++14 -Wall -g -Wextra -pedantic
OBJDIR = build
FILES = $(wildcard $(SRC)/*/)
OBJDIRS = $(sort $(dir $(addprefix $(OBJDIR)/, $(FILES:$(SRC)/%=%))))
SOURCES = $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*/*.cpp)
OBJS =	$(addprefix $(OBJDIR)/, $(patsubst $(SRC)/%.cpp, %.o, $(SOURCES)))
INC = include
SRC = src
LDFLAGS = -lGL -lglfw -lSDL -lpng -lz
TARGET =	main
DEPS = $(wildcard $(INC)/*.h)


.PHONY: all clean

all: $(OBJDIR) $(TARGET)
	@echo Done Building...

$(OBJDIR):
	@echo Making bin directory
	@mkdir $(OBJDIRS)

$(OBJDIR)/%.o:	$(SRC)/%.cpp
	@echo Building $@
	@$(CXX) $(CFLAGS) -c -I$(INC) $< -o $@ $(LDFLAGS)
	@echo Done Building $@


$(TARGET):	$(OBJS) $(DEPS)
	@echo Building executable $@
	@$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run:
	@./$(TARGET)

clean:
	@echo Cleaning $(OBJDIR) $(TARGET) $(wildcard *.o)...
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJDIR)
	@echo Done Cleaning...
