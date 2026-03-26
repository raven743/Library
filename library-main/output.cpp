#include <iostream>
#include "library.h"

int main()
{
    int choice;
    library lib;
    do
    {
        std::cout << "\n --- Menu ---\n";
        std::cout << "1. Add a book;\n";
        std::cout << "2. Show all books;\n";
        std::cout << "3. Delete by index;\n";
        std::cout << "4. Save to file;\n";
        std::cout << "5. Load file;\n";
        std::cout << "0. Exit.\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
                lib.AddFromConsole();
                break;
            case 2:
                lib.PrintAll();
                break;
            case 3:
            {
                lib.PrintAll();
                int idx;
                std::cout << "Enter the index to delete: ";
                if (!(std::cin >> idx))
                    throw std::runtime_error("Input error: Integer expected.");
                lib.DeleteIndex(idx);
                break;
            }
            case 4:
            {
                char filename[255];
                std::cout << "Enter a file name to save: ";
                std::cin >> filename;
                lib.SaveToFile(filename);
                break;
            }

            case 5:
            {
                char filename[255];
                std::cout << "Enter the file name to load: ";
                std::cin >> filename;
                lib.LoadFromFile(filename);
                break;
            }
            case 0:
                std::cout << "Exit." << std::endl;
                break;

            default:
                std::cout << "Wrong choice." << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    } while (choice != 0);
}