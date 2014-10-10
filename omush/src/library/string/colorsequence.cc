/**
 * \file colorsequence.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/library/string.h"

namespace omush {
  namespace library {
    namespace string {
      OString::ColorSequence::ColorSequence() {}
      OString::ColorSequence::ColorSequence(std::string s, std::size_t iter) {
        sequence = s;
        start = iter;
        end = std::string::npos;
      }
      bool OString::ColorSequence::hasEnd() {
        if (end == std::string::npos) {
          return false;
        }
        return true;
      }

      void OString::ColorSequence::setEnd(std::size_t iter) {
        end = iter;
      }

      std::string OString::ColorSequence::buildTag() {
        std::vector<std::string> sequence_parts;
        boost::split(sequence_parts, sequence, boost::is_any_of(":"));
        std::vector<std::string> tag;
        tag.push_back("x1lt|span");
        std::string f = sequence_parts[0];
        if (f.compare("class") == 0 &&
            sequence_parts.size() > 1) {
          tag.push_back(" class=x1qt|");
          tag.push_back(sequence_parts[1]);
        }
        else {
          tag.push_back(" style=x1qt|");
          tag.push_back(sequence);
        }

        tag.push_back("x1qt|x1gt|");

        return boost::algorithm::join(tag, "");
      }

      std::string OString::ColorSequence::buildEndTag() {
        return "x1lt|x1bs|spanx1gt|";
      }

      std::string OString::ColorSequence::buildInternalTag() {
        std::vector<std::string> sequence_parts;

        std::vector<std::string> tag;

        tag.push_back("x1b|");
        tag.push_back(sequence);
        tag.push_back("|");

        return boost::algorithm::join(tag, "");
      }


      std::string OString::ColorSequence::buildInternalEndTag() {
        return "x1b|end|";
      }
    }  // namespace string
  }  // namespace library
}  // namespace omush
