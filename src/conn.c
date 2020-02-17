
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>

#include <event.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent_ssl.h>

#include "conn.h"

struct _conn
{
	int	fd;
	int	type;
	int	state;
	int	addrlen;
	struct sockaddr *addr;
	struct bufferevent *bev;
};

conn_pt
conn_new(int fd)
{
	conn_pt p = (conn_pt)calloc(1, sizeof(conn_t));
	if(p) {
		p->fd = fd;
		p->type = CONN_TYPE_UNKNOWN;
		p->state = CONN_STATE_NEW;
	}
	return p;
}

int
conn_get_fd(conn_pt inp)
{
	if(inp)	{
		return inp->fd;
	}
	return -1;
}

int
conn_get_type(conn_pt inp)
{
	int type = CONN_TYPE_UNKNOWN;
	if(inp) {
		type = inp->type;
	}
	return type;
}

void
conn_set_type(conn_pt inp, int type)
{
	if(inp) {
		inp->type = type;
	}
}

int
conn_get_state(conn_pt inp)
{
	int state = CONN_STATE_NEW;
	if(inp) {
		state = inp->state;
	}
	return state;
}

void
conn_set_state(conn_pt inp, int state)
{
	if(inp) {
		inp->state = state;
	}
}

