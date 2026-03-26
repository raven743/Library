#pragma once
#include "book.h"
#include <vector>
#include <fstream>
#include <stdexcept>

class library
{
private:
	std::vector<Book*> books;
public:
    ~library()
    {
        for (auto& book : books)
            delete book;
    }


    void AddFromConsole()
    {
        Book* book = new Book();

        try
        {
            book->SetFromConsole();
            books.push_back(book);
        }
        catch (const std::exception& e)
        {
            delete book; 
            std::cout << "Error adding book: " << e.what() << std::endl;

            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    void PrintAll() const
    {
        if (books.empty())
        {
            std::cout << "The library is empty." << std::endl;
            return;
        }

        std::cout << "\n--- List of books  ---\n";
        std::cout << "Author\t\tTitle\t\tYear\n";
        std::cout << "------------------------\n";

        for (const auto& book : books)
            book->Print();
    }

    void DeleteIndex(int index) 
    {
        if (index < 0)
        {
            std::cout << "The book number was entered incorrectly.\n";
            return;
        }

        delete books[index];
        books.erase(books.begin() + index);
        std::cout << "Book deleted!\n";
    }

    void SaveToFile(const char* filename) const
    {
        try
        {
            std::ofstream file(filename);

            if (!file.is_open())
                throw std::runtime_error(std::string("Failed to open file for writing: ") + filename);

            for (const auto& book : books)
            {
                file << book->GetAuthor() << "\n"
                    << book->GetTitle() << "\n"
                    << book->GetYear() << "\n";
            }

            file.close();
            std::cout << "The library is saved to a file.: " << filename << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Save error: " << e.what() << std::endl;
        }
    }

    void LoadFromFile(const char* filename)
    {
        try
        {
            std::ifstream file(filename);

            if (!file.is_open())
                throw std::runtime_error(std::string("Failed to open file for reading: ") + filename);

            for (auto& book : books)
                delete book;
            books.clear();

            char author[255], title[255];
            int year;

            while (file.getline(author, 255))
            {
                if (!file.getline(title, 255))
                    throw std::runtime_error("The file is corrupted: the book title is missing..");

                if (!(file >> year))
                    throw std::runtime_error("The file is damaged: the publication year is missing.");

                file.ignore(); 

                Book* book = new Book(author, title, year);
                books.push_back(book);
            }

            file.close();
            std::cout << "Books loaded: " << books.size() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Loading error: " << e.what() << std::endl;

            for (auto& book : books)
                delete book;
            books.clear();
        }
    }

};