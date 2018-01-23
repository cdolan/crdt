CXXFLAGS = -std=c++11 -pipe
TESTS = t/test_gcounter

.PHONY: all
all: test

.PHONY: test
test: $(TESTS)
	$(foreach testrunner, $(TESTS), ./$(testrunner))

t/%: t/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(TESTS)
