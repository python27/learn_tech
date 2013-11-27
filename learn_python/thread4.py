from threading import Thread
from threading import Lock
import time

lock = Lock()

class CreateListThread(Thread):
    def run(self):
        self.entries = []
        for i in range(4):
            time.sleep(i)
            self.entries.append(i)
        lock.acquire()
        print self.entries
        lock.release()

def use_create_list_thread():
    for i in range(3):
        t = CreateListThread()
        t.start()

use_create_list_thread()
