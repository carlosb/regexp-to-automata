//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/23/17 Carlos Brito
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.*
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

//<editor-fold desc="Description">
/**
 * @file TokenDecls.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17
 *
 * # Description
 * This file contains the declaration of tokens and token tags.
 *
 * - We have instanced some of the fixed tokens which we already
 * know will appear like LPAREN and KLEENE_STAR.
 *
 * - We have instanced token tags which will aid in creating new tokens.
 *
 * # TODO
 * Nothing for the moment.
 */
//</editor-fold>

#ifndef MYREGEX_REGEXPTOKENS_H
#define MYREGEX_REGEXPTOKENS_H

#include "Token.h"

namespace Regexp {

/// This type aids in defining the ids for the Token Tags
/**
 * In order to get unique ids, we use an enum structure to assign
 * each of the tokens an id.
 */
enum {
    TOK_EOF = -1,
    TOK_NONE = 0,

    TOK_LPAREN,
    TOK_RPAREN,
    TOK_KLEENE,
    TOK_ALTER,
    TOK_CONCAT,
    TOK_QMARK,

    TOK_CHAR,
    TOK_ESCAPE_SEQUENCE
};

// Declare token tags
    //! Tag for left parentheses.
    static const Regexp::Token::Tag TAG_LPAREN(TOK_LPAREN, "left parentheses");

    //! Tag for right parentheses.
    static const Regexp::Token::Tag TAG_RPAREN(TOK_RPAREN, "right parentheses");

    //! Tag for Kleene Star operator.
    static const Regexp::Token::Tag TAG_KLEENE_STAR(TOK_KLEENE, "kleene star");

    //! Tag for Alternation operator.
    static const Regexp::Token::Tag TAG_ALTER(TOK_ALTER, "alternation");

    //! Tag for Concatenation operator.
    static const Regexp::Token::Tag TAG_CONCAT(TOK_CONCAT, "concatenation");

    //! Tag for Question mark symbol. Also known as, the optional operator.
    static const Regexp::Token::Tag TAG_QMARK(TOK_QMARK, "question mark");

    //! Tag for an escape sequence.
    static const Regexp::Token::Tag TAG_ESCAPE_SEQUENCE(TOK_ESCAPE_SEQUENCE, "escape sequence");

    //! Tag for a character.
    static const Regexp::Token::Tag TAG_CHAR(TOK_CHAR, "character");

    //! Tag for eof.
    static const Regexp::Token::Tag TAG_EOF(TOK_EOF, "eof");

    //! Tag for "no-tag".
    static const Regexp::Token::Tag TAG_NONE(TOK_NONE, "");


    // Declare the operator tokens
    //! Token type for left parentheses.
    static const Regexp::Token LPAREN(TAG_LPAREN, "(");

    //! Token type for right parentheses.
    static const Regexp::Token RPAREN(TAG_RPAREN, ")");

    //! Token type for Kleene Star.
    static const Regexp::Token KLEENE_STAR(TAG_KLEENE_STAR, "*");

    //! Token type for Alternation.
    static const Regexp::Token ALTER(TAG_ALTER, "|");

    //! Token type for Concatenation.
    static const Regexp::Token CONCAT(TAG_CONCAT, "&");

    //!
    static const Regexp::Token QMARK(TAG_QMARK, "?");
    static const Regexp::Token T_EOF(TAG_EOF, "eof");
    static const Regexp::Token NONE(TAG_NONE, "");

}

#endif //MYREGEX_REGEXPTOKENS_H
