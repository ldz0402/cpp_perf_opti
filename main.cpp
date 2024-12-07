#include <ctime>
#include <iomanip>
#include <iostream>

#include "utils.h"

using namespace std;
using namespace utils;

// original, naive remove_ctrl()
std::string remove_ctrl(std::string s) {
  std::string result;
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] >= 0x20) {
      result = result + s[i];
    }
  }
  return result;
}

// remove_ctrl() with operator replaced by mutating assignment
std::string remove_ctrl_mutating(std::string s) {
  std::string result;
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] >= 0x20) {
      result += s[i];
    }
  }
  return result;
}

// remove_ctrl_mutating() with space reserved in result
std::string remove_ctrl_reserve(std::string s) {
  std::string result;
  result.reserve(s.length());
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] >= 0x20) {
      result += s[i];
    }
  }
  return result;
}

// remove_ctrl_reserve() with reference arg instead of value arg
std::string remove_ctrl_refs(std::string const& s) {
  std::string result;
  result.reserve(s.length());
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] >= 0x20) {
      result += s[i];
    }
  }
  return result;
}

// remove_ctrl_reserve() with reference arg instead of value arg
std::string remove_ctrl_refs_it(std::string const& s) {
  std::string result;
  result.reserve(s.length());
  for (auto it = s.begin(), end = s.end(); it != end; ++it) {
    if (*it >= 0x20) {
      result += *it;
    }
  }
  return result;
}

// remove_ctrl_ref_ret with iterators
void remove_ctrl_ref_result_it(std::string& result, std::string const& s) {
  result.clear();
  result.reserve(s.length());
  for (auto it = s.begin(), end = s.end(); it != end; ++it) {
    if (*it >= 0x20) {
      result += *it;
    }
  }
}

// remove_ctrl_ref_result() done with buffers instead of strings
void remove_ctrl_cstrings(char* destp, char const* sourcep, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    if (sourcep[i] >= 0x20) {
      *destp++ = sourcep[i];
    }
  }
  *destp = 0;
}

string str =
    "fgeifhuwiohfisoejdifjoehfancuihfrioefjeiuhguiahfksjdafharuhfoisjfisaghgtgt"
    "eoihuigfrjfiefohrghrefhduriefhreiojfeiohfgjighqferijfioeqjfgqupgqufrqggtgt"
    "4g56eq7gfv8qe46rg8tq7g684dedefrwgtwrgtwgtgrgtg8qr7gf8qrefvquehfgviuhvguhgu"
    "ithgiurejgioerwjgitwhgorjfiuwhguifvgntuiwhgoufvsgnlvnknlwgjtriwqotq5801fji"
    "rog";

string result = "";

#define TestDriver(func, count, args...)                \
  {                                                     \
    for (int i = 0; i < count; ++i) {                   \
      func(args);                                       \
    }                                                   \
    timeSum += double(clock() - time) / CLOCKS_PER_SEC; \
    time = clock();                                     \
  }

#define TestDrivers(_count, func, count, args...)                    \
  {                                                                  \
    double timeSum = 0;                                              \
    for (int p = 0; p < _count; ++p) {                               \
      TestDriver(func, count, args);                                 \
    }                                                                \
    cout << "\nAverage Running time is: " << setiosflags(ios::fixed) \
         << setprecision(6) << setiosflags(ios::right) << setw(8)    \
         << timeSum / _count << " s!\n";                             \
  }

#define COUNT 100000
#define _COUNT 10

int main(int argc, char** argv) {
  time_t time = clock();
  TestDrivers(_COUNT, remove_ctrl, COUNT, str);
  TestDrivers(_COUNT, remove_ctrl_mutating, COUNT, str);
  TestDrivers(_COUNT, remove_ctrl_reserve, COUNT, str);
  TestDrivers(_COUNT, remove_ctrl_refs, COUNT, str);
  TestDrivers(_COUNT, remove_ctrl_refs_it, COUNT, str);
  TestDrivers(_COUNT, remove_ctrl_ref_result_it, COUNT, result, str);

  char ch_result[1000];
  TestDrivers(_COUNT, remove_ctrl_cstrings, COUNT, ch_result, str.c_str(),
              str.length());

  return 0;
}
