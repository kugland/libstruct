BUILD_DIR		:= ../build
CFLAGS			:= -I../include -pipe

ifndef DEBUG
	DEBUG 		:= 1
endif

ifeq ($(DEBUG),1)
	CFLAGS		+= -DDEBUG=1
else
	CFLAGS		+= -DNDEBUG -DDEBUG=0 -fomit-frame-pointer -march=native -O2
endif

# Main library
libstruct_OUT	:= $(BUILD_DIR)/libstruct.a

depends_OUT		:= $(BUILD_DIR)/dependencies

# Linked list module
list_HDR		:= ../include/libstruct/list.h

list_SRC		:= list/append.c		list/apply.c		list/clear.c \
				   list/copy.c			list/create.c		list/destroy.c \
				   list/filter.c		list/from_array.c	list/join.c \
				   list/node_create.c	list/node_destroy.c	list/prepend.c \
				   list/reverse.c		list/sort.c			list/to_array.c
list_OBJ		:= $(list_SRC:.c=.o)

libstruct_HDR	:= $(list_HDR)

all: $(libstruct_OUT)

dep: $(depends_OUT)

install: $(libstruct_OUT) $(list_HDR)
	for hdr in $(subst ../,,$(libstruct_HDR)); do \
		install -D -o root -g root -m 644 ../$$hdr $(DESTDIR)/$$hdr; \
	done
	install -D -o root -g root -m 644 $(libstruct_OUT) \
		$(DESTDIR)/lib/$(subst ../build/,,$(libstruct_OUT))

uninstall:
	-rm -rv $(DESTDIR)/include/libstruct
	-rm -v $(DESTDIR)/lib/$(subst ../build/,,$(libstruct_OUT))

$(libstruct_OUT): $(list_OBJ)
	$(AR) rcs $@ $(list_OBJ)

$(depends_OUT):
	$(CC) $(CFLAGS) -M $(list_SRC) >$@

clean:
	$(RM) $(depends_OUT)
	$(RM) $(libstruct_OUT)
	$(RM) $(list_OBJ)

ifneq ($(MAKECMDGOALS),clean)
	include $(depends_OUT)
endif
