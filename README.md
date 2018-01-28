# CRDT
[![Build Status](https://travis-ci.org/cdolan/crdt.svg?branch=master)](https://travis-ci.org/cdolan/crdt)

C++11 header-only [CRDT](https://hal.inria.fr/inria-00555588/document) library.

## Status

This library is under active development and **NOT PRODUCTION READY**.

## G-Counter

```c++
auto a = crdt::GCounter<std::string, unsigned int>("a");    // initializes counter to 0
a.increment();                                              // increment by 1

auto b = crdt::GCounter<std::string, unsigned int>("b", 3); // initializes counter to 3
b.increment(5);                                             // increment by 5

auto c = a.merge("c", b);                                   // join counters a and b

std::cout << c.value();                                     // prints 9
```

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/cdolan/crdt. This project is intended to be a safe, welcoming
space for collaboration, and contributors are expected to adhere to the
[Contributor Covenant](http://contributor-covenant.org) code of conduct.


## License

The gem is available as open source under the terms of the
[MIT License](http://opensource.org/licenses/MIT).
