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

	VectorDocumentsWithRelevance vec_found = FindTopDocuments(word_to_documents, stop_words, query);
	VectorDocumentsWithRelevance vec_expected = {
		{ 0, 3 },
		{ 2, 2 },
		{ 1, 2 },
		{ 5, 1 },
		{ 4, 1 }
	};
	EXPECT_EQ(vec_found, vec_expected);
}

TEST_F(TestLesson4, testNoStopWords)
{
	set<string> stop_words = { };

	vector<string> documents = {
		"a fat cat sat on a mat and ate a fat rat"s,
		"little funny fluffy cat"s,
		"the cat"s,
		"huge green crocodile"s
	};

	map<string, set<int>> word_to_documents;
	for (int i = 0; i < documents.size(); ++i) {
		const string & doc = documents.at(i);
		AddDocument(word_to_documents, stop_words, i, doc);
	}

	const string query = "funny fat cat"s;

	vector<int> vec_found = FindDocuments(word_to_documents, stop_words, query);
	set<int> set_found(vec_found.begin(), vec_found.end());
	set<int> set_expected = { 0, 1, 2 };
	EXPECT_EQ(set_found, set_expected);  
}

TEST_F(TestLesson4, testNoRelevantDocuments)
{
	set<string> stop_words = {
		"a"s, "the"s, "on"s, "cat"s
	};

	vector<string> documents = {
		"a fat cat sat on a mat and ate a fat rat"s,
		"little funny fluffy cat"s,
		"the cat"s,
		"huge green crocodile"s
	};

	map<string, set<int>> word_to_documents;
	for (int i = 0; i < documents.size(); ++i) {
		const string & doc = documents.at(i);
		AddDocument(word_to_documents, stop_words, i, doc);
	}

	const string query = "no words found"s;

	vector<int> vec_found = FindDocuments(word_to_documents, stop_words, query);
	set<int> set_found(vec_found.begin(), vec_found.end());
	set<int> set_expected = { };
	EXPECT_EQ(set_found, set_expected);
}

TEST_F(TestLesson4, testNoDuplicatesInResultVector) {
	set<string> stop_words = {
		"a"s, "the"s, "on"s, "cat"s
	};

	vector<string> documents = {
		"a fat cat sat on a mat and ate a fat rat"s,
		"little funny fluffy cat"s,
		"the cat"s,
		"huge green crocodile"s
	};

	map<string, set<int>> word_to_documents;
	for (int i = 0; i < documents.size(); ++i) {
		const string & doc = documents.at(i);
		AddDocument(word_to_documents, stop_words, i, doc);
	}

	const string query = "funny fat cat ate rat"s;

	vector<int> vec_found = FindDocuments(word_to_documents, stop_words, query);
	for (int id : vec_found) {
		clog << id << endl;
	}
	set<int> set_found(vec_found.begin(), vec_found.end());
	//	set<int> set_expected = { };
	EXPECT_EQ(vec_found.size(), set_found.size());
}
