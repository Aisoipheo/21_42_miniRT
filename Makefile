NAME				= miniRT

HDRS_DIR			= ./include
SRCS_DIR			= ./src
OBJS_DIR			= ./obj

MLX_DIR				= ./minilibx_opengl
MLX					= $(addprefix $(MLX_DIR)/, libmlx.a)

C_FILES				= main.c

SRCS				= $(addprefix $(SRCS_DIR)/, $(C_FILES))
OBJS				= $(addprefix $(OBJS_DIR)/, $(C_FILES:.c=.o))
DEPENDENCIES		= $(OBJS:.o=.d)

CC					= gcc
CFLAGS				= -O3 -Wall -Werror -Wextra -I $(HDRS_DIR) -I $(MLX_DIR)
LFLAGS				= $(CFLAGS) -lmlx -framework OpenGL -framework AppKit

AR					= ar
ARFLAGS				= rcs

RM					= rm
RMFLAGS				= -rf

MKDIR				= mkdir
MKDIRFLAGS			= -p

MAKE				= make -s

.PHONY : all clean fclean re bonus norm val
.DEFAULT_GOAL := all

-include $(DEPENDENCIES)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -MD

$(OBJS_DIR) :
	$(MKDIR) $(MKDIRFLAGS) $(OBJS_DIR)

$(MLX) :
	$(MAKE) -C $(MLX_DIR)

$(NAME) : $(SRCS) $(OBJS_DIR) $(OBJS) $(DEPENDENCIES) Makefile $(MLX)
	$(CC) $(LFLAGS) -o $(NAME) $(OBJS)

all : $(NAME)

bonus : $(NAME)

clean :
	$(RM) $(RMFLAGS) $(OBJS) $(DEPENDENCIES)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME) $(OBJS_DIR)
	$(MAKE) -C $(MLX_DIR) clean

norm :
	norminette $(SRCS_DIR) $(HDRS_DIR)

val : $(NAME)
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./$(NAME)

re: fclean all
