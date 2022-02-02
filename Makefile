NAME = minishell

FLAGS = -Wall -Werror -Wextra -g

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = ./libs/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC = 	$(SRC_DIR)/minishell.c \
        $(SRC_DIR)/cmd_exec.c \
        $(SRC_DIR)/input_handling.c \
        $(SRC_DIR)/parser.c \
        $(SRC_DIR)/env_functions.c \
        $(SRC_DIR)/built_in_functions1.c \
        $(SRC_DIR)/built_in_functions2.c \
        $(SRC_DIR)/cd_function.c \
        $(SRC_DIR)/shlvl.c \
        $(SRC_DIR)/pipe.c \
        $(SRC_DIR)/token.c \
        $(SRC_DIR)/token_utils.c

OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

INC = -I $(INC_DIR)

READLINE_LIB = -lreadline -lhistory -L $$HOME/.brew/opt/readline/lib
READLINE_INC = -I $$HOME/.brew/opt/readline/include

COM_COLOR   = \033[0;33m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
PRG_COLOR	= \033[0;35m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(READLINE_LIB) 2> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        else  \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        cat $@.log; \
        rm -f $@.log; \
        exit $$RESULT
	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@gcc $(FLAGS) $(INC) $(READLINE_INC) -c -o $@ $< 2> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        else  \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        cat $@.log; \
        rm -f $@.log; \
        exit $$RESULT

$(LIBFT):
	@printf "$(COM_COLOR)$(COM_STRING) $(LIB_COLOR)$(@)$(NO_COLOR)\n";
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@printf "%b" "$(COM_COLOR)Cleaning $(LIB_COLOR)libft\n"
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@printf "%b" "$(ERROR_COLOR)Removing $(OBJ_COLOR)object files\n"
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@printf "%b" "$(ERROR_COLOR)Removing $(PRG_COLOR)minishell\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re