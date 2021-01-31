#ifndef JSON_HPP
#define JSON_HPP

#include <map>
#include <string>
#include <vector>

class JSON
{
public:
    enum Type {
        NULL_VALUE,
        INT,
        FLOAT,
        BOOLEAN,
        STRING,
        ARRAY,
        OBJECT
    };

    JSON ();
    JSON (const int n);
    JSON (const double x);
    JSON (const bool b);
    JSON (const std::string &s);
    JSON (const std::vector<JSON*> &a);
    JSON (const std::map<std::string, JSON*> &o);

    JSON (const JSON &other);
    JSON (const JSON *other);

    ~JSON ();

    Type type () const { return m_type; }

    int& getInt () { return m_int; }
    double& getFloat () { return m_float; }
    bool& getBool () { return m_bool; }
    std::string& getString () { return m_string; }
    std::vector<JSON*>& getArray () { return m_array; }
    std::map<std::string, JSON*>& getObject () { return m_object; }

    int getInt () const { return m_int; }
    double getFloat () const { return m_float; }
    bool getBool () const { return m_bool; }
    const std::string& getString () const { return m_string; }
    const std::vector<JSON*>& getArray () const { return m_array; }
    const std::map<std::string, JSON*>& getObject () const { return m_object; }

    JSON* operator[] (const std::string &s);

    std::string toString () const;
    void fromString (const std::string &s); // The std::string must be valid JSON

private:
    void addToString (std::string &s) const;

    int fromString (const std::string &s, int i);
    int skipWhitespaces (const std::string &s, int i) const;
    std::pair<std::string, int> readString (const std::string &s, int i) const;

    Type m_type;

    union {
        int m_int;
        double m_float;
        bool m_bool;
        std::string m_string;
        std::vector<JSON*> m_array;
        std::map<std::string, JSON*> m_object;
    };
};

#endif // JSON_HPP
