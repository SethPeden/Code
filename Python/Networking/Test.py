# from multiprocessing import Pool
from multiprocessing.pool import ThreadPool as Pool
import time
import random

pool_size = 5  # your "parallelness"
pool = Pool(pool_size)

def worker(id):
    while True:
        print(id)
        time.sleep(random.uniform(0, 3))


for i in range(1, 5):
    pool.apply_async(worker, (i,))

pool.close()
pool.join()