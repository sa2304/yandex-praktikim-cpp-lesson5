#include <gtest/gtest.h>
#include <iostream>

#include "defines.h"

class TestLesson5 : public ::testing::Test {
private:

protected:
	void SetUp() 
	{ }
};

TEST_F(TestLesson5, testLessonExample) 
{
	set<string> stop_words = {
		"a"s, "the"s, "on"s, "cat"s
	};

	vector<string> documents = {
		"a fat cat sat on a mat and ate a fat rat"s,
		"fat rat"s,
		"a fat cat rat"s,
		"a fat cat sat"s,
		"a fat cat"s,
		"a fat dog"
	};

	map<string, set<int>> word_to_documents;
	for (int i = 0; i < documents.size(); ++i) {
		const string & doc = documents.at(i);
		AddDocument(word_to_documents, stop_words, i, doc);
	}

	const string query = "funny fat cat on a mat with rat"s;

	vector< pair<Relevance, DocumentId> > vec_found = FindTopDocuments(word_to_documents, stop_words, query);
	vector< pair<Relevance, DocumentId> > vec_expected = {
	   { 3, 0 },
	   { 2, 2 },
	   { 2, 1 },
	   { 1, 5 },
	   { 1, 4 }
	};
	EXPECT_EQ(vec_found, vec_expected);
}

