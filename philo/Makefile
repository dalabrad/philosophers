NAME = philo

PHILO_LIB = inc/philosophers.a

SRCS = $(wildcard src/philo*.c)

MAIN = main.c

OBJS = $(SRCS:.c=.o)


CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m


$(NAME): $(OBJS) $(PHILO_LIB)
	@echo "$(YELLOW)Compiling ./philo executable...$(RESET)"
	$(CC)  $(CFLAGS) $(OBJS) $(MAIN) -o $(NAME) $(PHILO_LIB)
	@echo "$(GREEN)./philo executable created successfully.$(RESET)"

$(PHILO_LIB) : 
	@echo "$(YELLOW)Compiling philosophers.a library...$(RESET)"
	@ar rcs $(PHILO_LIB) $(OBJS)
	@echo "$(GREEN)philosophers.a created successfully.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Deleting all the object files...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)All the object files deleted succesfully.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Performing a full clean...$(RESET)"
	@$(RM) $(NAME) $(PHILO_LIB)
	@echo "$(GREEN)Everything deleted successfully.$(RESET)"

all:  fclean $(NAME)

re : fclean all	

.PHONY: all clean fclean re