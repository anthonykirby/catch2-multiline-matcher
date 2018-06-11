#ifndef CATCH2_MULTILINE_MATCHER_HPP_INCLUDED
#define CATCH2_MULTILINE_MATCHER_HPP_INCLUDED


#ifndef CATCH_VERSION_MAJOR
//  (this extension doesn't include catch.hpp for you because
//  we don't know where catch.hpp lives on your filesystem and 
//  or whether you want the single-include version)
#error this is an extension to Catch2: you first need to include Catch2 itself i.e. "#include catch.hpp"
#endif

#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <iostream>

namespace CatchExtension {


/**
 * 
 * Custom matchers for multi-line strings
 * - NoLinesMatch
 * - OneLineMatches
 * 
 */


class MultiLineMatcher : public Catch::MatcherBase<std::string> {
public:
    enum HOW_MANY_MATCHES {
        MATCH_ALL,
        MATCH_NONE,
        MATCH_ONE
    };
    enum COMPARISON {
        COMPARISON_MATCHES,
        COMPARISON_CONTAINS
    };
    
    MultiLineMatcher(
    		std::string expression, 
    		HOW_MANY_MATCHES how_many_matches,
    		COMPARISON comparison
    		)
        : m_how_many_matches(how_many_matches), m_comparison(comparison) {}

    bool lineMatches ( std::string line) const {
        auto flags = std::regex::ECMAScript; // ECMAScript is the default syntax option anyway
        // TODO case sensitivity
//        if (m_caseSensitivity == CaseSensitive::Choice::No) {
//            flags |= std::regex::icase;
//        }
        auto reg = std::regex(m_expression, flags);
        return std::regex_match(line, reg);
    }
        
        
    // Performs the test for this matcher
    virtual bool match( std::string const& multiline ) const override {
        auto lines = split_lines(multiline);
        int matches = 0;
        for (auto line : lines) {
            if (lineMatches(line))
                matches++;
        }
        return matches == 1;//TODOm_matches;
    }

    // Produces a string describing what this matcher does. It should
    // include any provided data (the begin/ end in this case) and
    // be written as if it were stating a fact (in the output it will be
    // preceded by the value under test).
    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "contains no lines matching \"" << m_expression << "\"";
        return ss.str();
    }

protected:    
    const std::string m_expression;
    const HOW_MANY_MATCHES m_how_many_matches;
    const COMPARISON m_comparison;
    
    // split a multi-line string into vector of single-line strings
    std::vector<std::string> split_lines(const std::string& multiline) const {
		std::istringstream iss(multiline);
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(iss, line)) {
			lines.push_back(line);
		}
		return lines;
	}


};

inline MultiLineMatcher NoLinesMatch( std::string expression ) {
    return MultiLineMatcher( expression, MultiLineMatcher::MATCH_NONE, MultiLineMatcher::COMPARISON_MATCHES);
}

inline MultiLineMatcher OneLineMatches( std::string expression ) {
    return MultiLineMatcher( expression, MultiLineMatcher::MATCH_ONE, MultiLineMatcher::COMPARISON_MATCHES );
}

//inline MultiLineMatcher NoLinesContain( std::string expression ) {
//    return MultiLineMatcher( expression, 0 );
//}



}    // namespace CatchExtension

#endif // !CATCH2_MULTILINE_MATCHER_HPP_INCLUDED


