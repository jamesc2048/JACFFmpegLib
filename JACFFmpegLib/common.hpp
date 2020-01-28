#ifndef COMMON_HPP
#define COMMON_HPP

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(JACFFMPEGLIB_LIBRARY)
#  define JACFFMPEGLIB_EXPORT Q_DECL_EXPORT
#else
#  define JACFFMPEGLIB_EXPORT Q_DECL_IMPORT
#endif

#include "pch.hpp"
#include "utilities.hpp"

using std::string;
using std::stringstream;
using std::vector;
using std::unique_ptr;
using std::make_unique;

#define THROW_EXCEPTION(what) throw std::runtime_error(what)

#define LOG(message) JACFFmpegLib::Utils::log(message)

#define DISALLOW_COPY(className) className(const className &) = delete; \
                                        className& operator=(const className &) = delete; \

#define DISALLOW_COPY_AND_MOVE(className) DISALLOW_COPY(className) \
                                        className(className &&) = delete; \
                                        className& operator=(className &&) = delete;


#endif // COMMON_HPP
