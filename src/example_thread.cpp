#define _GNU_SOURCE
#include <assert.h>
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void print_affinity() {
    cpu_set_t mask;
    long nproc, i;

    std::cout << "Thread " << boost::this_thread::get_id() << " affinity : " << '\n';
    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        assert(false);
    } else {
        nproc = sysconf(_SC_NPROCESSORS_ONLN);
        printf("sched_getaffinity = ");
        for (i = 0; i < nproc; i++) {
            printf("%d ", CPU_ISSET(i, &mask));
        }
        printf("\n");
    }

    printf("sched_getcpu = %d\n", sched_getcpu());
}


void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void do_workload(int number)
{
  int j = number;
  for (int i = 0; i < 30000; ++i)
  {
    //std::cout << j << " ";
    for (int k = 0; k < 30000; k++)
    {
      if (k%2 == 0)
        j = j * 17;
      else
        j = j / 17;
    }
    j = j * 42;
  }
}
void thread(int cpuNum)
{
  std::cout << "Thread " << boost::this_thread::get_id() << " just started." << '\n';
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(cpuNum, &mask);

  if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
      perror("sched_setaffinity");
      assert(false);
  }
  print_affinity();

  do_workload(rand() % 100);

  std::cout << "Thread " << boost::this_thread::get_id() << " finished" << '\n';

  return;
}


int main(void) {
    std::cout << boost::this_thread::get_id() << " programm just started." << '\n';

    boost::thread tbis{thread, 1};
    wait(1);

    cpu_set_t mask;

    print_affinity();

    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_setaffinity");
        assert(false);
    }
    print_affinity();

    do_workload(rand() % 100);

    boost::thread t{thread, 2};
    tbis.join();
    t.join();

    std::cout << "Main thread finished" << '\n';
    return EXIT_SUCCESS;
}
