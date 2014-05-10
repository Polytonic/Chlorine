// Create a Chlorine Worker
ch::Worker worker("tests/kernels/floats.cl");

SECTION("Worker Successfully Writes and Reads Float Arrays")
{
    // Create Some Test Data
    std::vector<float> spam(5, 0.0f);
    std::vector<float> eggs(5, 1.0f);

    // Swap the Contents of Two Arrays
    worker.execute("swap", spam, eggs);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < spam.size(); i++)
        CHECK(spam[i] == 1.0f);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < eggs.size(); i++)
        CHECK(eggs[i] == 0.0f);
}

SECTION("Worker Successfully Handles Float Primitives")
{
    // Create Some Test Data
    std::vector<float> milk(5, 2.0f);
    float cheese = 3.0f;

    // Add a Float Primitive
    worker.execute("add", milk, cheese);

    // Assert the Data Was Correctly Added
    for (unsigned int i = 0; i < milk.size(); i++)
        CHECK(milk[i] == 5.0f);
}
