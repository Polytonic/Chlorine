// Create a Chlorine Worker
ch::Worker worker("tests/kernels/integers.cl");

SECTION("Worker Successfully Writes and Reads Integer Arrays")
{
    // Create Some Test Data
    std::vector<int> spam(5, 0);
    std::vector<int> eggs(5, 1);

    // Swap the Contents of Two Arrays
    worker.call("swap", spam, eggs);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < spam.size(); i++)
        CHECK(spam[i] == 1);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < eggs.size(); i++)
        CHECK(eggs[i] == 0);
}

SECTION("Worker Successfully Handles Integer Primitives")
{
    // Create Some Test Data
    std::vector<int> milk(5, 2);
    unsigned int cheese = 3;

    // Add an Integer Primitive
    worker.call("add", milk, cheese);

    // Assert the Data Was Correctly Added
    for (unsigned int i = 0; i < milk.size(); i++)
        CHECK(milk[i] == 5);
}
