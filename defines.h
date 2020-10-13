#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

static const int MAX_RESULT_DOCUMENT_COUNT = 5;

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            words.push_back(word);
            word = "";
        } else {
            word += c;
        }
    }
    words.push_back(word);

    return words;
}

set<string> ParseStopWords(const string& text) {
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {
    vector<string> words;
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}

void AddDocument(map<string, set<int>>& word_to_documents,
                 const set<string>& stop_words,
                 int document_id,
                 const string& document) {
    for (const string& word : SplitIntoWordsNoStop(document, stop_words)) {
        word_to_documents[word].insert(document_id);
    }
}

bool LessRelevant( const pair<int, int> left, pair<int, int> right ) {
	const auto [left_id, left_relevance] = left;
	const auto [right_id, right_relevance] = right;
	return (left_relevance < right_relevance);
}


typedef int Relevance;
typedef int DocumentId;
typedef vector< pair<DocumentId, Relevance> VectorDocumentsWithRelevance;
// For each document returns its id and relevance
VectorDocumentsWithRelevance FindAllDocuments(
        const map<string, set<int>>& word_to_documents,
        const set<string>& stop_words,
        const string& query) {
    const vector<string> query_words = SplitIntoWordsNoStop(query, stop_words);
    map<int, int> document_to_relevance;
    for (const string& word : query_words) {
        if (word_to_documents.count(word) == 0) {
            continue;
        }
        for (const int document_id : word_to_documents.at(word)) {
            ++document_to_relevance[document_id];
        }
    }

    VectorDocumentsWithRelevance found_documents;
    for (auto [document_id, relevance] : document_to_relevance) {
        found_documents.push_back({document_id, relevance});
    }
	sort(found_documents.begin(), found_documents.end(), LessRelevant);
	reverse(found_documents.begin(), found_documents.end());
	
    return found_documents;
}

vector<pair<int, int>> FindTopDocuments(
        const map<string, set<int>>& word_to_documents,
        const set<string>& stop_words,
        const string& query) {
		vector<pair<int, int>> all_relevant_documents = FindAllDocuments(word_to_documents, stop_words, query);
		
		return vector(all_relevant_documents.begin(), all_relevant_documents.begin() + MAX_RESULT_DOCUMENT_COUNT);
}