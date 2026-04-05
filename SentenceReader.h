#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class SentenceReader {
private:
    std::vector<std::string> sentences;

public:
    SentenceReader(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string word, sentence;

            while (ss >> word) {
                sentence += word + " ";
            }

            if (!sentence.empty()) {
                sentence.pop_back();
                sentences.push_back(sentence);
            }
        }

        file.close();
    }

    const std::vector<std::string>& getSentences() const {
        return sentences;
    }

    std::string getRandomSentence() const {
        if (sentences.empty()) return "";

        int index = rand() % sentences.size();
        return sentences[index];
    }

    std::string getSentence(int index) const {
        if (index < 0 || index >= (int)sentences.size()) return "";
        return sentences[index];
    }

    int size() const {
        return (int)sentences.size();
    }
};