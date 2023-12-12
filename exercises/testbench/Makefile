# header files
HEADERS := ./src/fir.h ./src/tb.h

# source files
SOURCES := ./src/main.cpp ./src/fir.cpp ./src/tb.cpp

# all dependencies
DEPENDENCIES := \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

# libraries
LIBRARIES := \
	-lsystemc \
	-lm

# outputs
OUTPUT := output.o

# flags
FLAGS := \
	-std=c++11 \
	-g \
	-o $(OUTPUT)

all: $(OUTPUT)
	./$(OUTPUT)
	@make cmp_results
	
$(OUTPUT): $(DEPENDENCIES)
	g++ $(FLAGS) -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib  $(SOURCES) $(HEADERS) $(LIBRARIES)

clean:
	rm -f $(OUTPUT) output.txt report.log trace.vcd

# results comparison
GOLD := ./golden_reference.txt
cmp_results:
	@echo "*************************************************"
	@if diff -w $(GOLD) ./output.txt; then \
		echo "SIMULATION PASSED"; \
	else \
		echo "SIMULATION FAILED"; \
	fi
	@echo "*************************************************"


