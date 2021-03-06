from threading import Thread
from threading import Lock

lock = Lock()
# define a global variable
some_var = 0

class IncreThread(Thread):
    def run(self):
        global some_var

        lock.acquire()
        read_value = some_var
        print "some_val in %s is %d" %(self.name, read_value)
        some_var = read_value + 1
        print "some_var in %s after increment is %d" %(self.name, some_var)
        lock.release()

def use_increment_thread():
    threads = []
    for i in range(50):
        t = IncreThread()
        t.start()

    for t in threads:
        t.join()
    print "After 50 increment, some_var should have become 50"
    print "After 50 increment, some_var is %d" %(some_var,)

use_increment_thread()
