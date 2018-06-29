#ifndef CATCH2_MULTILINE_MATCHER_HPP_INCLUDED
#define CATCH2_MULTILINE_MATCHER_HPP_INCLUDED


/**
 * 
 * Custom matchers for multi-line strings
 * - OneLineMatches
 * - NoLinesMatch / NoLineMatches
 * - AllLinesMatch
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

		enum class MatchCount {
			ALL,
			NONE,
			ONE
		};

		enum class Comparison {
			MATCHES,
			CONTAINS
		};

		MultiLineMatcher(
				std::string const& expression,
				Catch::CaseSensitive::Choice caseSensitivity,
				MatchCount howManyMatches,
				Comparison comparison
				) :
			m_expression(expression), 
			m_caseSensitivity(caseSensitivity),
			m_howManyMatches(howManyMatches), 
			m_comparison(comparison)
		{
		}

		bool lineMatches(std::string &line) const {
			if (m_comparison == Comparison::MATCHES) {
				auto flags = std::regex::ECMAScript; // ECMAScript is the default syntax option anyway
				if (m_caseSensitivity == Catch::CaseSensitive::Choice::No) {
					flags |= std::regex::icase;
				}
				auto reg = std::regex(m_expression, flags);
				return std::regex_match(line, reg);
			} else if (m_comparison == Comparison::CONTAINS) {
				if (m_caseSensitivity == Catch::CaseSensitive::Choice::No) {
					return Catch::contains(Catch::toLower(line), Catch::toLower(m_expression));
				} else {
					return Catch::contains(line, m_expression);
				}
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
				case MatchCount::ALL: return count_matches == count_lines;
				case MatchCount::ONE: return count_matches == 1;
				case MatchCount::NONE: return count_matches == 0;
				default: return false; // bug
			}
		}

		// Produces a string describing what this matcher does. It should
		// include any provided data and
		// be written as if it were stating a fact (in the output it will be
		// preceded by the value under test).
		virtual std::string describe() const override {
			std::ostringstream ss;
			bool plural;
			switch (m_howManyMatches) {
				case MatchCount::ALL:  ss << "all lines"; plural=false; break;
				case MatchCount::ONE:  ss << "exactly one line"; plural=true; break;
				case MatchCount::NONE: ss << "no lines";  plural=false;
			}
			switch(m_comparison) {
				case Comparison::MATCHES:  ss << " match" << (plural?"es":"");  break;	// TODO singular/plural
				case Comparison::CONTAINS: ss << " contain" << (plural?"s":""); break;
			}
			ss << " expression \"" << m_expression << "\"";
			return ss.str();
		}

	protected:
		std::string m_expression;
		const bool m_caseSensitivity;
		const MatchCount m_howManyMatches;
		const Comparison m_comparison;

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
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::ONE, 
				MultiLineMatcher::Comparison::MATCHES);
	}

	inline MultiLineMatcher NoLinesMatch(
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::NONE, 
				MultiLineMatcher::Comparison::MATCHES);
	}
	inline MultiLineMatcher NoLineMatches(
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::NONE, 
				MultiLineMatcher::Comparison::MATCHES);
	}

	inline MultiLineMatcher AllLinesMatch(
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::ALL, 
				MultiLineMatcher::Comparison::MATCHES);
	}

	inline MultiLineMatcher OneLineContains(
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::ONE, 
				MultiLineMatcher::Comparison::CONTAINS);
	}

	inline MultiLineMatcher NoLinesContain(
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::NONE, 
				MultiLineMatcher::Comparison::CONTAINS);
	}
	inline MultiLineMatcher NoLineContains(
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::NONE, 
				MultiLineMatcher::Comparison::CONTAINS);
	}

	inline MultiLineMatcher AllLinesContain(
			std::string const&expression, 
			Catch::CaseSensitive::Choice caseSensitivity = Catch::CaseSensitive::Choice::Yes
			) {
		return MultiLineMatcher(
				expression, 
				caseSensitivity, 
				MultiLineMatcher::MatchCount::ALL, 
				MultiLineMatcher::Comparison::CONTAINS);
	}

	


} // namespace CatchExtension

#endif // !CATCH2_MULTILINE_MATCHER_HPP_INCLUDED


