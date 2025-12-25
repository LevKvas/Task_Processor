#pragma once

#include "ResultHolder.hpp"


class Task {
public:
    virtual ~Task() = default;
    virtual void execute() = 0;
    virtual std::string getId() const = 0;
};

/**
* Count math problems
*/
class MathTask final: public Task {
public:
    MathTask();
    void execute() override;
    [[nodiscard]] std::string getId() const override;
private:
    ResultHolder<double> resultHolder;
};

/**
* Plot graph
*/
class Visualization final: public Task {
public:
    Visualization();
    void execute() override;
    [[nodiscard]] std::string getId() const override;
};