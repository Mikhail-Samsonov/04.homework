#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include <unordered_set>
#include <memory>
#include <cassert>
#include "document.h"

/**
 * @brief Class-controller for document
 */
class Application {
public:
    /**
     * @brief Creates a new document
     * @return unique pointer to the newly created document
     */
    const std::unique_ptr<Document> &createDocument() {
        auto[it, inserted] = m_documents.emplace(std::make_unique<Document>());
        assert(inserted);
        return *it;
    }

    /**
     * @brief Imports document from a file
     * @return unique pointer to the imported document
     */
    const std::unique_ptr<Document> &importDocument() {
        auto[it, inserted] = m_documents.emplace(std::make_unique<Document>());
        assert(inserted);
        return *it;
    }

    /**
     * @brief Exports document to a file
     * @param document const unique pointer to the document
     * @return bool expression whether export completed successfully
     */
    bool exportDocument(const std::unique_ptr<Document> &document) {
        std::size_t removed = m_documents.erase(document);
        if (removed == 0)
            return false;
        return true;
    }

private:
    std::unordered_set<std::unique_ptr<Document> > m_documents;
};

#endif //EDITOR_APPLICATION_H

