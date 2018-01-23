# CRDT

C++11 header-only [CRDT](https://hal.inria.fr/inria-00555588/document) library.

## Status

This library is under active development and **NOT PRODUCTION READY**.

## G-Counter

```c++
auto a = crdt::GCounter<std::string, int>("a");
a.increment();

auto b = crdt::GCounter<std::string, int>("b", 3);
b.increment();

auto c = a.merge("c", b);

std::cout << c.value(); // prints 5
```

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/cdolan/crdt. This project is intended to be a safe, welcoming
space for collaboration, and contributors are expected to adhere to the
[Contributor Covenant](http://contributor-covenant.org) code of conduct.


## License

The gem is available as open source under the terms of the
[MIT License](http://opensource.org/licenses/MIT).
