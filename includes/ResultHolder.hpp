#pragma once

#include <future>

template<typename ResultType>
class ResultHolder {
    std::future<ResultType> futureResult;
public:
    void setFuture(std::future<ResultType>&& fut);
    ResultType get() { return futureResult.get(); }
};