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

3. Build ``stress`` using ``make``
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
valgrind --leak-check=full ./stress
```

### Running StressHarness

``stress`` can run in a variety of modes

Example:
```shell
# Running Monte Carlo test
./stress -m

# Running Monte Carlo test verbosely
./stress -m -v

# Running Monte Carlo test quietly
./stress -m -q

# Running Monte Carlo test verbosely, with circle of radius 12 and 60 iterations
./stress -m -v -r 12 -n 60

# Running stress verbosely with the Monte Carlo test with a circle of radius 12 and 60 iterations, and run the Monte Carlo test until
# an error rate of 0.001% or less is achieved
./stress -m -v -r 12 -n 60 -M 0.001

```

``stress`` supports the following flags:
* ``-n [number]``: The number of iterations to run for a test. Omitting this flag uses the default value of 50
* ``-r [number]``: The radius size of the circle used for Monte Carlo pi approximation. Omitting this flag uses the default value of 10
* ``-M [number]``: Run the Monte Carlo pi approximation stress test until an error rate of ``number``% or less is reached (Range: 100% - 0.000001%)
* ``-m``: Run the Monte Carlo pi appoximation stress test
* ``-v``: Run ``stress`` in verbose mode
* ``-q``: Run ``stress`` in quiet mode. Note that this flag conflicts with the ``-v`` flag

### Future Plans
* [ ] Write a program to visualize the stress on the computer
* [ ] Implement a Graph Stress Test
* [ ] Implement Monte Carlo Integration
 
