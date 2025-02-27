# ********************** Section for Macros (Variables) ********************** #
NAME			= RPN
SRC				= main.cpp RPN.cpp

OS				= $(shell uname)

SRCDIR			= ./src
INCDIR			= ./include
OBJDIR			= ./obj

CXX				= c++
RM				= rm

CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP
INCLUDES		= -I$(INCDIR)
RMFLAGS			= -rf
DEBUGCFLAGS		= -g -ggdb -ftrapv -fstack-protector-all -fsanitize=address,undefined -fno-omit-frame-pointer
DEBUGLDFLAGS	= -fsanitize=address,undefined

ifneq ($(filter debug test, $(MAKECMDGOALS)), )
	CXXFLAGS	+= $(DEBUGCFLAGS)
	LDFLAGS		+= $(DEBUGLDFLAGS)
	DEF			+= -D DEBUG_MODE=1
endif

SRCS			= $(addprefix $(SRCDIR)/, $(SRC))
OBJS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.d)))

# ********************* Section for targets and commands ********************* #
.PHONY: all clean fclean re debug

all: $(NAME)
clean:
	-$(RM) $(RMFLAGS) $(OBJDIR)
fclean: clean
	-$(RM) $(RMFLAGS) $(NAME)
re: fclean all

debug: fclean all
test: debug test_success test_fail

test_success:
	@echo "\n\033[32;1;3mRegular tests: \033[m"
	@echo "\n\033[33;42m[TEST1]\033[m"
	-./$(NAME) "2"
	@echo "\n\033[33;42m[TEST2]\033[m"
	-./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	@echo "\n\033[33;42m[TEST3]\033[m"
	-./$(NAME) "7 7 * 7 -"
	@echo "\n\033[33;42m[TEST4]\033[m"
	-./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	@echo "\n\033[33;42m[TEST5]\033[m"
	-./$(NAME) "3 5 + 2 *"
	@echo "\n\033[33;42m[TEST6]\033[m"
	-./$(NAME) "4 2 3 + * 6 -"
	@echo "\n\033[33;42m[TEST7]\033[m"
	-./$(NAME) "1 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 2 *"
	@echo "\n\033[33;42m[TEST8]\033[m"
	-./$(NAME) "1 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 2 * 1 + 1 2 - *"
	@echo "\033[2;3mRegular tests finished\033[m"
test_fail:
	@echo "\n\033[31;1;3mError handling tests\033[m"
	@echo "To continue, hit the [Enter] key"
	-@read _
	@echo "\033[41mError case: No arguments\033[m"
	-./$(NAME)
	@echo "\033[41mError case: Empty string\033[m"
	-./$(NAME) ""
	@echo "\033[41mError case: Consecutive white spaces\033[m"
	-./$(NAME) "  "
	@echo "\033[41mError case: Multiple arguments\033[m"
	-./$(NAME) 22 32 +
	@echo "\033[41mError case: Invalid char\033[m"
	-./$(NAME) "1 1 + 2a -"
	@echo "\033[41mError case: Invalid RPN token\033[m"
	-./$(NAME) "( 1 2 + )"
	@echo "\033[41mError case: Number out of Range\033[m"
	-./$(NAME) "1 3 * 11 /"
	@echo "\033[41mError case: Invalid RPN expression\033[m"
	-./$(NAME) "1 + 2"
	@echo "\033[41mError case: Not enough operators\033[m"
	-./$(NAME) "1 3 2 +"
	@echo "\033[41mError case: Not enough operands\033[m"
	-./$(NAME) "1 3 + + +"
	@echo "\033[41mError case: Division by zero\033[m"
	-./$(NAME) "1 9 + 0 /"
	@echo "\033[41mError case: OverFlow 2^32\033[m"
	-./$(NAME) "8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 2 *"
	@echo "\033[41mError case: OverFlow INT_MAX + 1\033[m"
	-./$(NAME) "1 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 2 * 1 + 1 2 - * 1 +"
	@echo "\033[41mError case: OverFlow INT_MIN - 1\033[m"
	-./$(NAME) "1 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 2 * 1 -"
	@echo "\033[41mError case: OverFlow INT_MIN / -1\033[m"
	-./$(NAME) "1 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 2 * 1 2 - /"
	@echo "\033[2;3mError handling tests finished\033[m"

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<

-include $(DEPS)

# ******** ******** ******** ******** **** ******** ******** ******** ******** #