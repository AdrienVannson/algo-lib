#ifndef JSON_HPP
#define JSON_HPP

#include <cassert>
#include <map>
#include <string>
#include <vector>

class JSON
{
public:
    enum Type
    {
        NULL_VALUE,
        INT,
        FLOAT,
        BOOLEAN,
        STRING,
        ARRAY,
        OBJECT
    };

    /// \brief Returns an empty JSON object of a given type
    static JSON *createOfType(Type);

    JSON();
    JSON(Type type);
    JSON(const int n);
    JSON(const double x);
    JSON(const bool b);
    JSON(const std::string &s);
    JSON(const std::vector<JSON *> &a);
    JSON(const std::map<std::string, JSON *> &o);

    JSON(const JSON &other);
    JSON(const JSON *other);

    ~JSON();

    Type type() const
    {
        return m_type;
    }

    // Methods for integers
    int getInt() const
    {
        return m_int;
    }

    int &getInt()
    {
        // TODO assert type == int
        return m_int;
    }

    // Methods for floats
    double getFloat() const
    {
        return m_float;
    }

    double &getFloat()
    {
        return m_float;
    }

    // Methods for booleans
    bool getBool() const
    {
        return m_bool;
    }

    bool &getBool()
    {
        return m_bool;
    }

    // Methods for strings
    const std::string &getString() const
    {
        return m_string;
    }

    std::string &getString()
    {
        return m_string;
    }

    // Methods for arrays
    std::vector<JSON *> &getArray()
    {
        return m_array;
    }

    const std::vector<JSON *> &getArray() const
    {
        return m_array;
    }

    JSON *get(const int index)
    {
        return m_array[index];
    }

    // Methods for objects
    const std::map<std::string, JSON *> &getObject() const
    {
        return m_object;
    }

    std::map<std::string, JSON *> &getObject()
    {
        return m_object;
    }

    JSON *get(const std::string &key)
    {
        return m_object[key];
    }

    /// \brief Convert the JSON object to a string
    std::string toString() const;

    /* TODO
    /// \brief Convert the JSON object to a human-readable string
    std::string toFormattedString() const; */

    /// \brief Parse a JSON string
    void fromString(const std::string &s); // The string must be valid JSON

private:
    void addToString(std::string &s) const;

    int fromString(const std::string &s, int i);
    int skipWhitespaces(const std::string &s, int i) const;
    std::pair<std::string, int> readString(const std::string &s, int i) const;

    Type m_type;

    union {
        int m_int;
        double m_float;
        bool m_bool;
        std::string m_string;
        std::vector<JSON *> m_array;
        std::map<std::string, JSON *> m_object;
    };
};

#endif // JSON_HPP
