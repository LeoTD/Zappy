import socket
import os
from bossbot import BossBot
from workbot import WorkBot

server_ip = "0.0.0.0"
comm_port = 5555
worker = False

print "Hello"
boss = BossBot(server_ip, comm_port, "a")
for i in range(5):
    pid = os.fork()
    if pid == 0:
        boss = None
        work = WorkBot(server_ip, comm_port, "a")
        worker = True
    else:
        break
if worker:
    print(WorkBot.team_inventory)
    work.work_loop()
else:
    boss.boss_loop()

while True:
    pass
