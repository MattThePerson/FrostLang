#include "Lexer.hpp"

#include <iostream>
#include <unordered_set>
#include <vector>

std::string ESCAPE_SEQUENCES{'\0', '\n', '\r', '\t', '\b', '\f', '\v', '\a'};
std::string ESCAPE_SEQUENCE_CHARS = "0nrtbfva";

std::string SINGLE_CHAR_TOKENS = "<>(){}=[];:,.\"+-/*";

std::unordered_set<std::string> TYPE_TOKENS = {
    "ind",   "in8", "in16", "in32", "in64", "uind", "uin8", "uin16", "uin32",
    "uin64", "fld", "fl8",  "fl16", "fl32", "fl64", "vd",   "chr"};

/*
 * tokenize_stream - Apply lexing to stream of code, extracting and returning a
 * list of tokens.
 */
std::vector<std::string> tokenize(std::istream &stream) {

    std::vector<std::string> token_vect;
    std::string buffer;
    char ch;

    // 'value' token, eg. occuring between '=' and ';'
    // bool reading_value = false;
    bool quotes_open = false;
    bool special_char_flag = false;

    // read stream one char at a time
    while (stream.get(ch)) {

        // detect quotes state change
        if (ch == '"' && !special_char_flag) {
            if (quotes_open) { // they were open
                token_vect.push_back(buffer);
                buffer.clear();
            }
            quotes_open = !quotes_open;
            token_vect.push_back(std::string(1, '"'));
            continue;
        }

        // handle strings
        if (quotes_open) {
            if (ch == '\\' && !special_char_flag) {
                special_char_flag = true;
                continue;
            } else if (special_char_flag) {
                special_char_flag = false;
                if (ch == '"' || ch == '\\' || ch == '\'' || ch == '?') {
                    buffer.push_back(ch);
                }
                if (ESCAPE_SEQUENCE_CHARS.find(ch) != std::string::npos) {
                    token_vect.push_back(buffer);
                    buffer.clear();
                    token_vect.push_back(std::string{'\\', ch});
                }
                continue;
            }
            buffer.push_back(ch);
            continue;
        }

        // SPECIAL CASE: all spaces are ignored unless ocurring between type
        // and variable name, where they indicate token completion
        if (ch == ' ') {
            if (TYPE_TOKENS.count(buffer) || buffer == "return") {
                token_vect.push_back(buffer);
                buffer.clear();
            }
            continue;
        }

        // ignore char
        if (ESCAPE_SEQUENCES.find(ch) != std::string::npos) {
            continue;
        }

        // single token char
        if (SINGLE_CHAR_TOKENS.find(ch) != std::string::npos) {
            if (!buffer.empty()) {
                token_vect.push_back(buffer);
                buffer.clear();
            }
            token_vect.push_back(std::string(1, ch));
        } else {
            buffer.push_back(ch);
        }
    }

    // add final token
    if (!buffer.empty()) {
        token_vect.push_back(buffer);
    }

    // exception_handling
    if (quotes_open) {
        std::cerr << "LEXING_ERROR: quotes not closed\n";
        exit(1);
    }

    return token_vect;
}
