#!/usr/bin/python
import multiprocessing

def worker(num): print('Worked!', num)

if __name__ == '__main__':
  for i in range(500):
    p = multiprocessing.Process(target=worker, args=(i,))
    p.start()
    # Add `p.join()` if you want them to run in order

# sentdex. Multiprocessing: https://www.youtube.com/watch?v=oEYDqQ1pq9o
