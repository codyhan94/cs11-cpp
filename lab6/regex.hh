#include <cassert>
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

    // Operations to support optional and repeat operations.
    int getMinRepeat() const;
    int getMaxRepeat() const;
    void setMinRepeat(int n);
    void setMaxRepeat(int n);

    // Operations to support backtracking
    void clearMatches();
    void pushMatch(const Range &r);
    int numMatches() const;
    Range popMatch();
};


vector<RegexOperator *> parseRegex(const string &expr);
void clearRegex(vector<RegexOperator *> regex);

