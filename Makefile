# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 16:37:33 by tchoquet          #+#    #+#              #
#    Updated: 2023/09/21 13:33:11 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_TYPE	= dynamic# static | dynamic

EXPORT_INCLUDE_DIR	= ${MY_C_INCLUDE_PATH}
EXPORT_LIB_DIR		= ${MY_LIBRARY_PATH}

ROOT				= .
SRCS_DIR			= $(shell find ${ROOT}/sources -type d)
INCLUDES_DIR 		= $(shell find ${ROOT}/includes -type d)
BUILD_DIR			= ${ROOT}/.build

EXPORT_INCLUDE	= ${EXPORT_INCLUDE_DIR}/memory_leak_detector.h
NAME_BASE 		= ${EXPORT_LIB_DIR}/libmemory_leak_detector

SRC = $(foreach dir, ${SRCS_DIR}, $(wildcard ${dir}/*.c))
OBJ = $(foreach file, ${SRC:.c=.o}, ${BUILD_DIR}/$(notdir ${file}))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= -I${INCLUDES_DIR} -I${MY_C_INCLUDE_PATH}
LDFLAGS		=
LDLIBS		=


ifeq (${LIB_TYPE}, static)
    NAME = ${NAME_BASE}.a
else ifeq (${LIB_TYPE}, dynamic) 
    NAME = ${NAME_BASE}.dylib
else
    $(error Bad LIB_TYPE)
endif


vpath %.c ${SRCS_DIR}
vpath %.h ${INCLUDES_DIR}

.PHONY: all clean fclean re


all: ${NAME} ${EXPORT_INCLUDE}

${NAME}: ${OBJ} | ${EXPORT_LIB_DIR}
ifeq (${LIB_TYPE}, static)
	@ar rc $@ $^
else
	@${CC} ${LDFLAGS} -dynamiclib -o $@ $^ ${LDLIBS}
endif
	@echo "Library created at $@"

${BUILD_DIR}/%_debug.o ${BUILD_DIR}/%.o: %.c | ${BUILD_DIR}
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ -c $<

${EXPORT_INCLUDE_DIR}/%.h: %.h | ${EXPORT_INCLUDE_DIR}
	@cp $< $@
	@echo "Include file copied at $@"

clean:
	@rm -rf ${BUILD_DIR}
	@echo "Build directory deleted"

fclean: clean
	@rm -rf ${NAME}
	@echo "${NAME} deleted."
	@rm -rf ${EXPORT_INCLUDE}
	@echo "${EXPORT_INCLUDE} deleted"

re: fclean all


#folders
${EXPORT_INCLUDE_DIR} ${EXPORT_LIB_DIR} ${BUILD_DIR}:
	@mkdir -p $@
	@echo "Folder $@ created"
