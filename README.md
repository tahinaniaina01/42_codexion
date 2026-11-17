_This project has been created as part of the 42 curriculum by trakotos._

# Codexion

## Description

Codexion is a concurrent simulation in which coders compete for shared dongles
in order to complete a required number of compilation cycles. Each cycle has
three phases:

1. compiling, while holding two dongles;
2. debugging;
3. refactoring.

The program creates one thread per coder and a monitor thread. Coders request
their dongles through per-dongle waiting queues. Two scheduling policies are
available:

- `fifo`: requests are served in insertion order;
- `edf`: requests are ordered by the earliest burnout deadline.

The simulation stops when every coder has completed the required number of
compilations, or when a coder burns out.

## Instructions

### Compilation

The project requires a C compiler, POSIX threads, and `make`.

```bash
make
```

Additional targets are available:

```bash
make clean
make fclean
make re
```

### Execution

Run the program with:

```text
./codexion number_of_coders time_to_burnout time_to_compile \
    time_to_debug time_to_refactor number_of_compiles_required \
    dongle_cooldown fifo|edf
```

All time values are expressed in milliseconds.

Example:

```bash
./codexion 2 320 100 100 100 2 0 edf
```

The output contains the elapsed time, the coder identifier, and the state
change:

```text
1 1 has taken a dongle
1 1 is compiling
101 1 is debugging
```

## Blocking cases handled

### Deadlock prevention and Coffman's conditions

Each coder needs two dongles, which can normally create a circular wait:
coder A holds one dongle while waiting for a dongle held by coder B. Dongles
are assigned and acquired in one global order, from the highest dongle index
to the lowest. This prevents circular wait and therefore breaks the deadlock
cycle described by Coffman's conditions.

If the second dongle cannot be acquired because the simulation is stopping,
the waiting operation returns and the thread does not continue compiling.

### Fairness and starvation prevention

Every dongle owns a protected request queue. Requests are served according to
the selected policy:

- FIFO preserves request insertion order;
- EDF prioritizes the request with the earliest calculated burnout deadline.

The queue is checked while holding the dongle mutex, so two coders cannot
remove the same request or acquire the same dongle simultaneously.

### Dongle cooldown

When a dongle is released, it is marked unavailable until
`current_time + dongle_cooldown`. Waiting coders are not allowed to take it
before this timestamp. A timed condition wait is used when the waiting coder
is at the head of the queue.

### Precise burnout detection

The monitor periodically checks the time elapsed since each coder's last
compilation start. A coder that has completed all required compilations is not
declared burned out. The burnout timeout should include a small scheduling
margin because thread scheduling and monitor polling add a few milliseconds.

### Log serialization

All state messages use a shared logging mutex. This prevents output from
different threads from being interleaved and ensures that a stop or burnout
message is printed consistently.

## Thread synchronization mechanisms

### `pthread_mutex_t`

Mutexes protect shared state:

- each dongle mutex protects `in_use`, `available_at`, and its request queue;
- each coder mutex protects `last_compile_start` and `compile_count`;
- the logging mutex protects `stop` and serializes output.

For example, a coder locks a dongle mutex before adding its request and
checking whether it is allowed to acquire the dongle. The request is removed
and `in_use` is set while the same mutex is still held.

### `pthread_cond_t`

Each dongle has a condition variable. A coder that cannot acquire the dongle
waits with `pthread_cond_wait` or `pthread_cond_timedwait`. These operations
temporarily release the dongle mutex while the thread sleeps and reacquire it
before returning.

When a dongle is released, `pthread_cond_broadcast` wakes all coders waiting
for it. They then re-check the queue order, cooldown timestamp, and `in_use`
flag while holding the mutex. Waking a thread does not grant it the dongle:
the predicate must still be true.

The condition variables are also broadcast during shutdown so that coders
blocked on a dongle can observe the shared stop flag and exit.

### Custom event state

The project uses the shared `data->stop` flag as a shutdown event. Access to
this flag is protected by the logging mutex. The monitor sets it when all
coders are done or when a burnout is detected; condition-variable broadcasts
then wake threads that might otherwise remain blocked in a dongle wait.

This combination provides thread-safe communication between coder threads and
the monitor without busy-waiting on dongle availability.

## Resources

- [POSIX Threads Programming](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [`pthread_mutex_lock` documentation](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [`pthread_cond_wait` documentation](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html)
- [`pthread_cond_broadcast` documentation](https://man7.org/linux/man-pages/man3/pthread_cond_broadcast.3p.html)
- [The Linux man-pages project](https://man7.org/linux/man-pages/)
- [Operating Systems: Three Easy Pieces - Concurrency](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-intro.pdf)

### Use of AI

AI was used only to explain concurrency concepts and the use of threading
functions, including POSIX mutexes and condition variables. It was also used
to help write and organize this README.
