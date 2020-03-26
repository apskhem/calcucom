#ifndef KLIB_STRING_H
#define KLIB_STRING_H

#include <cstring>
#include <string> // for iostream

typedef class String {
    friend String operator+ (const char *, String &);
    friend bool operator== (const char *, String &);
    friend bool operator!= (const char *, String &);
    friend std::ostream& operator<< (std::ostream &, const String &);
    friend std::istream& operator>> (std::istream &, String &);
    friend std::istream& getline(std::istream &, String &);
    /* The method converts numbers to arithmetic string. max decimal places is 2. */
    template <class number>
    friend String toString(number);
    /* The method converts Unicode values into characters. */
    friend char fromCharCode(const unsigned);
    private:
        char *_proto_; // c-string data
    public:
        /* The length property returns the length of a string (number of characters). */
        unsigned length;
        
        String();
        String(const char *str);
        String(const char);
        String(const String &str);
        ~String();
        
        operator char*();
        operator const char*();

        char& operator[] (const int);
        String operator+ (const char *);
        String operator+ (const String &);
        String operator+= (const char *);
        String operator+= (const char);
        String operator+= (const String &);
        String operator= (const char *);
        String operator= (const String &);
        bool operator== (const char *);
        bool operator== (const String &);
        bool operator!= (const char *);
        bool operator!= (const String &);
        String operator* (const unsigned);
        
        /* The method returns the character at the specified index in a string. */
        char charAt(const unsigned);
        /* The method returns the Unicode of the character at the specified index in a string. */
        int charCodeAt(const unsigned);
        /* The method returns a non-negative integer that is the Unicode code point value. */
        unsigned codePointAt(const unsigned);
        /* The method is used to join two or more strings. */
        String concat(const String &);
        /* The method retunrs the value of c-string. */
        char* cstring();
        /* The method determines whether a string ends with the characters of a specified string. */
        bool endsWith(String, unsigned=-1);
        /* The method determines whether a string contains the characters of a specified string. */
        bool includes(String, const unsigned=0);
        /* The method returns the position of the first occurrence of a specified value in a string. */
        int indexOf(String, const unsigned=0);
        /* The method returns the position of the last occurrence of a specified value in a string. */
        int lastIndexOf(String, unsigned=-1);
        /* The method compares two strings in the current locale. */
        int localeCompare(String);
        /* The method searches a string for a match against a regular expression, and returns the matches, as an Array object. */
        String match();
        /* method pads the current string with a given string (repeated, if needed) so that the resulting string reaches a given length. */
        String matchAll();
        /* The method returns the Unicode Normalization Form of the string. */
        String normalize(String);
        /* The method pads the current string with another string (multiple times, if needed) until the resulting string reaches the given length */
        String padEnd(const unsigned, String);
        /* The method pads the current string with another string (multiple times, if needed) until the resulting string reaches the given length */
        String padStart(const unsigned, String);
        /* The method returns a new string with a specified number of copies of the string it was called on. */
        String repeat(const unsigned);
        /* The method searches a string for a specified value, or a regular expression, and returns a new string where the specified values are replaced. */
        String replace(String, String);
        /* The  method searches a string for a specified value, and returns the position of the match. */
        int search(String);
        /* The method extracts parts of a string and returns the extracted parts in a new string. */
        String slice(const unsigned, unsigned=-1);
        /* The method is used to split a string into an array of substrings, and returns the new array. */
        Array<String> split(String);
        /* The method determines whether a string begins with the characters of a specified string. */
        bool startsWith(String, const unsigned=0);
        /* The method extracts parts of a string, beginning at the character at the specified position, and returns the specified number of characters. */
        String substr(const unsigned, unsigned=-1);
        /* The method extracts the characters from a string, between two specified indices, and returns the new sub string. */
        String substring(unsigned, unsigned=-1);
        /* The method converts a string to lowercase letters. */
        String toLowerCase();
        /* The method returns the value of a String object. */
        String toString();
        /* The method converts a string to uppercase letters. */
        String toUpperCase();
        /* The method removes whitespace from both sides of a string. */
        String trim();
        /* The method removes whitespace from the beginning of the string. */
        String trimStart();
        /* The method removes whitespace from the beginning of the string. */
        String trimLeft();
        /* The method removes whitespace from the end of the string. */
        String trimEnd();
        /* The method removes whitespace from the end of the string. */
        String trimRight();
        /* The method returns the primitive value of a String object. */
        String valueOf();
} string;

/* constructor */
String::String() {
    _proto_ = NULL;
    length = 0;
}

String::String(const char *str) {
    _proto_ = new char[(length = strlen(str))+1];
    _proto_[length] = '\0';
        
    for (unsigned i = 0; i < length; i++) _proto_[i] = str[i];
}

String::String(const char c) {
    length = 1;

    _proto_ = new char[2];

    _proto_[0] = c;
    _proto_[1] = '\0';
}

String::String(const String &str) {
    _proto_ = new char[(length = str.length)+1];
    _proto_[length] = '\0';

    for (unsigned i = 0; i < length; i++) _proto_[i] = str._proto_[i];
}

