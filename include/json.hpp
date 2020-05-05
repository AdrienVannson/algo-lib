#ifndef JSON_HPP
#define JSON_HPP

#include "global.hpp"

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

    JSON () :
        m_type (NULL_VALUE)
    {}
    JSON (const int n) :
        m_type (INT),
        m_int (n)
    {}
    JSON (const double x) :
        m_type (FLOAT),
        m_float (x)
    {}
    JSON (const bool b) :
        m_type (BOOLEAN),
        m_bool (b)
    {}
    JSON (const string &s) :
        m_type (STRING),
        m_string (s)
    {}
    JSON (const vector<JSON*> &a) :
        m_type (ARRAY),
        m_array (a)
    {}
    JSON (const map<string, JSON*> &o) :
        m_type (OBJECT),
        m_object (o)
    {}

    JSON (const JSON &other);
    JSON (const JSON *other) :
        JSON (*other)
    {}

    ~JSON ();

    Type type () const { return m_type; }

    int& getInt () { return m_int; }
    double& getFloat () { return m_float; }
    bool& getBool () { return m_bool; }
    string& getString () { return m_string; }
    vector<JSON*>& getArray () { return m_array; }
    map<string, JSON*>& getObject () { return m_object; }

    int getInt () const { return m_int; }
    double getFloat () const { return m_float; }
    bool getBool () const { return m_bool; }
    const string& getString () const { return m_string; }
    const vector<JSON*>& getArray () const { return m_array; }
    const map<string, JSON*>& getObject () const { return m_object; }

    JSON* operator[] (const string &s);

    string toString () const;
    void fromString (const string &s); // The string must be valid JSON

private:
    void addToString (string &s) const;

    int fromString (const string &s, int i);
    int skipWhitespaces (const string &s, int i) const;
    pair<string, int> readString (const string &s, int i) const;

    Type m_type;

    union {
        int m_int;
        double m_float;
        bool m_bool;
        string m_string;
        vector<JSON*> m_array;
        map<string, JSON*> m_object;
    };

};

JSON::JSON (const JSON &other)
{
    m_type = other.m_type;

    if (m_type == INT) {
        m_int = other.m_int;
    }
    else if (m_type == FLOAT) {
        m_float = other.m_float;
    }
    else if (m_type == BOOLEAN) {
        m_bool = other.m_bool;
    }
    else if (m_type == STRING) {
        new (&m_string) string ();
        m_string = other.m_string;
    }
    else if (m_type == ARRAY) {
        new (&m_array) vector<JSON*> ();
        for (JSON* obj : other.m_array) {
            m_array.push_back(new JSON (obj));
        }
    }
    else if (m_type == OBJECT) {
        new (&m_object) map<string, JSON*> ();
        for (pair<string, JSON*> p : other.m_object) {
            m_object[p.first] = new JSON (p.second);
        }
    }
}

JSON::~JSON ()
{
    if (m_type == ARRAY) {
        for (JSON *child : m_array) {
            delete child;
        }
    }
    else if (m_type == OBJECT) {
        for (const pair<string, JSON*> &child : m_object) {
            delete child.second;
        }
    }
}

JSON* JSON::operator[] (const string &s)
{
    return getObject()[s];
}

string JSON::toString () const
{
    string s;
    addToString(s);
    return s;
}

void JSON::addToString (string &s) const
{
    if (m_type == NULL_VALUE) {
        s.append("null");
    }
    else if (m_type == INT) {
        s.append(to_string(m_int));
    }
    else if (m_type == FLOAT) {
        s.append(to_string(m_float));
    }
    else if (m_type == BOOLEAN) {
        if (m_bool) {
            s.append("true");
        }
        else {
            s.append("false");
        }
    }
    else if (m_type == STRING) {
        s.push_back('"');
        s.append(m_string);
        s.push_back('"');
    }
    else if (m_type == ARRAY) {
        s.push_back('[');

        bool isFirst = true;
        for (JSON* child : m_array) {
            if (!isFirst) s.push_back(',');
            isFirst = false;

            child->addToString(s);
        }

        s.push_back(']');
    }
    else { // Object
        s.push_back('{');

        bool isFirst = true;
        for (const pair<string, JSON*> &prop : m_object) {
            if (!isFirst) s.push_back(',');
            isFirst = false;

            s.push_back('"');
            s.append(prop.first);
            s.push_back('"');
            s.push_back(':');

            prop.second->addToString(s);
        }

        s.push_back('}');
    }
}

void JSON::fromString (const string &s)
{
    fromString(s, 0);
}

int JSON::fromString (const string &s, int i)
{
    i = skipWhitespaces(s, i);

    if (s[i] == 'n') {
        m_type = NULL_VALUE;
        return i + 4;
    }

    if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-') {
        bool isNegative = false;
        if (s[i] == '-') {
            isNegative = true;
            i = skipWhitespaces(s, i+1);
        }

        string number;
        while (s[i] >= '0' && s[i] <= '9') {
            number.push_back(s[i]);
            i++;
        }

        if (s[i] == '.') {
            number.push_back('.');
            i++;
            while (s[i] >= '0' && s[i] <= '9') {
                number.push_back(s[i]);
                i++;
            }

            m_type = FLOAT;
            m_float = stod(number);

            if (isNegative) {
                m_float *= -1;
            }
        }
        else {
            m_type = INT;
            m_int = stoi(number);

            if (isNegative) {
                m_int *= -1;
            }
        }

        return i;
    }

    if (s[i] == 'f') {
        m_type = BOOLEAN;
        m_bool = false;
        return i + 5;
    }

    if (s[i] == 't') {
        m_type = BOOLEAN;
        m_bool = true;
        return i + 4;
    }

    if (s[i] == '"') {
        i++;

        m_type = STRING;
        new (&m_string) string ();

        while (s[i] != '"') {
            m_string.push_back(s[i]);
            i++;
        }

        return i + 1;
    }

    if (s[i] == '[') {
        m_type = ARRAY;
        new (&m_array) vector<JSON*> ();

        i = skipWhitespaces(s, i+1);

        while (s[i] != ']') {
            JSON *child = new JSON ();
            i = child->fromString(s, i);
            m_array.push_back(child);

            i = skipWhitespaces(s, i);

            if (s[i] == ',') {
                i++;
                i = skipWhitespaces(s, i);
            }
        }

        return i + 1;
    }

    if (s[i] == '{') {
        m_type = OBJECT;
        new (&m_object) map<string, JSON*> ();

        i = skipWhitespaces(s, i+1);

        while (s[i] != '}') {
            pair<string, int> res = readString(s, i);
            i = skipWhitespaces(s, res.second) + 1;

            JSON *child = new JSON ();
            i = child->fromString(s, i);

            m_object[res.first] = child;

            i = skipWhitespaces(s, i);

            if (s[i] == ',') {
                i++;
            }
        }

        return i + 1;
    }

    exit(1);
}

int JSON::skipWhitespaces (const string &s, int i) const
{
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') {
        i++;
    }
    return i;
}

pair<string, int> JSON::readString (const string &s, int i) const
{
    i = skipWhitespaces(s, i) + 1;
    string content;

    while (s[i] != '"') {
        content.push_back(s[i]);
        i++;
    }

    return make_pair(content, i+1);
}

#endif // JSON_HPP
