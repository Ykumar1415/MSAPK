/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mxlwriter.h"

#include "io/buffer.h"

#include "musicxml/exportxml.h"

#include "log.h"

using namespace mu::iex::musicxml;
using namespace mu::io;

mu::Ret MxlWriter::write(notation::INotationPtr notation, QIODevice& destinationDevice, const Options&)
{
    IF_ASSERT_FAILED(notation) {
        return make_ret(Ret::Code::UnknownError);
    }
    mu::engraving::Score* score = notation->elements()->msScore();

    IF_ASSERT_FAILED(score) {
        return make_ret(Ret::Code::UnknownError);
    }

    io::Buffer buf;
    Ret ret = mu::engraving::saveMxl(score, &buf);
    if (ret) {
        destinationDevice.write(buf.data().toQByteArrayNoCopy());
    }

    return ret;
}
