
#ifndef CONN_H_INCLUDED
#define CONN_H_INCLUDED

struct _conn;
typedef struct _conn  conn_t;
typedef struct _conn *conn_pt;

#define	CONN_TYPE_UNKNOWN 0
#define	CONN_TYPE_WEBSOCKET_PRIMARY 1
#define CONN_TYPE_WEBSOCKET_AUXILIARY 2
#define CONN_TYPE_HTTP_1_1 3
#define	CONN_TYPE_HTTP_2 4

#define CONN_STATE_NEW 0
#define CONN_STATE_ACCEPT 1

conn_pt
conn_new(int fd);

int
conn_get_fd(conn_pt);

int
conn_get_type(conn_pt);

void
conn_set_type(conn_pt, int);

int
conn_get_state(conn_pt);

void
conn_set_state(conn_pt, int);

#endif /* CONN_H_INCLUDED */

