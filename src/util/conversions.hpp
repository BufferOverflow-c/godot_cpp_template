#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/char_string.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "core/assert.hpp"

namespace brain::inline utils {
    /** Converts std string types to godot::String at compile time */
    template <typename TStr>
    struct GDStrConv
    {
        explicit constexpr GDStrConv(TStr&& s)
            : m_str{ std::move(s) }
        {
        }

        explicit operator godot::String()
            requires std::same_as<std::string>
        {
            return godot::String(m_str.c_str());
        }

        explicit operator godot::String()
            requires std::same_as<std::string_view>
        {
            return godot::String(m_str.data());
        }

        TStr m_str{};
    };

    /* Can cast between objects in the inheritance chain below a godot::Object */
    template <typename TOut, typename TIn>
        requires std::derived_from<std::remove_cvref_t<TIn>, godot::Object>
    constexpr inline TOut* gdcast(TIn* obj)
    {
        runtime_assert(obj != nullptr);
        auto ret{ godot::Object::cast_to<TOut>(obj) };
        runtime_assert(ret != nullptr);
        return ret;
    }

    template <typename TOut>
    inline auto to(const auto& in) -> TOut
    {
        return TOut(in);
    }

    template <>
    inline auto to(const godot::String& in) -> std::string
    {
        static_assert(std::is_same_v<godot::String, std::remove_cvref_t<decltype(in)>>);
        return std::string(in.ascii().ptr());
    }

    template <>
    inline auto to(const godot::String& in) -> std::string_view
    {
        static_assert(std::is_same_v<godot::String, std::remove_cvref_t<decltype(in)>>);
        return std::string_view(in.ascii().ptr());
    }

    template <>
    inline auto to(const godot::StringName& in) -> std::string
    {
        static_assert(std::is_same_v<godot::StringName, std::remove_cvref_t<decltype(in)>>);
        godot::String tmp(in);
        return std::string(tmp.ascii().ptr());
    }

    template <>
    inline auto to(const godot::StringName& in) -> std::string_view
    {
        static_assert(std::is_same_v<godot::StringName, std::remove_cvref_t<decltype(in)>>);
        godot::String tmp(in);
        return std::string_view(tmp.ascii().ptr());
    }
}
