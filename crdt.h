/* MIT License
 *
 * Copyright (c) 2018 Christopher Dolan <chris@codinstream.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef CODINGSTREAM_CRDT_H
#define CODINGSTREAM_CRDT_H

#include <algorithm>
#include <numeric>
#include <unordered_map>

namespace crdt {

template <class Key, class T, class Map = std::unordered_map<Key, T>>
class GCounter {
 public:
  static_assert(std::is_integral<T>::value, "type T must be integral type");

  GCounter(Key id) : GCounter(id, 0) {}
  GCounter(Key id, T value) : id_(id) { counter_[id] = value; }

  Key id() const noexcept { return id_; }

  T value() const noexcept {
    return std::accumulate(counter_.begin(), counter_.end(), 0,
                           [](const T& acc, const std::pair<Key, T>& kv) {
                             return acc + kv.second;
                           });
  }

  void increment(T delta = 1) noexcept { counter_.at(id_) += delta; }

  bool equal(const GCounter<Key, T>& other) const noexcept {
    if (counter_.size() != other.counter_.size())
      return false;

    for (auto& kv : counter_) {
      auto id = kv.first;
      auto value = kv.second;

      auto result = other.counter_.find(id);
      if (result == other.counter_.end())
        return false;

      if (value != result->second)
        return false;
    }

    return true;
  }

  GCounter<Key, T> merge(Key id, const GCounter<Key, T>& other) {
    auto c = *this;

    c.id_ = id;

    for (auto& kv : other.counter_) {
      auto id = kv.first;
      auto value = std::max(kv.second, other.counter_.at(id));
      c.counter_[id] = value;
    }

    return c;
  }

 private:
  Key id_;
  Map counter_;
};

}  // namespace crdt

#endif  // CODINGSTREAM_CRDT_H
