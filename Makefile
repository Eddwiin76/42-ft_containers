FT			=	ft_containers

STL			=	stl_containers

CC			=	clang++

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -std=c++98

SRCS_STL	=	main_stl.cpp

SRCS_FT		=	main_ft.cpp

OBJS_STL	:=	${SRCS_STL.cpp=.o}

OBJS_FT		:=	${SRCS_FT.cpp=.o}

.PHONY: clean fclean re


all: ${FT} ${STL}

${FT}: ${OBJS_FT}
	$(CC) $(CFLAGS) $(SRCS_FT) -o $(FT)

${STL}: ${OBJS_STL}
	$(CC) $(CFLAGS) $(SRCS_STL) -o $(STL)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) ${OBJS_STL} ${OBJS_FT}

fclean: clean
	$(RM) ${STL} ${FT}

re: fclean all
