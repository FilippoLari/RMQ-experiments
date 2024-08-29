#pragma once

template<typename... Types>
struct TypeList {};

template<typename TypeList, typename Func>
struct ForEach;

template<typename Head, typename... Tail, typename Func>
struct ForEach<TypeList<Head, Tail...>, Func> {
    static void apply(Func func) {
        func.template operator()<Head>();
        ForEach<TypeList<Tail...>, Func>::apply(func);
    }
};

template<typename Func>
struct ForEach<TypeList<>, Func> {
    static void apply(Func) {
        // Base case: do nothing
    }
};