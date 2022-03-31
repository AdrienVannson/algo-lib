#include "json.hpp"

using namespace std;

JSON::JSON() : m_type(NULL_VALUE) {}
JSON::JSON(const int n) : m_type(INT), m_int(n) {}
JSON::JSON(const double x) : m_type(FLOAT), m_float(x) {}
JSON::JSON(const bool b) : m_type(BOOLEAN), m_bool(b) {}
JSON::JSON(const std::string &s) : m_type(STRING), m_string(s) {}
JSON::JSON(const std::vector<JSON *> &a) : m_type(ARRAY), m_array(a) {}
JSON::JSON(const std::map<std::string, JSON *> &o) : m_type(OBJECT), m_object(o)
{}

JSON::JSON(const JSON &other)
{
    m_type = other.m_type;

    if (m_type == INT) {
        m_int = other.m_int;
    } else if (m_type == FLOAT) {
        m_float = other.m_float;
    } else if (m_type == BOOLEAN) {
        m_bool = other.m_bool;
    } else if (m_type == STRING) {
        new (&m_string) string();
        m_string = other.m_string;
    } else if (m_type == ARRAY) {
        new (&m_array) vector<JSON *>();
        for (JSON *obj : other.m_array) {
            m_array.push_back(new JSON(obj));
        }
    } else if (m_type == OBJECT) {
        new (&m_object) map<string, JSON *>();
        for (pair<string, JSON *> p : other.m_object) {
            m_object[p.first] = new JSON(p.second);
        }
    }
}

JSON::JSON(const JSON *other) : JSON(*other) {}

JSON::~JSON()
{
    if (m_type == ARRAY) {
        for (JSON *child : m_array) {
            delete child;
        }
    } else if (m_type == OBJECT) {
        for (const auto &child : m_object) {
            delete child.second;
        }
    }
}

JSON *JSON::operator[](const string &s)
{
    return getObject()[s];
}

string JSON::toString() const
{
    string s;
    addToString(s);
    return s;
}

void JSON::addToString(string &s) const
{
    if (m_type == NULL_VALUE) {
        s.append("null");
    } else if (m_type == INT) {
        s.append(to_string(m_int));
    } else if (m_type == FLOAT) {
        s.append(to_string(m_float));
    } else if (m_type == BOOLEAN) {
        if (m_bool) {
            s.append("true");
        } else {
            s.append("false");
        }
    } else if (m_type == STRING) {
        s.push_back('"');
        s.append(m_string);
        s.push_back('"');
    } else if (m_type == ARRAY) {
        s.push_back('[');

        bool isFirst = true;
        for (JSON *child : m_array) {
            if (!isFirst) s.push_back(',');
            isFirst = false;

            child->addToString(s);
        }

        s.push_back(']');
    } else { // Object
        s.push_back('{');

        bool isFirst = true;
        for (const auto &prop : m_object) {
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

void JSON::fromString(const string &s)
{
    fromString(s, 0);
}

int JSON::fromString(const string &s, int i)
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
            i = skipWhitespaces(s, i + 1);
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
        } else {
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
        new (&m_string) string();

        while (s[i] != '"') {
            m_string.push_back(s[i]);
            i++;
        }

        return i + 1;
    }

    if (s[i] == '[') {
        m_type = ARRAY;
        new (&m_array) vector<JSON *>();

        i = skipWhitespaces(s, i + 1);

        while (s[i] != ']') {
            JSON *child = new JSON();
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
        new (&m_object) map<string, JSON *>();

        i = skipWhitespaces(s, i + 1);

        while (s[i] != '}') {
            pair<string, int> res = readString(s, i);
            i = skipWhitespaces(s, res.second) + 1;

            JSON *child = new JSON();
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

int JSON::skipWhitespaces(const string &s, int i) const
{
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') {
        i++;
    }
    return i;
}

pair<string, int> JSON::readString(const string &s, int i) const
{
    i = skipWhitespaces(s, i) + 1;
    string content;

    while (s[i] != '"') {
        content.push_back(s[i]);
        i++;
    }

    return make_pair(content, i + 1);
}
