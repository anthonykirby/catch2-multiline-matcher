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

	SECTION( "contains sensitivity") {
		CHECK_THAT("Food", Contains("foo", CaseSensitive::No));
		CHECK_THAT("Food", !Contains("foo", CaseSensitive::Yes));
	}

	SECTION( "matches sensitivity") {
		CHECK_THAT("Food", Matches("foo.*", CaseSensitive::No));
		CHECK_THAT("Food", !Matches("foo.*", CaseSensitive::Yes));
	}
}


using CatchExtension::OneLineMatches;
using CatchExtension::NoLinesMatch;
using CatchExtension::NoLineMatches;	// synonym for NoLinesMatch
using CatchExtension::AllLinesMatch;

using CatchExtension::OneLineContains;
using CatchExtension::NoLinesContain;
using CatchExtension::NoLineContains;	// synonym for NoLinesContain
using CatchExtension::AllLinesContain;



TEST_CASE("Matches") {
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
		CHECK_THAT("foo\nbar\nbaz", OneLineMatches("foo"));
		CHECK_THAT("foo\nbar\nbaz", OneLineMatches("bar"));
		CHECK_THAT("foo\nbar\nbaz", OneLineMatches("baz"));
		CHECK_THAT("foo\nbar\nbaz", !OneLineMatches("bum"));
		CHECK_THAT("foo\nbar\nbaz", !AllLinesMatch("foo"));
		CHECK_THAT("foo\nfoo\nfoo", AllLinesMatch("foo"));
		CHECK_THAT("foo\nbar\nbaz", NoLinesMatch("bum"));
		CHECK_THAT("foo\nbar\nbaz", NoLineMatches("bum"));
		CHECK_THAT("foo\nbar\nbaz", !NoLineMatches("foo"));
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


TEST_CASE("Contains") {
	SECTION( "multiline string is empty") {
		CHECK_THAT("", !OneLineContains("foo"));
		CHECK_THAT("", NoLinesContain("bar"));
		CHECK_THAT("", AllLinesContain("bar"));	// surprising?
	}
	
	SECTION( "multiline string has one line") {
		CHECK_THAT("xfood", OneLineContains("foo"));
		CHECK_THAT("xfood\n", OneLineContains("foo"));
		CHECK_THAT("xfood", !OneLineContains("bar"));
		CHECK_THAT("xfood\n", !OneLineContains("bar"));

		CHECK_THAT("xfood", !NoLinesContain("foo"));
		CHECK_THAT("xfood", NoLinesContain("bar"));
		CHECK_THAT("xfood", !NoLinesContain("foo"));
		CHECK_THAT("xfood", NoLinesContain("bar"));

		CHECK_THAT("xfood", AllLinesContain("foo"));
		CHECK_THAT("xfood", !AllLinesContain("bar"));
	}

	SECTION( "multiline string has multiple lines") {
		CHECK_THAT("xfoo\nbar\nbaz", OneLineContains("foo"));
		CHECK_THAT("xfoo\nbar\nbaz", OneLineContains("bar"));
		CHECK_THAT("xfoo\nbar\nbaz", OneLineContains("baz"));
		CHECK_THAT("xfoo\nbar\nbaz", !OneLineContains("bum"));
		CHECK_THAT("xfoo\nbar\nbaz", !AllLinesContain("foo"));
		CHECK_THAT("xfoo\nfoo\nfoo", AllLinesContain("foo"));
		CHECK_THAT("xfoo\nbar\nbaz", NoLinesContain("bum"));
		CHECK_THAT("xfoo\nbar\nbaz", NoLinesContain("bum"));
		CHECK_THAT("xfoo\nbar\nbaz", !NoLinesContain("foo"));
	}

	SECTION("Case sensitivity") {
		CHECK_THAT("foo", OneLineContains("foo"));
		CHECK_THAT("foo", !OneLineContains("Foo"));
		CHECK_THAT("foo", OneLineContains("foo", Catch::CaseSensitive::Choice::Yes));
		CHECK_THAT("foo", !OneLineContains("Foo", Catch::CaseSensitive::Choice::Yes));
		CHECK_THAT("Foo", !OneLineContains("foo", Catch::CaseSensitive::Choice::Yes));
		CHECK_THAT("foo", OneLineContains("foo", Catch::CaseSensitive::Choice::No));
		CHECK_THAT("foo", OneLineContains("Foo", Catch::CaseSensitive::Choice::No));
		CHECK_THAT("Foo", OneLineContains("foo", Catch::CaseSensitive::Choice::No));
	}
	
}