String::~String() {
    delete[] _proto_;
}

/* call operators */
String::operator char*() { return _proto_; }
String::operator const char*() { return _proto_; }
char& String::operator[] (const int index) { return _proto_[index]; }

/* processing operators: FRIEND */
std::ostream& operator<< (std::ostream &out, const String &str) {
    out << str._proto_;
    return out;
}

std::istream& operator>> (std::istream &in, String &str) {
    std::string t;
    in >> t;

    str._proto_ = new char[(str.length = t.size())+1];
    str._proto_[str.length] = '\0';
        
    for (unsigned i = 0; i < str.length; i++) str._proto_[i] = t[i];
    
    return in;
}

std::istream& getline(std::istream &in, String &str) {
    std::string t;
    std::getline(std::cin, t);

    str._proto_ = new char[(str.length = t.size())+1];
    str._proto_[str.length] = '\0';
        
    for (unsigned i = 0; i < str.length; i++) str._proto_[i] = t[i];
    
    return in;
}

/* processing operators: OVERLOAD */
String operator+ (const char *lstr, String &rstr) {
    unsigned len = strlen(lstr);

    char result[len+rstr.length+1];
    result[len+rstr.length] = '\0';

    for (unsigned i = 0; i < len; i++) result[i] = lstr[i];
    for (unsigned i = 0; i < rstr.length; i++) result[len+i] = rstr._proto_[i];

    return result;
}

String String::operator+ (const char *str) {
    unsigned len = strlen(str);

    char result[length+len+1];
    result[length+len] = '\0';

    for (unsigned i = 0; i < length; i++) result[i] = _proto_[i];
    for (unsigned i = 0; i < len; i++) result[length+i] = str[i];
    
    return result;
}

String String::operator+ (const String &str) {
    char result[length+str.length+1];
    result[length+str.length] = '\0';

    for (unsigned i = 0; i < length; i++) result[i] = _proto_[i];
    for (unsigned i = 0; i < str.length; i++) result[length+i] = str._proto_[i];
    
    return result;
}

/* ### */

String String::operator+= (const char *str) {
    unsigned len = strlen(str);

    char *old = _proto_;
    _proto_ = new char[length+len+1];
    _proto_[length+len] = '\0';

    for (unsigned i = 0; i < length; i++) _proto_[i] = old[i];
    for (unsigned i = 0; i < len; i++) _proto_[length+i] = str[i];

    delete[] old;
    length += len;
    
    return *this;
}

String String::operator+= (const char chr) {
    char *old = _proto_;
    _proto_ = new char[length+2];
    _proto_[++length] = chr;
    _proto_[length] = '\0';
    
    for (unsigned i = 0; i < length-1; i++) _proto_[i] = old[i];
    
    delete[] old;

    return *this;
}

String String::operator+= (const String &str) {
    char *old = _proto_;
    _proto_ = new char[length+str.length+1];
    _proto_[length+str.length] = '\0';

    for (unsigned i = 0; i < length; i++) _proto_[i] = old[i];
    for (unsigned i = 0; i < str.length; i++) _proto_[length+i] = str._proto_[i];

    delete[] old;
    length += str.length;
    
    return *this;
}

/* ### */

String String::operator= (const char *str) {
    delete[] _proto_;
    _proto_ = new char[(length = strlen(str))+1];
    _proto_[length] = '\0';

    for (unsigned i = 0; i < length; i++) _proto_[i] = str[i];

    return *this;
}

String String::operator= (const String &str) {
    delete[] _proto_;
    _proto_ = new char[(length = str.length)+1];
    _proto_[length] = '\0';

    for (unsigned i = 0; i < length; i++) _proto_[i] = str._proto_[i];

    return *this;
}

/* ### */

bool String::operator== (const String &str) {
    if (length != str.length) return false;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str._proto_[i]) return false;
    }
    
    return true;
}

bool String::operator== (const char *str) {
    if (length != strlen(str)) return false;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str[i]) return false;
    }
    
    return true;
}

bool String::operator!= (const String &str) {
    if (length != str.length) return true;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str._proto_[i]) return true;
    }
    
    return false;
}

bool String::operator!= (const char *str) {
    if (length != strlen(str)) return true;
    
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != str[i]) return true;
    }
    
    return false;
}

/* ### */

String String::operator* (const unsigned mul) {
    
}

/* class methods: FRIEND */
template <class number>
String toString(number n) {
    if (n == 1) return "";
    if (n == -1) return "-";

    string t = std::to_string(n).c_str();
    unsigned short dotPos = -1, lastZeroPos = -1;

    for (unsigned short i = 0; i < t.length; i++) {
        if (t[i] == '.') {
            dotPos = i;
            break;
        }
    }

    if (dotPos == -1) return t;

    for (unsigned short i = t.length-1; i >= dotPos; i++) {
        if (t[i] != '0' || i == dotPos) lastZeroPos = i+1;
    }

    switch (lastZeroPos - dotPos) {
        case 1: return t.slice(0, dotPos); // .0
        case 2: return t.slice(0, dotPos+2); // .x0
        default: return t.slice(0, dotPos+3); // .xx0
    }
}

