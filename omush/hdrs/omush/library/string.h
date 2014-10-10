/**
 * \file string.h
 *
 * Copyright 2014 Michael Smith
 */

#ifndef OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_
#define OMUSH_HDRS_OMUSH_LIBRARY_STRING_H_

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

namespace omush {
  namespace library {
    namespace string {
      class OString;
      std::string &ltrim(std::string &s, const std::string &chars);
      std::string &rtrim(std::string &s, const std::string &chars);
      std::string &trim(std::string &s, const std::string &chars);

      inline OString &ltrim(OString &s, const std::string &chars);
      inline OString &rtrim(OString &s, const std::string &chars);
      inline OString &trim(OString &s, const std::string &chars);

      void to_upper(std::string &str);
      void to_lower(std::string &str);
      bool iequals(std::string left, std::string right);
      void replace_all(std::string &in,
                       std::string search,
                       std::string replace);

      enum SplitStringOptions {
        leftToRight,
        rightToLeft,
      };

      inline std::vector<std::string> splitIntoSegments(std::string str,
                                                        std::string sep,
                                                        int segments,
                                                        SplitStringOptions direction) {
        if (segments < 0) {
          segments = 1000;
        }

        std::vector<std::string> result;
        int i = 0;
        std::size_t pos;
        if (direction == leftToRight) {
          pos = str.find(sep);
        }
        else {
          pos = str.rfind(sep);
        }

        while (i < (segments - 1) && pos != std::string::npos) {
          result.push_back(str.substr(0,pos));
          str = str.substr(pos + 1, str.length() - pos + 1);

          if (direction == leftToRight) {
            pos = str.find(sep);
          }
          else {
            pos = str.rfind(sep);
          }

          ++i;
        }

        result.push_back(str);
        /*
          if (direction == rightToLeft) {
          std::vector<std::string> newResult;
          for (int i = result.size() - 1; i >= 0; --i) {
          newResult.push_back(result[i]);
          }
          return newResult;
          }*/
        return result;
      }

      inline std::vector<std::string> splitIntoSegments(std::string str,
                                                        std::string sep,
                                                        int segments) {
        return splitIntoSegments(str, sep, segments, leftToRight);
      }

      inline std::vector<std::string> splitIntoSegments(std::string str,
                                                        std::string sep) {
        return  splitIntoSegments(str, sep, -1);
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
        void rtrim(const std::string chars);
        void ltrim(const std::string chars);
        void trim(const std::string chars);

        std::deque<OStringNode*> nodes;
        OString() {}
        OString(const OString& other);
        OString& operator=(const OString& other);
        OString& operator=(const std::string& other);
        OString& operator+=(const std::string& rhs);
        OString& operator+=(const OString& rhs);

        // friends defined inside class body are inline and are hidden from non-ADL lookup
        friend OString operator+(OString lhs, const OString& rhs) {
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

          return o;
        }

        friend OString operator+(OString lhs, const std::string& rhs) {
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

          OString r = OString(rhs);
          for (std::deque<OStringNode*>::const_iterator i = r.nodes.begin();
               i != r.nodes.end();
               ++i) {
            o.nodes.push_back(new OStringNode());
            o.nodes.back()->c = (*i)->c;
            o.nodes.back()->isSequence = (*i)->isSequence;
            o.nodes.back()->isEnd = (*i)->isEnd;
            o.nodes.back()->seq = (*i)->seq;
          }
          return o;
        }

        void reset();
        std::deque<OStringNode*> makeNodeCopy() const;
        ~OString();
        OString(const std::string s);
        std::string outString();
        std::string internalString();
        std::string plainText();
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
