class Tensor {
private:
    double* data;
    size_t size;

public:
    Tensor(size_t s = 0) : size(s), data(s ? new double[s] : nullptr) {}

    // Copy constructor
    Tensor(const Tensor& other) : size(other.size) {
        data = size ? new double[size] : nullptr;
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    // Copy assignment
    Tensor& operator=(const Tensor& other) {
        if (this == &other) return *this;

        delete[] data;

        size = other.size;
        data = size ? new double[size] : nullptr;

        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];

        return *this;
    }

    // Move constructor
    Tensor(Tensor&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
    }

    // Move assignment
    Tensor& operator=(Tensor&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;

        size = other.size;
        data = other.data;

        other.size = 0;
        other.data = nullptr;

        return *this;
    }

    // Destructor
    ~Tensor() {
        delete[] data;
    }
};
