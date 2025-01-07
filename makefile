# Defines the compiler
CC = gcc

# Defines compiler's flags
CFLAGS = -lm

# Defines the target executable
TARGET = C_BaseWizard

# Lists the source files
SRCS = main.c baseconverter.c basecalculator.c utility.c basesortingtool.c

# Default target
all: $(TARGET)

# Rule to compile all source files into the final executable
$(TARGET):
	$(CC)	$(SRCS) -o $(TARGET)	$(CFLAGS) 

# Rule to clean the build directory
clean:
	rm -f $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY:
	all clean run