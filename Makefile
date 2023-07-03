# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 16:37:33 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/03 15:26:00 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR 	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/build

EXPORT_INCLUDE_DIR	= ${MY_C_INCLUDE_PATH}
EXPORT_LIB_DIR		= ${MY_LIBRARY_PATH}

RELEASE_SRC	= ${wildcard ${SRCS_DIR}/*.c}
DEBUG_SRC 	= ${ROOT}/main_for_test.c

RELEASE_OBJ = ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${RELEASE_SRC:.c=.o}}
DEBUG_OBJ	= ${RELEASE_OBJ:.o=_debug.o} ${patsubst ${ROOT}%, ${BUILD_DIR}%, ${DEBUG_SRC:.c=.o}}

CC						= gcc
CFLAGS					= -Wall -Wextra -Werror
alldebug: CFLAGS		= -g

NAME			= ${EXPORT_LIB_DIR}/libmemory_leak_detector.a
EXPORT_INCLUDE	= ${EXPORT_INCLUDE_DIR}/memory_leak_detector.h

DEBUG_EXE 		= ${ROOT}/Debug.out

vpath %.c ${ROOT} ${SRCS_DIR}

.PHONY: all clean fclean re debug alldebug cleandebug fcleandebug redebug


all: ${NAME} ${EXPORT_INCLUDE}

${NAME}: ${RELEASE_OBJ} | ${EXPORT_LIB_DIR}
	ar rc $@ $^

${EXPORT_INCLUDE_DIR}/%.h: ${INCLUDES_DIR}/%.h | ${EXPORT_INCLUDE_DIR}
	cp $< $@

clean:
	rm -rf ${RELEASE_OBJ}

fclean: clean
	rm -rf ${NAME} ${EXPORT_INCLUDE}

re: fclean all


debug: alldebug

alldebug: ${DEBUG_EXE}

${DEBUG_EXE}: ${DEBUG_OBJ}
	${CC} -o $@ $^

cleandebug:
	rm -rf ${DEBUG_OBJ}

fcleandebug: cleandebug
	rm -rf ${DEBUG_EXE}

redebug: fcleandebug alldebug



#All targets
${BUILD_DIR}/%_debug.o: %.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}

${BUILD_DIR}/%.o: %.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}



#folders
${EXPORT_INCLUDE_DIR} ${EXPORT_LIB_DIR} ${BUILD_DIR}:
	mkdir -p $@