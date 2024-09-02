# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 02:23:38 by shurtado          #+#    #+#              #
#    Updated: 2024/09/02 14:50:14 by shurtado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Config
CC = cc
SERVER = server
CLIENT = client
SERVER_BONUS = server
CLIENT_BONUS = client
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_DIR)
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/include

# Debug
CFLAGS += -g -O0 #-fsanitize=address
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
SRV_SRCS_FILES_BONUS = server_bonus.c
CLT_SRCS_FILES_BONUS = client_bonus.c
SSRCS = $(addprefix $(SRC_DIR)/,$(SRV_SRCS_FILES))
CSRCS = $(addprefix $(SRC_DIR)/,$(CLT_SRCS_FILES))
BSSRCS = $(addprefix $(SRC_DIR)/,$(SRV_SRCS_FILES_BONUS))
BCSRCS = $(addprefix $(SRC_DIR)/,$(CLT_SRCS_FILES_BONUS))
SOBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SSRCS))
COBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CSRCS))
BSOBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BSSRCS))
BCOBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BCSRCS))
SDEPS = $(SOBJS:.o=.d)
CDEPS = $(COBJS:.o=.d)
BSDEPS = $(BSOBJS:.o=.d)
BCDEPS = $(BCOBJS:.o=.d)

# Main entrance
all: libft $(SERVER) $(CLIENT)

bonus: libft $(SERVER_BONUS) $(CLIENT_BONUS)

# Compile Binaries
$(SERVER): $(SOBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(SOBJS) $(LIBFT) $(LDFLAGS) -o $(SERVER)
	@echo "\033[1;36mBinary $@ created\033[0m"

$(CLIENT): $(COBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(COBJS) $(LIBFT) $(LDFLAGS) -o $(CLIENT)
	@echo "\033[1;36mBinary $@ created\033[0m"

$(SERVER_BONUS): $(BSOBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(BSOBJS) $(LIBFT) $(LDFLAGS) -o $(SERVER_BONUS)
	@echo "\033[1;36mBinary $@ created\033[0m"

$(CLIENT_BONUS): $(BCOBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(BCOBJS) $(LIBFT) $(LDFLAGS) -o $(CLIENT_BONUS)
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
	@if [ -f "$(SERVER)" ]; then \
		rm -f $(SERVER); \
		echo "\033[1;31m$(SERVER) deleted\033[0m"; \
	fi
	@if [ -f "$(CLIENT)" ]; then \
		rm -f $(CLIENT); \
		echo "\033[1;31m$(CLIENT) deleted\033[0m"; \
	fi

re: fclean all

# Include Dependences (header files)
-include $(SDEPS) $(CDEPS) $(BSDEPS) $(BCDEPS)

.PHONY: all clean fclean re bonus
