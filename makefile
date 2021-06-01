BDIR = build
SDIR = src

EXECUTABLE = $(BDIR)/application
SOURCES = $(wildcard $(SDIR)/*.cpp)
DEPENDENCIES = $(wildcard $(SDIR)/*.hpp) \

_OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst $(SDIR)/%,$(BDIR)/%,$(_OBJECTS))

CXX = g++
CXXFLAGS += -std=c++14

ifeq ($(DEBUG), 1)
	CXXFLAGS += -O0 -g3
else
	CXXFLAGS += -O2 -g0
endif

$(BDIR)/%.o : $(SDIR)/%.cpp $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

.PHONY : cleanobj clean

cleanobj :
	rm $(OBJECTS)

clean : cleanobj
	rm $(EXECUTABLE)
