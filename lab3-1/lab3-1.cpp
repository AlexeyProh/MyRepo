#include <iostream>
#include <string>
#include <vector>

class Article {
private:
    std::string title;
    std::string author;

public:
    Article(std::string title = "", std::string author = "") 
        : title(title), author(author) {}

    std::string getTitle() const { return title; }
    void setTitle(const std::string& t) { title = t; }

    std::string getAuthor() const { return author; }
    void setAuthor(const std::string& a) { author = a; }

    void print() const {
        std::cout << "Article: \"" << title << "\", Author: " << author << std::endl;
    }
};

class LibraryCard {
protected:
    std::string author;
    std::string title;
    std::string authorMark;
    int inventoryNumber;
    std::string themeCode;

public:
    LibraryCard(std::string author = "", std::string title = "", std::string authorMark = "", 
                int invNum = 0, std::string themeCode = "")
        : author(author), title(title), authorMark(authorMark), 
          inventoryNumber(invNum), themeCode(themeCode) {}

    virtual ~LibraryCard() {}

    std::string getAuthor() const { return author; }
    void setAuthor(const std::string& a) { author = a; }

    std::string getTitle() const { return title; }
    void setTitle(const std::string& t) { title = t; }

    std::string getAuthorMark() const { return authorMark; }
    void setAuthorMark(const std::string& am) { authorMark = am; }

    int getInventoryNumber() const { return inventoryNumber; }
    void setInventoryNumber(int num) { inventoryNumber = num; }

    std::string getThemeCode() const { return themeCode; }
    void setThemeCode(const std::string& code) { themeCode = code; }

    std::string getAlphabeticalKey() const {
        return author + " - " + title;
    }

    virtual void printInfo() const {
        std::cout << "[" << inventoryNumber << "] " << author << " \"" << title 
                  << "\" (Author mark: " << authorMark << ", Code: " << themeCode << ")" << std::endl;
    }
};

class StandaloneEditionCard : public LibraryCard {
protected:
    std::string publisher;
    int year;
    int circulation;
    int pages;

public:
    StandaloneEditionCard(std::string author = "", std::string title = "", std::string authorMark = "", 
                          int invNum = 0, std::string themeCode = "",
                          std::string publisher = "", int year = 0, int circulation = 0, int pages = 0)
        : LibraryCard(author, title, authorMark, invNum, themeCode),
          publisher(publisher), year(year), circulation(circulation), pages(pages) {}

    std::string getPublisher() const { return publisher; }
    void setPublisher(const std::string& p) { publisher = p; }

    int getYear() const { return year; }
    void setYear(int y) { year = y; }

    int getCirculation() const { return circulation; }
    void setCirculation(int c) { circulation = c; }

    int getPages() const { return pages; }
    void setPages(int p) { pages = p; }

    void printInfo() const override {
        LibraryCard::printInfo();
        std::cout << "   Publisher: " << publisher << ", Year: " << year 
                  << ", Circulation: " << circulation << ", Pages: " << pages << std::endl;
    }
};

class ArticleCard : public LibraryCard {
private:
    Article article;
    StandaloneEditionCard* edition;

public:
    ArticleCard(Article art = Article(), std::string authorMark = "", int invNum = 0, 
                std::string themeCode = "", StandaloneEditionCard* ed = nullptr)
        : LibraryCard(art.getAuthor(), art.getTitle(), authorMark, invNum, themeCode),
          article(art), edition(ed) {}

    Article getArticle() const { return article; }
    void setArticle(const Article& art) {
        article = art;
        author = art.getAuthor();
        title = art.getTitle();
    }

    StandaloneEditionCard* getEdition() const { return edition; }
    void setEdition(StandaloneEditionCard* ed) { edition = ed; }

    void printInfo() const override {
        std::cout << "Article Card -> ";
        LibraryCard::printInfo();
        if (edition != nullptr) {
            std::cout << "   Published in: \"" << edition->getTitle() 
                      << "\" (" << edition->getPublisher() << ", " << edition->getYear() << ")" << std::endl;
        }
    }
};

class ArticleCollectionCard : public StandaloneEditionCard {
private:
    std::vector<ArticleCard*> articleCards;

public:
    ArticleCollectionCard(std::string author = "", std::string title = "", std::string authorMark = "", 
                          int invNum = 0, std::string themeCode = "",
                          std::string publisher = "", int year = 0, int circulation = 0, int pages = 0)
        : StandaloneEditionCard(author, title, authorMark, invNum, themeCode, publisher, year, circulation, pages) {}

    std::vector<ArticleCard*> getArticleCards() const { return articleCards; }
    void setArticleCards(const std::vector<ArticleCard*>& cards) { articleCards = cards; }

