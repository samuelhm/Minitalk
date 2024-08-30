# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 02:23:38 by shurtado          #+#    #+#              #
#    Updated: 2024/08/27 02:30:03 by shurtado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Config
CC = cc
SERVER = server
CLIENT = client
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_DIR)
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/include

# Debug
# CFLAGS += -g -O0
# Directory
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIB_DIR = lib

# Librarys
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source + obj
SRV_SRCS_FILES = server.c
CLT_SRCS_FILES = client.c
SSRCS = $(addprefix $(SRC_DIR)/,$(SRV_SRCS_FILES))
CSRCS = $(addprefix $(SRC_DIR)/,$(CLT_SRCS_FILES))
SOBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SSRCS))
COBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CSRCS))

# Main entrance
all: libft $(SERVER) $(CLIENT)

# Compile Binaries
$(SERVER): $(SOBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(SOBJS) $(LIBFT) $(LDFLAGS) -o $(SERVER)
	@echo "\033[1;36mBinary $@ created\033[0m"

$(CLIENT): $(COBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(COBJS) $(LIBFT) $(LDFLAGS) -o $(CLIENT)
	@echo "\033[1;36mBinary $@ created\033[0m"

# -MMD to include header dependences to .d file and run $(OBJ_DIR) if not exist.make
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@ > /dev/null
	@echo "\033[0;32mObject $@ created\033[0m"

# Create obj dir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Lib libft rule
libft:
	@$(MAKE) --silent --no-print-directory -C $(LIBFT_DIR)

# Utils
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "\033[1;31mObjects deleted\033[0m"; \
	fi
	@$(MAKE) --silent --no-print-directory -C $(LIBFT_DIR) fclean

fclean: clean
	@if [ -f "$(TARGET)" ]; then \
		rm -f $(TARGET); \
		echo "\033[1;31m$(TARGET) deleted\033[0m"; \
	fi

re: fclean all

# Include Dependences (header files)
-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