/* class methods: BUILT-IN */
char String::charAt(const unsigned index) {
    return _proto_[index];
}

int String::charCodeAt(const unsigned index) {
    return _proto_[index];
}

String String::concat(const String &str) {
    char result[length+str.length+1];
    result[length+str.length] = '\0';
    
    for (unsigned i = 0; i < length; i++) result[i] = _proto_[i];
    for (unsigned i = 0; i < str.length; i++) result[length + i] = str._proto_[i];

    return result;
}

bool String::endsWith(String searchvalue, unsigned atlength) {
    if (atlength == -1 || atlength > length) atlength = length;

    unsigned j = 0;
    for (unsigned i = atlength-searchvalue.length-1; i < atlength; i++) {
        if (searchvalue[j] == _proto_[i] && ++j == searchvalue.length) return true;
        return false;
    }

    return false;
}

bool String::includes(String searchvalue, const unsigned start) {
    unsigned j = 0;
    for (unsigned i = start; i < length; i++) {
        if (_proto_[i] == searchvalue[j] && ++j == searchvalue.length) return true;
        else j = 0;
    }

    return false;
}

int String::indexOf(String searchvalue, const unsigned start) {
    unsigned j = 0, fisrtFindIndex = 0;
    for (unsigned i = start; i < length; i++) {
        if (_proto_[i] == searchvalue[j]) {
            if (j == 0) fisrtFindIndex = i;
            if (++j == searchvalue.length)
                return true;
        }
        else {
            j = 0;
        }
    }

    return -1;
}

int String::lastIndexOf(String searchvalue, unsigned start) {
    if (start == -1) start = length;

    unsigned j = length-1;
    for (unsigned i = j; i >= 0; i--) {
        if (searchvalue[j] == _proto_[i] && ++j == searchvalue.length) return i;
        else j = 0;
    }

    return -1;
}

String String::replace(String searchvalue, String newvalue) {
    if (searchvalue == "") return *this;

    string result = "";
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] == searchvalue[0]) {
            if (newvalue == "") continue;
            result += newvalue;
        }
        else {
            result += _proto_[i];
        }
    }

    return result;
}

int String::search(String searchvalue) {
    unsigned j = 0, fisrtFindIndex = 0;
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] == searchvalue[j]) {
            if (i == 0) fisrtFindIndex = i;
            if (i == searchvalue.length) return fisrtFindIndex;
        }
        else {
            j = 0;
        }
    }

    return -1;
}

String String::slice(const unsigned start, unsigned end) {
    if (end == -1) end = length;
    if (end-start <= 0) return "";

    char result[end-start+1];
    result[end-start] = '\0';

    unsigned j = 0;
    for (unsigned i = start; i < end; i++) result[j++] = _proto_[i];

    return result;
}

Array<String> String::split(String separator) {
    Array<String> splited;

    unsigned splitIndex = 0;
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] == separator[0]) {
            splited.push(this->slice(splitIndex,i));
            splitIndex = i+separator.length;
        }
    }

    splited.push(this->slice(splitIndex));

    return splited;
}

bool String::startsWith(String searchvalue, const unsigned start) {
    unsigned i = start;
    while (i < length) {
        if (_proto_[i] == searchvalue[i] && ++i == searchvalue.length) return true;
        return false;
    }

    return false;
}

String String::substr(const unsigned start, unsigned atlength) {
    if (atlength == -1) atlength = length;
    if (atlength-start <= 0) return "";

    char result[atlength-start+1];
    result[atlength-start] = '\0';

    unsigned j = 0;
    for (unsigned i = start; i < atlength; i++) result[j++] = _proto_[i];

    return result;
}

String String::substring(unsigned start, unsigned end) {
    if (end == -1) end = length;
    if (end-start <= 0) return "";
    else if (start > end) {
        unsigned temp = start;
        start = end;
        end = start;
    }

    char result[end-start+1];
    result[end-start] = '\0';

    unsigned j = 0;
    for (unsigned i = start; i < end; i++) result[j++] = _proto_[i];

    return result;
}

String String::toLowerCase() {
    char str[length+1];
    str[length] = '\0';

    for (unsigned i = 0; i < length; i++) {
        if ((str[i] = _proto_[i]) >= 65 && str[i] <= 90) str[i] += 32;
    }

    return str;
}

String String::toString() {
    return *this;
}

String String::toUpperCase() {
    char str[length+1];
    str[length] = '\0';

    for (unsigned i = 0; i < length; i++) {
        if ((str[i] = _proto_[i]) >= 97 && str[i] <= 122) str[i] -= 32;
    }

    return str;
}

String String::trim() {
    unsigned indexLeft = 0, indexRight = 0;
    for (unsigned i = 0; i < length; i++) {
        if (_proto_[i] != ' ') {
            indexLeft = i;
            break;
        }
    }

    for (unsigned i = length-1; i >= 0; i--) {
        if (_proto_[i] != ' ') {
            indexRight = i+1;
            break;
        }
    }

    return this->slice(indexLeft, indexRight);
}

String String::valueOf() {
    return *this;
}

#endif