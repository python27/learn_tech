from threading import Thread, Lock
from threading import Condition
import time
import random

queue = []
lock = Lock()

# Version1: Wrong Answer, when the queue is empty, consumer
#           will still want to consume items, which will 
#           cause IndexError
# 
# class ProducerThread(Thread):
#     def run(self):
#         nums = range(5)
#         global queue
#         while True:
#             num = random.choice(nums)
#             lock.acquire()
#             queue.append(num)
#             print ("Produced", num)
#             lock.release()
#             time.sleep(random.random())
# 
# class ConsumerThread(Thread):
#     def run(self):
#         global queue
#         while True:
#             lock.acquire()
#             if not queue:
#                 print ("Nothing in the queue")
#             num = queue.pop(0)
#             print ("Consumed", num)
#             lock.release()
#             time.sleep(random.random())
# 
# ProducerThread().start()
# ConsumerThread().start()

# Version 2
# for consumer, check whether the queue is empty or not, if it is
# wait (release all the locks) until producer put some items into the 
# queue, until producer notify it
# for producer, it can acquire the lock, after notify, consumer wake up
# but notify not release lock immediately.
# condition = Condition()
# class ConsumerThread(Thread):
#     def run(self):
#         global queue
#         while True:
#             condition.acquire()
#             if not queue:
#                 print("Nothing in the queue")
#                 condition.wait()
#                 print("Producer added something to queue and notify me")
#             num = queue.pop(0)
#             print("Consumed ", num)
#             condition.release()
#             time.sleep(random.random())
# 
# class ProducerThread(Thread):
#     def run(self):
#         nums = range(5)
#         global queue
#         while True:
#             condition.acquire()
#             num = random.choice(nums)
#             queue.append(num)
#             print("Produced ", num)
#             condition.notify()
#             condition.release()
#             time.sleep(random.random())
# 
# ProducerThread().start()
# ConsumerThread().start()

# Version 3
# the queue has a max capacity, which means that when the queue is
# full, the producer has to wait until the consumer consume some items

MAX_NUM = 10
condition = Condition()

class ProducerThread(Thread):
    def run(self):
        nums = range(5)
        global queue
        while True:
            condition.acquire()
            if len(queue) == MAX_NUM:
                print ("queue is full, producer is waiting ")
                condition.wait()
                print ("space in queue, consumer notified the producer")
            num = random.choice(nums)
            queue.append(num)
            print ("produced ", num)
            condition.notify()
            condition.release()
            time.sleep(random.random())

class ConsumerThread(Thread):
    def run(self):
        global queue
        while True:
            condition.acquire()
            if not queue:
                print ("queue is empty, consumer is waiting")
                condition.wait()
                print ("producer added some items and notified consumer")
            num = queue.pop(0)
            print ("consumed ", num)
            condition.notify()
            condition.release()
            time.sleep(random.random())

ProducerThread().start()
ConsumerThread().start()
