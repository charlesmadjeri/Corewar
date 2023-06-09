##
## EPITECH PROJECT, 2023
## my_rpg
## File description:
## Makefile
##

SRC_NO_MAIN = 								\
	../op.c 								\
	binary_argv_load_single_binary.c		\
	binary_file.c							\
	binary_load_all.c 						\
	champion_duplicate_remove.c				\
	dump_memory.c							\
	index_apply_to_pc.c 					\
	parse_argv.c							\
	parse_instruction.c						\
	prog_number.c 							\
	scheduler.c								\
	vm_init.c								\
	mnemonics/check_args.c					\
	mnemonics/get_arg.c						\
	mnemonics/get_indirect_address_value.c	\
	mnemonics/live.c						\
	mnemonics/ld.c 							\
	mnemonics/st.c 							\
	mnemonics/add.c							\
	mnemonics/sub.c							\
	mnemonics/and.c							\
	mnemonics/or.c							\
	mnemonics/xor.c							\
	mnemonics/zjmp.c						\
	mnemonics/ldi.c							\
	mnemonics/sti.c							\
	mnemonics/fork.c						\
	mnemonics/lld.c							\
	mnemonics/lldi.c						\
	mnemonics/lfork.c						\
	mnemonics/aff.c

SRC	=	$(SRC_NO_MAIN) main.c

OBJ =   $(SRC:.c=.o)

CC  =   gcc
DEBUG   =   -g3 -p -ggdb3 -DDEBUG_MODE

# To prevent Marvin from flagging my code due to optimizations
RELEASE = -O0 -fno-builtin
SANITIZE	=	-fsanitize=address,undefined \
-fsanitize-recover=address,undefined
ANALYZER	=

LIB_DIR	=	../lib/
CFLAGS  +=  -Wall -Wextra -pedantic -fsigned-char       \
-funsigned-bitfields -Wno-unused-parameter -std=gnu2x
LDFLAGS	+=	-L $(LIB_DIR) -lmy
LD_PRELOAD	=

NAME    =   corewar

.PHONY: all re
all: CFLAGS += $(RELEASE)
all: $(NAME)
re: fclean all

.PHONY: debug redebug
debug: CFLAGS += $(DEBUG)
debug: $(NAME)
redebug: fclean debug

.PHONY: sanitize resanitize
sanitize: CFLAGS += $(DEBUG) $(SANITIZE)
sanitize: LD_PRELOAD += -lasan -lubsan
sanitize: $(NAME)
resanitize: fclean sanitize

.PHONY: analyzer reanalyzer
analyzer: ANALYZER += on
analyzer: CFLAGS += $(DEBUG) -fanalyzer
analyzer: $(NAME)
reanalyzer: fclean analyzer

.PHONY: clean_tests
clean_tests:
	@echo [COREWAR] Removing criterion temporary files.
	@rm -f *.gcda
	@rm -f *.gcno

.PHONY: tests
tests: clean_tests
	@if [[ "$(shell find ../tests/corewar -type f -name '*.c')" == "" ]];	\
		then																\
		echo "[COREWAR] No .c file in /tests/corewar directory.";			\
	else																	\
		echo [COREWAR] Building tests;										\
		gcc -g3 $(SRC_NO_MAIN) ../tests/$(NAME)/*.c --coverage -lcriterion \
			-DRUNNING_CRITERION_TESTS $(CFLAGS) $(LDFLAGS) -o $(NAME);		\
	fi

.PHONY: tests_run
tests_run: clean_tests tests
	@echo "[COREWAR] Running tests :"
	@./$(NAME)
	@echo "[COREWAR] Writing line coverage log in corewar/line_coverage.log."
	@gcovr --exclude ../tests/ > line_coverage.log
	@echo -n "[COREWAR] Writing branch coverage log in "
	@echo "corewar/branch_coverage.log."
	@gcovr --exclude ../tests/ --branches > branch_coverage.log

$(NAME): $(OBJ)
	@echo -------------
	@echo -n "[COREWAR] CC : "
	@$(CC) --version | head -n 1
	@echo [COREWAR] CFLAGS : $(CFLAGS)
	@echo [COREWAR] LDFLAGS : $(LD_PRELOAD) $(LDFLAGS)
	@gcc $(OBJ) $(LD_PRELOAD) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@if [[ "$(ANALYZER)" != "" ]]; then\
		$(CC) -c $(CFLAGS) $< -o $@ 2>> ../analyzer_corewar.log;\
	else\
		$(CC) -c $(CFLAGS) $< -o $@;\
	fi

.PHONY: clean_vgcore
clean_vgcore:
	@echo [COREWAR] Removing Core Dumped files.
	@rm -f vgcore.*
	@rm -f valgrind*.log.core.*

.PHONY: clean
clean: clean_vgcore clean_tests
	@echo [COREWAR] Removing temporary and object files.
	@rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	@echo [COREWAR] Removing binary.
	@rm -f $(NAME)