    void addArticleCard(ArticleCard* card) {
        articleCards.push_back(card);
    }

    void printInfo() const override {
        std::cout << "Article Collection -> ";
        StandaloneEditionCard::printInfo();
        std::cout << "   Articles count: " << articleCards.size() << std::endl;
    }
};

class BookCard : public StandaloneEditionCard {
private:
    Article bookArticle;

public:
    BookCard(Article art, std::string authorMark = "", int invNum = 0, std::string themeCode = "",
             std::string publisher = "", int year = 0, int circulation = 0, int pages = 0)
        : StandaloneEditionCard(art.getAuthor(), art.getTitle(), authorMark, invNum, themeCode, 
                                publisher, year, circulation, pages),
          bookArticle(art) {}

    Article getArticle() const { return bookArticle; }
    void setArticle(const Article& art) {
        bookArticle = art;
        author = art.getAuthor();
        title = art.getTitle();
    }

    void printInfo() const override {
        std::cout << "Book -> ";
        StandaloneEditionCard::printInfo();
    }
};

class Catalog {
protected:
    std::vector<LibraryCard*> cards;

public:
    Catalog() {}
    virtual ~Catalog() {}

    void addCard(LibraryCard* card) {
        cards.push_back(card);
    }

    std::vector<LibraryCard*> getCards() const { return cards; }
    void setCards(const std::vector<LibraryCard*>& c) { cards = c; }

    void showAll() const {
        for (size_t i = 0; i < cards.size(); i++) {
            cards[i]->printInfo();
        }
    }
};

class ThematicCatalog : public Catalog {
public:
    std::vector<LibraryCard*> searchByCode(const std::string& code) const {
        std::vector<LibraryCard*> result;
        for (size_t i = 0; i < cards.size(); i++) {
            if (cards[i]->getThemeCode() == code) {
                result.push_back(cards[i]);
            }
        }
        return result;
    }
};

class AlphabeticalCatalog : public Catalog {
public:
    std::vector<LibraryCard*> search(const std::string& query) const {
        std::vector<LibraryCard*> result;
        for (size_t i = 0; i < cards.size(); i++) {
            if (cards[i]->getAlphabeticalKey().find(query) != std::string::npos) {
                result.push_back(cards[i]);
            }
        }
        return result;
    }
};

int main() {
    Article mainBookArt("The C++ Programming Language", "Stroustrup B.");
    BookCard book1(mainBookArt, "S83", 1001, "004.43", "Addison-Wesley", 2013, 3000, 1368);

    ArticleCollectionCard collection("Various Authors", "Computer Science Journal #4", "C38", 
                                     1002, "004.01", "Science Press", 2023, 500, 240);

    Article art1("Graph Sorting Algorithms", "Smith J.");
    Article art2("Database Optimization", "Doe A.");

    ArticleCard artCard1(art1, "S20", 1003, "004.42", &collection);
    ArticleCard artCard2(art2, "D30", 1004, "004.65", &collection);

    collection.addArticleCard(&artCard1);
    collection.addArticleCard(&artCard2);

    ThematicCatalog themeCat;
    AlphabeticalCatalog alphaCat;

    LibraryCard* allCards[] = { &book1, &collection, &artCard1, &artCard2 };
    for (int i = 0; i < 4; i++) {
        themeCat.addCard(allCards[i]);
        alphaCat.addCard(allCards[i]);
    }

    std::cout << "=== ALL CARDS IN CATALOG ===" << std::endl;
    alphaCat.showAll();

    std::cout << "\n=== ALPHABETICAL CATALOG SEARCH (query: 'Smith') ===" << std::endl;
    std::vector<LibraryCard*> foundAlpha = alphaCat.search("Smith");
    for (size_t i = 0; i < foundAlpha.size(); i++) {
        foundAlpha[i]->printInfo();
        std::cout << "   Alphabetical key: " << foundAlpha[i]->getAlphabeticalKey() << std::endl;
    }

    std::cout << "\n=== THEMATIC CATALOG SEARCH (code: '004.43') ===" << std::endl;
    std::vector<LibraryCard*> foundTheme = themeCat.searchByCode("004.43");
    for (size_t i = 0; i < foundTheme.size(); i++) {
        foundTheme[i]->printInfo();
    }

    std::cout << "\n=== ARTICLES INSIDE COLLECTION ===" << std::endl;
    std::vector<ArticleCard*> collArticles = collection.getArticleCards();
    for (size_t i = 0; i < collArticles.size(); i++) {
        collArticles[i]->getArticle().print();
    }

    return 0;
}