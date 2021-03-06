//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/30/17 Carlos Brito
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
 * @file NFA.cpp
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17
 *
 * # Description
 * This is the .cpp file which contains the implementation for all the methods declared in the header file Transition.h
 *
 * # TODO
 * Nothing for the moment.
 */
//</editor-fold>

#include <string>

#include "State.h"

namespace Automata {

    Transition::Transition(State *source, State *destination, char symbol)
            : source_(source),
              destination_(destination),
              symbol_(symbol),
              source_name_(source->name()),
              destination_name_(source->name())
    {
    }

    char Transition::symbol() const {
        return symbol_;
    }

    State *Transition::source() const {
        return source_;
    }

    State *Transition::destination() const {
        return destination_;
    }

    Transition::~Transition() {
//        delete source_;
//        delete destination_;
    }

    std::ostream &operator<<(std::ostream &os, const State &obj) {
        return os << obj.name();
    }
}