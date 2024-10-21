# ********************** Section for Macros (Variables) ********************** #
NAME			= btc
SRC				= main.cpp BitcoinExchange.cpp
DB				= cpp_09
TEST_INPUT		= input.txt

# https://stackoverflow.com/questions/649246/is-it-possible-to-create-a-multi-line-string-variable-in-a-makefile
define TEST_INPUT_BODY
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648

2022-03-29 | 1
2025-01-01 | 1
2009-01-03 | 1
2009-01-01 | 1
2002-01-02 | 1

2022-03-29 | 1 | 1
2013-03-2a | 1
2012-01-02 | a
2014-33-03 | 1
-1-1 | 1
1-1-1 | inf
9999-02-31 | 1
20000-01-01 | 1
420-01-01 | 1
endef

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
	-$(RM) $(RMFLAGS) $(OBJDIR) $(TEST_INPUT)
fclean: clean
	-$(RM) $(RMFLAGS) $(NAME) $(DB)
re: fclean all

debug: fclean all
test: debug test_success test_fail

test_success: $(TEST_INPUT)
	@echo "\n\033[32;1;3mRegular tests: \033[m"
	@echo "\n\033[33;42m[TEST]\033[m"
	-./$(NAME) $(TEST_INPUT)
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
	-./$(NAME) $(TEST_INPUT) test.txt
	@echo "\033[2;3mError handling tests finished\033[m"

$(NAME): $(DB) $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME)

$(DB):
	@curl -O https://cdn.intra.42.fr/document/document/27567/cpp_09.tgz
	@tar -xzf cpp_09.tgz
	@rm -rf cpp_09.tgz

$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<

export TEST_INPUT_BODY
$(TEST_INPUT):
	@echo "$$TEST_INPUT_BODY" > $(TEST_INPUT)

-include $(DEPS)

# ******** ******** ******** ******** **** ******** ******** ******** ******** #