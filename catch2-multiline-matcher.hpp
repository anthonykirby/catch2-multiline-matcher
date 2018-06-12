#ifndef CATCH2_MULTILINE_MATCHER_HPP_INCLUDED
#define CATCH2_MULTILINE_MATCHER_HPP_INCLUDED


/**
 * 
 * Custom matchers for multi-line strings
 * - NoLinesMatch
 * - OneLineMatches
 * 
 */


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
				Catch::CaseSensitive::Choice caseSensitivity,
				HOW_MANY_MATCHES howManyMatches,
				COMPARISON comparison
				) :
			m_expression(expression), 
			m_caseSensitivity(caseSensitivity),
			m_howManyMatches(howManyMatches), 
			m_comparison(comparison) {
		}

		bool lineMatches(std::string line) const {
			if (m_comparison == COMPARISON_MATCHES) {
				auto flags = std::regex::ECMAScript; // ECMAScript is the default syntax option anyway
				if (m_caseSensitivity == Catch::CaseSensitive::Choice::No) {
					flags |= std::regex::icase;
				}
				auto reg = std::regex(m_expression, flags);
				return std::regex_match(line, reg);
			} else if (m_comparison == COMPARISON_CONTAINS) {
				// TODO
				return false;
			} else {
				return false; // bug 
			}
		}


		// Performs the test for this matcher

		virtual bool match(std::string const& multiline) const override {
			auto lines = split_lines(multiline);
			int count_matches = 0;
			int count_lines = 0;
			for (auto line : lines) {
				if (lineMatches(line)) {
					count_matches++;
				}
				count_lines++;
			}
			switch (m_howManyMatches) {
				case MATCH_ALL: return count_matches == count_lines;
				case MATCH_ONE: return count_matches == 1;
				case MATCH_NONE: return count_matches == 0;
				default: return false; // bug
			}
		}

		// Produces a string describing what this matcher does. It should
		// include any provided data (the begin/ end in this case) and
		// be written as if it were stating a fact (in the output it will be
		// preceded by the value under test).

		virtual std::string describe() const {
			std::ostringstream ss;
			switch (m_howManyMatches) {
				case MATCH_ALL:  ss << "all lines"; break;
				case MATCH_ONE:  ss << "exactly one line";  break;
				case MATCH_NONE: ss << "no lines";  break;
			}
			switch(m_comparison) {
				case COMPARISON_MATCHES:  ss << " matches";  break;	// TODO singular/plural
				case COMPARISON_CONTAINS: ss << " contains"; break;
			}
			ss << " expression \"" << m_expression << "\"";
			return ss.str();
		}

	protected:
		const std::string m_expression;
		const HOW_MANY_MATCHES m_howManyMatches;
		const COMPARISON m_comparison;
		const bool m_caseSensitivity;

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

	inline MultiLineMatcher OneLineMatches(
			std::string expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(expression, caseSensitivity, MultiLineMatcher::MATCH_ONE, MultiLineMatcher::COMPARISON_MATCHES);
	}

	inline MultiLineMatcher NoLinesMatch(
			std::string expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(expression, caseSensitivity, MultiLineMatcher::MATCH_NONE, MultiLineMatcher::COMPARISON_MATCHES);
	}
	inline MultiLineMatcher NoLineMatches(
			std::string expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(expression, caseSensitivity, MultiLineMatcher::MATCH_NONE, MultiLineMatcher::COMPARISON_MATCHES);
	}

	inline MultiLineMatcher AllLinesMatch(
			std::string expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(expression, caseSensitivity, MultiLineMatcher::MATCH_ALL, MultiLineMatcher::COMPARISON_MATCHES);
	}




} // namespace CatchExtension

#endif // !CATCH2_MULTILINE_MATCHER_HPP_INCLUDED


