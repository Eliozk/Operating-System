# List of programs
PROGRAMS = Q1 Q2AndQ3 Q4 Q5 Q6

# Build all programs
all: $(PROGRAMS)

# Pattern rule for building each program
$(PROGRAMS):
	$(MAKE) -C $@ all

# Clean all programs
clean:
	@for dir in $(PROGRAMS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all clean $(PROGRAMS)