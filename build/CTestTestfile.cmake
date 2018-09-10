# CMake generated Testfile for 
# Source directory: C:/Users/richa/OneDrive/Desktop/smashtester
# Build directory: C:/Users/richa/OneDrive/Desktop/smashtester/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(student-tests "student-tests")
add_test(test00 "pathfinder" "C:/Users/richa/OneDrive/Desktop/smashtester/tests/maze00.png" "output00.png")
add_test(test00-compare "compare" "C:/Users/richa/OneDrive/Desktop/smashtester/tests/output00.png" "output00.png")
add_test(test01 "pathfinder" "C:/Users/richa/OneDrive/Desktop/smashtester/tests/maze01.png" "output01.png")
add_test(test01-compare "compare" "C:/Users/richa/OneDrive/Desktop/smashtester/tests/output01.png" "output01.png")
add_test(test02 "pathfinder" "C:/Users/richa/OneDrive/Desktop/smashtester/tests/maze02.png" "output02.png")
add_test(test02-compare "compare" "C:/Users/richa/OneDrive/Desktop/smashtester/tests/output02.png" "output02.png")
subdirs("lib")
