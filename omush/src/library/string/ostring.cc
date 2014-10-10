/**
 * \file ostring.cc
 *
 * Copyright 2014 Michael Smith
 */

#include "omush/library/string.h"

namespace omush {
  namespace library {
    namespace string {
      OString::OString(const OString& other) {
        reset();
        for (std::deque<OStringNode*>::const_iterator i = other.nodes.begin();
             i != other.nodes.end();
             ++i) {
          nodes.push_back(new OStringNode());
          nodes.back()->c = (*i)->c;
          nodes.back()->isSequence = (*i)->isSequence;
          nodes.back()->isEnd = (*i)->isEnd;
          nodes.back()->seq = (*i)->seq;
        }
      }

      OString& OString::operator=(const OString& other) {
        //    nodes = other.makeNodeCopy();
        reset();
        for (std::deque<OStringNode*>::const_iterator i = other.nodes.begin();
             i != other.nodes.end();
             ++i) {
          nodes.push_back(new OStringNode());
          nodes.back()->c = (*i)->c;
          nodes.back()->isSequence = (*i)->isSequence;
          nodes.back()->isEnd = (*i)->isEnd;
          nodes.back()->seq = (*i)->seq;
        }

        return *this;
      }

      void OString::reset() {
        while (!nodes.empty()) {
          delete nodes.front();
          nodes.pop_front();
        }
      }

      OString::~OString() {
        reset();
      }

      OString::OString(const std::string s) {
        std::deque<ColorSequence> sequences;
        std::string myString = s;
        while (true) {
          std::size_t start = myString.find("x1b|");

          if (start == std::string::npos)
            break;

          std::size_t end = myString.find("|", start + 4);
          for (int i = 0; i < start; ++i) {
            OStringNode* n = new OStringNode(myString.c_str()[i]);
            nodes.push_back(n);
          }

          std::string sequence = myString.substr(start + 4, end - start - 4);

          if (sequence.compare("end") == 0) {
            std::deque<OStringNode*> sQ;
            OStringNode *last;

            while (true) {
              last = nodes.back();
              nodes.pop_back();
              sQ.push_back(last);
              if (last->isSequence && !last->seq.hasEnd()) {
                break;
              }
            }
            sQ.back()->seq.setEnd(start);
            while (!sQ.empty()) {
              nodes.push_back(sQ.back());
              sQ.pop_back();
            }

            nodes.push_back(new OStringNode(ColorSequence(sequence, start)));
            nodes.back()->isEnd = true;
          } else {
            nodes.push_back(new OStringNode(ColorSequence(sequence, start)));
          }

          myString = std::string(myString.substr(end + 1, myString.size()));
        }

        for (int i = 0; i < myString.length(); ++i) {
          OStringNode* n = new OStringNode(myString.c_str()[i]);
          nodes.push_back(n);
        }

      }

      std::string OString::outString() {
        printf("Inside.\n");
        std::string str;
        for (int i = 0; i < nodes.size(); ++i) {

          if (nodes.front()->isEnd) {
            str += nodes.front()->seq.buildEndTag();
          }
          else if (nodes.front()->isSequence) {
            str += nodes.front()->seq.buildTag();
          }
          else
            str += nodes.front()->c;


          nodes.push_back(nodes.front());
          nodes.pop_front();
        }

        return str;
      }

      std::string OString::internalString() {
        std::string str;

        for (int i = 0; i < nodes.size(); ++i) {
          if (nodes.front()->isEnd) {
            str += nodes.front()->seq.buildInternalEndTag();
          }
          else if (nodes.front()->isSequence) {
            str += nodes.front()->seq.buildInternalTag();
          }
          else {
            str += nodes.front()->c;
          }


          nodes.push_back(nodes.front());
          nodes.pop_front();
        }
        return str;
      }

      std::string OString::plainText() {
        std::string str;

        for (int i = 0; i < nodes.size(); ++i) {
          if (nodes.front()->isEnd) {
            //            str += nodes.front()->seq.buildInternalEndTag();
          }
          else if (nodes.front()->isSequence) {
            //            str += nodes.front()->seq.buildInternalTag();
          }
          else {
            str += nodes.front()->c;
          }

          nodes.push_back(nodes.front());
          nodes.pop_front();
        }

        return str;
      }


      std::string OString::wrap(std::string str, std::string sequence) {
        return "x1b|" + sequence + "|" +  str + "x1b|end|";
      }

      std::string OString::color(std::string str, std::string color) {
        color[0] = std::toupper(color[0]);
        color = "ansi" + color;
        return OString::wrap(str, "class:" + color);
      }


      OString& OString::operator=(const std::string& other) {
        reset();

        OString o(other);
        for (std::deque<OStringNode*>::const_iterator i = o.nodes.begin();
             i != o.nodes.end();
             ++i) {
          nodes.push_back(new OStringNode());
          nodes.back()->c = (*i)->c;
          nodes.back()->isSequence = (*i)->isSequence;
          nodes.back()->isEnd = (*i)->isEnd;
          nodes.back()->seq = (*i)->seq;
        }

        return *this;
      }

      OString& OString::operator+=(const std::string& rhs) {
        OString o(rhs);
        for (std::deque<OStringNode*>::const_iterator i = o.nodes.begin();
             i != o.nodes.end();
             ++i) {
          nodes.push_back(new OStringNode());
          nodes.back()->c = (*i)->c;
          nodes.back()->isSequence = (*i)->isSequence;
          nodes.back()->isEnd = (*i)->isEnd;
          nodes.back()->seq = (*i)->seq;
        }

        return *this; // return the result by reference
      }

      OString& OString::operator+=(const OString& rhs) {
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

      void OString::ltrim(const std::string chars) {
      }
      void OString::rtrim(const std::string chars) {
      }
      void OString::trim(const std::string chars) {
      }
    }  // namespace string
  }  // namespace library
}  // namespace omush
