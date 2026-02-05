#include "Lexer.hpp"

#include <iostream>
#include <unordered_set>
#include <vector>

/*
 * tokenize_stream - Apply lexing to stream of code, extracting and returning a
 * list of tokens.
 */
std::vector<std::string> tokenize(std::istream &stream) {

    std::string ignore_chars = "\n\0\r\t";
    std::string single_token_chars = "<>(){}=[];:,.\"+-/*";
    std::unordered_set<std::string> type_tokens = {"uind", "ind"};

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
                if (ch != '"' && ch != '\\') {
                    buffer.push_back('\\');
                }
            }
            buffer.push_back(ch);
            continue;
        }

        // SPECIAL CASE: all spaces are ignored unless ocurring between type
        // and variable name, where they indicate token completion
        if (ch == ' ') {
            if (type_tokens.count(buffer) || buffer == "return") {
                token_vect.push_back(buffer);
                buffer.clear();
            }
            continue;
        }

        // ignore char
        if (ignore_chars.find(ch) != std::string::npos) {
            continue;
        }

        // single token char
        if (single_token_chars.find(ch) != std::string::npos) {
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
