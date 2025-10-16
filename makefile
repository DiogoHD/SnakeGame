PROG = bin/exe        # The name of the program
CC = gcc              # Compilator

# Necessary Flags
FLAGS = -Wall -Wextra -g -Ilib    # -Ilib looks for headers in the lib/ directory; -Wall and -Wextra give warnings
LIBS = -lncursesw           # Necessay libraries

# Source files and objects
SRC = $(wildcard src/*.c)		# Looks for all the files .c
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))	# Creates .o files for each .c and puts it into the build/

all: $(PROG)			# Main Rule

# Link all .o files into the final executable
$(PROG): $(OBJ)
	@mkdir -p bin					# Creates bin/ directory if it doesn't exist
	$(CC) $(FLAGS) $(OBJ) -o $(PROG) $(LIBS)

# Compile each .c file into its corresponding .o
build/%.o: src/%.c
	@mkdir -p build                	# Create build/ if it doesn't exist
	$(CC) $(FLAGS) -c $< -o $@

# Clean rule (to delete objects and executable)
clean:
	rm -f build/*.o $(PROG)

# Run rule: compile and execute the program
run: all
	./$(PROG)