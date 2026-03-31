
TARGET1 = main_lnode
TARGET2 = main_bstree
TARGET3 = main_list
TARGETS = $(TARGET1) $(TARGET2) $(TARGET3)

CFLAGS = -Wall -g -std=c99
LDFLAGS= -lm

# Incomplete list, these are the files given to students
DIST_FILES = dict.h list.h lnode.h key_value.h bstree.h\
		        list.c lnode.c key_value.c\
			   dict_bstree.c\
			   main.c dico-francais.txt\
			   Makefile


HELPERS = lnode.o list.o bstree.o key_value.o


OBJS_LIST = main.o dict_lnode.o ${HELPERS}
OBJS_TREE = main.o dict_bstree.o ${HELPERS}
OBJS_LIST2 = main.o dict_list.o  ${HELPERS}
COMMON_HEADERS = dict.h

all : $(TARGETS)

$(TARGET1) : $(OBJS_LIST)
	@echo "Building $@"
	@$(CC) -o $@ $(OBJS_LIST) $(LDFLAGS) $(CFLAGS)

$(TARGET2) : $(OBJS_TREE)
	@echo "Building $@"
	$(CC) -o $@ $(OBJS_TREE) $(LDFLAGS) $(CFLAGS)

$(TARGET3) : $(OBJS_LIST2)
	@echo "Building $@"
	@$(CC) -o $@ $(OBJS_LIST2) $(LDFLAGS) $(CFLAGS)

.c.o : 
	@echo "Building $@"
	@$(CC)  $(CFLAGS) -c $<

clean :
	@rm -f $(TARGETS) *.o *~


dist: $(DIST_FILES)
	@echo "* creating $(DIR)"
	@rm -rf $(DIR)
	@mkdir $(DIR)
	@cp $(DIST_FILES) $(DIR)
	@tar cvfz $(DISTNAME) $(DIR)
	@rm -rf $(DIR)
	@echo "* -> $(DISTNAME) built."
