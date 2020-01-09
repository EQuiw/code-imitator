
/**
 * Randomly sorts the vector w.r.t to given seed (call by reference).
 * @tparam T the inner type of vector
 * @param vec  the vector
 * @param seed the seed
 */
template <typename T>
void randomlySortVector(std::vector<T> &vec, int &seed) {
    // randomly sort the array
    std::srand ( unsigned ( seed ) );
    std::random_shuffle ( vec.begin(), vec.end() );
}