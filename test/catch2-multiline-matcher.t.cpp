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

TEST_CASE("xxx") {
	SECTION( "OneLineMatches") {
		CHECK_THAT("foo\nbar", !OneLineMatches("foo"));
	}

}
