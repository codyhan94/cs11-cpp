#include "regex.hh"
#include <iostream>
#include <string>


/* Initialize the regex operator to apply exactly once. */
RegexOperator::RegexOperator() {
    minRepeat = 1;
    maxRepeat = 1;
}


/* Returns the "minimum repeat count" value. */
int RegexOperator::getMinRepeat() const {
    return minRepeat;
}


/* Returns the "maximum repeat count" value. */
int RegexOperator::getMaxRepeat() const {
    return maxRepeat;
}


/* Sets the "minimum repeat count" value. */
void RegexOperator::setMinRepeat(int n) {
    assert(n >= 0);
    minRepeat = n;
}


/* Sets the "maximum repeat count" value. */
void RegexOperator::setMaxRepeat(int n) {
    assert(n >= -1);
    maxRepeat = n;
}


/* Clears the list of matches stored in the regex operator.  Typically done
 * in preparation to try to match the regex to a new string.
 */
void RegexOperator::clearMatches() {
    matches.clear();
}


/* Records a new match of the operator in the list of matches. */
void RegexOperator::pushMatch(const Range &r) {
    matches.push_back(r);
}


/* Reports how many times the regex operator has successfully matched in the
 * string.
 */
int RegexOperator::numMatches() const {
    return (int) matches.size();
}


/* Removes the last match the operator successfully matched against.  Used for
 * backtracking by the regex engine.
 */
Range RegexOperator::popMatch() {
    Range r = matches.back();
    matches.pop_back();
    return r;
}

/* Initializes a single character matcher. */
MatchChar::MatchChar(char c_) {
    c = c_;
}

bool MatchChar::match(const string &s, Range &r) const {
    if (r.start > s.length() - 1)
        return false;

    if (s[r.start] == c) {
        r.end = r.start + 1;
        return true;
    }

    return false;
}

bool MatchAny::match(const string &s, Range &r) const {
    if (r.start > s.length() - 1)
        return false;

    /* If there are any characters in the string, the match will succeed. */
    if (s.length() > 0) {
        r.end = r.start + 1;
        return true;
    }

    return false;
}

MatchFromSubset::MatchFromSubset(const string &s) {
    match_subset = s;
}

bool MatchFromSubset::match(const string &s, Range &r) const {
    if (r.start > s.length() - 1)
        return false;

    char c = s[r.start];

    /* If the character we are examining is in the match_subset, then success. */
    if (match_subset.find(c) != string::npos) {
        r.end = r.start + 1;
        return true;
    }

    return false;
}

ExcludeFromSubset::ExcludeFromSubset(const string &s) {
    exclude_subset = s;
}

bool ExcludeFromSubset::match(const string &s, Range &r) const {
    if (r.start > s.length() - 1)
        return false;

    char c = s[r.start];

    /* If the character is not in exclude_subset, then success. */
    if (exclude_subset.find(c) == string::npos) {
        r.end = r.start + 1;
        return true;
    }

    return false;
}

/*! Parses a regex into a vector of regex operators. */
vector<RegexOperator *> parseRegex(const string &expr) {
    vector<RegexOperator *> regex;
    int i;
    char c;
    RegexOperator *prev;
    bool is_literal = false;
    string char_class;
    bool is_char_class = false;
    bool invert = false;

    for (i = 0; i < expr.length(); i++) {
        c = expr[i];

        if (is_char_class)
        {
            // TODO: Handle literals inside character classes properly.
            // char_class += c;

            switch (c) {
            case '^':
                invert = true;
                break;
            // case '\\':
            //     is_literal = true;
            //     break;
            case ']':
                // Add the character class.
                if (invert) {
                    regex.push_back(new ExcludeFromSubset(char_class));
                } else {
                    regex.push_back(new MatchFromSubset(char_class));
                }
                is_char_class = false;
                invert = false;
                char_class.clear();
                break;

            default:
                char_class += c;
                break;
            }
            continue;
        }

        if (is_literal) {
            regex.push_back(new MatchChar(c));
            is_literal = false;
            continue;
        }

        switch (c) {
        case '\\':
            is_literal = true;
            break;

        case '[':
            is_char_class = true;
            break;

        case '.':
            regex.push_back(new MatchAny());
            break;

        case '?':
            prev = regex.back();
            prev->setMinRepeat(0);
            prev->setMaxRepeat(1);
            break;

        case '*':
            prev = regex.back();
            prev->setMinRepeat(0);
            prev->setMaxRepeat(-1);
            break;

        case '+':
            prev = regex.back();
            prev->setMinRepeat(1);
            prev->setMaxRepeat(-1);
            break;

        default:
            // just a character.
            regex.push_back(new MatchChar(c));
            break;
        }
    }

    return regex;
}

void clearRegex(vector<RegexOperator *> regex) {
    for (auto r : regex) {
        delete r;
    }
}
