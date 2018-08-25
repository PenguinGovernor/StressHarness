# Stress Harness
A suite of cpu-intensive tasks implemented as a Stress Harness

### Download and Install
1. Download this repo using ``git``
```shell
git clone https://github.com/penguingovernor/StressHarness.git
```

2. Change directory into the repo using ``cd``
```shell
cd StressHarness
```

3. Build ``StressHarness`` using ``make``
```shell
make
```

### Cleaning up
After using the program the files can be cleaned with ``make``
```shell
make clean
```

### Testing
To ensure that installation went smoothly run ``valgrind`` to test for memory leaks
```shell
valgrind --leak-check=full ./StressHarness
```

### Running StressHarness

``StressHarness`` can run in a variety of modes

Example:
```shell
# Running montecarlo test
./StressHarness -m

# Running montecarlo test verbosely
./StressHarness -m -v

# Running montecarlo test verbosely, with circle of radius 12 and 60 iterations
./StressHarness -m -v -r 12 -n 60
```

``StressHarness`` supports the following flags:
* ``-n [number]``: The number of iterations to run for a test. Omitting this flag uses the default value of 50
* ``-r [number]``: The radius size of the circle used for Monte Carlo pi approximation. Omitting this uses the default value of 10
* ``-m``: Run the Monte Carlo pi appoximation stress test
* ``-v``: Run ``StressHarness`` in verbose mode

### Future Plans
* [ ] Write a program to visualize the stress on the computer
* [ ] Implement a Graph Stress Test
* [ ] Implement Monte Carlo Integration
