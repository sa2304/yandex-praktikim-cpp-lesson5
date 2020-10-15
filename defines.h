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

/** Индексирует новый документ в поисковой системе 
 * 
 * Индекс поисковой системы запоминает, в каких документах встречается 
 * каждое известное ему слово (word -> document_id). */
void AddDocument(map<string, set<int>>& word_to_documents,
                 const set<string>& stop_words,
                 int document_id,
                 const string& document) {
    for (const string& word : SplitIntoWordsNoStop(document, stop_words)) {
        word_to_documents[word].insert(document_id);
    }
}

typedef int Relevance;
typedef int DocumentId;

bool LessRelevant( const pair<Relevance, DocumentId> left, pair<Relevance, DocumentId> right ) {
  const auto [left_relevance, left_id] = left;
  const auto [right_relevance, right_id] = right;
	return (left_relevance < right_relevance);
}

/** Возвращает документы, релевантные поисковому запросу
 * 
 * @param word_to_documents Поисковый индекс
 * @param stop_words Множество стоп-слов
 * @param query Текст запроса
 * 
 * @returns Пары <document_id, relevance>
 * Документ считается релевантным запросу, если в нем встречается 
 * любое из слов запроса. Величина релевантности выражается целым числом - 
 * количеством различных слов запроса, которые есть в документе.
 * 
 * Например, по запросу 
 *     funny fat cat
 * у документа 
 *     fat cat ate a fat rat on a mat
 * релевантность = 2, т.к. слова "fat" и "cat" в нем есть. 
 * Повторения слов в документе (например, "fat") не имеют значения. */
vector< pair<Relevance, DocumentId> > FindAllDocuments(
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

    vector< pair<Relevance, DocumentId> > found_documents;
    for (auto [document_id, relevance] : document_to_relevance) {
      found_documents.push_back({relevance, document_id});
    }
	sort(found_documents.begin(), found_documents.end(), LessRelevant);
	reverse(found_documents.begin(), found_documents.end());
	
    return found_documents;
}

/** Возвращает MAX_RESULT_DOCUMENT_COUNT наиболее релевантных запросу документов */
vector< pair<Relevance, DocumentId> > FindTopDocuments(
        const map<string, set<int>>& word_to_documents,
        const set<string>& stop_words,
        const string& query) {
		vector< pair<Relevance, DocumentId> > all_relevant_documents = FindAllDocuments(word_to_documents, stop_words, query);
		
		return vector(all_relevant_documents.begin(), all_relevant_documents.begin() + MAX_RESULT_DOCUMENT_COUNT);
}
