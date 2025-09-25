#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

// CAUTION: If you run this code in Windows platform, you may need to change 
// line 81 and line 182 in autograder/autograder.py with adding encoding="utf-8" 
// parameter to open().

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */
  auto spaces = find_all(
    source.begin(), 
    source.end(), 
    [](unsigned char ch) { 
      return std::isspace(ch); 
    }
  );
  auto binary_op = [&source](auto it1, auto it2) {
    return Token{source, it1, it2};
  };

  // "history will absolve me"
  //  ▲      ▲    ▲       ▲  ▲
  //  ├──────┼────┼───────┼──┤
  //  │  t1  │ t2 │   t3  │t4│
  auto first1 = spaces.begin();
  auto last1 = spaces.end() - 1;
  auto first2 = spaces.begin() + 1;

  Corpus tokens;
  std::transform(first1, last1, first2, std::inserter(tokens, tokens.end()), binary_op);
  std::erase_if(
    tokens, 
    [](auto& token) {
      return token.content.empty();
    }
  );
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;

  // Step One: Skip words that are already correctly spelled.
  auto IsMisspelled = [&dictionary](const Token& token) {
    return !dictionary.contains(token.content);
  };

  // Step Two: Find one-edit-away words in the dictionary using Damerau-Levenshtein.
  auto TokenToMisspelling = [&dictionary](const Token& token) {
    auto dist_is_1 = [&token](const std::string& s) {
      return levenshtein(token.content, s) == 1;
    };

    auto view2 = dictionary | rv::filter(dist_is_1);
    std::set<std::string> suggestions(view2.begin(), view2.end());
    return Misspelling{token, suggestions};
  };

  // Step Three: Drop misspellings with no suggestions.
  auto HasSuggestions = [](const Misspelling& m) {
    return !m.suggestions.empty();
  };

  auto view = source 
    | rv::filter(IsMisspelled)
    | rv::transform(TokenToMisspelling)
 // | std::ranges::to<std::set<Misspelling>>()  // C++23
    | rv::filter(HasSuggestions);
  std::set<Misspelling> result(view.begin(), view.end());
  return result;
}

/* Helper methods */

#include "utils.cpp"