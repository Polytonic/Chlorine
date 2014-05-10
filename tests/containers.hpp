// Create a Chlorine Worker
ch::Worker worker("tests/kernels/containers.cl");

SECTION("Worker is Compatible With C-Style Arrays")
{
    // Create Some Test Data
    float spam[5] = { 3.141f, 2.718f, 1.414f, 1.618f, 0.577f };
    float eggs[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    // Swap the Contents of Two Arrays
    worker.execute("swap", spam, eggs);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < 5; i++)
        CHECK(spam[i] == 0);

    // Assert the Data was Correctly Swapped
    CHECK(eggs[0] == 3.141f);
    CHECK(eggs[1] == 2.718f);
    CHECK(eggs[2] == 1.414f);
    CHECK(eggs[3] == 1.618f);
    CHECK(eggs[4] == 0.577f);
}

SECTION("Worker is Compatible With STL Arrays")
{
    // Create Some Test Data
    std::array<float, 5> spam = {{ 3.141f, 2.718f, 1.414f, 1.618f, 0.577f }};
    std::array<float, 5> eggs = {{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }};

    // Swap the Contents of Two Arrays
    worker.execute("swap", spam, eggs);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < spam.size(); i++)
        CHECK(spam[i] == 0);

    // Assert the Data was Correctly Swapped
    CHECK(eggs[0] == 3.141f);
    CHECK(eggs[1] == 2.718f);
    CHECK(eggs[2] == 1.414f);
    CHECK(eggs[3] == 1.618f);
    CHECK(eggs[4] == 0.577f);
}

SECTION("Worker is Compatible With STL Valarrays")
{
    // Create Some Test Data
    std::valarray<float> spam(0.0f, 5);
    std::valarray<float> eggs(1.0f, 5);

    // Swap the Contents of Two Arrays
    worker.execute("swap", spam, eggs);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < spam.size(); i++)
        CHECK(spam[i] == 1.0f);

    // Assert the Data was Correctly Swapped
    for (unsigned int i = 0; i < eggs.size(); i++)
        CHECK(eggs[i] == 0.0f);
}

SECTION("Worker is Compatible With STL Vectors")
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
