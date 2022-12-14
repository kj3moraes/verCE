# README

The naming scheme in this testing suite is as follows:

* `.in` files are input files for the test. `.out` files are the expected output (both stderr and stdout)
* The first letter of the testname indicates whether it is meant to pass or // throw and error. `P_.*` means the tests should pass and `F._.*` measn the test should // throw an error.
* The second character for failed tests indicate which part of the compiler should fail.
  * `Fl_.*` means the lexer should fail.
  * `Fp_.*` means the parser should fail.
  * `Ft_.*` means the typechecker should fail.
  * `Fg_.*` means the code generator should fail.

The `produce_outputs.sh` script will consume all the input files and create / overwrite the respective output files.

The `run_tests.sh` script will run all the tests and compare the output to the expected output. It will also print the diff if the output does not match the expected output.
