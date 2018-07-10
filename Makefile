##
## EPITECH PROJECT, 2018
## AbstractVM
## File description:
## Makefile
##

CC	=	g++

CXXFLAGS=	-W -Wall -Wextra

INCLUDES=	-I./Srcs -I./Srcs/VM

CXXFLAGS+=	$(INCLUDES)

SRCS	=	Srcs/Main.cpp		\
		Srcs/VM/Core.cpp	\
		Srcs/VM/Factory.cpp	\
		Srcs/VM/Operand.cpp	\
		Srcs/VM/VMTools.cpp	\

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	abstractVM

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CXXFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all