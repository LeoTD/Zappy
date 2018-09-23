import socket
import sys
import time
import os
import random
import time
from gnl import get_next_line
from gnl import clear_gnl


team_name = "banana"
server_ip = "0.0.0.0"
comm_port = 5555
open_seats = 0
map_x = 0
map_y = 0
ticks_to_hatch = -1;
inventory = [0, 0, 0, 0, 0, 0, 0]
bot_zero = True
conn = 0
tick_len = 0

def print_bot():
    global team_name
    global open_seats
    global map_x
    global map_y
    print("Bot:\n  team: {}".format(team_name))
    print("  open_seats: {}".format(open_seats))
    print("  map_x = {}".format(map_x))
    print("  map_y = {}".format(map_y))

def init_child():
    global conn
    print("\tCHILD : What is my purpose")
    while True:
        pass

def stupid_ai():
    global conn
    stupid_ai = random.randint(1, 8)
    if stupid_ai == 1:
        conn.send("right\n")
    elif stupid_ai == 2:
        conn.send("left\n")
    else:
        conn.send("advance\n")

def fork_ai():
    global conn
    newpid = os.fork()
    if newpid == 0:
        init_child(conn)
        clear_gnl()

def is_boss():
    global conn
    global bot_zero
    global tick_len
    start = time.time()
    conn.send("broadcast bot_zero? " + team_name + "\n")
    data = ''
    print 'a'
    while data != "ok":
        print data
        data = get_next_line(conn, 1)
    print 'b'
    end = time.time()
    tick_len = (end - start) / 7
    print tick_len
    while (time.time() - end) < tick_len * 15:
        data = get_next_line(conn, 0)
        if data.split(' ', 1)[0] == "message":
            data = data.split(',', 1)[1]
            if data == ("bot_zero " + team_name + " false\n"):
                bot_zero = False
                print("NOT BOT ZERO")
                break
    if bot_zero:
        print("I AM BOT ZERO!")

def bot_loop():
    global conn
    thing_counter = 0
    is_boss()
    while True:
        data = ''
        stupid_ai()
        while data != "ok":
            data = get_next_line(conn)
            if data:
                print("server: " + data)
                if bot_zero and data.split(' ', 1)[0] == "message":
                    data = data.split(',', 1)[1]
                    if data == ("bot_zero? " + team_name + "\n"):
                        conn.send("broadcast bot_zero " + team_name + " false\n")
                        continue
        print("I'm doing a thing {}!".format(thing_counter))
        thing_counter += 1

def valid_ip_port(address):
    try:
        socket.inet_pton(socket.AF_INET6, address)
    except socket.error:
        return False
    return True

def init_comms():
    global team_name
    global open_seats
    global map_x
    global map_y
    global conn
    if len(sys.argv) > 1:
        team_name = sys.argv[1]
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect((server_ip, comm_port))
    print("Waiting on server welcome\n")
    data = get_next_line(conn, 1)
    if data != "WELCOME":
        print("Sorry, wrong number.\n")
        sys.exit()
    print("server: " + data)
    print("We're in...\n")
    conn.send(team_name)
    open_seats = get_next_line(conn, 1)
    (map_x, map_y) = get_next_line(conn, 1).split(' ', 1)
    print_bot()
    bot_loop()
    
def init_bot():
    if (not server_ip and not comm_port):
        if len(sys.argv) == 4:
            (team_name, server_ip, comm_port) = sys.argv[1:3]
        else:
            print("Invalid bot arguments.\n")
            exit()

if __name__ == "__main__":
    init_comms()
