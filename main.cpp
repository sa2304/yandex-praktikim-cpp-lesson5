#include "defines.h"


using namespace std;

int main() {
    const string stop_words_joined = ReadLine();
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Read documents
    map<string, set<int>> word_to_documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        AddDocument(word_to_documents, stop_words, document_id, ReadLine());
    }

    const string query = ReadLine();
    for (auto [relevance, document_id] : FindTopDocuments(word_to_documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s << endl;
    }
}
