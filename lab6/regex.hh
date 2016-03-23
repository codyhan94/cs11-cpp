#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


/* This class represents a range in a string, as a pair of indexes.  The "start"
 * index is inclusive, and the "end" index is exclusive, so that the range
 * [1, 5) represents the substring that starts at index 1 and ends at index 4;
 * index 5 is one past the last character in the substring.
 *
 * The "start" and "end" indexes are public access, so that they can be
 * accessed and manipulated directly.
 *
 * A range with identical "start" and "end" values indicates an empty string.
 *
 * The start and end indexes are also allowed to be -1, to indicate an invalid
 * range.
 */
class Range {
public:
    // The starting index of the range (inclusive)
    int start;
    
    // The ending index of the range (exclusive)
    int end;

    // Initialize a Range object with the specified start and end indexes
    Range(int start_, int end_) {
        assert(start_ <= end_);
        assert(start_ >= -1);
        assert(end_ >= -1);

        start = start_;
        end = end_;
    }
    
    // Initialize a Range object to the range [0, 0).
    Range() {
        start = 0;
        end = 0;
    }

    friend ostream &operator <<(ostream &os, const Range &r) {
        return os << "[" << r.start << ", " << r.end << ")";
    }
};


/* A class for representing operations that can be performed in a regular
 * expression.
 */
class RegexOperator {
    // The minimum and maximum number of times the operator is *required* to
    // match.  The minimum value must be at least 0.  The maximum value must be
    // at least -1; -1 indicates "unlimited matches", and all other values
    // specify an actual maximum number of matches.
    int minRepeat, maxRepeat;
    
    // A vector of ranges where the regex operator has matched the test string.
    vector<Range> matches;
    
public:
    RegexOperator();

    // Empty virtual destructor for subclasses to override if necessary.
    virtual ~RegexOperator() { }

    // Operations to support optional and repeat operations.
    int getMinRepeat() const;
    int getMaxRepeat() const;
    void setMinRepeat(int n);
    void setMaxRepeat(int n);

    // Operations to support backtracking
    void clearMatches();
    void pushMatch(const Range &r);
    int numMatches() const;

    // Matching operations.
    virtual bool match(const string &s, Range &r) const = 0;
    Range popMatch();
};


class MatchChar : public RegexOperator {
private:
    char c;  // The character that this class matches.
public:
    MatchChar(char c_);
    bool match(const string &s, Range &r) const;
};


class MatchAny : public RegexOperator {
public:
    MatchAny() { }
    bool match(const string &s, Range &r) const;
};


class MatchFromSubset : public RegexOperator {
private:
    string match_subset;
public:
    MatchFromSubset(const string &s);
    bool match(const string &s, Range &r) const;
};


class ExcludeFromSubset : public RegexOperator {
private:
    string exclude_subset;
public:
    ExcludeFromSubset(const string &s);
    bool match(const string &s, Range &r) const;
};

vector<RegexOperator *> parseRegex(const string &expr);
void clearRegex(vector<RegexOperator *> regex);

