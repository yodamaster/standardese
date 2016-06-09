// Copyright (C) 2016 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#ifndef STANDARDESE_ERROR_HPP_INCLUDED
#define STANDARDESE_ERROR_HPP_INCLUDED

#include <stdexcept>

#include <clang-c/Index.h>

#include <standardese/noexcept.hpp>

namespace standardese
{
    struct cpp_cursor;

    class libclang_error
    : public std::runtime_error
    {
    public:
        libclang_error(CXErrorCode error, std::string type);

        CXErrorCode error_code() const STANDARDESE_NOEXCEPT
        {
            return error_;
        }

    private:
        CXErrorCode error_;
    };

    struct source_location
    {
        std::string entity_name, file_name;
        unsigned line;

        source_location(std::string entity, std::string file, unsigned line)
        : entity_name(std::move(entity)), file_name(std::move(file)), line(line)
        {}

        source_location(CXSourceLocation location, std::string entity);

        explicit source_location(cpp_cursor cur);
    };

    enum class severity
    {
        warning,
        error
    };

    class parse_error
    : public std::runtime_error
    {
    public:
        parse_error(source_location location, std::string message, severity sev = severity::error)
        : std::runtime_error(std::move(message)),
          location_(std::move(location)), severity_(sev)
        {}

        const source_location& get_location() const STANDARDESE_NOEXCEPT
        {
           return location_;
        }

        severity get_severity() const STANDARDESE_NOEXCEPT
        {
            return severity_;
        }

    private:
        source_location location_;
        severity severity_;
    };
} // namespace standardese

#endif // STANDARDESE_ERROR_HPP_INCLUDED
