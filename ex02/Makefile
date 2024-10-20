# ********************** Section for Macros (Variables) ********************** #
NAME			= PmergeMe
SRC				= main.cpp PmergeMe.cpp
RESULT			= result

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

ifneq ($(ENABLE_COMPARISON_COUNT),)
    DEF         += -D ENABLE_COMPARISON_COUNT=$(ENABLE_COMPARISON_COUNT)
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
	-$(RM) $(RMFLAGS) $(NAME) $(RESULT)*
re: fclean all

debug: fclean all
test: debug test_success test_fail

test_success:
	@echo "\n\033[32;1;3mRegular tests: \033[m"
	@echo "\n\033[33;42m[TEST1]\033[m"
	-./$(NAME) 42
	@echo "\n\033[33;42m[TEST2]\033[m"
	-./$(NAME) 225 12 3232 34348 1221
	@echo "\n\033[33;42m[TEST3]\033[m"
	-./$(NAME) 125 32 43343 1212 1 1 1 22 22
	@echo "\n\033[33;42m[TEST4]\033[m"
	-./$(NAME) 12 3232 121526 237 346 126 43738 1267 432379 5865 3473 23627 43 444
	@echo "\n\033[33;42m[TEST5]\033[m"
	-./$(NAME) 896 495 449 694 863 366 164 86 543 584 541 447 599 6 326 398 637 997 199 788 66 49 596 715 809 411 699 872 979 695
	@echo "\n\033[33;42m[TEST6]\033[m"
	-./$(NAME) `shuf -i 1-100000 -n 3000 | tr '\n' ' '` > $(RESULT)
	@echo "\n\033[33;42m[RANDOM TEST1]\033[m"
	-./$(NAME) `shuf -i 1-100000 -n 6000 | tr '\n' ' '` | awk '/After:/ { for(i=2;i<=NF;i++) print $i }' | sort -n -c
	@if [ $$? -eq 0 ]; then \
        echo "Success"; \
    else \
        echo "Failure"; \
    fi
	@echo "\n\033[33;42m[RANDOM TEST2]\033[m"
	-./$(NAME) `shuf -i 1-100000 -n 10000 | tr '\n' ' '` | awk '/After:/ { for(i=2;i<=NF;i++) print $i }' | sort -n -c
	@if [ $$? -eq 0 ]; then \
        echo "Success"; \
    else \
        echo "Failure"; \
    fi
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
	@echo "\033[41mError case: Invalid char\033[m"
	-./$(NAME) 22 272aa 1
	@echo "\033[41mError case: Not a positive integer\033[m"
	-./$(NAME) "-43" "22" 121
	@echo "\033[41mError case: Over than IntMax\033[m"
	-./$(NAME) 2147483648 126 2121 3223
	@echo "\033[2;3mError handling tests finished\033[m"

count: fclean
	@$(MAKE) all ENABLE_COMPARISON_COUNT=1
	@echo "\033[34;1;3mCounting the number of comparisons\033[m"
	@echo "\n\033[33;42m[TEST1]\033[m"
	-./$(NAME) 42
	@echo "\n\033[33;42m[TEST2]\033[m"
	-./$(NAME) 225 12 3232 34348 1221
	@echo "\n\033[33;42m[TEST3]\033[m"
	-./$(NAME) 125 32 43343 1212 1 1 1 22 22
	@echo "\n\033[33;42m[TEST4]\033[m"
	-./$(NAME) 12 3232 121526 237 346 126 43738 1267 432379 5865 3473 23627 43 444
	@echo "\n\033[33;42m[TEST5]\033[m"
	-./$(NAME) 896 495 449 694 863 366 164 86 543 584 541 447 599 6 326 398 637 997 199 788 66 49 596 715 809 411 699 872 979 695
	@echo "\n\033[33;42m[TEST6]\033[m"
	-./$(NAME) `shuf -i 1-100000 -n 3000 | tr '\n' ' '` > $(RESULT)_3000
	@echo "\n\033[33;42m[RANDOM TEST1]\033[m"
	-./$(NAME) `shuf -i 1-100000 -n 6000 | tr '\n' ' '` > $(RESULT)_6000
	@echo "\n\033[33;42m[RANDOM TEST2]\033[m"
	-./$(NAME) `shuf -i 1-100000 -n 10000 | tr '\n' ' '` > $(RESULT)_10000

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<

-include $(DEPS)

# ******** ******** ******** ******** **** ******** ******** ******** ******** #