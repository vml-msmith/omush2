/**
 * \file string.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_
#define OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_

#include <boost/algorithm/string.hpp>
#include <string>

namespace omush {
  namespace library {
    namespace string {
      inline bool iequals(std::string left, std::string right) {
        return boost::iequals(left, right);
      }

      class OString {
      private:
        class ColorSequence {
        public:
          ColorSequence();
          ColorSequence(std::string s, std::size_t iter);
          bool hasEnd();
          void setEnd(std::size_t iter);
          std::string buildTag();
          std::string buildEndTag();
          std::string buildInternalTag();
          std::string buildInternalEndTag();
          std::string sequence;
          std::size_t start;
          std::size_t end;
        };

        struct OStringNode {
          char c;
          bool isSequence;
          bool isEnd;
          ColorSequence seq;

          OStringNode(char c) : c(c), isSequence(false), isEnd(false) {  }
          OStringNode(ColorSequence c) : seq(c), isSequence(true), isEnd(false) {  }
          OStringNode() :  isSequence(false) {  }
        };
       public:
        std::deque<OStringNode*> nodes;
        OString(const OString& other);
        OString& operator=(const OString& other);
        OString& operator+=(const OString& rhs) // compound assignment (does not need to be a member,
          {                           // but often is, to modify the private members)
            /* addition of rhs to *this takes place here */
            for (std::deque<OStringNode*>::const_iterator i = rhs.nodes.begin();
                 i != rhs.nodes.end();
                 ++i) {
              nodes.push_back(new OStringNode());
              nodes.back()->c = (*i)->c;
              nodes.back()->isSequence = (*i)->isSequence;
              nodes.back()->isEnd = (*i)->isEnd;
              nodes.back()->seq = (*i)->seq;
            }

            return *this; // return the result by reference
          }

  // friends defined inside class body are inline and are hidden from non-ADL lookup
        friend OString operator+(OString lhs,       // passing first arg by value helps optimize chained a+b+c
                           const OString& rhs) // alternatively, both parameters may be const references.
        {
          OString o = OString("");
          o.reset();
          for (std::deque<OStringNode*>::const_iterator i = lhs.nodes.begin();
               i != lhs.nodes.end();
               ++i) {
            o.nodes.push_back(new OStringNode());
            o.nodes.back()->c = (*i)->c;
            o.nodes.back()->isSequence = (*i)->isSequence;
            o.nodes.back()->isEnd = (*i)->isEnd;
            o.nodes.back()->seq = (*i)->seq;
          }
          for (std::deque<OStringNode*>::const_iterator i = rhs.nodes.begin();
               i != rhs.nodes.end();
               ++i) {
            o.nodes.push_back(new OStringNode());
            o.nodes.back()->c = (*i)->c;
            o.nodes.back()->isSequence = (*i)->isSequence;
            o.nodes.back()->isEnd = (*i)->isEnd;
            o.nodes.back()->seq = (*i)->seq;
          }

          // return lhs += rhs; // reuse compound assignment and return the result by value
        }

        void reset();
        std::deque<OStringNode*> makeNodeCopy() const;
        ~OString();
        OString(std::string s);
        std::string outString();
        std::string internalString();
        std::string basicString();
        static std::string wrap(std::string str, std::string sequence);
        static std::string color(std::string str, std::string color);
        void to_upper();
      };

    }  // namespace string
    typedef string::OString OString;
  }  // namespace library
}  // namesapce omush

#endif  // OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_
