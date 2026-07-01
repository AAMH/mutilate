#pragma once
#include <vector>
#include <cmath>
#include <cstdlib>

class ZipfGenerator {
public:
    ZipfGenerator(uint64_t n, double alpha)
        : N(n), alpha(alpha) {
        build_cdf();
    }

    uint64_t next() {
        double z = drand48();
        // binary search
        size_t low = 0, high = cdf.size() - 1;
        while (low < high) {
            size_t mid = (low + high) / 2;
            if (cdf[mid] >= z)
                high = mid;
            else
                low = mid + 1;
        }
        return low;
    }

private:
    uint64_t N;
    double alpha;
    std::vector<double> cdf;

    void build_cdf() {
        cdf.resize(N);

        // compute normalization constant
        double H = 0.0;
        for (uint64_t i = 1; i <= N; ++i)
            H += 1.0 / pow(i, alpha);

        double cumulative = 0.0;
        for (uint64_t i = 1; i <= N; ++i) {
            cumulative += (1.0 / pow(i, alpha)) / H;
            cdf[i - 1] = cumulative;
        }
    }
};