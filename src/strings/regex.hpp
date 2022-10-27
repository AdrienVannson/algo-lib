#ifndef REGEX_HPP
#define REGEX_HPP

#include <cassert>
#include <ostream>

template<class T>
class Regex;

template<class T>
std::ostream &operator<<(std::ostream &, const Regex<T> &);

template<class T>
bool operator==(const Regex<T> &, const Regex<T> &);

template<class T>
class Regex
{
public:
    enum Type
    {
        EMPTY_SET,
        EMPTY_STRING, // Epsilon
        CHARACTER,
        CONCATENATION,
        ALTERNATION, // Union
        KLEEN_STAR
    };

    Regex() : m_type(EMPTY_SET), m_regex1(0), m_regex2(0) {}

    Regex(const Regex &r) : m_type(r.m_type)
    {
        if (r.m_regex1) {
            m_regex1 = new Regex(*r.m_regex1);
        }
        if (r.m_regex2) {
            m_regex2 = new Regex(*r.m_regex2);
        }
    }

    ~Regex()
    {
        delete m_regex1;
        delete m_regex2;
    }

    // Static constructors
    static inline Regex *emptySet()
    {
        Regex *regex = new Regex;
        regex->m_type = EMPTY_SET;
        return regex;
    }

    static inline Regex *emptyString()
    {
        Regex *regex = new Regex;
        regex->m_type = EMPTY_STRING;
        return regex;
    }

    static inline Regex *character(const T c)
    {
        Regex *regex = new Regex;
        regex->m_type = CHARACTER;
        regex->m_character = c;
        return regex;
    }

    static inline Regex *concatenation(Regex *a, Regex *b)
    {
        Regex *regex = new Regex;
        regex->m_type = CONCATENATION;
        regex->m_regex1 = a;
        regex->m_regex2 = b;
        return regex;
    }

    static inline Regex *alternation(Regex *a, Regex *b)
    {
        Regex *regex = new Regex;
        regex->m_type = ALTERNATION;
        regex->m_regex1 = a;
        regex->m_regex2 = b;
        return regex;
    }

    static inline Regex *kleenStar(Regex *r)
    {
        Regex *regex = new Regex;
        regex->m_type = KLEEN_STAR;
        regex->m_regex1 = r;
        return regex;
    }

    // Getters
    inline Type type() const
    {
        return m_type;
    }

    inline Regex *regex1() const
    {
        assert(
            m_type == CONCATENATION || m_type == ALTERNATION
            || m_type == KLEEN_STAR
        );
        return m_regex1;
    }

    inline Regex *regex2() const
    {
        assert(m_type == CONCATENATION || m_type == ALTERNATION);
        return m_regex2;
    }

    inline T character() const
    {
        assert(m_type == CHARACTER);
        return m_character;
    }

    template<class U>
    friend class Regex;
    friend bool operator==<T>(const Regex<T> &, const Regex<T> &);
    friend std::ostream &operator<< <T>(std::ostream &, const Regex<T> &);

private:
    std::pair<Regex<std::pair<T, int>> *, int> linearised(const int i) const;

    Type m_type;
    Regex *m_regex1;
    Regex *m_regex2;
    T m_character;
};

using Reg = Regex<char>;

template<class T>
std::ostream &operator<<(std::ostream &s, const Regex<T> &r)
{
    if (r.m_type == Regex<T>::EMPTY_SET) {
        s << "∅";
    }
    if (r.m_type == Regex<T>::EMPTY_STRING) {
        s << "ε";
    }
    if (r.m_type == Regex<T>::CHARACTER) {
        s << r.m_character.first;
    }
    if (r.m_type == Regex<T>::CONCATENATION) {
        s << "(" << (*r.m_regex1) << (*r.m_regex2) << ")";
    }
    if (r.m_type == Regex<T>::ALTERNATION) {
        s << "(" << (*r.m_regex1) << "+" << (*r.m_regex2) << ")";
    }
    if (r.m_type == Regex<T>::KLEEN_STAR) {
        s << (*r.m_regex1) << "*";
    }

    return s;
}

template<class T>
bool operator==(const Regex<T> &a, const Regex<T> &b)
{
    if (a.m_type != b.m_type) {
        return false;
    }

    if (a.m_type == Regex<T>::CHARACTER) {
        return a.m_character == b.m_character;
    }

    if (a.m_type == Regex<T>::KLEEN_STAR) {
        return (*a.m_regex1) == (*b.m_regex1);
    }

    if (a.m_type == Regex<T>::CONCATENATION
        || a.m_type == Regex<T>::ALTERNATION) {
        return (*a.m_regex1) == (*b.m_regex1) && (*a.m_regex2) == (*b.m_regex2);
    }

    return true;
}

#endif // REGEX_HPP
