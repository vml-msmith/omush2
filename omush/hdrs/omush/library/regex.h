/**
 * \file regex.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_LIBRARY_REGEX_H_
#define OMUSH_HDRS_OMUSH_LIBRARY_REGEX_H_

#include <regex>

namespace omush {
  namespace library {
    std::string parseRegexErrorCode(std::regex_constants::error_type etype) {
      using namespace std;
      switch (etype) {
       case regex_constants::error_collate:
         return "error_collate: invalid collating element request";
      case regex_constants::error_ctype:
        return "error_ctype: invalid character class";
      case regex_constants::error_escape:
        return "error_escape: invalid escape character or trailing escape";
      case regex_constants::error_backref:
        return "error_backref: invalid back reference";
      case regex_constants::error_brack:
        return "error_brack: mismatched bracket([ or ])";
      case regex_constants::error_paren:
        return "error_paren: mismatched parentheses(( or ))";
      case regex_constants::error_brace:
        return "error_brace: mismatched brace({ or })";
      case regex_constants::error_badbrace:
        return "error_badbrace: invalid range inside a { }";
      case regex_constants::error_range:
        return "erro_range: invalid character range(e.g., [z-a])";
      case regex_constants::error_space:
        return "error_space: insufficient memory to handle this regular expression";
      case regex_constants::error_badrepeat:
        return "error_badrepeat: a repetition character (*, ?, +, or {) was not preceded by a valid regular expression";
      case regex_constants::error_complexity:
        return "error_complexity: the requested match is too complex";
      case regex_constants::error_stack:
        return "error_stack: insufficient memory to evaluate a match";
      default:
        return "";
      }
    }
  }  // namespace library
}  // namespace omush

#endif  // OMUSH_HDRS_OMUSH_LIBRARY_REGEX_H_
