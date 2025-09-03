NAME			=	philo
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
HEADERS			=	include/philo.h

# Directories
SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	include

# Source files (all inside src/)
SRC_FILES	=	philo_eat.c \
				init.c \
				routine.c \
				threads.c \
				time.c \
				utils.c \
				main.c \
				one_philo.c \
				forks.c \
				monitor.c

# Add src/ path
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files (keep obj/ structure clean)
OBJS		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Colors for output
GREEN	= \033[1;32m
CYAN	= \033[1;36m
YELLOW	= \033[1;33m
RED		= \033[1;31m
BLUE	= \033[1;34m
MAGENTA	= \033[1;35m
RESET	= \033[0m

# Progress tracking
TOTAL_FILES := $(words $(SRC_FILES))
COMPILED_FILES = 0

define update_progress
	$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES) + 1))))
	@printf "$(CYAN)[%2d/%d]$(RESET) Compiling $(notdir $<)...\n" $(COMPILED_FILES) $(TOTAL_FILES)
endef

define check_error
	@if [ $$? -ne 0 ]; then \
		echo "$(RED)[PHILO] ❌ Build failed!$(RESET)"; \
		exit 1; \
	fi
endef

# Main targets
all:
	@echo "$(GREEN)╔══════════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║                 PHILO BUILD                  ║$(RESET)"
	@echo "$(GREEN)╚══════════════════════════════════════════════╝$(RESET)"
	@$(MAKE) --no-print-directory $(NAME) || { echo "$(RED)[PHILO] ❌ Build failed$(RESET)"; exit 1; }

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Linking executable...$(RESET)"
	@$(CC) $(OBJS) $(CFLAGS) -lpthread -o $(NAME)
	$(call check_error)
	@echo "$(GREEN)✅ Build complete! Executable: $(NAME)$(RESET)"
	@echo "$(GREEN)╔══════════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║                 BUILD SUCCESS                ║$(RESET)"
	@echo "$(GREEN)╚══════════════════════════════════════════════╝$(RESET)"

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(call update_progress)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call check_error)

# Utility targets
clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)🗑️  Removing executable...$(RESET)"
	@$(RM) $(NAME)

re:
	@echo "$(CYAN)♻️  Rebuilding everything...$(RESET)"
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

# Debug target
debug: CFLAGS += -DDEBUG -g3
debug: $(NAME)

info:
	@echo "$(CYAN)Project Information:$(RESET)"
	@echo "	Name: $(NAME)"
	@echo "	Source files: $(words $(SRC_FILES))"
	@echo "	Compiler: $(CC)"
	@echo "	Flags: $(CFLAGS)"

help:
	@echo "$(GREEN)Available targets:$(RESET)"
	@echo "	all     - Build the project"
	@echo "	clean   - Remove object files"
	@echo "	fclean  - Remove object files and executable"
	@echo "	re      - Rebuild everything"
	@echo "	debug   - Build with debug flags"
	@echo "	info    - Show project information"
	@echo "	help    - Show this help"

.PHONY: all clean fclean re debug info help
