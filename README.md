# About
This is a simple C / C++ unit testing framework with no non-standard deps. You 
can use it in your EECS projects, assuming of course that doing so does not 
violate the code use, or honor code restrictions, by which you MUST abide.

# Usage
First, clone the framework into your project folder:

    git clone https://github.com/michiganhackers/unit-test-framework.git

If you want to have a folder specifically for tests, run `mkdir tests` on the root level of your project and add a test file:

    #include "../unit-test-framework/unit_test_framework.h"
    
    int main(int argc, char const *argv[])
    {
      // Describe the suite of tests to be run.
        start_suite("Start test suite:");
        
      // Run some tests.
	    if( assertEqual(1, 1) )
		    test_passed("1 is equal to 1!");
	    else
		    test_failed("1 is not equal to one.");
        
      // End the suite
	    end_suite();
	    return 0;
    }
    
Compile at the project's root folder:

    g++ tests/test.cpp -o test unit-test-framework/unit_test_framework.c

Run your test suite:

    ./test
    
That's it!

# Contributors
We (I) would love to get feedback on this, either via issue submissions, or via
pull-requests. If you submit a pull-request, be sure to add your name to this 
list. 

+ Max Seiden <140dbs@gmail.com>
+ Ryan Gonzalez <ryan@ionizedmedia.com>

# License
Copyright (C) 2012 Max Seiden <140dbs@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
