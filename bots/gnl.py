import socket

buff = ''
call_counter = 0

def get_next_line(conn, blocking=0):
    global buff
    global call_counter
    conn.setblocking(blocking)
    while '\n' not in buff:
        try:
            buff += conn.recv(256)
        except:
            break
    if '\n' in buff:
        (line, buff) = buff.split('\n', 1)
    else:
        line = buff
        buff = ''
    if blocking == 1:
        print "GNL : call %d, line\"%s\"\n" % (call_counter, line)
        call_counter += 1
    return line

def clear_gnl():
    global buff
    buff = ''
