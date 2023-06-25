# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 16:37:33 by tchoquet          #+#    #+#              #
#    Updated: 2023/06/25 19:19:31 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}
INCLUDES_DIR 	= ${ROOT}
BUILD_DIR		= ${ROOT}

EXPORT_INCLUDE_DIR	= ${MY_C_INCLUDE_PATH}
EXPORT_LIB_DIR		= ${MY_LIBRARY_PATH}

SRC	= ${wildcard ${SRCS_DIR}/*.c}

OBJ = ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}

CC					= gcc
CFLAGS				=

NAME			= ${EXPORT_LIB_DIR}/libmemory_leak_detector.a
EXPORT_INCLUDE	= ${EXPORT_INCLUDE_DIR}/memory_leak_detector.h

.PHONY: all clean fclean re

all: ${NAME} ${EXPORT_INCLUDE}

${NAME}: ${OBJ}
	ar rc $@ $^

${EXPORT_INCLUDE_DIR}/%.h: ${INCLUDES_DIR}/%.h | ${EXPORT_INCLUDE_DIR}
	cp $< $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME} ${EXPORT_INCLUDE}

re: fclean all

${BUILD_DIR}/%.o: %.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}


#folders
${EXPORT_INCLUDE_DIR} ${EXPORT_LIB_DIR} ${BUILD_DIR}:
	mkdir -p $@