NAME				= miniRT
BENCH				= benchmark

HDRS_DIR			= ./include
SRCS_DIR			= ./src
OBJS_DIR			= ./obj

MLX_DIR				= ./minilibx_opengl
MLX					= $(addprefix $(MLX_DIR)/, libmlx.a)

C_FILES				= main.c \
						benchmark.c \
						vec3.c \
						vec32.c \
						vec33.c \
						utils.c \
						array.c \
						object.c \
						rt_error.c \
						rt_init.c \

BENCH_FILES			= benchmark.c \
						benchmark_main.c \

SRCS				= $(addprefix $(SRCS_DIR)/, $(C_FILES))
BENCH_SRCS			= $(addprefix $(SRCS_DIR)/, $(BENCH_FILES))
OBJS				= $(addprefix $(OBJS_DIR)/, $(C_FILES:.c=.o))
BENCH_OBJS			= $(addprefix $(OBJS_DIR)/, $(BENCH_FILES:.c=.o))
DEPENDENCIES		= $(OBJS:.o=.d)
BENCH_DEPENDENCIES	= $(BENCH_OBJS:.o=.d)

CC					= gcc
CFLAGS				= -O3 -ffast-math -Wall -Werror -Wextra -I $(HDRS_DIR) -I $(MLX_DIR)
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
	$(RM) $(RMFLAGS) $(OBJS) $(DEPENDENCIES) $(BENCH_OBJS) $(BENCH_DEPENDENCIES)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME) $(BENCH) $(OBJS_DIR)
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

cval : $(NAME)
	valgrind --tool=cachegrind \
		--log-file=cachegrind-out.txt \
		./$(NAME)

$(BENCH) :  Makefile $(BENCH_SRCS) $(OBJS_DIR) $(BENCH_OBJS) $(BENCH_DEPENDENCIES)
	$(CC) $(LFLAGS) -o $(BENCH) $(BENCH_OBJS)

bench : $(BENCH)
	./$(BENCH)

re: fclean all
