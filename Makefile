# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 16:37:33 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/10 17:16:31 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR 	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/.build

EXPORT_INCLUDE_DIR	= ${MY_C_INCLUDE_PATH}
EXPORT_LIB_DIR		= ${MY_LIBRARY_PATH}

SRC		= ${wildcard ${SRCS_DIR}/*.c}
EXE_SRC	= ${ROOT}/main_for_test.c

RELEASE_OBJ = ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}
DEBUG_OBJ	= ${RELEASE_OBJ:.o=_debug.o}
EXE_OBJ		= ${patsubst ${ROOT}%, ${BUILD_DIR}%, ${EXE_SRC:.c=.o}}

CC						= gcc
CFLAGS					= -Wall -Wextra -Werror
debug debugexe: CFLAGS	= -g -D MEMCHECK

NAME			= ${EXPORT_LIB_DIR}/libmemory_leak_detector.a
EXPORT_INCLUDE	= ${EXPORT_INCLUDE_DIR}/memory_leak_detector.h
DEBUG_EXE		= ${ROOT}/Debug.out

vpath %.c ${ROOT} ${SRCS_DIR}

.PHONY: all clean fclean re debug cleandebug fcleandebug redebug cleanbuild


all: ${NAME} ${EXPORT_INCLUDE}

${NAME}: ${RELEASE_OBJ} | ${EXPORT_LIB_DIR}
	@ar rc $@ $^
	@echo "Archive created at $@."

clean:
	@rm -rf ${RELEASE_OBJ}
	@echo "Release object files deleted."

fclean: clean
	@rm -rf ${NAME}
	@echo "${NAME} deleted."
	@rm -rf ${EXPORT_INCLUDE}
	@echo "${EXPORT_INCLUDE} deleted."

re: fclean all



debug: ${DEBUG_EXE}

${DEBUG_EXE}: ${DEBUG_OBJ} ${EXE_OBJ}
	@${CC} -o $@ $^ ${EXTERNAL_LIBS}
	@echo "Executable created at $@."

cleandebug:
	@rm -rf ${EXE_OBJ}
	@echo "Object files for executable deleted."

fcleandebug:
	@rm -rf ${DEBUG_OBJ}
	@echo "Debug object files deleted."
	@rm -rf ${DEBUG_EXE}
	@echo "${DEBUG_EXE} deleted."

redebug: fcleandebug debug



cleanbuild:
	@rm -rf ${BUILD_DIR}
	@echo "Build folder deleted."



#All targets
${BUILD_DIR}/%_debug.o ${BUILD_DIR}/%.o: %.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}

${EXPORT_INCLUDE_DIR}/%.h: ${INCLUDES_DIR}/%.h | ${EXPORT_INCLUDE_DIR}
	@cp $< $@
	@echo "Include file copied at $@."


#folders
${EXPORT_INCLUDE_DIR} ${EXPORT_LIB_DIR} ${BUILD_DIR}:
	@mkdir -p $@
	@echo "Folder $@ created."

