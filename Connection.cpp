#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
using namespace std;
int main(int, char **)
{
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb+srv://admin2:1EiG7CUoKjvMn6p9@cluster0.hayoush.mongodb.net/test"}};

    bsoncxx::builder::stream::document document{};
    auto collection = conn["MOVIE_APP"]["Movies"];

    document << "hello"
             << "world";
    // collection.insert_one(document.view());

    auto cursor = collection.find({});

    for (auto &&doc : cursor)
    {
        std::cout << bsoncxx::to_json(doc) << std::endl;
        // std::cout << "SUCCESS!" << std::endl;
    }

    return 0;
}
// Print the contents of the given collection.
void printCollection(mongocxx::collection &collection)
{
    // Check if collection is empty.
    if (collection.count_documents({}) == 0)
    {
        cout << "Collection is empty." << endl;
        return;
    }
    auto cursor = collection.find({});
    for (auto &&doc : cursor)
    {
        cout << bsoncxx::to_json(doc) << endl;
    }
}
// Find the document with given key-value pair.
void findDocument(mongocxx::collection &collection, const string &key, const string &value)
{
    // Create the query filter
    auto filter = bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize;
    // Add query filter argument in find
    auto cursor = collection.find({filter});
    for (auto &&doc : cursor)
    {
        cout << bsoncxx::to_json(doc) << endl;
    }
}