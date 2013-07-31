# What is wheels?

Wheels is just a library where I collect stuff I think I can reuse.

*Note: this is a cleaned up version of the [old repo].*

[![Build Status](https://travis-ci.org/rmartinho/wheels.png?branch=master)](https://travis-ci.org/rmartinho/wheels)

# Compilers

Many compilers currently support only a small subset of the interesting C++
features. Wheels targets GCC 4.8 as the compiler of choice.
There are no plans to support any older compilers, or compilers with less
support for C++ features.

# Dependencies

Boost 1.53 is required. It may work with older versions, but I don't plan on
supporting them.

# Usage

Wheels is header-only: you can drop the header files somewhere and `#include`
them.

# Documentation

Documentation is forthcoming. For now the best documentation is the tests and
the comments in the code.

# Feedback

You can suggest improvements or report bugs in the [issue tracker]

# Thanks

Special thanks go to the folks in the [Lounge<C++>][lounge].

 [lounge]: http://chat.stackoverflow.com/rooms/10
 [old repo]: https://bitbucket.org/martinhofernandes/wheels
 [issue tracker]: http://bugs.flamingdangerzone.com/youtrack/issues?q=project%3A+Wheels

