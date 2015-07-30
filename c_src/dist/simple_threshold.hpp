#ifndef SIMPLE_THRESHOLD_H
#define SIMPLE_THRESHOLD_H

#include <vector>
#include <armadillo>


arma::uvec outlier_index(const arma::mat& samples){
    auto nsamples = samples.n_cols;
    auto dim = samples.n_rows;

    int neighbor_no_less_than = int(fraction * nsamples);

    arma::mat dist_mat = arma::zeros(nsamples, nsamples);

    {// naive imp. pdist
        for (uint i=0; i<nsamples; ++i){
            arma::vec c = samples.col(i);
            for (uint j=0; j<i; ++j){
                double d = arma::norm(c - samples.col(j), 2);
                dist_mat(i,j) = dist_mat(j,i) = d;
            }
        }
    }

    auto sorted_dist = arma::sort(dist_mat);

    std::vector<uint> outlier;
    outlier.reserve(nsamples);

    for (auto j=0u; j<nsamples; ++j){
        if (sorted_dist(neighbor_no_less_than, j) > r)
            outlier.push_back(j);
    }

    return arma::uvec(outlier);
}


#endif /* SIMPLE_THRESHOLD_H */
