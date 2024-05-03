# ********************** Section for Macros (Variables) ********************** #
NAME			= btc
SRC				= main.cpp BitcoinExchange.cpp
INPUT			= input.txt

OS				= $(shell uname)

SRCDIR			= ./src
INCDIR			= ./include
OBJDIR			= ./obj

CXX				= c++
RM				= rm

CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -MMD -MP
INCLUDES		= -I$(INCDIR)
RMFLAGS			= -rf
DEBUGCFLAGS		= -g -ggdb -fsanitize=address -fno-omit-frame-pointer
ifneq ($(OS), Darwin)
	DEBUGCFLAGS	+= -fstack-usage
endif
DEBUGLDFLAGS	= -fsanitize=address

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
	-$(RM) $(RMFLAGS) $(OBJDIR) $(INPUT)
fclean: clean
	-$(RM) $(RMFLAGS) $(NAME)
re: fclean all

debug: fclean all
test: debug test_success test_fail

test_success: $(INPUT)
	@echo "\n\033[32;1;3mRegular tests: \033[m"
	@echo "\n\033[33;42m[TEST]\033[m"
	-./$(NAME) $(INPUT)
	@echo "\033[2;3mRegular tests finished\033[m"
test_fail:
	@echo "\n\033[31;1;3mError handling tests\033[m"
	@echo "To continue, hit the [Enter] key"
	-@read _
	@echo "\033[41mError case: No arguments\033[m"
	-./$(NAME)
	@echo "\033[41mError case: Invalid file\033[m"
	-./$(NAME) noooo.txt
	@echo "\033[41mError case: Multiple arguments\033[m"
	-./$(NAME) input.txt test.txt
	@echo "\033[2;3mError handling tests finished\033[m"

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<

$(INPUT):
	@echo "date | value" > input.txt
	@echo "2011-01-03 | 3" >> input.txt
	@echo "2011-01-03 | 2" >> input.txt
	@echo "2011-01-03 | 1" >> input.txt
	@echo "2011-01-03 | 1.2" >> input.txt
	@echo "2011-01-09 | 1" >> input.txt
	@echo "2012-01-11 | -1" >> input.txt
	@echo "2001-42-42" >> input.txt
	@echo "2012-01-11 | 1" >> input.txt
	@echo "2012-01-11 | 2147483648" >> input.txt
	@echo "" >> input.txt
	@echo "2022-03-29 | 1" >> input.txt
	@echo "2025-01-01 | 1" >> input.txt
	@echo "2009-01-03 | 1" >> input.txt
	@echo "2002-01-02 | 1" >> input.txt
	@echo "" >> input.txt
	@echo "2022-03-29 | 1 | 1" >> input.txt
	@echo "2013-03-2a | 1" >> input.txt
	@echo "2012-01-02 | a" >> input.txt
	@echo "2014-33-03 | 1" >> input.txt

-include $(DEPS)

# ******** ******** ******** ******** **** ******** ******** ******** ******** #