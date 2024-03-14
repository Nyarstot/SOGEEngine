/******************************************************************************************
*    Chili Direct3D Engine                                                                *
*    Copyright 2018 PlanetChili <http://www.planetchili.net>                              *
*                                                                                         *
*    This file is part of Chili Direct3D Engine.                                          *
*                                                                                         *
*    Chili Direct3D Engine is free software: you can redistribute it and/or modify        *
*    it under the terms of the GNU General Public License as published by                 *
*    the Free Software Foundation, either version 3 of the License, or                    *
*    (at your option) any later version.                                                  *
*                                                                                         *
*    The Chili Direct3D Engine is distributed in the hope that it will be useful,         *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of                       *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                        *
*    GNU General Public License for more details.                                         *
*                                                                                         *
*    You should have received a copy of the GNU General Public License                    *
*    along with The Chili Direct3D Engine.  If not, see <http://www.gnu.org/licenses/>.   *
******************************************************************************************/

#include "sogepch.hpp"
#include "SOGE/DebugSystem/Exception.hpp"

namespace soge
{
    Exception::Exception(int aLine, const char* aFile) noexcept
        : mLine(aLine), mFile(aFile)
    {

    }

    const char* Exception::GetType() const noexcept
    {
        return "Engine Exception";
    }

    int Exception::GetLine() const noexcept
    {
        return mLine;
    }

    const std::string& Exception::GetFile() const noexcept
    {
        return mFile;
    }

    std::string Exception::GetOriginString() const noexcept
    {
        std::ostringstream oss;
        oss << "[FILE] " << mFile << std::endl
            << "[LINE] " << mLine << std::endl;

        return oss.str();
    }

    const char* Exception::what() const noexcept
    {
        std::ostringstream oss;
        oss << this->GetType() << std::endl
            << this->GetOriginString();

        mWhatBuffer = oss.str();
        return mWhatBuffer.c_str();
    }

}