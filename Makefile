CXX := g++ # This is the main compiler

SRCDIR := src
BUILDDIR := build
TARGET := client server

SRCEXT := cpp
# Get all files with SRCEXT a folder inside src  i.e src/*/*.cpp
SOURCES := $(shell find $(SRCDIR)/*/ -type f -name *.$(SRCEXT))
# Convert all the SOURCES to OBJECTS with root dir build and extension .o
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
# Optimization ON and show all warnings
CFLAGS := -O2 -Wall
# LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
RM = /bin/rm -f

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CXX) $(CFLAGS) src/client.cpp $^ -o client $(LIB);
	$(CXX) $(CFLAGS) src/server.cpp $^ -o server $(LIB);
	# @echo " $(CXX) $^ -o $(TARGET) $(LIB)"; $(CXX) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " $(CXX) $(CFLAGS) -c -o $@ $<"; $(CXX) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
