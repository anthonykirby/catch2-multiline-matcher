#include "catch.hpp"

#include "../catch2-multiline-matcher.hpp"

using Catch::Matchers::Contains;
using Catch::Matchers::Matches;
using Catch::CaseSensitive;

TEST_CASE("vanilla functionality") {

	SECTION( "contains") {
		CHECK_THAT("food", Contains("foo"));
		CHECK_THAT("food", !Contains("bar"));
	}

	SECTION( "matches") {
		CHECK_THAT("food", Matches("foo.*"));
		CHECK_THAT("food", !Matches("foo"));
	}

	SECTION( "sensitivity") {
		CHECK_THAT("Food", Contains("foo", CaseSensitive::No));
		CHECK_THAT("Food", !Contains("foo", CaseSensitive::Yes));
	}
}


using CatchExtension::OneLineMatches;
using CatchExtension::NoLineMatches;
using CatchExtension::NoLinesMatch;
using CatchExtension::AllLinesMatch;
using CatchExtension::AllLinesMatch;


TEST_CASE("OneLineMatches") {
	SECTION( "multiline string is empty") {
		CHECK_THAT("", !OneLineMatches("foo"));
		CHECK_THAT("", !OneLineMatches(".*"));
		CHECK_THAT("", NoLinesMatch("bar"));
		CHECK_THAT("", AllLinesMatch("bar"));	// surprising?
	}

	SECTION( "multiline string has one line") {
		CHECK_THAT("foo", OneLineMatches("foo"));
		CHECK_THAT("foo\n", OneLineMatches("foo"));
		CHECK_THAT("foo", !OneLineMatches("bar"));
		CHECK_THAT("foo\n", !OneLineMatches("bar"));
		CHECK_THAT("foo", OneLineMatches(".*"));

		CHECK_THAT("foo", !NoLinesMatch("foo"));
		CHECK_THAT("foo", NoLinesMatch("bar"));
		CHECK_THAT("foo", !NoLineMatches("foo"));
		CHECK_THAT("foo", NoLineMatches("bar"));

		CHECK_THAT("foo", AllLinesMatch("foo"));
		CHECK_THAT("foo", !AllLinesMatch("bar"));
		
	}

	SECTION( "multiline string has multiple lines") {
		CHECK_THAT("foo", OneLineMatches("foo"));
	}

	SECTION("Case sensitivity") {
		CHECK_THAT("foo", OneLineMatches("foo"));
		CHECK_THAT("foo", !OneLineMatches("Foo"));
		CHECK_THAT("foo", OneLineMatches("foo", Catch::CaseSensitive::Choice::Yes));
		CHECK_THAT("foo", !OneLineMatches("Foo", Catch::CaseSensitive::Choice::Yes));
		CHECK_THAT("foo", OneLineMatches("foo", Catch::CaseSensitive::Choice::No));
		CHECK_THAT("foo", OneLineMatches("Foo", Catch::CaseSensitive::Choice::No));
		

	}
	
}
