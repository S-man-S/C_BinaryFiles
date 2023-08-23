GCC = gcc -Wall -Wextra -Werror

all: state_sort state_search clear_state

clean:
	rm -rf ../build/*

rebuild: clean all

state_sort:
	$(GCC) -o ../build/Quest_1 state_sort.c

state_search:
	$(GCC) -o ../build/Quest_2 state_search.c

clear_state:
	$(GCC) -o ../build/Quest_3 clear_state.c